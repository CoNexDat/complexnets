#include "ComplexNetsGui/inc/GraphLoadingValidationDialog.h"

using namespace ComplexNetsGui;

GraphLoadingValidationDialog::GraphLoadingValidationDialog(QWidget* parent) : QDialog(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Dialog"));
    this->resize(257, 268);
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setGeometry(QRect(40, 220, 171, 32));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    groupBox = new QGroupBox(this);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(10, 20, 241, 91));
    verticalLayoutWidget_2 = new QWidget(groupBox);
    verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
    verticalLayoutWidget_2->setGeometry(QRect(10, 30, 160, 52));
    verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    verticalLayout_2->setContentsMargins(0, 0, 0, 0);
    radioButton_3 = new QRadioButton(verticalLayoutWidget_2);
    radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

    verticalLayout_2->addWidget(radioButton_3);

    radioButton_4 = new QRadioButton(verticalLayoutWidget_2);
    radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

    verticalLayout_2->addWidget(radioButton_4);

    groupBox_2 = new QGroupBox(this);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    groupBox_2->setGeometry(QRect(10, 120, 241, 91));
    verticalLayoutWidget = new QWidget(groupBox_2);
    verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
    verticalLayoutWidget->setGeometry(QRect(10, 30, 160, 52));
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    radioButton = new QRadioButton(verticalLayoutWidget);
    radioButton->setObjectName(QString::fromUtf8("radioButton"));

    verticalLayout->addWidget(radioButton);

    radioButton_2 = new QRadioButton(verticalLayoutWidget);
    radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

    verticalLayout->addWidget(radioButton_2);

    radioButton_3->setChecked(true);
    radioButton_4->setChecked(false);
    radioButton_3->setEnabled(false);
    radioButton_4->setEnabled(false);

    radioButton->setChecked(true);


    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void GraphLoadingValidationDialog::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("Dialog", "Load graph", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("Dialog", "Undirected or directed graph", 0, QApplication::UnicodeUTF8));
    radioButton_3->setText(QApplication::translate("Dialog", "Undirected graph", 0, QApplication::UnicodeUTF8));
    radioButton_4->setText(QApplication::translate("Dialog", "Directed graph", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("Dialog", "Unweighted or weighted graph", 0, QApplication::UnicodeUTF8));
    radioButton->setText(QApplication::translate("Dialog", "Unweighted graph", 0, QApplication::UnicodeUTF8));
    radioButton_2->setText(QApplication::translate("Dialog", "Weighted graph", 0, QApplication::UnicodeUTF8));
}

bool GraphLoadingValidationDialog::isMultigraph() const
{
    return true;
}

bool GraphLoadingValidationDialog::isWeigthed() const
{
    return !radioButton->isChecked();
    //return checkBox->isChecked();
}

bool GraphLoadingValidationDialog::isDirected() const
{
    return !radioButton_3->isChecked();
    //return checkBox_2->isChecked();
}

GraphLoadingValidationDialog::~GraphLoadingValidationDialog()
{
}
