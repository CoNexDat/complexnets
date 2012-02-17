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
        //If no network is loaded user may procede to load a new network.
        ui->textBrowser->append("Loading new network...");
        if (graphValidationDialog.exec())
        {
            if (fileDialog.exec())
            {
                graph = Graph(graphValidationDialog.isDirected(), graphValidationDialog.isMultigraph());
                weightedGraph = WeightedGraph(graphValidationDialog.isDirected(), graphValidationDialog.isMultigraph());
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
                catch (const DuplicateEdge& ex)
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
                propertyMap.addProperty<unsigned int>("degreeDistribution", to_string<unsigned int>(it->first), it->second);
                propertyMap.addProperty<unsigned int>("degreeDistributionProbability", to_string<unsigned int>(it->first), it->second / weightedGraph.verticesCount());
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
                propertyMap.addProperty<unsigned int>("degreeDistributionProbability", to_string<unsigned int>(it->first), it->second / graph.verticesCount());
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
    ui->textBrowser->append("Plotting degree distribution...");
    if (!propertyMap.containsPropertySet("degreeDistributionProbability"))
    {
        ui->textBrowser->append("Digree distribution has not been previously computed. Computing now.");
        this->computeDegreeDistribution();
    }
    grapher.plotLogBinDegree(propertyMap.getPropertySet("degreeDistribution"), 2);

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
    ret = grapher.plotPropertySet(propertyMap.getPropertySet("clusteringCoeficientForDegree"), "d", "CC(d)", "Clustering Coefficient vs Degree");
    if (ret == 0)
        ui->textBrowser->append("Done\n");
    else
        ui->textBrowser->append("Action canceled: an error while plotting ocurred.\n");
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
    ret = grapher.plotPropertySet(propertyMap.getPropertySet("nearestNeighborDegreeForDegree"), "d", "Knn(d)", "Clustering Coefficient vs Degree");
    if (ret == 0)
        ui->textBrowser->append("Done\n");
    else
        ui->textBrowser->append("Action canceled: an error while plotting ocurred.\n");
}

void MainWindow::on_actionShell_Index_vs_Degree_triggered()
{
    if(this->weightedgraph)
    {
        ui->textBrowser->append("Shell index for weighted graphs is not supported.");
        return;
    }
    this->computeShellIndex();
    this->computeDegreeDistribution();
    double shellAuxAcum;
    unsigned int degreeAmount;
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
        unsigned int vertedId = from_string<unsigned int>(shellIt->first);
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

        shellIndexVsDegree.insert<double>(degree , shellAuxAcum / degreeAmount);
        ++shellVsDegreeIt;
    }

    ret = grapher.plotPropertySet(shellIndexVsDegree, "d", "k-Core(d)", "Shell Index vs Degree");
    if (ret == 0)
        ui->textBrowser->append("Done\n");
    else
        ui->textBrowser->append("Action canceled: an error while plotting ocurred.\n");
}

void MainWindow::on_actionBetweenness_vs_Degree_triggered()
{
    if(this->weightedgraph)
    {
        ui->textBrowser->append("Betweenness for weighted graphs is not supported.");
        return;
    }
    this->computeShellIndex();
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
        betweennessVsDegree.insert<double>(it->first, 0);
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

        betweennessVsDegree.insert<double>(degree , betweennessAuxAcum / degreeAmount);
        ++betweennessVsDegreeIt;
    }

    ret = grapher.plotPropertySet(betweennessVsDegree, "d", "CC(d)", "Shell Index vs Degree");
    if (ret == 0)
        ui->textBrowser->append("Done\n");
    else
        ui->textBrowser->append("Action canceled: an error while plotting ocurred.\n");
}
