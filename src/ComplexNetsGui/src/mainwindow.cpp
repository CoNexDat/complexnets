// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 16th, 2015.

#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// File ui_mainwindow.h will be generated on compile time. Don't look for it, unless you have
// already compiled the project.
#include "ComplexNets/DegreeDistribution.h"
#include "ComplexNets/DirectedDegreeDistribution.h"
#include "ComplexNets/DirectedGraphFactory.h"
#include "ComplexNets/GraphFactory.h"
#include "ComplexNets/GraphGenerator.h"
#include "ComplexNets/IBetweenness.h"
#include "ComplexNets/IGraphReader.h"
#include "ComplexNets/IShellIndex.h"
#include "ComplexNets/MaxClique.h"
#include "ComplexNets/WeightedGraphFactory.h"
#include "ComplexNetsGui/inc/GnuplotConsole.h"
#include "ComplexNetsGui/inc/GraphLoadingValidationDialog.h"
#include "ComplexNetsGui/inc/LogBinningPolicy.h"
#include "ComplexNetsGui/inc/mainwindow.h"
#include "ComplexNetsGui/inc/ui_mainwindow.h"

using namespace ComplexNetsGui;
using namespace graphpp;
using namespace std;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    weightedFactory = NULL;
    factory = NULL;
    directedFactory = NULL;
    directed_in = false;
    directed_out = true;
    this->onNetworkUnload();
    this->console = new GnuplotConsole();
    ui->textBrowser->setOpenExternalLinks(true);
    ui->textBrowser->append(
        "Welcome to ComplexNets++!!\nIf you are a developer feel free to visit our GitHub page:");
    ui->textBrowser->append(
        "<a href='https://github.com/ihameli/complexnets'>ComplexNets++ - GitHub</a>");
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
        // If no network is loaded user may procede to load a new network.
        ui->textBrowser->append("Loading new network...");
        if (graphValidationDialog.exec())
        {
            if (fileDialog.exec())
            {
                bool isDirected = graphValidationDialog.isDirected();
                bool isMultigraph = graphValidationDialog.isMultigraph();
                selectedFiles = fileDialog.selectedFiles();
                this->onNetworkLoad(graphValidationDialog.isWeigthed(),
                                    graphValidationDialog.isDirected(),
                                    graphValidationDialog.isMultigraph());
                buildGraphFactory(graphValidationDialog.isWeigthed(),
                                  graphValidationDialog.isDirected());
                try
                {
                    string path = selectedFiles[0].toStdString();

                    if (this->weightedgraph)
                    {
                        graph = Graph(isDirected, isMultigraph);
                        weightedGraph =
                            *(GraphGenerator::getInstance()->generateWeightedGraphFromFile(
                                path, isDirected, isMultigraph));
                    }
                    else if (isDirected)
                    {
                        graph = Graph(isDirected, isMultigraph);
                        directedGraph =
                            *(GraphGenerator::getInstance()->generateDirectedGraphFromFile(
                                path, isMultigraph));
                    }
                    else
                    {
                        graph = *(GraphGenerator::getInstance()->generateGraphFromFile(
                            path, isDirected, isMultigraph));
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
                unsigned int verticesCount =
                    this->weightedgraph
                        ? weightedGraph.verticesCount()
                        : this->digraph ? directedGraph.verticesCount() : graph.verticesCount();
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
        ui->textBrowser->append(
            "Action canceled: Only one network can be loaded at any given time.\n");
    }
}

void MainWindow::on_actionExportPowerLawDegreeDistribution_triggered()
{
    std::string ret;
    ui->textBrowser->append("Exporting power law distribution...");
    ret = this->getSavePath();
    cout << ret << "\n";
    int alfa;
    int n;
    if (!ret.empty())
    {
        QString inputN = inputId("alfa:");
        if (!inputN.isEmpty())
        {
            alfa = inputN.toInt();

            inputN = inputId("nodes:");
            if (!inputN.isEmpty())
            {
                n = inputN.toInt();
                double dmax = pow(n, 1.0 / alfa);
                cout << "dmax: " << dmax << "\n";
                double c2 = (double)n / alfa;
                cout << "c2: " << c2 << "\n";
                ofstream myfile;
                myfile.open(ret.c_str());
                for (int i = 1; i <= dmax; i++)
                {
                    double quant = c2 * pow(i, -alfa);
                    if ((int)quant != 0)
                    {
                        myfile << i << " " << (int)quant << "\n";
                    }
                }
                myfile.close();
                ui->textBrowser->append("Power law succefully exported.");
            }
            else
            {
                ui->textBrowser->append("Action canceled by user.");
            }
        }
        else
        {
            ui->textBrowser->append("Action canceled by user.");
        }
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

void MainWindow::on_actionQuit_triggered()
{
    QMessageBox msg(QMessageBox::Question, "Quit", "Are you sure you want to quit?",
                    QMessageBox::Ok | QMessageBox::Cancel, this);
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
    QMessageBox msg(QMessageBox::Question, "Close current network",
                    "Are you sure you want to close the current network?",
                    QMessageBox::Ok | QMessageBox::Cancel, this);
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

    // TODO start taking functionality out of this block when they are implemented
    if (!digraph)
    {
        ui->actionClose_current_network->setEnabled(true);
        ui->actionBetweenness->setEnabled(true);
        ui->actionClustering_coefficient->setEnabled(true);
        ui->actionNearest_neighbors_degree->setEnabled(true);
        ui->actionShell_index->setEnabled(true);
        ui->actionBetweenness_vs_Degree->setEnabled(true);
        ui->actionClustering_Coefficient_vs_Degree->setEnabled(true);
        ui->actionNearest_Neighbors_Degree_vs_Degree->setEnabled(true);
        ui->actionShell_Index_vs_Degree->setEnabled(true);
        ui->actionExportBetweenness_vs_Degree->setEnabled(true);
        ui->actionExportClustering_Coefficient_vs_Degree->setEnabled(true);
        ui->actionExportShell_Index_vs_Degree->setEnabled(true);
        ui->actionExportNearest_Neighbors_Degree_vs_Degree->setEnabled(true);
        ui->actionMaxClique->setEnabled(true);
        ui->actionMaxCliqueExact->setEnabled(true);
        ui->action_maxClique_plotting->setEnabled(true);
        ui->action_maxCliqueExact_plotting->setEnabled(true);
        ui->actionExportMaxClique_distribution->setEnabled(true);
        ui->actionExportMaxCliqueExact_distribution->setEnabled(true);
        ui->actionBoxplotCC->setEnabled(true);
        ui->actionExportCCBoxplot->setEnabled(true);
        ui->actionExportKnnBoxplot->setEnabled(true);
        ui->actionExportPowerLawDegreeDistribution->setEnabled(true);
        ui->actionBoxplotNearestNeighborsDegree->setEnabled(true);
    }

    if (weightedgraph)
    {
        ui->actionBetweenness->setEnabled(true);
        ui->actionBetweenness_vs_Degree->setEnabled(true);
        ui->actionMaxClique->setEnabled(false);
        ui->action_maxClique_plotting->setEnabled(false);
        ui->actionMaxCliqueExact->setEnabled(false);
        ui->action_maxCliqueExact_plotting->setEnabled(false);
        ui->actionShell_index->setEnabled(false);
        ui->actionShell_Index_vs_Degree->setEnabled(false);
        // export menue
        ui->actionExportBetweenness_vs_Degree->setEnabled(true);
        ui->actionExportShell_Index_vs_Degree->setEnabled(false);
        ui->actionExportMaxClique_distribution->setEnabled(false);
        ui->actionExportMaxCliqueExact_distribution->setEnabled(false);
        ui->actionBoxplotCC->setEnabled(false);
        ui->actionExportCCBoxplot->setEnabled(false);
        ui->actionExportKnnBoxplot->setEnabled(false);
        ui->actionExportPowerLawDegreeDistribution->setEnabled(false);
        ui->actionBoxplotNearestNeighborsDegree->setEnabled(false);
    }

    if (digraph)
    {
        ui->actionClustering_coefficient->setEnabled(true);
        ui->actionNearest_neighbors_degree->setEnabled(true);
        ui->actionConfigure_Directed_Degree_sign->setEnabled(true);

        ui->actionClustering_Coefficient_vs_Degree->setEnabled(true);
        ui->actionNearest_Neighbors_Degree_vs_Degree->setEnabled(true);

        ui->actionExportClustering_Coefficient_vs_Degree->setEnabled(true);
        ui->actionExportNearest_Neighbors_Degree_vs_Degree->setEnabled(true);
    }

    // Enabled actions for all graph types
    ui->actionDegree_distribution->setEnabled(true);
    ui->actionDegree_distribution_plotting->setEnabled(true);
    ui->actionExportDegree_distribution->setEnabled(true);
    ui->actionClose_current_network->setEnabled(true);
    ui->actionCumulativeDegree_distribution_plotting->setEnabled(true);
    ui->actionExportCumulativeDegree_distribution->setEnabled(true);
}

void MainWindow::onNetworkUnload()
{
    this->graphLoaded = false;
    this->weightedgraph = false;
    this->digraph = false;
    this->multigraph = false;
    disableActions();
}

void MainWindow::disableActions()
{
    ui->actionClose_current_network->setEnabled(false);
    ui->actionBetweenness->setEnabled(false);
    ui->actionMaxClique->setEnabled(false);
    ui->actionMaxCliqueExact->setEnabled(false);
    ui->actionClustering_coefficient->setEnabled(false);
    ui->actionDegree_distribution->setEnabled(false);
    ui->actionDegree_distribution_plotting->setEnabled(false);
    ui->action_maxClique_plotting->setEnabled(false);
    ui->action_maxCliqueExact_plotting->setEnabled(false);
    ui->actionClose_current_network->setEnabled(false);
    ui->actionNearest_neighbors_degree->setEnabled(false);
    ui->actionShell_index->setEnabled(false);
    ui->actionBetweenness_vs_Degree->setEnabled(false);
    ui->actionClustering_Coefficient_vs_Degree->setEnabled(false);
    ui->actionNearest_Neighbors_Degree_vs_Degree->setEnabled(false);
    ui->actionShell_Index_vs_Degree->setEnabled(false);
    ui->actionExportBetweenness_vs_Degree->setEnabled(false);
    ui->actionExportDegree_distribution->setEnabled(false);
    ui->actionExportClustering_Coefficient_vs_Degree->setEnabled(false);
    ui->actionExportShell_Index_vs_Degree->setEnabled(false);
    ui->actionExportNearest_Neighbors_Degree_vs_Degree->setEnabled(false);
    ui->actionExportMaxClique_distribution->setEnabled(false);
    ui->actionExportMaxCliqueExact_distribution->setEnabled(false);
    ui->actionBoxplotCC->setEnabled(false);
    ui->actionExportKnnBoxplot->setEnabled(false);
    ui->actionExportPowerLawDegreeDistribution->setEnabled(false);
    ui->actionExportCCBoxplot->setEnabled(false);
    ui->actionBoxplotNearestNeighborsDegree->setEnabled(false);
    ui->actionConfigure_Directed_Degree_sign->setEnabled(false);
    ui->actionCumulativeDegree_distribution_plotting->setEnabled(false);
    ui->actionExportCumulativeDegree_distribution->setEnabled(false);
}

void MainWindow::buildGraphFactory(const bool isWeighted, const bool isDirected)
{
    if (isWeighted)
        weightedFactory = new WeightedGraphFactory<WeightedGraph, WeightedVertex>();
    else if (isDirected)
        directedFactory = new DirectedGraphFactory<DirectedGraph, DirectedVertex>();
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
    else if (directedFactory != NULL)
    {
        delete directedFactory;
        directedFactory = NULL;
    }
    else if (factory != NULL)
    {
        delete factory;
        factory = NULL;
    }
}

// TODO this function doesnt validate input. should be const
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

typedef typename std::list<int> id_list;

void MainWindow::on_actionExportMaxCliqueExact_distribution_triggered()
{
    on_actionExportMaxClique_distribution_generic_triggered(true);
}

void MainWindow::on_actionExportMaxClique_distribution_triggered()
{
    on_actionExportMaxClique_distribution_generic_triggered(false);
}

void MainWindow::on_actionExportMaxClique_distribution_generic_triggered(bool exact)
{
    std::string ret;
    ui->textBrowser->append("Exporting MaxClique Distribution...");
    ret = this->getSavePath();
    if (!ret.empty())
    {
        if (propertyMap.containsPropertySet(exact ? "maxCliqueExactDistribution"
                                                  : "maxCliqueAproxDistribution"))
        {
            grapherUtils.exportPropertySet(
                propertyMap.getPropertySet(exact ? "maxCliqueExactDistribution"
                                                 : "maxCliqueAproxDistribution"),
                ret);
            ui->textBrowser->append("Done.");
        }
        else
            ui->textBrowser->append(
                "Max Clique has not been previously computed. Please go to Plot->MaxClique "
                "Distribution first.");
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

void MainWindow::on_action_maxCliqueExact_plotting_triggered()
{
    on_action_maxClique_plotting_generic_triggered(true);
}

void MainWindow::on_action_maxClique_plotting_triggered()
{
    on_action_maxClique_plotting_generic_triggered(false);
}

void MainWindow::on_action_maxClique_plotting_generic_triggered(bool exact)
{
    bool ret, logBin = false;
    unsigned int bins = 25;
    ui->textBrowser->append("Plotting maxClique distribution...");

    this->computeMaxClique(exact);

    if (LogBinningDialog() == QMessageBox::Yes)
    {
        logBin = true;
        QString inputN = inputId("bins:");
        if (!inputN.isEmpty())
        {
            bins = inputN.toInt();
        }
    }
    ret = this->console->plotPropertySet(
        propertyMap.getPropertySet(exact ? "maxCliqueExactDistribution"
                                         : "maxCliqueAproxDistribution"),
        "maxCliqueDistribution", logBin, bins);
    this->console->show();
    this->activateWindow();
    if (!ret)
        ui->textBrowser->append("An unexpected error has occured.\n");

    ui->textBrowser->append("Done\n");
}

void MainWindow::on_actionMaxCliqueExact_triggered()
{
    on_actionMaxClique_generic_triggered(true);
}

void MainWindow::on_actionMaxClique_triggered()
{
    on_actionMaxClique_generic_triggered(false);
}

void MainWindow::on_actionMaxClique_generic_triggered(bool exact)
{
    if (this->weightedgraph)
    {
        ui->textBrowser->append("Max clique for weighted graphs is not supported.");
        return;
    }

    QString ret;

    this->computeMaxClique(exact);
    if (exact && !propertyMap.containsPropertySet("maxCliqueExact"))
    {
        ret.append("Calculation timed out.\n");
        ui->textBrowser->append(ret);
        return;
    }
    try
    {
        int maxCliqueSize =
            propertyMap.getProperty<int>(exact ? "maxCliqueExact" : "maxCliqueAprox", "size");
        id_list list =
            propertyMap.getProperty<id_list>(exact ? "maxCliqueExact" : "maxCliqueAprox", "list");
        ui->textBrowser->append(exact ? "Exact Max clique" : "Aprox Max clique");
        ret.append(" size is: ").append(to_string<int>(maxCliqueSize).c_str()).append(".\n");
        ret.append("clique is: ");
        for (std::list<int>::iterator iterator = list.begin(); iterator != list.end(); iterator++)
        {
            ret.append(to_string<int>(*iterator).c_str()).append(" ");
        }
        ret.append(".\n");
        ui->textBrowser->append(ret);
    }
    catch (const BadElementName& ex)
    {
        ret.append("'Max clique: property was not found.");
        ui->textBrowser->append(ret);
    }
    //}
}

void MainWindow::on_actionBetweenness_triggered()
{
    // if (this->weightedgraph)
    //{
    //    ui->textBrowser->append("Betweenness for weighted graphs is not supported.");
    //    return;
    //}
    QString vertexId = "2";
    QString ret;
    double vertexBetweenness;
    if (!vertexId.isEmpty())
    {
        this->computeBetweenness();
        try
        {
            graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry;
            if (!propertyMap.containsProperty("BetweennessBPMean", to_string(0)))
            {
                entry = this->computeTotalBpEntriesBetweenness();
                propertyMap.addProperty<double>("BetweennessBPMean", to_string(0), entry.mean);
                propertyMap.addProperty<double>("BetweennessBPMin", to_string(0), entry.min);
                propertyMap.addProperty<double>("BetweennessBPQ1", to_string(0), entry.Q1);
                propertyMap.addProperty<double>("BetweennessBPQ2", to_string(0), entry.Q2);
                propertyMap.addProperty<double>("BetweennessBPQ3", to_string(0), entry.Q3);
                propertyMap.addProperty<double>("BetweennessBPMax", to_string(0), entry.max);
            }
            else
            {
                ret.append("Data already calculated. \n");
                entry.mean = propertyMap.getProperty<double>("BetweennessBPMean", to_string(0));
                entry.min = propertyMap.getProperty<double>("BetweennessBPMin", to_string(0));
                entry.Q1 = propertyMap.getProperty<double>("BetweennessBPQ1", to_string(0));
                entry.Q2 = propertyMap.getProperty<double>("BetweennessBPQ2", to_string(0));
                entry.Q3 = propertyMap.getProperty<double>("BetweennessBPQ3", to_string(0));
                entry.max = propertyMap.getProperty<double>("BetweennessBPMax", to_string(0));
            }
            ret.append("Mean: ").append(to_string<double>(entry.mean).c_str()).append("\n");
            ret.append("Min: ").append(to_string<double>(entry.min).c_str()).append("\n");
            ret.append("Q1: ").append(to_string<double>(entry.Q1).c_str()).append("\n");
            ret.append("Q2: ").append(to_string<double>(entry.Q2).c_str()).append("\n");
            ret.append("Q3: ").append(to_string<double>(entry.Q3).c_str()).append("\n");
            ret.append("Max: ").append(to_string<double>(entry.max).c_str()).append("\n");
            // coefficient = propertyMap.getProperty<double>("clusteringCoeficientForVertex", key);
            // ret.append("Clustering coefficient for vertex ").append(vertexId);
            // ret.append(" is: ").append(to_string<double>(coefficient).c_str()).append(".\n");
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
    QString vertexId = "2";
    QString ret;
    unsigned int vertexShellIndex;
    if (!vertexId.isEmpty())
    {
        this->computeShellIndex();
        if (vertexId.toStdString() == "all")
        {
            try
            {
                ret.append("Looking for all the vertexes starting from 1\n");
                unsigned int i = 1;
                while (true)
                {
                    vertexShellIndex = propertyMap.getProperty<unsigned int>(
                        "shellIndex", to_string<unsigned int>(i));
                    ret.append("Shell index for vertex ").append(to_string<int>(i).c_str());
                    ret.append(" is: ")
                        .append(to_string<unsigned int>(vertexShellIndex).c_str())
                        .append(".\n");
                    i++;
                }
            }
            catch (const BadElementName& ex)
            {
                ui->textBrowser->append(ret);
            }
        }
        else
        {
            try
            {
                graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry;
                if (!propertyMap.containsProperty("ShellIndexBPMean", to_string(0)))
                {
                    entry = this->computeTotalBpEntriesShellIndex();
                    propertyMap.addProperty<double>("ShellIndexBPMean", to_string(0), entry.mean);
                    propertyMap.addProperty<double>("ShellIndexBPMin", to_string(0), entry.min);
                    propertyMap.addProperty<double>("ShellIndexBPQ1", to_string(0), entry.Q1);
                    propertyMap.addProperty<double>("ShellIndexBPQ2", to_string(0), entry.Q2);
                    propertyMap.addProperty<double>("ShellIndexBPQ3", to_string(0), entry.Q3);
                    propertyMap.addProperty<double>("ShellIndexBPMax", to_string(0), entry.max);
                }
                else
                {
                    ret.append("Data already calculated. \n");
                    entry.mean = propertyMap.getProperty<double>("ShellIndexBPMean", to_string(0));
                    entry.min = propertyMap.getProperty<double>("ShellIndexBPMin", to_string(0));
                    entry.Q1 = propertyMap.getProperty<double>("ShellIndexBPQ1", to_string(0));
                    entry.Q2 = propertyMap.getProperty<double>("ShellIndexBPQ2", to_string(0));
                    entry.Q3 = propertyMap.getProperty<double>("ShellIndexBPQ3", to_string(0));
                    entry.max = propertyMap.getProperty<double>("ShellIndexBPMax", to_string(0));
                }
                ret.append("Mean: ").append(to_string<double>(entry.mean).c_str()).append("\n");
                ret.append("Min: ").append(to_string<double>(entry.min).c_str()).append("\n");
                ret.append("Q1: ").append(to_string<double>(entry.Q1).c_str()).append("\n");
                ret.append("Q2: ").append(to_string<double>(entry.Q2).c_str()).append("\n");
                ret.append("Q3: ").append(to_string<double>(entry.Q3).c_str()).append("\n");
                ret.append("Max: ").append(to_string<double>(entry.max).c_str()).append("\n");
                // coefficient = propertyMap.getProperty<double>("clusteringCoeficientForVertex",
                // key);
                // ret.append("Clustering coefficient for vertex ").append(vertexId);
                // ret.append(" is: ").append(to_string<double>(coefficient).c_str()).append(".\n");
                ui->textBrowser->append(ret);
            }
            catch (const BadElementName& ex)
            {
                ret.append("Shell index: Vertex with id ")
                    .append(vertexId)
                    .append(" was not found.");
                ui->textBrowser->append(ret);
            }
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
                propertyMap.addProperty<unsigned int>(
                    "shellIndex", to_string<unsigned int>(it->first), it->second);
                ++it;
            }
            delete shellIndex;
        }
    }
}

void MainWindow::computeMaxClique(bool exact)
{
    if (!propertyMap.containsPropertySet(exact ? "maxCliqueExact" : "maxCliqueAprox"))
    {
        ui->textBrowser->append(exact ? "Exact Max clique" : "Aprox Max clique");
        ui->textBrowser->append(" has not been previously computed. Computing now.");
        if (this->weightedgraph)
        {
            ui->textBrowser->append("Max clique for weighted graphs is not supported.");
            return;
        }
        else
        {
            int timeout = 0;
            if (exact)
            {
                QString timeString = inputId("Time out (seconds):");
                if (!timeString.isEmpty())
                {
                    timeout = timeString.toInt();
                }
            }
            IMaxClique<Graph, Vertex>* maxClique =
                exact ? (IMaxClique<Graph, Vertex>*)factory->createExactMaxClique(graph, timeout)
                      : (IMaxClique<Graph, Vertex>*)factory->createMaxClique(graph);

            if (maxClique->finished())
            {
                id_list ids = maxClique->getMaxCliqueList();
                propertyMap.addProperty<int>(exact ? "maxCliqueExact" : "maxCliqueAprox", "size",
                                             ids.size());
                propertyMap.addProperty<id_list>(exact ? "maxCliqueExact" : "maxCliqueAprox",
                                                 "list", ids);

                DistributionIterator it = maxClique->distIterator();
                while (!it.end())
                {
                    propertyMap.addProperty<double>(
                        exact ? "maxCliqueExactDistribution" : "maxCliqueAproxDistribution",
                        to_string<int>(it->first), it->second);
                    it++;
                }
            }

            delete maxClique;
        }
    }
}

void MainWindow::computeBetweenness()
{
    if (!propertyMap.containsPropertySet("betweenness"))
    {
        ui->textBrowser->append("Betweenness has not been previously computed. Computing now.");
        IBetweenness<WeightedGraph, WeightedVertex>* wbetweenness;

        if (this->weightedgraph)
        {
            // ui->textBrowser->append("Betweenness for weighted graphs is not supported.");
            // return;
            printf("\nENTERING BETWEENNESS\n");
            IBetweenness<WeightedGraph, WeightedVertex>* betweenness =
                weightedFactory->createBetweenness(weightedGraph);
            IBetweenness<WeightedGraph, WeightedVertex>::BetweennessIterator it =
                betweenness->iterator();
            while (!it.end())
            {
                propertyMap.addProperty<double>("betweenness", to_string<unsigned int>(it->first),
                                                it->second);
                ++it;
            }
            delete betweenness;
        }
        else
        {
            IBetweenness<Graph, Vertex>* betweenness = factory->createBetweenness(graph);
            IBetweenness<Graph, Vertex>::BetweennessIterator it = betweenness->iterator();
            while (!it.end())
            {
                propertyMap.addProperty<double>("betweenness", to_string<unsigned int>(it->first),
                                                it->second);
                ++it;
            }
            delete betweenness;
        }
    }
}

void MainWindow::computeDegreeDistribution()
{
    if (!propertyMap.containsPropertySet("degreeDistribution") || this->digraph)
    {
        if (this->weightedgraph)
        {
            StrengthDistribution<WeightedGraph, WeightedVertex>* degreeDistribution =
                weightedFactory->createStrengthDistribution(weightedGraph);
            StrengthDistribution<WeightedGraph, WeightedVertex>::DistributionIterator it =
                degreeDistribution->iterator();
            while (!it.end())
            {
                propertyMap.addProperty<double>("degreeDistribution", to_string<double>(it->first),
                                                it->second);
                propertyMap.addProperty<double>("degreeDistributionProbability",
                                                to_string<double>(it->first),
                                                it->second / (double)weightedGraph.verticesCount());
                ++it;
            }
            delete degreeDistribution;
        }
        else if (this->digraph)
        {
            DirectedDegreeDistribution<DirectedGraph, DirectedVertex>* degreeDistribution =
                static_cast<DirectedDegreeDistribution<DirectedGraph, DirectedVertex>*>(
                    directedFactory->createDegreeDistribution(directedGraph));
            DirectedDegreeDistribution<DirectedGraph, DirectedVertex>::DistributionIterator it =
                degreeDistribution->inDegreeIterator();
            DirectedDegreeDistribution<DirectedGraph, DirectedVertex>::DistributionIterator it2 =
                degreeDistribution->outDegreeIterator();
            DirectedDegreeDistribution<DirectedGraph, DirectedVertex>::DistributionIterator it3 =
                degreeDistribution->inOutDegreeIterator();

            while (!it.end() || !it2.end() || !it3.end())
            {
                if (!it.end())
                {
                    propertyMap.addProperty<double>("inDegreeDistribution",
                                                    to_string<unsigned int>(it->first), it->second);
                    propertyMap.addProperty<double>(
                        "inDegreeDistributionProbability", to_string<unsigned int>(it->first),
                        it->second / (double)directedGraph.verticesCount());
                    ++it;
                }
                if (!it2.end())
                {
                    propertyMap.addProperty<double>(
                        "outDegreeDistribution", to_string<unsigned int>(it2->first), it2->second);
                    propertyMap.addProperty<double>(
                        "outDegreeDistributionProbability", to_string<unsigned int>(it2->first),
                        it2->second / (double)directedGraph.verticesCount());
                    ++it2;
                }
                if (!it3.end())
                {
                    propertyMap.addProperty<double>("inOutDegreeDistribution",
                                                    to_string<unsigned int>(it3->first),
                                                    it3->second);
                    propertyMap.addProperty<double>(
                        "inOutDegreeDistributionProbability", to_string<unsigned int>(it3->first),
                        it3->second / (double)directedGraph.verticesCount());
                    ++it3;
                }
            }
            delete degreeDistribution;
        }
        else
        {
            IDegreeDistribution<Graph, Vertex>* degreeDistribution =
                factory->createDegreeDistribution(graph);
            DegreeDistribution<Graph, Vertex>::DistributionIterator it =
                degreeDistribution->iterator();
            while (!it.end())
            {
                propertyMap.addProperty<double>("degreeDistribution",
                                                to_string<unsigned int>(it->first), it->second);
                propertyMap.addProperty<double>("degreeDistributionProbability",
                                                to_string<unsigned int>(it->first),
                                                it->second / (double)graph.verticesCount());
                ++it;
            }
            delete degreeDistribution;
        }
    }
}

void MainWindow::on_actionDegree_distribution_triggered()
{
    QString degree;
    QString outDegree;
    QString inDegree;
    if (!this->digraph)
    {
        degree = "1";
    }
    else
    {
        outDegree = inputId("OutDegree:");
        inDegree = inputId("InDegree:");
    }
    QString ret;
    unsigned int degreeAmount;
    if (!this->digraph && !degree.isEmpty())
    {
        if (!propertyMap.containsPropertySet("degreeDistribution"))
        {
            ui->textBrowser->append(
                "Degree distribution has not been previously computed. Computing now.");
            this->computeDegreeDistribution();
        }
        try
        {
            // degreeAmount = propertyMap.getProperty<unsigned int>("degreeDistribution",
            // degree.toStdString());
            // ret.append("Degree distribution for degree ").append(degree);
            // ret.append(" is: ").append(to_string<unsigned
            // int>(degreeAmount).c_str()).append(".\n");
            // ui->textBrowser->append(ret);
            graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry;
            if (!propertyMap.containsProperty("degreeDistributionBPMean", to_string(0)))
            {
                entry = this->computeTotalBpEntriesDegreeDistribution();
                propertyMap.addProperty<double>("degreeDistributionBPMean", to_string(0),
                                                entry.mean);
                propertyMap.addProperty<double>("degreeDistributionBPMin", to_string(0), entry.min);
                propertyMap.addProperty<double>("degreeDistributionBPQ1", to_string(0), entry.Q1);
                propertyMap.addProperty<double>("degreeDistributionBPQ2", to_string(0), entry.Q2);
                propertyMap.addProperty<double>("degreeDistributionBPQ3", to_string(0), entry.Q3);
                propertyMap.addProperty<double>("degreeDistributionBPMax", to_string(0), entry.max);
            }
            else
            {
                ret.append("Data already calculated. \n");
                entry.mean =
                    propertyMap.getProperty<double>("degreeDistributionBPMean", to_string(0));
                entry.min =
                    propertyMap.getProperty<double>("degreeDistributionBPMin", to_string(0));
                entry.Q1 = propertyMap.getProperty<double>("degreeDistributionBPQ1", to_string(0));
                entry.Q2 = propertyMap.getProperty<double>("degreeDistributionBPQ2", to_string(0));
                entry.Q3 = propertyMap.getProperty<double>("degreeDistributionBPQ3", to_string(0));
                entry.max =
                    propertyMap.getProperty<double>("degreeDistributionBPMax", to_string(0));
            }
            ret.append("Mean: ").append(to_string<double>(entry.mean).c_str()).append("\n");
            ret.append("Min: ").append(to_string<double>(entry.min).c_str()).append("\n");
            ret.append("Q1: ").append(to_string<double>(entry.Q1).c_str()).append("\n");
            ret.append("Q2: ").append(to_string<double>(entry.Q2).c_str()).append("\n");
            ret.append("Q3: ").append(to_string<double>(entry.Q3).c_str()).append("\n");
            ret.append("Max: ").append(to_string<double>(entry.max).c_str()).append("\n");
            // coefficient = propertyMap.getProperty<double>("clusteringCoeficientForVertex", key);
            // ret.append("Clustering coefficient for vertex ").append(vertexId);
            // ret.append(" is: ").append(to_string<double>(coefficient).c_str()).append(".\n");
            ui->textBrowser->append(ret);
        }
        catch (const BadElementName& ex)
        {
            ret.append("There are no vertices with degree ").append(degree).append(".\n");
            ui->textBrowser->append(ret);
        }
    }
    if (this->digraph && !outDegree.isEmpty())
    {
        if (!propertyMap.containsPropertySet("outDegreeDistribution"))
        {
            ui->textBrowser->append(
                "Degree distribution has not been previously computed. Computing now.");
            this->computeDegreeDistribution();
        }
        try
        {
            unsigned int outDegreeAmount = propertyMap.getProperty<unsigned int>(
                "outDegreeDistribution", outDegree.toStdString());
            ret.append("Out-Degree distribution for degree ").append(outDegree);
            ret.append(" is: ")
                .append(to_string<unsigned int>(outDegreeAmount).c_str())
                .append(".\n");
            ui->textBrowser->append(ret);
        }

        catch (const BadElementName& ex)
        {
            ret.append("There are no vertices with out-degree ").append(outDegree).append(".\n");
            ui->textBrowser->append(ret);
        }

        ret = "";
        try
        {
            unsigned int inDegreeAmount = propertyMap.getProperty<unsigned int>(
                "inDegreeDistribution", inDegree.toStdString());
            ret.append("In-Degree distribution for degree ").append(inDegree);
            ret.append(" is: ")
                .append(to_string<unsigned int>(inDegreeAmount).c_str())
                .append(".\n");
            ui->textBrowser->append(ret);
        }
        catch (const BadElementName& ex)
        {
            ret.append("There are no vertices with in-degree ").append(inDegree).append(".\n");
            ui->textBrowser->append(ret);
        }
    }
}

void MainWindow::on_actionDegree_distribution_plotting_triggered()
{
    bool ret, logBin = false;
    unsigned int bins = 25;
    ui->textBrowser->append("Plotting degree distribution...");

    if (!this->digraph || !propertyMap.containsPropertySet("degreeDistribution"))
    {
        ui->textBrowser->append(
            "Degree distribution has not been previously computed. Computing now.");
        this->computeDegreeDistribution();
    }
    if (LogBinningDialog() == QMessageBox::Yes)
    {
        logBin = true;
        QString inputN = inputId("bins:");
        if (!inputN.isEmpty())
        {
            bins = inputN.toInt();
        }
    }
    if (!this->digraph)
    {
        if (logBin)
        {
            ret = this->console->plotPropertySet(propertyMap.getPropertySet("degreeDistribution"),
                                                 "degreeDistribution", logBin, bins);
        }
        else
        {
            ret = this->console->plotPropertySet(
                propertyMap.getPropertySet("degreeDistributionProbability"), "degreeDistribution",
                logBin, bins);
        }
    }
    else
    {
        configureDirectedDirection();
        std::string key = "degreeDistribution";
        if (directed_in && directed_out)
        {
            key = "inOutDegreeDistribution";
        }
        else if (directed_in)
        {
            key = "inDegreeDistribution";
        }
        else if (directed_out)
        {
            key = "outDegreeDistribution";
        }

        if (logBin)
        {
            ret =
                this->console->plotPropertySet(propertyMap.getPropertySet(key), key, logBin, bins);
            this->console->show();
            this->activateWindow();
        }
        else
        {
            ret = this->console->plotPropertySet(propertyMap.getPropertySet(key + "Probability"),
                                                 key, logBin, bins);
            this->console->show();
            this->activateWindow();
        }
    }
    if (!ret)
        ui->textBrowser->append("An unexpected error has occured.\n");

    ui->textBrowser->append("Done\n");
}

void MainWindow::on_actionClustering_coefficient_triggered()
{
    QString vertexId = "2";
    QString ret;
    double coefficient;

    std::string directedPostfix = "d";
    if (directed_out)
    {
        directedPostfix += "p";
    }
    if (directed_in)
    {
        directedPostfix += "n";
    }

    if (!vertexId.isEmpty())
    {
        std::string key = vertexId.toStdString();
        if (this->digraph)
        {
            key += directedPostfix;
        }

        if (!propertyMap.containsProperty("clusteringCoeficientForVertex", key))
        {
            ui->textBrowser->append("Clustering coefficient has not been previously computed.");
            if (this->weightedgraph)
            {
                WeightedVertex* vertex;
                if ((vertex = weightedGraph.getVertexById(
                         from_string<unsigned int>(vertexId.toStdString()))) != NULL)
                {
                    IClusteringCoefficient<WeightedGraph, WeightedVertex>* clusteringCoefficient =
                        weightedFactory->createClusteringCoefficient();
                    propertyMap.addProperty<double>(
                        "clusteringCoeficientForVertex",
                        to_string<unsigned int>(vertex->getVertexId()),
                        clusteringCoefficient->vertexClusteringCoefficient(vertex));
                    delete clusteringCoefficient;
                }
            }
            else if (this->digraph)
            {
                DirectedVertex* vertex;
                if ((vertex = directedGraph.getVertexById(
                         from_string<unsigned int>(vertexId.toStdString()))) != NULL)
                {
                    IClusteringCoefficient<DirectedGraph, DirectedVertex>* clusteringCoefficient =
                        directedFactory->createClusteringCoefficient();
                    propertyMap.addProperty<double>(
                        "clusteringCoeficientForVertex",
                        to_string<unsigned int>(vertex->getVertexId()) + directedPostfix,
                        clusteringCoefficient->vertexClusteringCoefficient(vertex, directed_out,
                                                                           directed_in));
                    delete clusteringCoefficient;
                }
            }
            else
            {
                Vertex* vertex;
                if ((vertex = graph.getVertexById(
                         from_string<unsigned int>(vertexId.toStdString()))) != NULL)
                {
                    // IClusteringCoefficient<Graph, Vertex>* clusteringCoefficient =
                    // factory->createClusteringCoefficient();
                    // propertyMap.addProperty<double>("clusteringCoeficientForVertex",
                    // to_string<unsigned int>(vertex->getVertexId()),
                    // clusteringCoefficient->vertexClusteringCoefficient(vertex));
                    // delete clusteringCoefficient;
                }
            }
        }

        if ((graph.getVertexById(from_string<unsigned int>(vertexId.toStdString()))) != NULL ||
            (this->digraph &&
             directedGraph.getVertexById(from_string<unsigned int>(vertexId.toStdString())) !=
                 NULL))
        {
            try
            {
                // std::string key = vertexId.toStdString();
                // if (this->digraph) {
                //    key += directedPostfix;
                //}
                graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry;
                if (!propertyMap.containsProperty("ClusteringCoefficientBPMean", to_string(0)))
                {
                    this->computeDegreeDistribution();
                    entry = this->computeTotalBpEntries();
                    propertyMap.addProperty<double>("ClusteringCoefficientBPMean", to_string(0),
                                                    entry.mean);
                    propertyMap.addProperty<double>("ClusteringCoefficientBPMin", to_string(0),
                                                    entry.min);
                    propertyMap.addProperty<double>("ClusteringCoefficientBPQ1", to_string(0),
                                                    entry.Q1);
                    propertyMap.addProperty<double>("ClusteringCoefficientBPQ2", to_string(0),
                                                    entry.Q2);
                    propertyMap.addProperty<double>("ClusteringCoefficientBPQ3", to_string(0),
                                                    entry.Q3);
                    propertyMap.addProperty<double>("ClusteringCoefficientBPMax", to_string(0),
                                                    entry.max);
                    // while(1);
                }
                else
                {
                    ret.append("Data already calculated. \n");
                    entry.mean = propertyMap.getProperty<double>("ClusteringCoefficientBPMean",
                                                                 to_string(0));
                    entry.min =
                        propertyMap.getProperty<double>("ClusteringCoefficientBPMin", to_string(0));
                    entry.Q1 =
                        propertyMap.getProperty<double>("ClusteringCoefficientBPQ1", to_string(0));
                    entry.Q2 =
                        propertyMap.getProperty<double>("ClusteringCoefficientBPQ2", to_string(0));
                    entry.Q3 =
                        propertyMap.getProperty<double>("ClusteringCoefficientBPQ3", to_string(0));
                    entry.max =
                        propertyMap.getProperty<double>("ClusteringCoefficientBPMax", to_string(0));
                }
                // graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry =
                // this->computeTotalBpEntries();
                // while(1);
                ret.append("Mean: ").append(to_string<double>(entry.mean).c_str()).append("\n");
                ret.append("Min: ").append(to_string<double>(entry.min).c_str()).append("\n");
                ret.append("Q1: ").append(to_string<double>(entry.Q1).c_str()).append("\n");
                ret.append("Q2: ").append(to_string<double>(entry.Q2).c_str()).append("\n");
                ret.append("Q3: ").append(to_string<double>(entry.Q3).c_str()).append("\n");
                ret.append("Max: ").append(to_string<double>(entry.max).c_str()).append("\n");
                // coefficient = propertyMap.getProperty<double>("clusteringCoeficientForVertex",
                // key);
                // ret.append("Clustering coefficient for vertex ").append(vertexId);
                // ret.append(" is: ").append(to_string<double>(coefficient).c_str()).append(".\n");
                ui->textBrowser->append(ret);
            }
            catch (const BadElementName& ex)
            {
                ret.append("There is no vertices with id ").append(vertexId).append(".\n");
                ui->textBrowser->append(ret);
            }
        }
        else
        {
            ret.append("There is no vertices with id ").append(vertexId).append(".\n");
            ui->textBrowser->append(ret);
        }
    }
}

void MainWindow::on_actionNearest_neighbors_degree_triggered()
{
    QString vertexId = "2";
    QString ret;
    double neighborsDegree;

    std::string directedPostfix = "d";
    if (directed_out)
    {
        directedPostfix += "p";
    }
    if (directed_in)
    {
        directedPostfix += "n";
    }

    if (!vertexId.isEmpty())
    {
        std::string key = vertexId.toStdString();
        if (this->digraph)
        {
            key += directedPostfix;
        }

        if (!propertyMap.containsProperty("nearestNeighborsDegreeForVertex", key))
        {
            ui->textBrowser->append(
                "Nearest neighbors degree has not been previously computed. Computing now.");
            if (this->weightedgraph)
            {
                WeightedVertex* vertex;
                if ((vertex = weightedGraph.getVertexById(
                         from_string<unsigned int>(vertexId.toStdString()))) != NULL)
                {
                    INearestNeighborsDegree<WeightedGraph, WeightedVertex>* nearestNeighborsDegree =
                        weightedFactory->createNearestNeighborsDegree();
                    propertyMap.addProperty<double>(
                        "nearestNeighborsDegreeForVertex",
                        to_string<unsigned int>(vertex->getVertexId()),
                        nearestNeighborsDegree->meanDegreeForVertex(vertex));
                    delete nearestNeighborsDegree;
                }
            }
            else if (this->digraph)
            {
                DirectedVertex* vertex;
                if ((vertex = directedGraph.getVertexById(
                         from_string<unsigned int>(vertexId.toStdString()))) != NULL)
                {
                    INearestNeighborsDegree<DirectedGraph, DirectedVertex>* nearestNeighborsDegree =
                        directedFactory->createNearestNeighborsDegree();
                    propertyMap.addProperty<double>(
                        "nearestNeighborsDegreeForVertex",
                        to_string<unsigned int>(vertex->getVertexId()) + directedPostfix,
                        nearestNeighborsDegree->meanDegreeForVertex(vertex, directed_out,
                                                                    directed_in));
                    delete nearestNeighborsDegree;
                }
            }
            else
            {
                Vertex* vertex;
                if ((vertex = graph.getVertexById(
                         from_string<unsigned int>(vertexId.toStdString()))) != NULL)
                {
                    // INearestNeighborsDegree<Graph, Vertex>* nearestNeighborsDegree =
                    // factory->createNearestNeighborsDegree();
                    // propertyMap.addProperty<double>("nearestNeighborsDegreeForVertex",
                    // to_string<unsigned int>(vertex->getVertexId()),
                    // nearestNeighborsDegree->meanDegreeForVertex(vertex));
                    // delete nearestNeighborsDegree;
                }
            }
        }

        if ((graph.getVertexById(from_string<unsigned int>(vertexId.toStdString()))) != NULL ||
            (this->digraph &&
             directedGraph.getVertexById(from_string<unsigned int>(vertexId.toStdString())) !=
                 NULL))
        {
            try
            {
                // std::string key = vertexId.toStdString();
                // if (this->digraph) {
                //    key += directedPostfix;
                //}
                graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry;
                if (!propertyMap.containsProperty("KnnBPMean", to_string(0)))
                {
                    this->computeDegreeDistribution();
                    entry = this->computeTotalBpEntriesKnn();
                    propertyMap.addProperty<double>("KnnBPMean", to_string(0), entry.mean);
                    propertyMap.addProperty<double>("KnnBPMin", to_string(0), entry.min);
                    propertyMap.addProperty<double>("KnnBPQ1", to_string(0), entry.Q1);
                    propertyMap.addProperty<double>("KnnBPQ2", to_string(0), entry.Q2);
                    propertyMap.addProperty<double>("KnnBPQ3", to_string(0), entry.Q3);
                    propertyMap.addProperty<double>("KnnBPMax", to_string(0), entry.max);
                }
                else
                {
                    ret.append("Data already calculated. \n");
                    entry.mean = propertyMap.getProperty<double>("KnnBPMean", to_string(0));
                    entry.min = propertyMap.getProperty<double>("KnnBPMin", to_string(0));
                    entry.Q1 = propertyMap.getProperty<double>("KnnBPQ1", to_string(0));
                    entry.Q2 = propertyMap.getProperty<double>("KnnBPQ2", to_string(0));
                    entry.Q3 = propertyMap.getProperty<double>("KnnBPQ3", to_string(0));
                    entry.max = propertyMap.getProperty<double>("KnnBPMax", to_string(0));
                }
                ret.append("Mean: ").append(to_string<double>(entry.mean).c_str()).append("\n");
                ret.append("Min: ").append(to_string<double>(entry.min).c_str()).append("\n");
                ret.append("Q1: ").append(to_string<double>(entry.Q1).c_str()).append("\n");
                ret.append("Q2: ").append(to_string<double>(entry.Q2).c_str()).append("\n");
                ret.append("Q3: ").append(to_string<double>(entry.Q3).c_str()).append("\n");
                ret.append("Max: ").append(to_string<double>(entry.max).c_str()).append("\n");
                // neighborsDegree =
                // propertyMap.getProperty<double>("nearestNeighborsDegreeForVertex", key);
                // ret.append("Nearest neighbors degree for vertex ").append(vertexId);
                // ret.append(" is:
                // ").append(to_string<double>(neighborsDegree).c_str()).append(".\n");
                ui->textBrowser->append(ret);
            }
            catch (const BadElementName& ex)
            {
                ret.append("There is no vertices with id ").append(vertexId).append(".\n");
                ui->textBrowser->append(ret);
            }
        }
        else
        {
            ret.append("There is no vertices with id ").append(vertexId).append(".\n");
            ui->textBrowser->append(ret);
        }
    }
}

void MainWindow::on_actionClustering_Coefficient_vs_Degree_triggered()
{
    configureDirectedDirection();

    int ret = 0;
    ui->textBrowser->append("Plotting Clustering Coefficient vs Degree...");
    double cc = 0;

    std::string directedPostfix;
    if (directed_out)
    {
        directedPostfix += "O";
    }
    if (directed_in)
    {
        directedPostfix += "I";
    }

    std::string ccKey = "clusteringCoeficientForDegree" + directedPostfix;

    if (!propertyMap.containsPropertySet(ccKey))
    {
        ui->textBrowser->append("Some data missing.\n");
        this->computeDegreeDistribution();

        std::string key = "degreeDistribution";
        if (this->digraph)
        {
            if (directed_in && directed_out)
            {
                key = "inOutDegreeDistribution";
            }
            else if (directed_in)
            {
                key = "inDegreeDistribution";
            }
            else if (directed_out)
            {
                key = "outDegreeDistribution";
            }
        }

        VariantsSet& degrees = propertyMap.getPropertySet(key);
        VariantsSet::const_iterator it = degrees.begin();

        if (this->weightedgraph)
        {
            IClusteringCoefficient<WeightedGraph, WeightedVertex>* clusteringCoefficient =
                weightedFactory->createClusteringCoefficient();
            while (it != degrees.end())
            {
                cc = clusteringCoefficient->clusteringCoefficient(
                    weightedGraph, from_string<unsigned int>(it->first));
                propertyMap.addProperty<double>(ccKey, it->first, cc);
                ++it;
            }
            delete clusteringCoefficient;
        }
        else if (this->digraph)
        {
            IClusteringCoefficient<DirectedGraph, DirectedVertex>* clusteringCoefficient =
                directedFactory->createClusteringCoefficient();
            while (it != degrees.end())
            {
                cc = clusteringCoefficient->clusteringCoefficient(
                    directedGraph, from_string<unsigned int>(it->first), directed_out, directed_in);
                propertyMap.addProperty<double>(ccKey, it->first, cc);
                ++it;
            }
            delete clusteringCoefficient;
        }
        else
        {
            IClusteringCoefficient<Graph, Vertex>* clusteringCoefficient =
                factory->createClusteringCoefficient();
            while (it != degrees.end())
            {
                cc = clusteringCoefficient->clusteringCoefficient(
                    graph, from_string<unsigned int>(it->first));
                propertyMap.addProperty<double>(ccKey, it->first, cc);
                ++it;
            }
            delete clusteringCoefficient;
        }
    }
    ret = this->console->plotPropertySet(propertyMap.getPropertySet(ccKey), ccKey);
    this->console->show();
    this->activateWindow();
    if (!ret)
        ui->textBrowser->append("An unexpected error has occured.\n");
}

void MainWindow::on_actionNearest_Neighbors_Degree_vs_Degree_triggered()
{
    configureDirectedDirection();

    int ret = 0;
    ui->textBrowser->append("Plotting Nearest Neighbors Degree vs Degree...");
    double knn = 0;

    std::string directedPostfix;
    if (directed_out)
    {
        directedPostfix += "O";
    }
    if (directed_in)
    {
        directedPostfix += "I";
    }

    std::string nnKey = "nearestNeighborDegreeForDegree" + directedPostfix;

    if (!propertyMap.containsPropertySet(nnKey))
    {
        this->computeDegreeDistribution();

        std::string key = "degreeDistribution";
        if (this->digraph)
        {
            if (directed_in && directed_out)
            {
                key = "inOutDegreeDistribution";
            }
            else if (directed_in)
            {
                key = "inDegreeDistribution";
            }
            else if (directed_out)
            {
                key = "outDegreeDistribution";
            }
        }

        VariantsSet& degrees = propertyMap.getPropertySet(key);
        VariantsSet::const_iterator it = degrees.begin();

        if (this->weightedgraph)
        {
            INearestNeighborsDegree<WeightedGraph, WeightedVertex>* nearestNeighborDegree =
                weightedFactory->createNearestNeighborsDegree();
            while (it != degrees.end())
            {
                knn = nearestNeighborDegree->meanDegree(weightedGraph,
                                                        from_string<unsigned int>(it->first));
                propertyMap.addProperty<double>(nnKey, it->first, knn);
                ++it;
            }
            delete nearestNeighborDegree;
        }
        else if (this->digraph)
        {
            INearestNeighborsDegree<DirectedGraph, DirectedVertex>* nearestNeighborDegree =
                directedFactory->createNearestNeighborsDegree();
            while (it != degrees.end())
            {
                knn = nearestNeighborDegree->meanDegree(
                    directedGraph, from_string<unsigned int>(it->first), directed_out, directed_in);
                propertyMap.addProperty<double>(nnKey, it->first, knn);
                ++it;
            }
            delete nearestNeighborDegree;
        }
        else
        {
            INearestNeighborsDegree<Graph, Vertex>* nearestNeighborDegree =
                factory->createNearestNeighborsDegree();
            while (it != degrees.end())
            {
                knn =
                    nearestNeighborDegree->meanDegree(graph, from_string<unsigned int>(it->first));
                propertyMap.addProperty<double>(nnKey, it->first, knn);
                ++it;
            }
            delete nearestNeighborDegree;
        }
    }
    ret = this->console->plotPropertySet(propertyMap.getPropertySet(nnKey), nnKey);
    this->console->show();
    this->activateWindow();
    if (!ret)
        ui->textBrowser->append("An unexpected error has occured.\n");
}

// TODO check if shellIndexVsDegree has previously calculated and avoid unnecesary computation. If
// not calculated save in property map
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
        Vertex* v = this->weightedgraph ? weightedGraph.getVertexById(vertedId)
                                        : graph.getVertexById(vertedId);
        shellAuxAcum = shellIndexVsDegree.get_element<double>(to_string<unsigned int>(v->degree()));
        shellIndexVsDegree.insert<double>(
            to_string<unsigned int>(v->degree()),
            shellAuxAcum + from_string<unsigned int>(shellIt->second));

        ++shellIt;
    }

    shellVsDegreeIt = shellIndexVsDegree.begin();
    while (shellVsDegreeIt != shellIndexVsDegree.end())
    {
        std::string degree = shellVsDegreeIt->first;
        shellAuxAcum = from_string<double>(shellVsDegreeIt->second);
        degreeAmount = degreeDistribution.get_element<unsigned int>(degree);

        shellIndexVsDegree.insert<double>(degree, shellAuxAcum / (double)degreeAmount);
        ++shellVsDegreeIt;
    }
    shellVsDegreeIt = shellIndexVsDegree.begin();
    while (shellVsDegreeIt != shellIndexVsDegree.end())
    {
        propertyMap.addProperty<double>("shellIndexVsDegree", shellVsDegreeIt->first,
                                        from_string<double>(shellVsDegreeIt->second));
        ++shellVsDegreeIt;
    }

    ret = this->console->plotPropertySet(shellIndexVsDegree, "shellIndexVsDegree");
    this->console->show();
    this->activateWindow();
    if (!ret)
        ui->textBrowser->append("An unexpected error has occured.\n");
}

void MainWindow::on_actionBetweenness_vs_Degree_triggered()
{
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
    // initialize for each degree betweenness in zero.
    while (it != degreeDistribution.end())
    {
        betweennessVsDegree.insert<double>(it->first, 0.0);
        unsigned int degree = from_string<unsigned int>(it->first);
        unsigned int cant = from_string<unsigned int>(it->second);
        // TODO remove printf
        printf("\n degree %i - n %i\n", degree, cant);
        ++it;
    }

    while (betwennessIt != betweenness.end())
    {
        unsigned int vertedId = from_string<unsigned int>(betwennessIt->first);
        Vertex* v = this->weightedgraph ? weightedGraph.getVertexById(vertedId)
                                        : graph.getVertexById(vertedId);
        betweennessAuxAcum =
            betweennessVsDegree.get_element<double>(to_string<unsigned int>(v->degree()));
        // TODO remove printf
        // printf("vertex id: %i - betweenness: %f \n",vertedId, );
        betweennessVsDegree.insert<double>(
            to_string<unsigned int>(v->degree()),
            betweennessAuxAcum + from_string<double>(betwennessIt->second));

        ++betwennessIt;
    }

    betweennessVsDegreeIt = betweennessVsDegree.begin();
    while (betweennessVsDegreeIt != betweennessVsDegree.end())
    {
        std::string degree = betweennessVsDegreeIt->first;
        betweennessAuxAcum = from_string<double>(betweennessVsDegreeIt->second);
        degreeAmount = degreeDistribution.get_element<unsigned int>(degree);

        betweennessVsDegree.insert<double>(degree, betweennessAuxAcum / (double)degreeAmount);
        ++betweennessVsDegreeIt;
    }

    betweennessVsDegreeIt = betweennessVsDegree.begin();
    while (betweennessVsDegreeIt != betweennessVsDegree.end())
    {
        propertyMap.addProperty<double>("betweennessVsDegree", betweennessVsDegreeIt->first,
                                        from_string<double>(betweennessVsDegreeIt->second));
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
    configureDirectedDirection();

    std::string ret;
    ui->textBrowser->append("Exporting Nearest Neighbors Degree vs Degree...");
    ret = this->getSavePath();
    if (!ret.empty())
    {
        std::string directedPostfix;
        if (directed_out)
        {
            directedPostfix += "O";
        }
        if (directed_in)
        {
            directedPostfix += "I";
        }

        std::string nnKey = "nearestNeighborDegreeForDegree" + directedPostfix;

        if (propertyMap.containsPropertySet(nnKey))
        {
            grapherUtils.exportPropertySet(propertyMap.getPropertySet(nnKey), ret);
            ui->textBrowser->append("Done.");
        }
        else
            ui->textBrowser->append(
                "Nearest Neighbors Degree vs Degree has not been previously computed. Please go to "
                "Plot->Nearest Neighbors Degree vs Degree first.\n");
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
            ui->textBrowser->append(
                "Shell Index vs Degree has not been previously computed. Please go to Plot->Shell "
                "Index vs Degree first.");
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

void MainWindow::on_actionExportClustering_Coefficient_vs_Degree_triggered()
{
    configureDirectedDirection();

    std::string ret;
    ui->textBrowser->append("Exporting Clustering Coefficient vs Degree...");
    ret = this->getSavePath();
    if (!ret.empty())
    {
        std::string directedPostfix;
        if (directed_out)
        {
            directedPostfix += "O";
        }
        if (directed_in)
        {
            directedPostfix += "I";
        }

        std::string ccKey = "clusteringCoeficientForDegree" + directedPostfix;

        if (propertyMap.containsPropertySet(ccKey))
        {
            grapherUtils.exportPropertySet(propertyMap.getPropertySet(ccKey), ret);
            ui->textBrowser->append("Done.");
        }
        else
            ui->textBrowser->append(
                "Clustering Coefficient vs Degree has not been previously computed. Please go to "
                "Plot->Clustering Coefficient vs Degree first.\n");
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

void MainWindow::on_actionExportDegree_distribution_triggered()
{
    std::string ret;
    ui->textBrowser->append("Exporting Degree Distribution...");
    ret = this->getSavePath();
    std::string filename = ret;
    if (!ret.empty())
    {
        if (!this->digraph)
        {
            if (propertyMap.containsPropertySet("degreeDistributionProbability"))
            {
                grapherUtils.exportPropertySet(
                    propertyMap.getPropertySet("degreeDistributionProbability"), ret);
                ui->textBrowser->append("Done.");
            }
            else
                ui->textBrowser->append(
                    "Degree Distribution has not been previously computed. Please go to "
                    "Plot->Degree Distribution first.");
        }
        else
        {
            if (propertyMap.containsPropertySet("outDegreeDistributionProbability"))
            {
                grapherUtils.exportPropertySet(
                    propertyMap.getPropertySet("outDegreeDistributionProbability"),
                    ret.append("_out_degree"));
                std::string text = "Out-Degree Distribution was exported to ";
                text.append(ret.append("_out_degree"));
                ui->textBrowser->append(QString::fromUtf8(text.data(), text.size()));
                ui->textBrowser->append("Done.");
            }
            else
                ui->textBrowser->append(
                    "Degree Distribution has not been previously computed. Please go to "
                    "Plot->Degree Distribution first.");

            if (propertyMap.containsPropertySet("inDegreeDistributionProbability"))
            {
                grapherUtils.exportPropertySet(
                    propertyMap.getPropertySet("inDegreeDistributionProbability"),
                    filename.append("_in_degree"));
                std::string text = "In-Degree Distribution was exported to ";
                text.append(filename.append("_in_degree"));
                ui->textBrowser->append(QString::fromUtf8(text.data(), text.size()));
                ui->textBrowser->append("Done.");
            }
            else
                ui->textBrowser->append(
                    "Degree Distribution has not been previously computed. Please go to "
                    "Plot->Degree Distribution first.");
        }
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

void MainWindow::on_actionExportBetweenness_vs_Degree_triggered()
{
    std::string ret;
    ui->textBrowser->append("Exporting Betweenness vs Degree...");
    ret = this->getSavePath();
    if (!ret.empty())
    {
        if (propertyMap.containsPropertySet("betweennessVsDegree"))
        {
            grapherUtils.exportPropertySet(propertyMap.getPropertySet("betweennessVsDegree"), ret);
            ui->textBrowser->append("Done.");
        }
        else
            ui->textBrowser->append(
                "Betweenness vs Degree has not been previously computed. Please go to "
                "Plot->Betweenness vs Degree first.");
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

void MainWindow::on_actionExport_current_network_triggered()
{
    std::string ret;
    ui->textBrowser->append("Exporting current network...");
    ret = this->getSavePath();
    if (!ret.empty())
    {
        if (this->graphLoaded)
        {
            GraphWriter* graphWriter = new GraphWriter();
            if (this->weightedgraph)
                graphWriter->writeWeightedGraph(&(this->weightedGraph), ret);
            else
                graphWriter->writeGraph(&(this->graph), ret);

            delete graphWriter;
            ui->textBrowser->append("Done.");
        }
        else
            ui->textBrowser->append("No network is loaded.");
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
    QMessageBox msgBox(QMessageBox::Question, title, text, QMessageBox::Yes | QMessageBox::No,
                       this);
    msgBox.setDefaultButton(QMessageBox::Yes);
    return msgBox.exec();
}

int MainWindow::ChooseDigraphDegreeDialog()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Which degree would you like to use?"));
    QPushButton* pButtonYes = msgBox.addButton(tr("In"), QMessageBox::YesRole);
    msgBox.addButton(tr("Out"), QMessageBox::NoRole);
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
            buildGraphFactory(false, false);

            if (!inputN.isEmpty())
                n = inputN.toInt();
            if (!inputP.isEmpty())
                p = inputP.toFloat();

            graph = *(GraphGenerator::getInstance()->generateErdosRenyiGraph(n, p));

            QString text("Network created using Erdos-Renyi algorithm");
            text.append(
                "\nReference: P. Erdos y A. Renyi. On random graphs I. Publ. Math. (Debrecen), "
                "6:290-297, 1959");
            text.append("\nn: ");
            text.append(QString("%1").arg(n));
            text.append("\np: ");
            text.append(QString("%1").arg(p));
            text.append("\nAmount of vertices in the graph: ");
            unsigned int verticesCount = graph.verticesCount();
            text.append(QString("%1").arg(verticesCount));
            text.append(".\n");
            text.append("Done.\n");
            ui->textBrowser->append(text);
        }
        catch (const BadElementName& ex)
        {
            ret.append("Error ").append(".\n");
            ui->textBrowser->append(ret);
        }
    }
    else
    {
        ui->textBrowser->append(
            "Action canceled: Only one network can be loaded at any given time.\n");
    }
}

void MainWindow::on_actionNewHiperbolic_triggered()
{
    if (!this->graphLoaded)
    {
        srand(time(NULL));
        QString inputN = inputId("n:");
        QString inputA = inputId("a:");
        QString inputD = inputId("deg:");
        QString ret;

        unsigned int n = 10000;
        float a = 0.75;
        float deg = 0.0014;

        try
        {
            this->onNetworkLoad(false, false, false);
            buildGraphFactory(false, false);

            if (!inputN.isEmpty())
                n = inputN.toInt();
            if (!inputA.isEmpty())
                a = inputA.toFloat();
            if (!inputD.isEmpty())
                deg = inputD.toFloat();
            QString text("Creating a network using a Papadopoulos hyperbolic graph algorithm...");
            text.append("\nexpected avg node deg: ");
            text.append(
                QString("%1").arg(GraphGenerator::getInstance()->getExpectedAvgNodeDeg(n, a, deg)));

            graph = *(GraphGenerator::getInstance()->generateHiperbolicGraph(n, a, deg));

            text.append("\nn: ");
            text.append(QString("%1").arg(n));
            text.append("\na: ");
            text.append(QString("%1").arg(a));
            text.append("\ndeg: ");
            text.append(QString("%1").arg(deg));

            text.append("\nAmount of vertices in the graph: ");
            unsigned int verticesCount = graph.verticesCount();
            text.append(QString("%1").arg(verticesCount));
            text.append(".\n");
            text.append("Done.\n");
            ui->textBrowser->append(text);
        }
        catch (const BadElementName& ex)
        {
            ret.append("Error ").append(".\n");
            ui->textBrowser->append(ret);
        }
    }
    else
    {
        ui->textBrowser->append(
            "Action canceled: Only one network can be loaded at any given time.\n");
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
            buildGraphFactory(false, false);

            if (!inputM_0.isEmpty())
                m_0 = inputM_0.toInt();
            if (!inputM.isEmpty())
                m = inputM.toInt();
            if (!inputN.isEmpty())
                n = inputN.toInt();
            m_0 = max(m_0, m);

            graph = *(GraphGenerator::getInstance()->generateBarabasiAlbertGraph(m_0, m, n));

            QString text("Network created using Barabasi-Albert algorithm");
            text.append(
                "\nReference: L. Barabasi y R. Albert. Emergence of scaling in random networks. "
                "Science, 286:509-512,1999.");
            text.append("\nm_0: ");
            text.append(QString("%1").arg(m_0));
            text.append("\nm: ");
            text.append(QString("%1").arg(m));
            text.append("\nn: ");
            text.append(QString("%1").arg(n));
            text.append("\nAmount of vertices in the graph: ");
            unsigned int verticesCount = graph.verticesCount();
            text.append(QString("%1").arg(verticesCount));
            text.append(".\n");
            text.append("Done.\n");
            ui->textBrowser->append(text);
        }
        catch (const BadElementName& ex)
        {
            ret.append("Error ").append(".\n");
            ui->textBrowser->append(ret);
        }
    }
    else
    {
        ui->textBrowser->append(
            "Action canceled: Only one network can be loaded at any given time.\n");
    }
}

void MainWindow::on_actionNewExtendedHOT_triggered()
{
    if (!this->graphLoaded)
    {
        srand(time(NULL));
        QString inputN = inputId("n:");
        QString inputM = inputId("m:");
        QString inputXI = inputId("xi:");
        QString inputQ = inputId("q:");
        QString inputT = inputId("T:");
        QString ret;

        // The default parameters are taken from the paper
        // (http://cnet.fi.uba.ar/ignacio.alvarez-hamelin/pdf/model_internet_jiah_ns.pdf)

        unsigned int m = 1;
        unsigned int n = 50;
        unsigned int q = 1;
        float xi = 0.03;
        float r = xi;
        unsigned int t = 1;

        try
        {
            this->onNetworkLoad(false, false, false);
            buildGraphFactory(false, false);

            if (!inputN.isEmpty())
                n = inputN.toInt();
            if (!inputM.isEmpty())
                m = inputM.toInt();
            if (!inputXI.isEmpty())
                xi = inputXI.toInt();
            if (!inputQ.isEmpty())
                q = inputQ.toInt();
            if (!inputT.isEmpty())
                t = inputT.toInt();

            graph = *(GraphGenerator::getInstance()->generateHotExtendedGraph(m, n, xi, q, r, t));

            QString text("Network created using HOT extended Algorithm");
            text.append(
                "\nReference: J. I. Alvarez-Hamelin y N. Schabanel. An Internet Graph Model Based "
                "on Trade-Off Optimization.Eur. Phys.J.B, special issue on 'Applications of "
                "networks', 38(2):231-237, march II2004.");
            text.append("\nn: ");
            text.append(QString("%1").arg(n));
            text.append("\nm: ");
            text.append(QString("%1").arg(m));
            text.append("\nxi: ");
            text.append(QString("%1").arg(xi));
            text.append("\nr: ");
            text.append(QString("%1").arg(r));
            text.append("\nq: ");
            text.append(QString("%1").arg(q));
            text.append("\nT: ");
            text.append(QString("%1").arg(t));
            text.append("\nVertex count:");
            unsigned int verticesCount = graph.verticesCount();
            text.append(QString("%1").arg(verticesCount));
            text.append(".\n");
            text.append("Done.\n");
            ui->textBrowser->append(text);
        }
        catch (const BadElementName& ex)
        {
            ret.append("Error ").append(".\n");
            ui->textBrowser->append(ret);
        }
    }
    else
    {
        ui->textBrowser->append(
            "Action canceled: Only one network can be loaded at any given time.\n");
    }
}

void MainWindow::on_actionNewMolloyReed_triggered()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setDirectory(QDir::homePath());
    QStringList selectedFiles;

    if (!this->graphLoaded)
    {
        srand(time(NULL));
        QString ret;
        if (fileDialog.exec())
        {
            try
            {
                this->onNetworkLoad(false, false, false);
                buildGraphFactory(false, false);

                selectedFiles = fileDialog.selectedFiles();
                string path = selectedFiles[0].toStdString();
                graph = *(GraphGenerator::getInstance()->generateMolloyReedGraph(path));

                QString text("Network created using Molloy-Reed algorithm using the file: ");
                text.append(selectedFiles[0]);
                text.append(
                    "\nReference: M. Molloy and B. Reed, A critical point for random graphs with a "
                    "given degree sequence,Random Struct. Algorithms, 6 (1995), 161-179.");
                text.append(
                    "\nReference: M. Molloy and B. Reed, The size of the giant component of a "
                    "random graph with a given degree distribution, Combinatorics, Probab. "
                    "Comput., 7factory (1998), 295-305.");
                text.append("\nAmount of vertices in the graph: ");
                unsigned int verticesCount = graph.verticesCount();
                text.append(QString("%1").arg(verticesCount));
                text.append(".\n");
                text.append("Done.\n");
                ui->textBrowser->append(text);
            }
            catch (const FileNotFoundException& ex)
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
        }
    }
    else
    {
        ui->textBrowser->append(
            "Action canceled: Only one network can be loaded at any given time.\n");
    }
}
void MainWindow::computeCumulativeDegreeDistribution()
{
    configureDirectedDirection();
    this->computeDegreeDistribution();

    std::string key = "degreeDistribution";
    if (this->digraph)
    {
        if (directed_in && directed_out)
        {
            key = "inOutDegreeDistribution";
        }
        else if (directed_in)
        {
            key = "inDegreeDistribution";
        }
        else if (directed_out)
        {
            key = "outDegreeDistribution";
        }
    }

    VariantsSet& degrees = propertyMap.getPropertySet(key);
    VariantsSet::const_iterator transferIt = degrees.begin();

    std::map<unsigned int, double> myMap;
    double total = 0;
    while (transferIt != degrees.end())
    {
        double degree = from_string<double>(transferIt->second);
        myMap[from_string<unsigned int>(transferIt->first)] = degree;
        total += degree;
        ++transferIt;
    }

    std::map<unsigned int, double>::const_iterator it = myMap.begin();
    double cumulate = 0;
    while (it != myMap.end())
    {
        cumulate += it->second;
        propertyMap.addProperty<double>("cumulativeDegreeDistribution",
                                        to_string<unsigned int>(it->first), cumulate);
        propertyMap.addProperty<double>("cumulativeDegreeDistributionProbability",
                                        to_string<unsigned int>(it->first), cumulate / total);

        ++it;
    }
}

void MainWindow::on_actionCumulativeDegree_distribution_plotting_triggered()
{
    bool ret = false;
    ui->textBrowser->append("Plotting Cumulative Degree Distribution...");
    if (!propertyMap.containsPropertySet("cumulativeDegreeDistribution") || this->digraph)
    {
        ui->textBrowser->append(
            "Cumulative Degree distribution has not been previously computed. Computing now.");
        this->computeCumulativeDegreeDistribution();
    }

    ui->textBrowser->append("Done\n");
    ret = this->console->plotPropertySet(
        propertyMap.getPropertySet("cumulativeDegreeDistributionProbability"),
        "cumulativeDegreeDistribution");
    this->console->show();
    this->activateWindow();
    if (!ret)
        ui->textBrowser->append("An unexpected error has occured.\n");
}

void MainWindow::on_actionExportCumulativeDegree_distribution_triggered()
{
    std::string ret;
    ui->textBrowser->append("Exporting Cumulative Degree Distribution...");
    ret = this->getSavePath();
    std::string filename = ret;
    if (!ret.empty())
    {
        if (propertyMap.containsPropertySet("cumulativeDegreeDistributionProbability"))
        {
            grapherUtils.exportPropertySet(
                propertyMap.getPropertySet("cumulativeDegreeDistributionProbability"), ret);
            ui->textBrowser->append("Done.");
        }
        else
        {
            ui->textBrowser->append(
                "Cumulative Degree Distribution has not been previously computed. Please go to "
                "Plot->Cumulative Degree Distribution first.");
        }
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

// Calculates for each node the 5 relevant values for a boxplot regarding Clustering Coefficient.
// Min, Max, Q1, Q2, Q3.
// If the user chooses to bin the data, the result will be a boxplot.
// For non-bined data, the result will be a line plot of Q1, Q2 and Q3
void MainWindow::on_actionBoxplotCC_triggered()
{
    bool ret, logBin = false;
    unsigned int bins = 10;

    ui->textBrowser->append("Initializing boxplot for Clustering Coefficient...");

    if (!propertyMap.containsPropertySet("degreeDistribution"))
    {
        ui->textBrowser->append(
            "Degree distribution has not been previously computed. Computing now.");
        this->computeDegreeDistribution();
    }

    if (this->weightedgraph)
    {  // Weighted
        printf("Function not available for weighted graphs. \n");
    }
    else
    {  // Unweighted

        std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry> bpentries =
            this->computeBpentries();

        if (LogBinningDialog() == QMessageBox::Yes)
        {
            logBin = true;
            QString inputN = inputId("bins:");
            if (!inputN.isEmpty())
            {
                bins = inputN.toInt();
            }
        }

        ret = this->console->boxplotCC(bpentries, logBin, bins);
        if (!ret)
            ui->textBrowser->append("An unexpected error has occured.\n");
    }

    ui->textBrowser->append("Done\n");
}

std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry>
MainWindow::computeBpentries()
{
    VariantsSet& degrees = propertyMap.getPropertySet("degreeDistribution");
    VariantsSet::const_iterator it = degrees.begin();
    IClusteringCoefficient<Graph, Vertex>* clusteringCoefficient =
        factory->createClusteringCoefficient();
    double cc = 0;
    std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry> bpentries;
    while (it != degrees.end())
    {
        // this calculates the Mean CC for a degree. I think it's unnecesary..
        cc = clusteringCoefficient->clusteringCoefficient(graph,
                                                          from_string<unsigned int>(it->first));

        // Starting here: instead of calling a function at ClusteringCoefficient.h, I've put
        // everything here because the other way was not working.

        Graph& g = graph;
        IClusteringCoefficient<Graph, Vertex>::Degree d = from_string<unsigned int>(it->first);
        Graph::VerticesIterator vit = g.verticesIterator();
        std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Coefficient> clusteringCoefs;

        while (!vit.end())
        {
            Vertex* v = *vit;

            if (v->degree() == d)
            {
                graphpp::IClusteringCoefficient<Graph, Vertex>::Coefficient c =
                    clusteringCoefficient->vertexClusteringCoefficient(v);
                clusteringCoefs.push_back(c);
            }

            ++vit;
        }
        // to here

        std::sort(clusteringCoefs.begin(), clusteringCoefs.end());
        graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry;
        if (clusteringCoefs.size() > 0)
        {
            entry.degree = d;
            entry.mean = cc;
            entry.min = clusteringCoefs.front();
            entry.max = clusteringCoefs.back();
            int const Q1 = clusteringCoefs.size() / 4;
            int const Q2 = clusteringCoefs.size() / 2;
            int const Q3 = clusteringCoefs.size() * (0.75);
            entry.Q1 = clusteringCoefs.at(Q1);
            entry.Q2 = clusteringCoefs.at(Q2);
            entry.Q3 = clusteringCoefs.at(Q3);
            for (int t = 0; t < clusteringCoefs.size(); t++)
            {
                entry.values.push_back(clusteringCoefs[t]);
            }
        }

        bpentries.push_back(entry);
        clusteringCoefs.clear();

        ++it;
    }

    std::sort(bpentries.begin(), bpentries.end());
    return bpentries;
}

graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry MainWindow::computeTotalBpEntries()
{
    Graph& g = graph;
    Graph::VerticesIterator vit = g.verticesIterator();
    std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Coefficient> clusteringCoefs;
    IClusteringCoefficient<Graph, Vertex>* clusteringCoefficient =
        factory->createClusteringCoefficient();
    double coefSums = 0.0;
    unsigned int count = 0;
    double oldCoef;
    int degree_exists = propertyMap.containsPropertySet("clusteringCoeficientForDegreeO") ? 1 : 0;

    while (!vit.end())
    {
        Vertex* v = *vit;
        if (!propertyMap.containsProperty("clusteringCoeficientForDegreeO",
                                          to_string<unsigned int>(v->degree())))
        {
            oldCoef = 0;
        }
        else
        {
            oldCoef = propertyMap.getProperty<double>("clusteringCoeficientForDegreeO",
                                                      to_string<unsigned int>(v->degree()));
        }
        graphpp::IClusteringCoefficient<Graph, Vertex>::Coefficient c =
            clusteringCoefficient->vertexClusteringCoefficient(v);
        propertyMap.addProperty<double>("clusteringCoeficientForVertex",
                                        to_string<unsigned int>(v->getVertexId()), c);
        if (degree_exists == 0)
            propertyMap.addProperty<double>(
                "clusteringCoeficientForDegreeO", to_string<unsigned int>(v->degree()),
                oldCoef + (c /
                           propertyMap.getProperty<double>("degreeDistribution",
                                                           to_string<unsigned int>(v->degree()))));
        clusteringCoefs.push_back(c);
        coefSums += c;
        ++vit;
        count++;
    }
    std::sort(clusteringCoefs.begin(), clusteringCoefs.end());
    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry;
    if (clusteringCoefs.size() > 0)
    {
        entry.mean = count == 0 ? 0 : coefSums / count;
        entry.min = clusteringCoefs.front();
        entry.max = clusteringCoefs.back();
        int const Q1 = clusteringCoefs.size() / 4;
        int const Q2 = clusteringCoefs.size() / 2;
        int const Q3 = clusteringCoefs.size() * (0.75);
        entry.Q1 = clusteringCoefs.at(Q1);
        entry.Q2 = clusteringCoefs.at(Q2);
        entry.Q3 = clusteringCoefs.at(Q3);
        for (int t = 0; t < clusteringCoefs.size(); t++)
        {
            entry.values.push_back(clusteringCoefs[t]);
        }
    }
    clusteringCoefs.clear();
    return entry;
}

graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry MainWindow::computeTotalBpEntriesKnn()
{
    Graph& g = graph;
    Graph::VerticesIterator vit = g.verticesIterator();
    std::vector<graphpp::INearestNeighborsDegree<Graph, Vertex>::MeanDegree> nnCoefs;
    INearestNeighborsDegree<Graph, Vertex>* nearestNeighborDegree =
        factory->createNearestNeighborsDegree();
    double coefSums = 0.0;
    unsigned int count = 0;

    double oldCoef;
    int degree_exists = propertyMap.containsPropertySet("nearestNeighborDegreeForDegreeO") ? 1 : 0;

    while (!vit.end())
    {
        Vertex* v = *vit;
        if (!propertyMap.containsProperty("nearestNeighborDegreeForDegreeO",
                                          to_string<unsigned int>(v->degree())))
        {
            oldCoef = 0;
        }
        else
        {
            oldCoef = propertyMap.getProperty<double>("nearestNeighborDegreeForDegreeO",
                                                      to_string<unsigned int>(v->degree()));
        }
        graphpp::INearestNeighborsDegree<Graph, Vertex>::MeanDegree c =
            nearestNeighborDegree->meanDegreeForVertex(v);
        propertyMap.addProperty<double>("nearestNeighborDegreeForVertex",
                                        to_string<unsigned int>(v->getVertexId()), c);
        if (degree_exists == 0)
            propertyMap.addProperty<double>(
                "nearestNeighborDegreeForDegreeO", to_string<unsigned int>(v->degree()),
                oldCoef + (c /
                           propertyMap.getProperty<double>("degreeDistribution",
                                                           to_string<unsigned int>(v->degree()))));
        nnCoefs.push_back(c);
        coefSums += c;
        ++vit;
        count++;
    }
    std::sort(nnCoefs.begin(), nnCoefs.end());
    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry;
    if (nnCoefs.size() > 0)
    {
        entry.mean = count == 0 ? 0 : coefSums / count;
        entry.min = nnCoefs.front();
        entry.max = nnCoefs.back();
        int const Q1 = nnCoefs.size() / 4;
        int const Q2 = nnCoefs.size() / 2;
        int const Q3 = nnCoefs.size() * (0.75);
        entry.Q1 = nnCoefs.at(Q1);
        entry.Q2 = nnCoefs.at(Q2);
        entry.Q3 = nnCoefs.at(Q3);
        for (int t = 0; t < nnCoefs.size(); t++)
        {
            entry.values.push_back(nnCoefs[t]);
        }
    }
    nnCoefs.clear();
    return entry;
}

graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry
MainWindow::computeTotalBpEntriesBetweenness()
{
    Graph& g = graph;
    Graph::VerticesIterator vit = g.verticesIterator();
    std::vector<double> bCoefs;
    IBetweenness<Graph, Vertex>* betweenness = factory->createBetweenness(g);
    double coefSums = 0.0;
    unsigned int count = 0;

    while (!vit.end())
    {
        Vertex* v = *vit;
        double c = propertyMap.getProperty<double>("betweenness",
                                                   to_string<unsigned int>(v->getVertexId()));
        bCoefs.push_back(c);
        coefSums += c;
        ++vit;
        count++;
    }
    std::sort(bCoefs.begin(), bCoefs.end());
    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry;
    if (bCoefs.size() > 0)
    {
        entry.mean = count == 0 ? 0 : coefSums / count;
        entry.min = bCoefs.front();
        entry.max = bCoefs.back();
        int const Q1 = bCoefs.size() / 4;
        int const Q2 = bCoefs.size() / 2;
        int const Q3 = bCoefs.size() * (0.75);
        entry.Q1 = bCoefs.at(Q1);
        entry.Q2 = bCoefs.at(Q2);
        entry.Q3 = bCoefs.at(Q3);
        for (int t = 0; t < bCoefs.size(); t++)
        {
            entry.values.push_back(bCoefs[t]);
        }
    }
    bCoefs.clear();
    return entry;
}

graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry
MainWindow::computeTotalBpEntriesDegreeDistribution()
{
    Graph& g = graph;
    Graph::VerticesIterator vit = g.verticesIterator();
    std::vector<int> bCoefs;
    //	IBetweenness<Graph, Vertex>* betweenness = factory->createBetweenness(g);
    double coefSums = 0.0;
    unsigned int count = 0;

    while (!vit.end())
    {
        Vertex* v = *vit;
        int c = v->degree();
        bCoefs.push_back(c);
        coefSums += c;
        ++vit;
        count++;
    }
    std::sort(bCoefs.begin(), bCoefs.end());
    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry;
    if (bCoefs.size() > 0)
    {
        entry.mean = count == 0 ? 0 : coefSums / count;
        entry.min = bCoefs.front();
        entry.max = bCoefs.back();
        int const Q1 = bCoefs.size() / 4;
        int const Q2 = bCoefs.size() / 2;
        int const Q3 = bCoefs.size() * (0.75);
        entry.Q1 = bCoefs.at(Q1);
        entry.Q2 = bCoefs.at(Q2);
        entry.Q3 = bCoefs.at(Q3);
        for (int t = 0; t < bCoefs.size(); t++)
        {
            entry.values.push_back(bCoefs[t]);
        }
    }
    bCoefs.clear();
    return entry;
}

graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry
MainWindow::computeTotalBpEntriesShellIndex()
{
    Graph& g = graph;
    Graph::VerticesIterator vit = g.verticesIterator();
    std::vector<double> bCoefs;
    IShellIndex<Graph, Vertex>* betweenness = factory->createShellIndex(g);
    double coefSums = 0.0;
    unsigned int count = 0;

    while (!vit.end())
    {
        Vertex* v = *vit;
        int c =
            propertyMap.getProperty<int>("shellIndex", to_string<unsigned int>(v->getVertexId()));
        bCoefs.push_back(c);
        coefSums += c;
        ++vit;
        count++;
    }
    std::sort(bCoefs.begin(), bCoefs.end());
    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry;
    if (bCoefs.size() > 0)
    {
        entry.mean = count == 0 ? 0 : coefSums / count;
        entry.min = bCoefs.front();
        entry.max = bCoefs.back();
        int const Q1 = bCoefs.size() / 4;
        int const Q2 = bCoefs.size() / 2;
        int const Q3 = bCoefs.size() * (0.75);
        entry.Q1 = bCoefs.at(Q1);
        entry.Q2 = bCoefs.at(Q2);
        entry.Q3 = bCoefs.at(Q3);
        for (int t = 0; t < bCoefs.size(); t++)
        {
            entry.values.push_back(bCoefs[t]);
        }
    }
    bCoefs.clear();
    return entry;
}

void MainWindow::computeClusteringCoefficient(QString vertexId)
{
    if (this->weightedgraph)
    {
        WeightedVertex* vertex;
        if ((vertex = weightedGraph.getVertexById(
                 from_string<unsigned int>(vertexId.toStdString()))) != NULL)
        {
            IClusteringCoefficient<WeightedGraph, WeightedVertex>* clusteringCoefficient =
                weightedFactory->createClusteringCoefficient();
            propertyMap.addProperty<double>(
                "clusteringCoeficientForVertex", to_string<unsigned int>(vertex->getVertexId()),
                clusteringCoefficient->vertexClusteringCoefficient(vertex));
            delete clusteringCoefficient;
        }
    }
    else
    {
        Vertex* vertex;
        if ((vertex = graph.getVertexById(from_string<unsigned int>(vertexId.toStdString()))) !=
            NULL)
        {
            IClusteringCoefficient<Graph, Vertex>* clusteringCoefficient =
                factory->createClusteringCoefficient();
            propertyMap.addProperty<double>(
                "clusteringCoeficientForVertex", to_string<unsigned int>(vertex->getVertexId()),
                clusteringCoefficient->vertexClusteringCoefficient(vertex));
            delete clusteringCoefficient;
        }
    }
}

void MainWindow::on_actionExportCCBoxplot_triggered()
{
    std::string ret;
    bool logBin = false;
    unsigned int bins = 10;
    ui->textBrowser->append("Exporting Clustering Coefficient boxplot data...");
    ret = this->getSavePath();
    if (!ret.empty())
    {
        if (!propertyMap.containsPropertySet("degreeDistribution"))
        {
            ui->textBrowser->append(
                "Degree distribution has not been previously computed. Computing now.");
            this->computeDegreeDistribution();
        }

        GrapherUtils utils;
        std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry> bpentries =
            this->computeBpentries();
        if (LogBinningDialog() == QMessageBox::Yes)
        {
            QString inputN = inputId("bins:");
            if (!inputN.isEmpty())
            {
                bins = inputN.toInt();
            }
            LogBinningPolicy policy;
            policy.transform(bpentries, bins);
            std::vector<double> d, m;
            std::vector<unsigned int> bin;
            for (unsigned int i = 0; i < bpentries.size(); ++i)
            {
                graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry =
                    bpentries.at(i);
                for (unsigned int w = 0; w < entry.values.size(); w++)
                {
                    d.push_back(entry.degree);
                    m.push_back(entry.values[w]);
                    bin.push_back(entry.bin);
                }
            }
            utils.exportThreeVectors(d, m, bin, ret);
            ui->textBrowser->append("Done exporting.");
        }
        else
        {
            std::vector<double> d, q1, q2, q3;
            for (unsigned int i = 0; i < bpentries.size(); ++i)
            {
                graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry =
                    bpentries.at(i);
                d.push_back(entry.degree);
                q1.push_back(entry.Q1);
                q2.push_back(entry.Q2);
                q3.push_back(entry.Q3);
            }
            utils.exportFourVectors(d, q1, q2, q3, ret);
            ui->textBrowser->append("Done exporting.");
        }
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

// Calculates for each node the 5 relevant values for a boxplot regarding Nearest Neighbors Degree.
// Min, Max, Q1, Q2, Q3.
// If the user chooses to bin the data, the result will be a boxplot.
// For non-bined data, the result will be a line plot of Q1, Q2 and Q3
void MainWindow::on_actionBoxplotNearestNeighborsDegree_triggered()
{
    bool ret, logBin = false;
    unsigned int bins = 10;

    ui->textBrowser->append("Initializing boxplot for Nearest Neighbors Degree...");

    if (!propertyMap.containsPropertySet("degreeDistribution"))
    {
        ui->textBrowser->append(
            "Degree distribution has not been previously computed. Computing now.");
        this->computeDegreeDistribution();
    }

    if (this->weightedgraph)
    {  // Weighted
        printf("Function not available for weighted graphs. \n");
    }
    else
    {  // Unweighted

        std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry> bpentries =
            this->computeBpentriesKnn();

        if (LogBinningDialog() == QMessageBox::Yes)
        {
            logBin = true;
            QString inputN = inputId("bins:");
            if (!inputN.isEmpty())
            {
                bins = inputN.toInt();
            }
        }

        ret = this->console->boxplotCC(bpentries, logBin, bins);
        if (!ret)
            ui->textBrowser->append("An unexpected error has occured.\n");
    }

    ui->textBrowser->append("Done\n");
}

std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry>
MainWindow::computeBpentriesKnn()
{
    VariantsSet& degrees = propertyMap.getPropertySet("degreeDistribution");
    VariantsSet::const_iterator it = degrees.begin();
    INearestNeighborsDegree<Graph, Vertex>* nearestNeighborDegree =
        factory->createNearestNeighborsDegree();
    double nnd = 0;
    std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry> bpentries;
    while (it != degrees.end())
    {
        // this calculates the Mean Knn for a degree. I think it's unnecesary..
        nnd = nearestNeighborDegree->meanDegree(graph, from_string<unsigned int>(it->first));

        // Starting here: instead of calling a function at NearestNeighborsDegree.h, I've put
        // everything here because the other way was not working.

        Graph& g = graph;
        INearestNeighborsDegree<Graph, Vertex>::Degree d = from_string<unsigned int>(it->first);
        Graph::VerticesIterator vit = g.verticesIterator();
        std::vector<graphpp::INearestNeighborsDegree<Graph, Vertex>::MeanDegree> nnCoefs;

        while (!vit.end())
        {
            Vertex* v = *vit;

            if (v->degree() == d)
            {
                graphpp::INearestNeighborsDegree<Graph, Vertex>::MeanDegree c =
                    nearestNeighborDegree->meanDegreeForVertex(v);
                nnCoefs.push_back(c);
            }

            ++vit;
        }
        // to here

        std::sort(nnCoefs.begin(), nnCoefs.end());
        // Ok, we are using 'Boxplotentry' from clustering coefficient,
        // but it's a common class.. We should put it in a common location.
        graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry;
        if (nnCoefs.size() > 0)
        {
            entry.degree = d;
            entry.mean = nnd;
            entry.min = nnCoefs.front();
            entry.max = nnCoefs.back();
            int const Q1 = nnCoefs.size() / 4;
            int const Q2 = nnCoefs.size() / 2;
            int const Q3 = nnCoefs.size() * (0.75);
            entry.Q1 = nnCoefs.at(Q1);
            entry.Q2 = nnCoefs.at(Q2);
            entry.Q3 = nnCoefs.at(Q3);
            for (int t = 0; t < nnCoefs.size(); t++)
            {
                entry.values.push_back(nnCoefs[t]);
            }
        }

        bpentries.push_back(entry);
        nnCoefs.clear();

        ++it;
    }

    std::sort(bpentries.begin(), bpentries.end());
    return bpentries;
}

void MainWindow::on_actionExportKnnBoxplot_triggered()
{
    std::string ret;
    bool logBin = false;
    unsigned int bins = 10;
    ui->textBrowser->append("Exporting Nearest Neighbors Degree boxplot data...");
    ret = this->getSavePath();
    if (!ret.empty())
    {
        if (!propertyMap.containsPropertySet("degreeDistribution"))
        {
            ui->textBrowser->append(
                "Degree distribution has not been previously computed. Computing now.");
            this->computeDegreeDistribution();
        }

        GrapherUtils utils;
        std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry> bpentries =
            this->computeBpentriesKnn();
        if (LogBinningDialog() == QMessageBox::Yes)
        {
            QString inputN = inputId("bins:");
            if (!inputN.isEmpty())
            {
                bins = inputN.toInt();
            }
            LogBinningPolicy policy;
            policy.transform(bpentries, bins);
            std::vector<double> d, m;
            std::vector<unsigned int> bin;
            for (int i = 0; i < bpentries.size(); ++i)
            {
                graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry =
                    bpentries.at(i);
                for (int w = 0; w < entry.values.size(); w++)
                {
                    d.push_back(entry.degree);
                    m.push_back(entry.values[w]);
                    bin.push_back(entry.bin);
                }
            }
            utils.exportThreeVectors(d, m, bin, ret);
            ui->textBrowser->append("Done exporting.");
        }
        else
        {
            std::vector<double> d, q1, q2, q3;
            for (int i = 0; i < bpentries.size(); ++i)
            {
                graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry entry =
                    bpentries.at(i);
                d.push_back(entry.degree);
                q1.push_back(entry.Q1);
                q2.push_back(entry.Q2);
                q3.push_back(entry.Q3);
            }
            utils.exportFourVectors(d, q1, q2, q3, ret);
            ui->textBrowser->append("Done exporting.");
        }
    }
    else
        ui->textBrowser->append("Action canceled by user.");
}

void MainWindow::on_actionAbout_triggered()
{
    QString title = "About ComplexNets++";
    QString body;

    body +=
        "This toolbox provides different tools to analyze complex networks, i.e., networks issues "
        "from complex systems or any graph in general.\n\n";
    body += "Project manager: Jose Ignacio Alvarez-Hamelin.\n\n";
    body +=
        "This toolbox is licensed under the Academic Free License 3.0, and it was developed in the "
        "Instituto Tecnologico de Buenos Aires (http://itba.edu.ar). The first version was "
        "released in 2012.\n\n";

    QMessageBox::about(this, title, body);
}

void MainWindow::configureDirectedDirection()
{
    if (!this->digraph)
    {
        return;
    }

    QStringList items;

    QString p = "Out";
    QString n = "In";
    QString pn = "In and Out";

    items << p << n << pn;
    bool ok;

    QString item = QInputDialog::getItem(this, "Directed Degree direction", "Direction:", items, 0,
                                         false, &ok);
    if (ok && !item.isEmpty())
    {
        if (item == pn)
        {
            directed_out = true;
            directed_in = true;
        }
        else if (item == n)
        {
            directed_in = true;
            directed_out = false;
        }
        else if (item == p)
        {
            directed_out = true;
            directed_in = false;
        }

        ui->textBrowser->append("Directed degree direction set to:");
        ui->textBrowser->append(QString("Out: ") + (directed_out ? "true" : "false"));
        ui->textBrowser->append(QString("In: ") + (directed_in ? "true" : "false"));
        ui->textBrowser->append("");
    }
}
