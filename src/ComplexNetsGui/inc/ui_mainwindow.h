/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

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
    QAction *actionExportNearest_Neighbors_Degree_vs_Degree;
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
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionNewErdosRenyi = new QAction(MainWindow);
        actionNewErdosRenyi->setObjectName(QString::fromUtf8("actionNewErdosRenyi"));
        actionNewBarabasiAlbert = new QAction(MainWindow);
        actionNewBarabasiAlbert->setObjectName(QString::fromUtf8("actionNewBarabasiAlbert"));
        actionNewExtendedHOT = new QAction(MainWindow);
        actionNewExtendedHOT->setObjectName(QString::fromUtf8("actionNewExtendedHOT"));
        actionNewMolloyReed = new QAction(MainWindow);
        actionNewMolloyReed->setObjectName(QString::fromUtf8("actionNewMolloyReed"));
        actionNewHiperbolic = new QAction(MainWindow);
        actionNewHiperbolic->setObjectName(QString::fromUtf8("actionNewHiperbolic"));
        actionExport_current_network = new QAction(MainWindow);
        actionExport_current_network->setObjectName(QString::fromUtf8("actionExport_current_network"));
        actionClose_current_network = new QAction(MainWindow);
        actionClose_current_network->setObjectName(QString::fromUtf8("actionClose_current_network"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        action_maxClique_plotting = new QAction(MainWindow);
        action_maxClique_plotting->setObjectName(QString::fromUtf8("action_maxClique_plotting"));
        action_maxCliqueExact_plotting = new QAction(MainWindow);
        action_maxCliqueExact_plotting->setObjectName(QString::fromUtf8("action_maxCliqueExact_plotting"));
        actionDegree_distribution_plotting = new QAction(MainWindow);
        actionDegree_distribution_plotting->setObjectName(QString::fromUtf8("actionDegree_distribution_plotting"));
        actionCumulativeDegree_distribution_plotting = new QAction(MainWindow);
        actionCumulativeDegree_distribution_plotting->setObjectName(QString::fromUtf8("actionCumulativeDegree_distribution_plotting"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionMaxClique = new QAction(MainWindow);
        actionMaxClique->setObjectName(QString::fromUtf8("actionMaxClique"));
        actionMaxCliqueExact = new QAction(MainWindow);
        actionMaxCliqueExact->setObjectName(QString::fromUtf8("actionMaxCliqueExact"));
        actionBetweenness = new QAction(MainWindow);
        actionBetweenness->setObjectName(QString::fromUtf8("actionBetweenness"));
        actionClustering_coefficient = new QAction(MainWindow);
        actionClustering_coefficient->setObjectName(QString::fromUtf8("actionClustering_coefficient"));
        actionNearest_neighbors_degree = new QAction(MainWindow);
        actionNearest_neighbors_degree->setObjectName(QString::fromUtf8("actionNearest_neighbors_degree"));
        actionShell_index = new QAction(MainWindow);
        actionShell_index->setObjectName(QString::fromUtf8("actionShell_index"));
        actionDegree_distribution = new QAction(MainWindow);
        actionDegree_distribution->setObjectName(QString::fromUtf8("actionDegree_distribution"));
        actionClustering_Coefficient_vs_Degree = new QAction(MainWindow);
        actionClustering_Coefficient_vs_Degree->setObjectName(QString::fromUtf8("actionClustering_Coefficient_vs_Degree"));
        actionNearest_Neighbors_Degree_vs_Degree = new QAction(MainWindow);
        actionNearest_Neighbors_Degree_vs_Degree->setObjectName(QString::fromUtf8("actionNearest_Neighbors_Degree_vs_Degree"));
        actionShell_Index_vs_Degree = new QAction(MainWindow);
        actionShell_Index_vs_Degree->setObjectName(QString::fromUtf8("actionShell_Index_vs_Degree"));
        actionBetweenness_vs_Degree = new QAction(MainWindow);
        actionBetweenness_vs_Degree->setObjectName(QString::fromUtf8("actionBetweenness_vs_Degree"));
        actionExportBetweenness_vs_Degree = new QAction(MainWindow);
        actionExportBetweenness_vs_Degree->setObjectName(QString::fromUtf8("actionExportBetweenness_vs_Degree"));
        actionExportMaxClique_distribution = new QAction(MainWindow);
        actionExportMaxClique_distribution->setObjectName(QString::fromUtf8("actionExportMaxClique_distribution"));
        actionExportMaxCliqueExact_distribution = new QAction(MainWindow);
        actionExportMaxCliqueExact_distribution->setObjectName(QString::fromUtf8("actionExportMaxCliqueExact_distribution"));
        actionExportDegree_distribution = new QAction(MainWindow);
        actionExportDegree_distribution->setObjectName(QString::fromUtf8("actionExportDegree_distribution"));
        actionExportCumulativeDegree_distribution = new QAction(MainWindow);
        actionExportCumulativeDegree_distribution->setObjectName(QString::fromUtf8("actionExportCumulativeDegree_distribution"));
        actionExportClustering_Coefficient_vs_Degree = new QAction(MainWindow);
        actionExportClustering_Coefficient_vs_Degree->setObjectName(QString::fromUtf8("actionExportClustering_Coefficient_vs_Degree"));
        actionExportShell_Index_vs_Degree = new QAction(MainWindow);
        actionExportShell_Index_vs_Degree->setObjectName(QString::fromUtf8("actionExportShell_Index_vs_Degree"));
        actionExportNearest_Neighbors_Degree_vs_Degree = new QAction(MainWindow);
        actionExportNearest_Neighbors_Degree_vs_Degree->setObjectName(QString::fromUtf8("actionExportNearest_Neighbors_Degree_vs_Degree"));
        actionConfigure_Directed_Degree_sign = new QAction(MainWindow);
        actionConfigure_Directed_Degree_sign->setObjectName(QString::fromUtf8("actionConfigure_Directed_Degree_sign"));
        actionConfigure_Directed_Degree_sign->setEnabled(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuNode = new QMenu(menuBar);
        menuNode->setObjectName(QString::fromUtf8("menuNode"));
        menuPlot = new QMenu(menuBar);
        menuPlot->setObjectName(QString::fromUtf8("menuPlot"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menu_Export = new QMenu(menuBar);
        menu_Export->setObjectName(QString::fromUtf8("menu_Export"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
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
        menuNode->addAction(actionConfigure_Directed_Degree_sign);
        menuPlot->addAction(actionBetweenness_vs_Degree);
        menuPlot->addAction(actionDegree_distribution_plotting);
        menuPlot->addAction(actionCumulativeDegree_distribution_plotting);
        menuPlot->addAction(action_maxClique_plotting);
        menuPlot->addAction(action_maxCliqueExact_plotting);
        menuPlot->addAction(actionClustering_Coefficient_vs_Degree);
        menuPlot->addAction(actionNearest_Neighbors_Degree_vs_Degree);
        menuPlot->addAction(actionShell_Index_vs_Degree);
        menuHelp->addAction(actionAbout);
        menu_Export->addAction(actionExportBetweenness_vs_Degree);
        menu_Export->addAction(actionExportDegree_distribution);
        menu_Export->addAction(actionExportCumulativeDegree_distribution);
        menu_Export->addAction(actionExportMaxClique_distribution);
        menu_Export->addAction(actionExportMaxCliqueExact_distribution);
        menu_Export->addAction(actionExportClustering_Coefficient_vs_Degree);
        menu_Export->addAction(actionExportNearest_Neighbors_Degree_vs_Degree);
        menu_Export->addAction(actionExportShell_Index_vs_Degree);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ComplexNets++", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open new network...", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionNewErdosRenyi->setText(QApplication::translate("MainWindow", "New Erdos-Renyi graph...", 0, QApplication::UnicodeUTF8));
        actionNewBarabasiAlbert->setText(QApplication::translate("MainWindow", "New Barabasi-Albert graph...", 0, QApplication::UnicodeUTF8));
        actionNewExtendedHOT->setText(QApplication::translate("MainWindow", "New Extended HOT graph...", 0, QApplication::UnicodeUTF8));
        actionNewMolloyReed->setText(QApplication::translate("MainWindow", "New Molloy-Reed graph...", 0, QApplication::UnicodeUTF8));
        actionNewHiperbolic->setText(QApplication::translate("MainWindow", "New Hyperbolic graph...", 0, QApplication::UnicodeUTF8));
        actionExport_current_network->setText(QApplication::translate("MainWindow", "Export current network...", 0, QApplication::UnicodeUTF8));
        actionClose_current_network->setText(QApplication::translate("MainWindow", "Close current network...", 0, QApplication::UnicodeUTF8));
        actionClose_current_network->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        action_maxClique_plotting->setText(QApplication::translate("MainWindow", "maxClique distribution", 0, QApplication::UnicodeUTF8));
        action_maxCliqueExact_plotting->setText(QApplication::translate("MainWindow", "maxCliqueExact distribution", 0, QApplication::UnicodeUTF8));
        actionDegree_distribution_plotting->setText(QApplication::translate("MainWindow", "Degree distribution", 0, QApplication::UnicodeUTF8));
        actionCumulativeDegree_distribution_plotting->setText(QApplication::translate("MainWindow", "Cumulative Degree distribution", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About...", 0, QApplication::UnicodeUTF8));
        actionMaxClique->setText(QApplication::translate("MainWindow", "Max Clique Aprox...", 0, QApplication::UnicodeUTF8));
        actionMaxCliqueExact->setText(QApplication::translate("MainWindow", "Max Clique Exact...", 0, QApplication::UnicodeUTF8));
        actionBetweenness->setText(QApplication::translate("MainWindow", "Betweenness...", 0, QApplication::UnicodeUTF8));
        actionClustering_coefficient->setText(QApplication::translate("MainWindow", "Clustering coefficient...", 0, QApplication::UnicodeUTF8));
        actionNearest_neighbors_degree->setText(QApplication::translate("MainWindow", "Nearest neighbors degree...", 0, QApplication::UnicodeUTF8));
        actionShell_index->setText(QApplication::translate("MainWindow", "Shell index...", 0, QApplication::UnicodeUTF8));
        actionDegree_distribution->setText(QApplication::translate("MainWindow", "Degree distribution...", 0, QApplication::UnicodeUTF8));
        actionClustering_Coefficient_vs_Degree->setText(QApplication::translate("MainWindow", "Clustering Coefficient vs Degree", 0, QApplication::UnicodeUTF8));
        actionNearest_Neighbors_Degree_vs_Degree->setText(QApplication::translate("MainWindow", "Nearest Neighbors Degree vs Degree", 0, QApplication::UnicodeUTF8));
        actionShell_Index_vs_Degree->setText(QApplication::translate("MainWindow", "Shell Index vs Degree", 0, QApplication::UnicodeUTF8));
        actionBetweenness_vs_Degree->setText(QApplication::translate("MainWindow", "Betweenness vs Degree", 0, QApplication::UnicodeUTF8));
        actionExportBetweenness_vs_Degree->setText(QApplication::translate("MainWindow", "Betweenness vs Degree", 0, QApplication::UnicodeUTF8));
        actionExportMaxClique_distribution->setText(QApplication::translate("MainWindow", "maxClique distribution", 0, QApplication::UnicodeUTF8));
        actionExportMaxCliqueExact_distribution->setText(QApplication::translate("MainWindow", "maxCliqueExact distribution", 0, QApplication::UnicodeUTF8));
        actionExportDegree_distribution->setText(QApplication::translate("MainWindow", "Degree distribution", 0, QApplication::UnicodeUTF8));
        actionExportCumulativeDegree_distribution->setText(QApplication::translate("MainWindow", "Cumulative Degree distribution", 0, QApplication::UnicodeUTF8));
        actionExportClustering_Coefficient_vs_Degree->setText(QApplication::translate("MainWindow", "Clustering Coefficient vs Degree", 0, QApplication::UnicodeUTF8));
        actionExportShell_Index_vs_Degree->setText(QApplication::translate("MainWindow", "Shell Index vs Degree", 0, QApplication::UnicodeUTF8));
        actionExportNearest_Neighbors_Degree_vs_Degree->setText(QApplication::translate("MainWindow", "Nearest Neighbors Degree vs Degree", 0, QApplication::UnicodeUTF8));
        actionConfigure_Directed_Degree_sign->setText(QApplication::translate("MainWindow", "Configure Directed Degree sign...", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuNode->setTitle(QApplication::translate("MainWindow", "&Analysis", 0, QApplication::UnicodeUTF8));
        menuPlot->setTitle(QApplication::translate("MainWindow", "&Plot", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menu_Export->setTitle(QApplication::translate("MainWindow", "&Export", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
