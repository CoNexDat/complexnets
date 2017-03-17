// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 16th, 2015.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ComplexNets/AdjacencyListGraph.h"
#include "ComplexNets/AdjacencyListVertex.h"
#include "ComplexNets/DirectedGraphAspect.h"
#include "ComplexNets/DirectedVertexAspect.h"
#include "ComplexNets/GraphWriter.h"
#include "ComplexNets/IGraphFactory.h"
#include "ComplexNets/PropertyMap.h"
#include "ComplexNets/WeightedGraphAspect.h"
#include "ComplexNets/WeightedVertexAspect.h"
#include "ComplexNets/typedefs.h"
#include "ComplexNetsGui/inc/GnuplotConsole.h"
#include "ComplexNetsGui/inc/GrapherUtils.h"

namespace Ui
{
class MainWindow;
}

namespace ComplexNetsGui
{
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();
    void disableActions();

protected:
    void changeEvent(QEvent* e);

private:
    GnuplotConsole* console;
    GrapherUtils grapherUtils;
    bool weightedgraph;
    bool multigraph;
    bool digraph;
    bool graphLoaded;
    Ui::MainWindow* ui;
    graphpp::PropertyMap propertyMap;

    graphpp::IGraphFactory<WeightedGraph, WeightedVertex>* weightedFactory = nullptr;
    graphpp::IGraphFactory<Graph, Vertex>* factory = nullptr;
    graphpp::IGraphFactory<DirectedGraph, DirectedVertex>* directedFactory = nullptr;
    Graph graph;
    WeightedGraph weightedGraph;
    DirectedGraph directedGraph;

    bool directed_out = true;
    bool directed_in = false;

    void computeDegreeDistribution();
    void computeClusteringCoefficient(QString vertexId);
    void computeCumulativeDegreeDistribution();
    void computeShellIndex();
    void computeMaxClique(bool exact);
    void on_actionMaxClique_generic_triggered(bool);
    void on_action_maxClique_plotting_generic_triggered(bool exact);
    void on_actionExportMaxClique_distribution_generic_triggered(bool exact);
    std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry> computeBpentries();
    std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry> computeBpentriesKnn();
    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry computeTotalBpEntries();
    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry computeTotalBpEntriesKnn();
    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry computeTotalBpEntriesBetweenness();
    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry
    computeTotalBpEntriesDegreeDistribution();
    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry computeTotalBpEntriesShellIndex();

    //    void computeMaxCliqueExact();
    void computeBetweenness();
    int LogBinningDialog();
    int ChooseDigraphDegreeDialog();
    void readGraph(const std::string path);
    void buildGraphFactory(const bool isWeighted, const bool isDirected);
    void deleteGraphFactory();
    void onNetworkLoad(const bool weightedgraph, const bool digraph, const bool multigraph);
    void onNetworkUnload();
    std::string getSavePath() const;
    QString inputId(const std::string label);

private slots:
    void on_actionExportPowerLawDegreeDistribution_triggered();
    void on_actionExportNearest_Neighbors_Degree_vs_Degree_triggered();
    void on_actionExportShell_Index_vs_Degree_triggered();
    void on_actionExportClustering_Coefficient_vs_Degree_triggered();
    void on_actionExportDegree_distribution_triggered();
    void on_actionExportBetweenness_vs_Degree_triggered();
    void on_actionExportMaxClique_distribution_triggered();
    void on_actionExportMaxCliqueExact_distribution_triggered();
    void on_actionShell_Index_vs_Degree_triggered();
    void on_actionBetweenness_vs_Degree_triggered();
    void on_actionNearest_Neighbors_Degree_vs_Degree_triggered();
    void on_actionClustering_Coefficient_vs_Degree_triggered();
    void on_actionNearest_neighbors_degree_triggered();
    void on_actionClustering_coefficient_triggered();
    void on_actionDegree_distribution_plotting_triggered();
    void on_action_maxClique_plotting_triggered();
    void on_action_maxCliqueExact_plotting_triggered();
    void on_actionDegree_distribution_triggered();
    void on_actionShell_index_triggered();
    void on_actionMaxClique_triggered();
    void on_actionMaxCliqueExact_triggered();
    void on_actionBetweenness_triggered();
    void on_actionClose_current_network_triggered();
    void on_actionQuit_triggered();
    void on_actionOpen_triggered();
    void on_actionNewErdosRenyi_triggered();
    void on_actionNewHiperbolic_triggered();
    void on_actionNewBarabasiAlbert_triggered();
    void on_actionNewExtendedHOT_triggered();
    void on_actionNewMolloyReed_triggered();
    void on_actionExport_current_network_triggered();
    void configureDirectedDirection();
    void on_actionAbout_triggered();
    void on_actionCumulativeDegree_distribution_plotting_triggered();
    void on_actionExportCumulativeDegree_distribution_triggered();
    void on_actionBoxplotCC_triggered();
    void on_actionExportCCBoxplot_triggered();
    void on_actionBoxplotNearestNeighborsDegree_triggered();
    void on_actionExportKnnBoxplot_triggered();
};
}

#endif
