#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include <cstdlib>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

//File ui_mainwindow.h will be generated on compile time. Don't look for it, unless you have already compiled the project.
#include "ComplexNetsGui/inc/ui_mainwindow.h"
#include "ComplexNetsGui/inc/mainwindow.h"
#include "../../ComplexNets/GraphFactory.h"
#include "ComplexNetsGui/inc/GraphLoadingValidationDialog.h"
#include "ComplexNetsGui/inc/GnuplotConsole.h"
#include "../../ComplexNets/GraphFactory.h"
#include "../../ComplexNets/WeightedGraphFactory.h"
#include "../../ComplexNets/IGraphReader.h"
#include "../../ComplexNets/IBetweenness.h"
#include "../../ComplexNets/IShellIndex.h"
#include "../../ComplexNets/DegreeDistribution.h"
#include "../../ComplexNets/GraphGenerator.h"

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
    this->console = new GnuplotConsole();
    ui->textBrowser->setOpenExternalLinks(true);
    ui->textBrowser->append("Welcome to ComplexNets++!!\nIf you are a developer feel free to visit our Google Code site:");
    ui->textBrowser->append("<a href='http://code.google.com/p/complexnets/'>ComplexNets++ - Google Code</a>");
    ui->textBrowser->append("\n");
}

MainWindow::~MainWindow()
{
    delete console;
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
        //If no network is loaded user may procede to load a new network.
        ui->textBrowser->append("Loading new network...");
        if (graphValidationDialog.exec())
        {
            if (fileDialog.exec())
            {
                bool isDirected = graphValidationDialog.isDirected();
                bool isMultigraph = graphValidationDialog.isMultigraph();
                selectedFiles = fileDialog.selectedFiles();
                this->onNetworkLoad(graphValidationDialog.isWeigthed(), graphValidationDialog.isDirected(), graphValidationDialog.isMultigraph());
                buildGraphFactory(graphValidationDialog.isWeigthed());
                try
                {
                    string path = selectedFiles[0].toStdString();

                    if (this->weightedgraph) {
                        graph = Graph(isDirected, isMultigraph);
                        weightedGraph = GraphGenerator::getInstance()->generateWeightedGraphFromFile(path, isDirected, isMultigraph);
                    } else {
                        graph = GraphGenerator::getInstance()->generateGraphFromFile(path, isDirected, isMultigraph);
                        weightedGraph = WeightedGraph(isDirected, isMultigraph);
                    }
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
                catch (const DuplicatedEdgeLoading& ex)
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
        propertyMap.clear();
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
    ui->actionClose_current_network->setEnabled(true);
    ui->actionBetweenness->setEnabled(true);
    ui->actionClustering_coefficient->setEnabled(true);
    ui->actionDegree_distribution->setEnabled(true);
    ui->actionDegree_distribution_plotting->setEnabled(true);
    ui->actionClose_current_network->setEnabled(true);
    ui->actionNearest_neighbors_degree->setEnabled(true);
    ui->actionShell_index->setEnabled(true);
    ui->actionBetweenness_vs_Degree->setEnabled(true);
    ui->actionClustering_Coefficient_vs_Degree->setEnabled(true);
    ui->actionNearest_Neighbors_Degree_vs_Degree->setEnabled(true);
    ui->actionShell_Index_vs_Degree->setEnabled(true);
}

void MainWindow::onNetworkUnload()
{
    this->graphLoaded = false;
    this->weightedgraph = false;
    this->digraph = false;
    this->multigraph = false;
    ui->actionClose_current_network->setEnabled(false);
    ui->actionBetweenness->setEnabled(false);
    ui->actionClustering_coefficient->setEnabled(false);
    ui->actionDegree_distribution->setEnabled(false);
    ui->actionDegree_distribution_plotting->setEnabled(false);
    ui->actionClose_current_network->setEnabled(false);
    ui->actionNearest_neighbors_degree->setEnabled(false);
    ui->actionShell_index->setEnabled(false);
    ui->actionBetweenness_vs_Degree->setEnabled(false);
    ui->actionClustering_Coefficient_vs_Degree->setEnabled(false);
    ui->actionNearest_Neighbors_Degree_vs_Degree->setEnabled(false);
    ui->actionShell_Index_vs_Degree->setEnabled(false);
}



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
    if (this->weightedgraph)
    {
        ui->textBrowser->append("Betweenness for weighted graphs is not supported.");
        return;
    }
    QString vertexId = inputId("Vertex id:");
    QString ret;
    double vertexBetweenness;
    if (!vertexId.isEmpty())
    {
        this->computeBetweenness();
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
    if (this->weightedgraph)
    {
        ui->textBrowser->append("Shell index for weighted graphs is not supported.");
        return;
    }
    QString vertexId = inputId("Vertex id:");
    QString ret;
    unsigned int vertexShellIndex;
    if (!vertexId.isEmpty())
    {
        this->computeShellIndex();
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

void MainWindow::computeShellIndex()
{
    if (!propertyMap.containsPropertySet("shellIndex"))
    {
        ui->textBrowser->append("Shell index has not been previously computed. Computing now.");
        if (this->weightedgraph)
        {
            ui->textBrowser->append("Shell index for weighted graphs is not supported.");
            return;
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
}
void MainWindow::computeBetweenness()
{
    if (!propertyMap.containsPropertySet("betweenness"))
    {
        ui->textBrowser->append("Betweenness has not been previously computed. Computing now.");
        if (this->weightedgraph)
        {
            ui->textBrowser->append("Betweenness for weighted graphs is not supported.");
            return;
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
}

void MainWindow::computeDegreeDistribution()
{
    if (!propertyMap.containsPropertySet("degreeDistribution"))
    {
        if (this->weightedgraph)
        {
            DegreeDistribution<WeightedGraph, WeightedVertex>* degreeDistribution = weightedFactory->createDegreeDistribution(weightedGraph);
            DegreeDistribution<WeightedGraph, WeightedVertex>::DistributionIterator it = degreeDistribution->iterator();
            while (!it.end())
            {
                propertyMap.addProperty<double>("degreeDistribution", to_string<unsigned int>(it->first), it->second);
                propertyMap.addProperty<double>("degreeDistributionProbability", to_string<unsigned int>(it->first), it->second / (double)weightedGraph.verticesCount());
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
                propertyMap.addProperty<double>("degreeDistribution", to_string<unsigned int>(it->first), it->second);
                propertyMap.addProperty<double>("degreeDistributionProbability", to_string<unsigned int>(it->first), it->second / (double)graph.verticesCount());
                ++it;
            }
            delete degreeDistribution;
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
            this->computeDegreeDistribution();
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
    bool ret, logBin = false;
    ui->textBrowser->append("Plotting degree distribution...");
    if (!propertyMap.containsPropertySet("degreeDistribution"))
    {
        ui->textBrowser->append("Digree distribution has not been previously computed. Computing now.");
        this->computeDegreeDistribution();
    }
    if (LogBinningDialog() == QMessageBox::Yes)
        logBin = true;
    ret = this->console->plotPropertySet(propertyMap.getPropertySet("degreeDistribution"), "degreeDistribution", logBin);
    this->console->show();
    this->activateWindow();
    if (!ret)
        ui->textBrowser->append("An unexpected error has occured.\n");

    ui->textBrowser->append("Done\n");
}

void MainWindow::on_actionClustering_coefficient_triggered()
{
    QString vertexId = inputId("Vertex id:");
    QString ret;
    double coefficient;
    if (!vertexId.isEmpty())
    {
        if (!propertyMap.containsProperty("clusteringCoeficientForVertex", vertexId.toStdString()))
        {
            ui->textBrowser->append("Clustering coefficient has not been previously computed. Computing now.");
            if (this->weightedgraph)
            {
                WeightedVertex* vertex;
                if ((vertex = weightedGraph.getVertexById(from_string<unsigned int>(vertexId.toStdString()))) != NULL)
                {
                    IClusteringCoefficient<WeightedGraph, WeightedVertex>* clusteringCoefficient = weightedFactory->createClusteringCoefficient();
                    propertyMap.addProperty<double>("clusteringCoeficientForVertex", to_string<unsigned int>(vertex->getVertexId()), clusteringCoefficient->vertexClusteringCoefficient(vertex));
                    delete clusteringCoefficient;
                }
            }
            else
            {
                Vertex* vertex;
                if ((vertex = graph.getVertexById(from_string<unsigned int>(vertexId.toStdString()))) != NULL)
                {
                    IClusteringCoefficient<Graph, Vertex>* clusteringCoefficient = factory->createClusteringCoefficient();
                    propertyMap.addProperty<double>("clusteringCoeficientForVertex", to_string<unsigned int>(vertex->getVertexId()), clusteringCoefficient->vertexClusteringCoefficient(vertex));
                    delete clusteringCoefficient;
                }
            }
        }
        try
        {
            coefficient = propertyMap.getProperty<double>("clusteringCoeficientForVertex", vertexId.toStdString());
            ret.append("Clustering coefficient for vertex ").append(vertexId);
            ret.append(" is: ").append(to_string<double>(coefficient).c_str()).append(".\n");
            ui->textBrowser->append(ret);
        }
        catch (const BadElementName& ex)
        {
            ret.append("There is no vertices with id ").append(vertexId).append(".\n");
            ui->textBrowser->append(ret);
        }
    }
}

void MainWindow::on_actionNearest_neighbors_degree_triggered()
{
    QString vertexId = inputId("Vertex id:");
    QString ret;
    double neighborsDegree;
    if (!vertexId.isEmpty())
    {
        if (!propertyMap.containsProperty("nearestNeighborsDegreeForVertex", vertexId.toStdString()))
        {
            ui->textBrowser->append("Nearest neighbors degree has not been previously computed. Computing now.");
            if (this->weightedgraph)
            {
                WeightedVertex* vertex;
                if ((vertex = weightedGraph.getVertexById(from_string<unsigned int>(vertexId.toStdString()))) != NULL)
                {
                    INearestNeighborsDegree<WeightedGraph, WeightedVertex>* nearestNeighborsDegree = weightedFactory->createNearestNeighborsDegree();
                    propertyMap.addProperty<double>("nearestNeighborsDegreeForVertex", to_string<unsigned int>(vertex->getVertexId()), nearestNeighborsDegree->meanDegreeForVertex(vertex));
                    delete nearestNeighborsDegree;
                }
            }
            else
            {
                Vertex* vertex;
                if ((vertex = graph.getVertexById(from_string<unsigned int>(vertexId.toStdString()))) != NULL)
                {
                    INearestNeighborsDegree<Graph, Vertex>* nearestNeighborsDegree = factory->createNearestNeighborsDegree();
                    propertyMap.addProperty<double>("nearestNeighborsDegreeForVertex", to_string<unsigned int>(vertex->getVertexId()), nearestNeighborsDegree->meanDegreeForVertex(vertex));
                    delete nearestNeighborsDegree;
                }
            }
        }
        try
        {
            neighborsDegree = propertyMap.getProperty<double>("nearestNeighborsDegreeForVertex", vertexId.toStdString());
            ret.append("Nearest neighbors degree for vertex ").append(vertexId);
            ret.append(" is: ").append(to_string<double>(neighborsDegree).c_str()).append(".\n");
            ui->textBrowser->append(ret);
        }
        catch (const BadElementName& ex)
        {
            ret.append("There is no vertices with id ").append(vertexId).append(".\n");
            ui->textBrowser->append(ret);
        }
    }
}

void MainWindow::on_actionClustering_Coefficient_vs_Degree_triggered()
{
    int ret = 0 ;
    ui->textBrowser->append("Plotting Clustering Coefficient vs Degree...");
    double cc = 0;
    if (!propertyMap.containsPropertySet("clusteringCoeficientForDegree"))
    {
        this->computeDegreeDistribution();
        VariantsSet& degrees = propertyMap.getPropertySet("degreeDistribution");
        VariantsSet::const_iterator it = degrees.begin();

        if (this->weightedgraph)
        {
            IClusteringCoefficient<WeightedGraph, WeightedVertex>* clusteringCoefficient = weightedFactory->createClusteringCoefficient();
            while (it != degrees.end())
            {
                cc = clusteringCoefficient->clusteringCoefficient(weightedGraph, from_string<unsigned int>(it->first));
                propertyMap.addProperty<double>("clusteringCoeficientForDegree", it->first, cc);
                ++it;
            }
            delete clusteringCoefficient;
        }
        else
        {
            IClusteringCoefficient<Graph, Vertex>* clusteringCoefficient = factory->createClusteringCoefficient();
            while (it != degrees.end())
            {
                cc = clusteringCoefficient->clusteringCoefficient(graph, from_string<unsigned int>(it->first));
                propertyMap.addProperty<double>("clusteringCoeficientForDegree", it->first, cc);
                ++it;
            }
            delete clusteringCoefficient;
        }
    }
    ret = this->console->plotPropertySet(propertyMap.getPropertySet("clusteringCoeficientForDegree"), "clusteringCoeficientForDegree");
    this->console->show();
    this->activateWindow();
    if (!ret)
        ui->textBrowser->append("An unexpected error has occured.\n");
}

void MainWindow::on_actionNearest_Neighbors_Degree_vs_Degree_triggered()
{
    int ret = 0 ;
    ui->textBrowser->append("Plotting Neirest Neighbors Degree vs Degree...");
    double knn = 0;
    if (!propertyMap.containsPropertySet("nearestNeighborDegreeForDegree"))
    {
        this->computeDegreeDistribution();
        VariantsSet& degrees = propertyMap.getPropertySet("degreeDistribution");
        VariantsSet::const_iterator it = degrees.begin();

        if (this->weightedgraph)
        {
            INearestNeighborsDegree<WeightedGraph, WeightedVertex>* nearestNeighborDegree = weightedFactory->createNearestNeighborsDegree();
            while (it != degrees.end())
            {
                knn = nearestNeighborDegree->meanDegree(weightedGraph, from_string<unsigned int>(it->first));
                propertyMap.addProperty<double>("nearestNeighborDegreeForDegree", it->first, knn);
                ++it;
            }
            delete nearestNeighborDegree;
        }
        else
        {
            INearestNeighborsDegree<Graph, Vertex>* nearestNeighborDegree = factory->createNearestNeighborsDegree();
            while (it != degrees.end())
            {
                knn = nearestNeighborDegree->meanDegree(graph, from_string<unsigned int>(it->first));
                propertyMap.addProperty<double>("nearestNeighborDegreeForDegree", it->first, knn);
                ++it;
            }
            delete nearestNeighborDegree;
        }
    }
    ret = this->console->plotPropertySet(propertyMap.getPropertySet("nearestNeighborDegreeForDegree"), "nearestNeighborDegreeForDegree");
    this->console->show();
    this->activateWindow();
    if (!ret)
        ui->textBrowser->append("An unexpected error has occured.\n");
}

//TODO check if shellIndexVsDegree has previously calculated and avoid unnecesary computation. If not calculated save in property map
void MainWindow::on_actionShell_Index_vs_Degree_triggered()
{
    if (this->weightedgraph)
    {
        ui->textBrowser->append("Shell index for weighted graphs is not supported.");
        return;
    }
    this->computeShellIndex();
    this->computeDegreeDistribution();
    double shellAuxAcum;
    unsigned int degreeAmount, vertedId;
    int ret;
    VariantsSet shellIndexVsDegree;
    VariantsSet& shellIndex = propertyMap.getPropertySet("shellIndex");
    VariantsSet& degreeDistribution = propertyMap.getPropertySet("degreeDistribution");
    VariantsSet::const_iterator it = degreeDistribution.begin();
    VariantsSet::const_iterator shellIt = shellIndex.begin();
    VariantsSet::const_iterator shellVsDegreeIt;
    while (it != degreeDistribution.end())
    {
        shellIndexVsDegree.insert<double>(it->first, 0);
        ++it;
    }

    while (shellIt != shellIndex.end())
    {
        vertedId = from_string<unsigned int>(shellIt->first);
        Vertex* v = this->weightedgraph ? weightedGraph.getVertexById(vertedId) : graph.getVertexById(vertedId);
        shellAuxAcum = shellIndexVsDegree.get_element<double>(to_string<unsigned int>(v->degree()));
        shellIndexVsDegree.insert<double>(to_string<unsigned int>(v->degree()) , shellAuxAcum + from_string<unsigned int>(shellIt->second));

        ++shellIt;
    }

    shellVsDegreeIt = shellIndexVsDegree.begin();
    while (shellVsDegreeIt != shellIndexVsDegree.end())
    {
        std::string degree = shellVsDegreeIt->first;
        shellAuxAcum = from_string<double>(shellVsDegreeIt->second);
        degreeAmount = degreeDistribution.get_element<unsigned int>(degree);

        shellIndexVsDegree.insert<double>(degree , shellAuxAcum / (double)degreeAmount);
        ++shellVsDegreeIt;
    }

    ret = this->console->plotPropertySet(shellIndexVsDegree, "shellIndexVsDegree");
    this->console->show();
    this->activateWindow();
    if (!ret)
        ui->textBrowser->append("An unexpected error has occured.\n");
}

//TODO check if betweennessVsDegree has previously calculated and avoid unnecesary computation. If not calculated save in property map
void MainWindow::on_actionBetweenness_vs_Degree_triggered()
{
    if (this->weightedgraph)
    {
        ui->textBrowser->append("Betweenness for weighted graphs is not supported.");
        return;
    }
    this->computeBetweenness();
    this->computeDegreeDistribution();
    double betweennessAuxAcum;
    unsigned int degreeAmount;
    int ret;
    VariantsSet betweennessVsDegree;
    VariantsSet& betweenness = propertyMap.getPropertySet("betweenness");
    VariantsSet& degreeDistribution = propertyMap.getPropertySet("degreeDistribution");
    VariantsSet::const_iterator it = degreeDistribution.begin();
    VariantsSet::const_iterator betwennessIt = betweenness.begin();
    VariantsSet::const_iterator betweennessVsDegreeIt;
    while (it != degreeDistribution.end())
    {
        betweennessVsDegree.insert<double>(it->first, 0.0);
        ++it;
    }

    while (betwennessIt != betweenness.end())
    {
        unsigned int vertedId = from_string<unsigned int>(betwennessIt->first);
        Vertex* v = this->weightedgraph ? weightedGraph.getVertexById(vertedId) : graph.getVertexById(vertedId);
        betweennessAuxAcum = betweennessVsDegree.get_element<double>(to_string<unsigned int>(v->degree()));
        betweennessVsDegree.insert<double>(to_string<unsigned int>(v->degree()) , betweennessAuxAcum + from_string<unsigned int>(betwennessIt->second));

        ++betwennessIt;
    }

    betweennessVsDegreeIt = betweennessVsDegree.begin();
    while (betweennessVsDegreeIt != betweennessVsDegree.end())
    {
        std::string degree = betweennessVsDegreeIt->first;
        betweennessAuxAcum = from_string<double>(betweennessVsDegreeIt->second);
        degreeAmount = degreeDistribution.get_element<unsigned int>(degree);

        betweennessVsDegree.insert<double>(degree , betweennessAuxAcum / (double)degreeAmount);
        ++betweennessVsDegreeIt;
    }

    ret = this->console->plotPropertySet(betweennessVsDegree, "betweennessVsDegree");
    this->console->show();
    this->activateWindow();
    if (!ret)
        ui->textBrowser->append("An unexpected error has occured.\n");
}

void MainWindow::on_actionExportNearest_Neighbors_Degree_vs_Degree_triggered()
{
    std::string ret;
    ui->textBrowser->append("Exporting Nearest Neighbors Degree vs Degree...");
    ret = this->getSavePath();
    if (!ret.empty())
    {
        if (propertyMap.containsPropertySet("nearestNeighborDegreeForDegree"))
        {
            grapherUtils.exportPropertySet(propertyMap.getPropertySet("nearestNeighborDegreeForDegree"), ret);
            ui->textBrowser->append("Done.");
        }
        else
            ui->textBrowser->append("Nearest Neighbors Degree vs Degree has not been previously computed. Please go to Plot->Nearest Neighbors Degree vs Degree first.");
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

void MainWindow::on_actionExportShell_Index_vs_Degree_triggered()
{
    std::string ret;
    ui->textBrowser->append("Exporting Shell Index vs Degree...");
    ret = this->getSavePath();
    if (!ret.empty())
    {
        if (propertyMap.containsPropertySet("shellIndexVsDegree"))
        {
            grapherUtils.exportPropertySet(propertyMap.getPropertySet("shellIndexVsDegree"), ret);
            ui->textBrowser->append("Done.");
        }
        else
            ui->textBrowser->append("Shell Index vs Degree has not been previously computed. Please go to Plot->Shell Index vs Degree first.");
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

void MainWindow::on_actionExportClustering_Coefficient_vs_Degree_triggered()
{
    std::string ret;
    ui->textBrowser->append("Exporting Clustering Coefficient vs Degree...");
    ret = this->getSavePath();
    if (!ret.empty())
    {
        if (propertyMap.containsPropertySet("clusteringCoeficientForDegree"))
        {
            grapherUtils.exportPropertySet(propertyMap.getPropertySet("clusteringCoeficientForDegree"), ret);
            ui->textBrowser->append("Done.");
        }
        else
            ui->textBrowser->append("Clustering Coefficient vs Degree has not been previously computed. Please go to Plot->Clustering Coefficient vs Degree first.");
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

void MainWindow::on_actionExportDegree_distribution_triggered()
{
    std::string ret;
    ui->textBrowser->append("Exporting Degree Distribution...");
    ret = this->getSavePath();
    if (!ret.empty())
    {
        if (propertyMap.containsPropertySet("degreeDistributionProbability"))
        {
            grapherUtils.exportPropertySet(propertyMap.getPropertySet("degreeDistributionProbability"), ret);
            ui->textBrowser->append("Done.");
        }
        else
            ui->textBrowser->append("Degree Distribution has not been previously computed. Please go to Plot->Degree Distribution first.");
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

void MainWindow::on_actionExportBetweenness_vs_Degree_triggered()
{
    std::string ret;
    ui->textBrowser->append("Exporting Netweenness vs Degree...");
    ret = this->getSavePath();
    if (!ret.empty())
    {
        if (propertyMap.containsPropertySet("betweennessVsDegree"))
        {
            grapherUtils.exportPropertySet(propertyMap.getPropertySet("betweennessVsDegree"), ret);
            ui->textBrowser->append("Done.");
        }
        else
            ui->textBrowser->append("Netweenness vs Degree has not been previously computed. Please go to Plot->Netweenness vs Degree first.");
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

std::string MainWindow::getSavePath() const
{
    QFileDialog dialog(0, "Save tree", QDir::homePath(), "");
    std::string ret;
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec())
    {
        ret.append(dialog.selectedFiles().at(0).toStdString());
    }
    return ret;
}

int MainWindow::LogBinningDialog()
{
    QString title("Logarithmic Binning");
    QString text("Would you like to log-bin the data before plotting?");
    QMessageBox msgBox(QMessageBox::Question, title, text, QMessageBox::Yes | QMessageBox::No, this);
    msgBox.setDefaultButton(QMessageBox::Yes);
    return msgBox.exec();
}




void MainWindow::on_actionNewErdosRenyi_triggered()
{
	if (!this->graphLoaded)
    {
		srand(time(NULL));
		QString inputN = inputId("n:");
		QString inputP = inputId("p:");
		QString ret;

		unsigned int n = 1000;
		float p = 0.1;

		try
	    {
	        this->onNetworkLoad(false, false, false);
			buildGraphFactory(false);


			if(!inputN.isEmpty())
	        	n = inputN.toInt();
			if(!inputP.isEmpty())
	        	p = inputP.toFloat();

            graph = *(GraphGenerator::getInstance()->generateErdosRenyiGraph(n, p));

			/*ConexityVisitor<Graph, Vertex> conexityVisitor;

			graphpp::AdjacencyListGraph<graphpp::AdjacencyListVertex>::VerticesIterator it = graph.verticesIterator();
		    while (!it.end())
		    {
		        conexityVisitor.vertexesLeft.push_back((*it)->getVertexId());
		        ++it;
		    }

			while (conexityVisitor.vertexesLeft.size()>0)
			{
				unsigned int element = conexityVisitor.vertexesLeft.back();
				conexityVisitor.vertexesLeft.pop_back();
				ui->textBrowser->append(QString("%1").arg(element));
			}

			conexityVisitor.vertexesInComponent.clear();
			Vertex* source = graph.getVertexById(conexityVisitor.vertexesLeft.back());
			TraverserBFS<Graph, Vertex, ConexityVisitor<Graph, Vertex> >::traverse(source, conexityVisitor);*/

			// Keep only the bigest component (at least n/2 vertexes)
			//ConexityVerifier<Graph, Vertex>* conexityVerifier = new ConexityVerifier();
			//conexityVerifier.getBigestComponent(graph);

			QString text("Network created using Erdos-Renyi algorithm");
	        text.append("\nAmount of vertices in the graph: ");
	        unsigned int verticesCount = graph.verticesCount();
	        text.append(QString("%1").arg(verticesCount));
	        text.append(".\n");
	        ui->textBrowser->append(text);         
    	}
	    catch (const BadElementName& ex)
	    {
	        ret.append("Error ").append(".\n");
	        ui->textBrowser->append(ret);
	    }
	}
}

void MainWindow::on_actionNewBarabasiAlbert_triggered()
{
	if (!this->graphLoaded)
    {
		srand(time(NULL));
		QString inputM_0 = inputId("m_0:");
		QString inputM = inputId("m:");
		QString inputN = inputId("n:");
		QString ret;

		
		unsigned int m_0 = 4;
		unsigned int m = 2;
		unsigned int n = 1000;

	    try
	    {
			this->onNetworkLoad(false, false, false);
			buildGraphFactory(false);

			if(!inputM_0.isEmpty())
	        	m_0 = inputM_0.toInt();
			if(!inputM.isEmpty())
	        	m = inputM.toInt();
			if(!inputN.isEmpty())
	        	n = inputN.toInt();
			m_0 = max(m_0, m);

			graph = *(GraphGenerator::getInstance()->generateBarabasiAlbertGraph(m_0, m, n));

			QString text("Network created using Barabasi-Albert algorithm");
	        text.append("\nAmount of vertices in the graph: ");
	        unsigned int verticesCount = graph.verticesCount();
	        text.append(QString("%1").arg(verticesCount));
	        text.append(".\n");
	        ui->textBrowser->append(text);         
	    }
	    catch (const BadElementName& ex)
	    {
	        ret.append("Error ").append(".\n");
	        ui->textBrowser->append(ret);
	    }
	}
}

void MainWindow::on_actionNewExtendedHOT_triggered()
{
	
}

void MainWindow::on_actionNewMolloyReed_triggered()
{
	
}

