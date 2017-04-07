#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextBrowser>
#include <cstdio>
#include <fstream>
#include <iostream>
#include "ComplexNets/AdjacencyListGraph.h"
#include "ComplexNets/AdjacencyListVertex.h"
#include "ComplexNets/Boxplotentry.h"
#include "ComplexNets/IClusteringCoefficient.h"
#include "ComplexNets/mili/mili.h"
#include "ComplexNets/typedefs.h"

namespace ComplexNetsGui
{
class GnuplotConsole : public QDialog
{
    Q_OBJECT
public:
    GnuplotConsole(QWidget* parent = nullptr);
    ~GnuplotConsole();
    bool plotPropertySet(
        const VariantsSet& set,
        const std::string& propertyName,
        const bool logBin = false,
        unsigned int bins = 25);
    void writeCommand(const std::string& command);
    bool boxplotCC(
        std::vector<graphpp::Boxplotentry> bpentries,
        const bool logBin = false,
        unsigned int bins = 25);
    bool addLogBins(std::vector<graphpp::Boxplotentry>& vec, unsigned int binsAmount);
    unsigned int findBin(const std::vector<double>& bins, const unsigned int value);

    // void closeDialog();

private slots:
    void commandEntered();

private:
    std::ifstream outputFile;
    FILE* pipe = nullptr;

    QGroupBox* groupBox;
    QTextBrowser* textBrowser;
    QGroupBox* groupBox_2;
    QLineEdit* lineEdit;
};
}
