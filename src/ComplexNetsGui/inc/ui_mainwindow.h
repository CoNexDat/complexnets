/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionNewErdosRenyi;
    QAction *actionNewBarabasiAlbert;
    QAction *actionNewExtendedHOT;
    QAction *actionNewMolloyReed;
    QAction *actionNewHiperbolic;
    QAction *actionExport_current_network;
    QAction *actionClose_current_network;
    QAction *actionQuit;
    QAction *action_maxClique_plotting;
    QAction *action_maxCliqueExact_plotting;
    QAction *actionDegree_distribution_plotting;
    QAction *actionCumulativeDegree_distribution_plotting;
    QAction *actionAbout;
    QAction *actionMaxClique;
    QAction *actionMaxCliqueExact;
    QAction *actionBetweenness;
    QAction *actionClustering_coefficient;
    QAction *actionNearest_neighbors_degree;
    QAction *actionShell_index;
    QAction *actionDegree_distribution;
    QAction *actionClustering_Coefficient_vs_Degree;
    QAction *actionNearest_Neighbors_Degree_vs_Degree;
    QAction *actionShell_Index_vs_Degree;
    QAction *actionBetweenness_vs_Degree;
    QAction *actionExportBetweenness_vs_Degree;
    QAction *actionExportMaxClique_distribution;
    QAction *actionExportMaxCliqueExact_distribution;
    QAction *actionExportDegree_distribution;
    QAction *actionExportCumulativeDegree_distribution;
    QAction *actionExportClustering_Coefficient_vs_Degree;
    QAction *actionExportShell_Index_vs_Degree;
    QAction *actionExportCCBoxplot;
    QAction *actionExportKnnBoxplot;
    QAction *actionExportPowerLawDegreeDistribution;
    QAction *actionExportNearest_Neighbors_Degree_vs_Degree;
    QAction *actionBoxplotCC;
    QAction *actionBoxplotNearestNeighborsDegree;
    QAction *actionConfigure_Directed_Degree_sign;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuNode;
    QMenu *menuPlot;
    QMenu *menuHelp;
    QMenu *menu_Export;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 400);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionNewErdosRenyi = new QAction(MainWindow);
        actionNewErdosRenyi->setObjectName(QStringLiteral("actionNewErdosRenyi"));
        actionNewBarabasiAlbert = new QAction(MainWindow);
        actionNewBarabasiAlbert->setObjectName(QStringLiteral("actionNewBarabasiAlbert"));
        actionNewExtendedHOT = new QAction(MainWindow);
        actionNewExtendedHOT->setObjectName(QStringLiteral("actionNewExtendedHOT"));
        actionNewMolloyReed = new QAction(MainWindow);
        actionNewMolloyReed->setObjectName(QStringLiteral("actionNewMolloyReed"));
        actionNewHiperbolic = new QAction(MainWindow);
        actionNewHiperbolic->setObjectName(QStringLiteral("actionNewHiperbolic"));
        actionExport_current_network = new QAction(MainWindow);
        actionExport_current_network->setObjectName(QStringLiteral("actionExport_current_network"));
        actionClose_current_network = new QAction(MainWindow);
        actionClose_current_network->setObjectName(QStringLiteral("actionClose_current_network"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        action_maxClique_plotting = new QAction(MainWindow);
        action_maxClique_plotting->setObjectName(QStringLiteral("action_maxClique_plotting"));
        action_maxCliqueExact_plotting = new QAction(MainWindow);
        action_maxCliqueExact_plotting->setObjectName(QStringLiteral("action_maxCliqueExact_plotting"));
        actionDegree_distribution_plotting = new QAction(MainWindow);
        actionDegree_distribution_plotting->setObjectName(QStringLiteral("actionDegree_distribution_plotting"));
        actionCumulativeDegree_distribution_plotting = new QAction(MainWindow);
        actionCumulativeDegree_distribution_plotting->setObjectName(QStringLiteral("actionCumulativeDegree_distribution_plotting"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionMaxClique = new QAction(MainWindow);
        actionMaxClique->setObjectName(QStringLiteral("actionMaxClique"));
        actionMaxCliqueExact = new QAction(MainWindow);
        actionMaxCliqueExact->setObjectName(QStringLiteral("actionMaxCliqueExact"));
        actionBetweenness = new QAction(MainWindow);
        actionBetweenness->setObjectName(QStringLiteral("actionBetweenness"));
        actionClustering_coefficient = new QAction(MainWindow);
        actionClustering_coefficient->setObjectName(QStringLiteral("actionClustering_coefficient"));
        actionNearest_neighbors_degree = new QAction(MainWindow);
        actionNearest_neighbors_degree->setObjectName(QStringLiteral("actionNearest_neighbors_degree"));
        actionShell_index = new QAction(MainWindow);
        actionShell_index->setObjectName(QStringLiteral("actionShell_index"));
        actionDegree_distribution = new QAction(MainWindow);
        actionDegree_distribution->setObjectName(QStringLiteral("actionDegree_distribution"));
        actionClustering_Coefficient_vs_Degree = new QAction(MainWindow);
        actionClustering_Coefficient_vs_Degree->setObjectName(QStringLiteral("actionClustering_Coefficient_vs_Degree"));
        actionNearest_Neighbors_Degree_vs_Degree = new QAction(MainWindow);
        actionNearest_Neighbors_Degree_vs_Degree->setObjectName(QStringLiteral("actionNearest_Neighbors_Degree_vs_Degree"));
        actionShell_Index_vs_Degree = new QAction(MainWindow);
        actionShell_Index_vs_Degree->setObjectName(QStringLiteral("actionShell_Index_vs_Degree"));
        actionBetweenness_vs_Degree = new QAction(MainWindow);
        actionBetweenness_vs_Degree->setObjectName(QStringLiteral("actionBetweenness_vs_Degree"));
        actionExportBetweenness_vs_Degree = new QAction(MainWindow);
        actionExportBetweenness_vs_Degree->setObjectName(QStringLiteral("actionExportBetweenness_vs_Degree"));
        actionExportMaxClique_distribution = new QAction(MainWindow);
        actionExportMaxClique_distribution->setObjectName(QStringLiteral("actionExportMaxClique_distribution"));
        actionExportMaxCliqueExact_distribution = new QAction(MainWindow);
        actionExportMaxCliqueExact_distribution->setObjectName(QStringLiteral("actionExportMaxCliqueExact_distribution"));
        actionExportDegree_distribution = new QAction(MainWindow);
        actionExportDegree_distribution->setObjectName(QStringLiteral("actionExportDegree_distribution"));
        actionExportCumulativeDegree_distribution = new QAction(MainWindow);
        actionExportCumulativeDegree_distribution->setObjectName(QStringLiteral("actionExportCumulativeDegree_distribution"));
        actionExportClustering_Coefficient_vs_Degree = new QAction(MainWindow);
        actionExportClustering_Coefficient_vs_Degree->setObjectName(QStringLiteral("actionExportClustering_Coefficient_vs_Degree"));
        actionExportShell_Index_vs_Degree = new QAction(MainWindow);
        actionExportShell_Index_vs_Degree->setObjectName(QStringLiteral("actionExportShell_Index_vs_Degree"));
        actionExportCCBoxplot = new QAction(MainWindow);
        actionExportCCBoxplot->setObjectName(QStringLiteral("actionExportCCBoxplot"));
        actionExportKnnBoxplot = new QAction(MainWindow);
        actionExportKnnBoxplot->setObjectName(QStringLiteral("actionExportKnnBoxplot"));
        actionExportPowerLawDegreeDistribution = new QAction(MainWindow);
        actionExportPowerLawDegreeDistribution->setObjectName(QStringLiteral("actionExportPowerLawDegreeDistribution"));
        actionExportNearest_Neighbors_Degree_vs_Degree = new QAction(MainWindow);
        actionExportNearest_Neighbors_Degree_vs_Degree->setObjectName(QStringLiteral("actionExportNearest_Neighbors_Degree_vs_Degree"));
        actionBoxplotCC = new QAction(MainWindow);
        actionBoxplotCC->setObjectName(QStringLiteral("actionBoxplotCC"));
        actionBoxplotNearestNeighborsDegree = new QAction(MainWindow);
        actionBoxplotNearestNeighborsDegree->setObjectName(QStringLiteral("actionBoxplotNearestNeighborsDegree"));
        actionConfigure_Directed_Degree_sign = new QAction(MainWindow);
        actionConfigure_Directed_Degree_sign->setObjectName(QStringLiteral("actionConfigure_Directed_Degree_sign"));
        actionConfigure_Directed_Degree_sign->setEnabled(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuNode = new QMenu(menuBar);
        menuNode->setObjectName(QStringLiteral("menuNode"));
        menuPlot = new QMenu(menuBar);
        menuPlot->setObjectName(QStringLiteral("menuPlot"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menu_Export = new QMenu(menuBar);
        menu_Export->setObjectName(QStringLiteral("menu_Export"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuNode->menuAction());
        menuBar->addAction(menuPlot->menuAction());
        menuBar->addAction(menu_Export->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionNewErdosRenyi);
        menuFile->addAction(actionNewBarabasiAlbert);
        menuFile->addAction(actionNewExtendedHOT);
        menuFile->addAction(actionNewMolloyReed);
        menuFile->addAction(actionNewHiperbolic);
        menuFile->addSeparator();
        menuFile->addAction(actionExport_current_network);
        menuFile->addSeparator();
        menuFile->addAction(actionClose_current_network);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuNode->addAction(actionMaxClique);
        menuNode->addAction(actionMaxCliqueExact);
        menuNode->addAction(actionBetweenness);
        menuNode->addAction(actionDegree_distribution);
        menuNode->addAction(actionClustering_coefficient);
        menuNode->addAction(actionNearest_neighbors_degree);
        menuNode->addAction(actionShell_index);
        menuPlot->addAction(actionBetweenness_vs_Degree);
        menuPlot->addAction(actionDegree_distribution_plotting);
        menuPlot->addAction(actionCumulativeDegree_distribution_plotting);
        menuPlot->addAction(action_maxClique_plotting);
        menuPlot->addAction(action_maxCliqueExact_plotting);
        menuPlot->addAction(actionClustering_Coefficient_vs_Degree);
        menuPlot->addAction(actionNearest_Neighbors_Degree_vs_Degree);
        menuPlot->addAction(actionShell_Index_vs_Degree);
        menuPlot->addAction(actionBoxplotCC);
        menuPlot->addAction(actionBoxplotNearestNeighborsDegree);
        menuHelp->addAction(actionAbout);
        menu_Export->addAction(actionExportBetweenness_vs_Degree);
        menu_Export->addAction(actionExportDegree_distribution);
        menu_Export->addAction(actionExportCumulativeDegree_distribution);
        menu_Export->addAction(actionExportMaxClique_distribution);
        menu_Export->addAction(actionExportMaxCliqueExact_distribution);
        menu_Export->addAction(actionExportClustering_Coefficient_vs_Degree);
        menu_Export->addAction(actionExportNearest_Neighbors_Degree_vs_Degree);
        menu_Export->addAction(actionExportShell_Index_vs_Degree);
        menu_Export->addAction(actionExportCCBoxplot);
        menu_Export->addAction(actionExportKnnBoxplot);
        menu_Export->addAction(actionExportPowerLawDegreeDistribution);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ComplexNets++", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open new network...", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionNewErdosRenyi->setText(QApplication::translate("MainWindow", "New Erdos-Renyi graph...", Q_NULLPTR));
        actionNewBarabasiAlbert->setText(QApplication::translate("MainWindow", "New Barabasi-Albert graph...", Q_NULLPTR));
        actionNewExtendedHOT->setText(QApplication::translate("MainWindow", "New Extended HOT graph...", Q_NULLPTR));
        actionNewMolloyReed->setText(QApplication::translate("MainWindow", "New Molloy-Reed graph...", Q_NULLPTR));
        actionNewHiperbolic->setText(QApplication::translate("MainWindow", "New Hyperbolic graph...", Q_NULLPTR));
        actionExport_current_network->setText(QApplication::translate("MainWindow", "Export current network...", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionExport_current_network->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionClose_current_network->setText(QApplication::translate("MainWindow", "Close current network...", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionClose_current_network->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_maxClique_plotting->setText(QApplication::translate("MainWindow", "maxClique distribution", Q_NULLPTR));
        action_maxCliqueExact_plotting->setText(QApplication::translate("MainWindow", "maxCliqueExact distribution", Q_NULLPTR));
        actionDegree_distribution_plotting->setText(QApplication::translate("MainWindow", "Degree distribution", Q_NULLPTR));
        actionCumulativeDegree_distribution_plotting->setText(QApplication::translate("MainWindow", "Cumulative Degree distribution", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "About...", Q_NULLPTR));
        actionMaxClique->setText(QApplication::translate("MainWindow", "Max Clique Aprox...", Q_NULLPTR));
        actionMaxCliqueExact->setText(QApplication::translate("MainWindow", "Max Clique Exact...", Q_NULLPTR));
        actionBetweenness->setText(QApplication::translate("MainWindow", "Betweenness...", Q_NULLPTR));
        actionClustering_coefficient->setText(QApplication::translate("MainWindow", "Clustering coefficient...", Q_NULLPTR));
        actionNearest_neighbors_degree->setText(QApplication::translate("MainWindow", "Nearest neighbors degree...", Q_NULLPTR));
        actionShell_index->setText(QApplication::translate("MainWindow", "Shell index...", Q_NULLPTR));
        actionDegree_distribution->setText(QApplication::translate("MainWindow", "Degree distribution...", Q_NULLPTR));
        actionClustering_Coefficient_vs_Degree->setText(QApplication::translate("MainWindow", "Clustering Coefficient vs Degree", Q_NULLPTR));
        actionNearest_Neighbors_Degree_vs_Degree->setText(QApplication::translate("MainWindow", "Nearest Neighbors Degree vs Degree", Q_NULLPTR));
        actionShell_Index_vs_Degree->setText(QApplication::translate("MainWindow", "Shell Index vs Degree", Q_NULLPTR));
        actionBetweenness_vs_Degree->setText(QApplication::translate("MainWindow", "Betweenness vs Degree", Q_NULLPTR));
        actionExportBetweenness_vs_Degree->setText(QApplication::translate("MainWindow", "Betweenness vs Degree", Q_NULLPTR));
        actionExportMaxClique_distribution->setText(QApplication::translate("MainWindow", "maxClique distribution", Q_NULLPTR));
        actionExportMaxCliqueExact_distribution->setText(QApplication::translate("MainWindow", "maxCliqueExact distribution", Q_NULLPTR));
        actionExportDegree_distribution->setText(QApplication::translate("MainWindow", "Degree distribution", Q_NULLPTR));
        actionExportCumulativeDegree_distribution->setText(QApplication::translate("MainWindow", "Cumulative Degree distribution", Q_NULLPTR));
        actionExportClustering_Coefficient_vs_Degree->setText(QApplication::translate("MainWindow", "Clustering Coefficient vs Degree", Q_NULLPTR));
        actionExportShell_Index_vs_Degree->setText(QApplication::translate("MainWindow", "Shell Index vs Degree", Q_NULLPTR));
        actionExportCCBoxplot->setText(QApplication::translate("MainWindow", "Boxplot Clustering Coeficient", Q_NULLPTR));
        actionExportKnnBoxplot->setText(QApplication::translate("MainWindow", "Boxplot Nearest Neighbors Degree", Q_NULLPTR));
        actionExportPowerLawDegreeDistribution->setText(QApplication::translate("MainWindow", "Power Law Degree Distribution", Q_NULLPTR));
        actionExportNearest_Neighbors_Degree_vs_Degree->setText(QApplication::translate("MainWindow", "Nearest Neighbors Degree vs Degree", Q_NULLPTR));
        actionBoxplotCC->setText(QApplication::translate("MainWindow", "Boxplot Clustering Coeficient", Q_NULLPTR));
        actionBoxplotNearestNeighborsDegree->setText(QApplication::translate("MainWindow", "Boxplot Nearest Neighbor Degree", Q_NULLPTR));
        actionConfigure_Directed_Degree_sign->setText(QApplication::translate("MainWindow", "Configure Directed Degree direction...", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", Q_NULLPTR));
        menuNode->setTitle(QApplication::translate("MainWindow", "&Analysis", Q_NULLPTR));
        menuPlot->setTitle(QApplication::translate("MainWindow", "&Plot", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", Q_NULLPTR));
        menu_Export->setTitle(QApplication::translate("MainWindow", "&Export", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
