#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include <cstdlib>
#include <sstream>
#include <string>

//File ui_mainwindow.h will be generated on compile time. Don't look for it, unless you have already compiled the project.
#include "ComplexNetsGui/inc/ui_mainwindow.h"
#include "ComplexNetsGui/inc/mainwindow.h"
#include "../../ComplexNets/GraphFactory.h"
#include "ComplexNetsGui/inc/GraphLoadingValidationDialog.h"
#include "../../ComplexNets/GraphFactory.h"
#include "../../ComplexNets/WeightedGraphFactory.h"
#include "../../ComplexNets/IGraphReader.h"
#include "../../ComplexNets/IBetweenness.h"
#include "../../ComplexNets/IShellIndex.h"
#include "../../ComplexNets/DegreeDistribution.h"

using namespace ComplexNetsGui;
using namespace graphpp;
using namespace std;

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    weightedFactory = NULL;
    factory = NULL;
    this->onNetworkUnload();
    ui->textBrowser->setOpenExternalLinks(true);
    ui->textBrowser->append("Welcome to ComplexNets++!!\nIf you are a developer feel free to visit our Google Code site:");
    ui->textBrowser->append("<a href='http://code.google.com/p/complexnets/'>ComplexNets++ - Google Code</a>");
    ui->textBrowser->append("\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent* e)
{
    QMainWindow::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setDirectory(QDir::homePath());
    QStringList selectedFiles;
    GraphLoadingValidationDialog graphValidationDialog(this);

    if (!this->graphLoaded)
    {
        graph = Graph();
        weightedGraph = WeightedGraph();
        //If no network is loaded user may procede to load a new network.
        ui->textBrowser->append("Loading new network...");
        if (graphValidationDialog.exec())
        {
            if (fileDialog.exec())
            {
                selectedFiles = fileDialog.selectedFiles();
                this->onNetworkLoad(graphValidationDialog.isWeigthed(), graphValidationDialog.isDirected(), graphValidationDialog.isMultigraph());
                buildGraphFactory(graphValidationDialog.isWeigthed());
                try
                {
                    readGraph(selectedFiles[0].toStdString());
                }
                catch (const FileNotFoundException& ex)
                {
                    ui->textBrowser->append("Error while loading graph.");
                    ui->textBrowser->append(ex.what());
                    onNetworkUnload();
                    return;
                }
                catch (const MalformedLineException& ex)
                {
                    ui->textBrowser->append("Error while loading graph.");
                    ui->textBrowser->append(ex.what());
                    onNetworkUnload();
                    return;

                }
                catch (const UnsignedIntegerMalformedException& ex)
                {
                    ui->textBrowser->append("Error while loading graph.");
                    ui->textBrowser->append(ex.what());
                    onNetworkUnload();
                    return;

                }
                catch (const MalformedDoubleException& ex)
                {
                    ui->textBrowser->append("Error while loading graph.");
                    onNetworkUnload();
                    ui->textBrowser->append(ex.what());
                    return;

                }
                QString text("Network loaded from file: ");
                text.append(selectedFiles[0]);
                text.append("\nAmount of vertices in the graph: ");
                unsigned int verticesCount = this->weightedgraph ? weightedGraph.verticesCount() : graph.verticesCount();
                text.append(QString("%1").arg(verticesCount));
                text.append(".\n");
                ui->textBrowser->append(text);
            }
            else
                ui->textBrowser->append("Action canceled by user.\n");
        }
        else
            ui->textBrowser->append("Action canceled by user.\n");
    }
    else
    {
        ui->textBrowser->append("Action canceled: Only one network can be loaded at any given time.\n");
    }
}

void MainWindow::on_actionQuit_triggered()
{
    QMessageBox msg(QMessageBox::Question, "Quit", "Are you sure you want to quit?", QMessageBox::Ok | QMessageBox::Cancel, this);
    ui->textBrowser->append("About to quit ComplexNets++...");
    if (msg.exec() == QMessageBox::Ok)
    {
        ui->textBrowser->append("Bye bye.\n");
        this->deleteGraphFactory();
        exit(EXIT_SUCCESS);
    }
    else
        ui->textBrowser->append("Action canceled by user.\n");
}

void MainWindow::on_actionClose_current_network_triggered()
{
    ui->textBrowser->append("About to close the current network...");
    QMessageBox msg(QMessageBox::Question, "Close current network", "Are you sure you want to close the current network?", QMessageBox::Ok | QMessageBox::Cancel, this);
    if (msg.exec() == QMessageBox::Ok)
    {
        graph = Graph();
        weightedGraph = WeightedGraph();
        this->deleteGraphFactory();
        this->onNetworkUnload();
        ui->textBrowser->append("Done.\n");
    }
    else
        ui->textBrowser->append("Action canceled by user.\n");
}

void MainWindow::onNetworkLoad(const bool weightedgraph, const bool digraph, const bool multigraph)
{
    this->graphLoaded = true;
    this->weightedgraph = weightedgraph;
    this->digraph = digraph;
    this->multigraph = multigraph;
}

void MainWindow::onNetworkUnload()
{
    this->graphLoaded = false;
    this->weightedgraph = false;
    this->digraph = false;
    this->multigraph = false;
}

/*void MainWindow::on_actionDegree_distribution_triggered()
{
    int systemRet = 0;
    ui->textBrowser->append("Ploting degree distribution...");
    systemRet = system("gnuplot -persist ./command.tmp");
    if (systemRet == 0)
        ui->textBrowser->append("Done.\n");
}*/




void MainWindow::buildGraphFactory(const bool isWeighted)
{
    if (isWeighted)
        weightedFactory = new WeightedGraphFactory<WeightedGraph, WeightedVertex>();
    else
        factory = new GraphFactory<Graph, Vertex>();
}

void MainWindow::deleteGraphFactory()
{
    if (weightedFactory != NULL)
    {
        delete weightedFactory;
        weightedFactory = NULL;
    }
    else if (factory != NULL)
    {
        delete factory;
        factory = NULL;
    }
}

void MainWindow::readGraph(const std::string path)
{
    if (this->weightedgraph)
    {
        IGraphReader<WeightedGraph, WeightedVertex>* reader = weightedFactory->createGraphReader();
        reader->read(weightedGraph, path);
        delete reader;
    }
    else
    {
        IGraphReader<Graph, Vertex>* reader = factory->createGraphReader();
        reader->read(graph, path);
        delete reader;
    }
}

//TODO this function doesnt validate input. should be const
QString MainWindow::inputId(const std::string label)
{
    QString ret;
    QInputDialog inputVertexIdDialog(this);
    inputVertexIdDialog.setInputMode(QInputDialog::TextInput);
    inputVertexIdDialog.setLabelText(label.c_str());
    if (inputVertexIdDialog.exec())
        ret.append(inputVertexIdDialog.textValue());
    return ret;
}

void MainWindow::on_actionBetweenness_triggered()
{
    QString vertexId = inputId("Vertex id:");
    QString ret;
    double vertexBetweenness;
    if (!vertexId.isEmpty())
    {
        if (!propertyMap.containsPropertySet("betweenness"))
        {
            ui->textBrowser->append("Betweenness has not been previously computed. Computing now.");
            if (this->weightedgraph)
            {
                ui->textBrowser->append("Betweenness for weighted graphs is not supported.");
            }
            else
            {
                IBetweenness<Graph, Vertex>* betweenness = factory->createBetweenness(graph);
                IBetweenness<Graph, Vertex>::BetweennessIterator it = betweenness->iterator();
                while (!it.end())
                {
                    propertyMap.addProperty<double>("betweenness", to_string<unsigned int>(it->first), it->second);
                    ++it;
                }
                delete betweenness;
            }
        }
        try
        {
            vertexBetweenness = propertyMap.getProperty<double>("betweenness", vertexId.toStdString());
            ret.append("Betweenness for vertex ").append(vertexId);
            ret.append(" is: ").append(to_string<double>(vertexBetweenness).c_str()).append(".\n");
            ui->textBrowser->append(ret);
        }
        catch (const BadElementName& ex)
        {
            ret.append("Betweenness: Vertex with id ").append(vertexId).append(" was not found.");
            ui->textBrowser->append(ret);
        }
    }
}

void MainWindow::on_actionShell_index_triggered()
{
    QString vertexId = inputId("Vertex id:");
    QString ret;
    unsigned int vertexShellIndex;
    if (!vertexId.isEmpty())
    {
        if (!propertyMap.containsPropertySet("shellIndex"))
        {
            ui->textBrowser->append("Shell index has not been previously computed. Computing now.");
            if (this->weightedgraph)
            {
                ui->textBrowser->append("Shell index for weighted graphs is not supported.");
            }
            else
            {
                IShellIndex<Graph, Vertex>* shellIndex = factory->createShellIndex(graph);
                IShellIndex<Graph, Vertex>::ShellIndexIterator it = shellIndex->iterator();
                while (!it.end())
                {
                    propertyMap.addProperty<unsigned int>("shellIndex", to_string<unsigned int>(it->first), it->second);
                    ++it;
                }
                delete shellIndex;
            }
        }
        try
        {
            vertexShellIndex = propertyMap.getProperty<unsigned int>("shellIndex", vertexId.toStdString());
            ret.append("Shell index for vertex ").append(vertexId);
            ret.append(" is: ").append(to_string<unsigned int>(vertexShellIndex).c_str()).append(".\n");
            ui->textBrowser->append(ret);
        }
        catch (const BadElementName& ex)
        {
            ret.append("Shell index: Vertex with id ").append(vertexId).append(" was not found.");
            ui->textBrowser->append(ret);
        }
    }
}

void MainWindow::on_actionDegree_distribution_triggered()
{
    QString degree = inputId("Degree:");
    QString ret;
    unsigned int degreeAmount;
    if (!degree.isEmpty())
    {
        if (!propertyMap.containsPropertySet("degreeDistribution"))
        {
            ui->textBrowser->append("Digree distribution has not been previously computed. Computing now.");
            if (this->weightedgraph)
            {
                //ui->textBrowser->append("Digree distribution for weighted graphs is not supported.");
                DegreeDistribution<WeightedGraph, WeightedVertex>* degreeDistribution = weightedFactory->createDegreeDistribution(weightedGraph);
                DegreeDistribution<WeightedGraph, WeightedVertex>::DistributionIterator it = degreeDistribution->iterator();
                while (!it.end())
                {
                    propertyMap.addProperty<unsigned int>("degreeDistribution", to_string<unsigned int>(it->first), it->second);
                    ++it;
                }
                delete degreeDistribution;
            }
            else
            {
                DegreeDistribution<Graph, Vertex>* degreeDistribution = factory->createDegreeDistribution(graph);
                DegreeDistribution<Graph, Vertex>::DistributionIterator it = degreeDistribution->iterator();
                while (!it.end())
                {
                    propertyMap.addProperty<unsigned int>("degreeDistribution", to_string<unsigned int>(it->first), it->second);
                    ++it;
                }
                delete degreeDistribution;
            }
        }
        try
        {
            degreeAmount = propertyMap.getProperty<unsigned int>("degreeDistribution", degree.toStdString());
            ret.append("Digree distribution for degree ").append(degree);
            ret.append(" is: ").append(to_string<unsigned int>(degreeAmount).c_str()).append(".\n");
            ui->textBrowser->append(ret);
        }
        catch (const BadElementName& ex)
        {
            ret.append("There are no vertices with degree ").append(degree).append(".\n");
            ui->textBrowser->append(ret);
        }
    }
}




void MainWindow::on_actionDegree_distribution_plotting_triggered()
{
    int ret = 0 ;
    ui->textBrowser->append("Plotting degree distribution...");
    ret = grapher.plotPropertySet(propertyMap.getPropertySet("degreeDistribution"), "g", "c_nn(g)", "Degree distribution");
    if (ret == 0)
        ui->textBrowser->append("Done\n");
    else
        ui->textBrowser->append("Action canceled: an error while plotting ocurred.\n");
}
