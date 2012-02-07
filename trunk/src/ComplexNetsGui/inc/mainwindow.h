#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ComplexNets/AdjacencyListVertex.h"
#include "ComplexNets/AdjacencyListGraph.h"
#include "ComplexNets/WeightedGraphAspect.h"
#include "ComplexNets/WeightedVertexAspect.h"

namespace Ui
{
class MainWindow;
}

namespace ComplexNetsGui
{

class MainWindow : public QMainWindow
{
    typedef graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex> WeigthedVertex;
    typedef graphpp::WeightedGraphAspect<WeigthedVertex, graphpp::AdjacencyListGraph<WeigthedVertex> > WeightedGraph;

    typedef graphpp::AdjacencyListVertex Vertex;
    typedef graphpp::AdjacencyListGraph<Vertex> IndexedGraph;

    Q_OBJECT
public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent* e);

private:
    Ui::MainWindow* ui;
    void onNetworkLoad();
    void onNetworkUnload();

private slots:
    void on_actionDegree_distribution_triggered();
    void on_actionClose_current_network_triggered();
    void on_actionQuit_triggered();
    void on_actionOpen_triggered();
};

}

#endif
