#ifndef GRAPHLOADINGVALIDATIONDIALOG_H
#define GRAPHLOADINGVALIDATIONDIALOG_H

#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

namespace ComplexNetsGui
{
class GraphLoadingValidationDialog : public QDialog
{
public:
    GraphLoadingValidationDialog(QWidget* parent = 0);
    ~GraphLoadingValidationDialog();
    bool isMultigraph() const;
    bool isWeigthed() const;
    bool isDirected() const;
private:
    void retranslateUi();
    QWidget* gridLayoutWidget;
    QGridLayout* gridLayout;
    QCheckBox* checkBox_3;
    QCheckBox* checkBox;
    QCheckBox* checkBox_2;
    QDialogButtonBox* buttonBox;
    QLabel* label;
};
}

#endif
