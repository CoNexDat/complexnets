// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../../ComplexNets/typedefs.h"
#include "../../ComplexNets/IGraphFactory.h"
#include "../../ComplexNets/AdjacencyListVertex.h"
#include "../../ComplexNets/AdjacencyListGraph.h"
#include "../../ComplexNets/WeightedGraphAspect.h"
#include "../../ComplexNets/WeightedVertexAspect.h"
#include "../../ComplexNets/PropertyMap.h"
#include "ComplexNetsGui/inc/GrapherUtils.h"
#include "ComplexNetsGui/inc/GnuplotConsole.h"
#include "../../ComplexNets/GraphWriter.h"

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

    graphpp::IGraphFactory<WeightedGraph, WeightedVertex>* weightedFactory;
    graphpp::IGraphFactory<Graph, Vertex>* factory;
    Graph graph;
    WeightedGraph weightedGraph;

    void computeDegreeDistribution();
    void computeShellIndex();
    void computeBetweenness();
    int LogBinningDialog();
    void readGraph(const std::string path);
    void buildGraphFactory(const bool isWeighted);
    void deleteGraphFactory();
    void onNetworkLoad(const bool weightedgraph, const bool digraph, const bool multigraph);
    void onNetworkUnload();
    std::string getSavePath() const;
    QString inputId(const std::string label);

private slots:
    void on_actionExportNearest_Neighbors_Degree_vs_Degree_triggered();
    void on_actionExportShell_Index_vs_Degree_triggered();
    void on_actionExportClustering_Coefficient_vs_Degree_triggered();
    void on_actionExportDegree_distribution_triggered();
    void on_actionExportBetweenness_vs_Degree_triggered();
    void on_actionShell_Index_vs_Degree_triggered();
    void on_actionBetweenness_vs_Degree_triggered();
    void on_actionNearest_Neighbors_Degree_vs_Degree_triggered();
    void on_actionClustering_Coefficient_vs_Degree_triggered();
    void on_actionNearest_neighbors_degree_triggered();
    void on_actionClustering_coefficient_triggered();
    void on_actionDegree_distribution_plotting_triggered();
    void on_actionDegree_distribution_triggered();
    void on_actionShell_index_triggered();
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
};

}

#endif
