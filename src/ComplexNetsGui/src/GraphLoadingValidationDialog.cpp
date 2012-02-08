#include "ComplexNetsGui/inc/GraphLoadingValidationDialog.h"

using namespace ComplexNetsGui;

GraphLoadingValidationDialog::GraphLoadingValidationDialog(QWidget* parent)
{
    this->setParent(parent);
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Dialog"));
    this->resize(341, 179);
    gridLayoutWidget = new QWidget(this);
    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(10, 10, 321, 151));
    gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    checkBox_3 = new QCheckBox(gridLayoutWidget);
    checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

    gridLayout->addWidget(checkBox_3, 3, 0, 1, 1);

    checkBox = new QCheckBox(gridLayoutWidget);
    checkBox->setObjectName(QString::fromUtf8("checkBox"));

    gridLayout->addWidget(checkBox, 2, 0, 1, 1);

    checkBox_2 = new QCheckBox(gridLayoutWidget);
    checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

    gridLayout->addWidget(checkBox_2, 1, 0, 1, 1);

    buttonBox = new QDialogButtonBox(gridLayoutWidget);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    gridLayout->addWidget(buttonBox, 4, 0, 1, 1);

    label = new QLabel(gridLayoutWidget);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);


    retranslateUi();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}

void GraphLoadingValidationDialog::retranslateUi()
{
    this->setWindowTitle(QApplication::translate("Dialog", "Graph properties validation", 0, QApplication::UnicodeUTF8));
    checkBox_3->setText(QApplication::translate("Dialog", "Multigraph", 0, QApplication::UnicodeUTF8));
    checkBox->setText(QApplication::translate("Dialog", "Weigthed graph", 0, QApplication::UnicodeUTF8));
    checkBox_2->setText(QApplication::translate("Dialog", "Directed graph", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Dialog", "Select graph properties for validation pouposes:", 0, QApplication::UnicodeUTF8));
}

bool GraphLoadingValidationDialog::isMultigraph() const
{
    return checkBox_3->isChecked();
}

bool GraphLoadingValidationDialog::isWeigthed() const
{
    return checkBox->isChecked();
}

bool GraphLoadingValidationDialog::isDirected() const
{
    return checkBox_2->isChecked();
}

GraphLoadingValidationDialog::~GraphLoadingValidationDialog()
{
}
