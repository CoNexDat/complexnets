#ifndef GRAPHLOADINGVALIDATIONDIALOG_H
#define GRAPHLOADINGVALIDATIONDIALOG_H


#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>
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
