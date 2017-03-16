#ifndef GRAPHLOADINGVALIDATIONDIALOG_H
#define GRAPHLOADINGVALIDATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "ComplexNetsGui/inc/mainwindow.h"

namespace ComplexNetsGui
{
class GraphLoadingValidationDialog : public QDialog
{
    Q_OBJECT
public:
    GraphLoadingValidationDialog(QWidget* parent = 0);
    virtual ~GraphLoadingValidationDialog();
    bool isMultigraph() const;
    bool isWeigthed() const;
    bool isDirected() const;
    MainWindow* mainWindow;

public slots:
    void radioButton4Changed(bool checked);

private:
    void retranslateUi();
    QDialogButtonBox* buttonBox;
    QGroupBox* groupBox;
    QWidget* verticalLayoutWidget_2;
    QVBoxLayout* verticalLayout_2;
    QRadioButton* radioButton_3;
    QRadioButton* radioButton_4;
    QGroupBox* groupBox_2;
    QWidget* verticalLayoutWidget;
    QVBoxLayout* verticalLayout;
    QRadioButton* radioButton;
    QRadioButton* radioButton_2;
};
}

#endif
