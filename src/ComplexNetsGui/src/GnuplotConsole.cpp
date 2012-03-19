#include "ComplexNetsGui/inc/GnuplotConsole.h"
#include "ComplexNetsGui/inc/GrapherUtils.h"

#include "ComplexNetsGui/inc/LogBinningPolicy.h"

using namespace ComplexNetsGui;

GnuplotConsole::GnuplotConsole(QWidget* parent) : QDialog(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Dialog"));
    pipe = NULL;
    this->resize(706, 326);
    this->setModal(false);
    groupBox = new QGroupBox(this);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(10, 10, 681, 241));
    textBrowser = new QTextBrowser(groupBox);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    textBrowser->setGeometry(QRect(10, 20, 661, 211));
    groupBox_2 = new QGroupBox(this);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    groupBox_2->setGeometry(QRect(10, 260, 681, 61));
    lineEdit = new QLineEdit(groupBox_2);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setGeometry(QRect(10, 20, 661, 27));

    this->setWindowTitle(QApplication::translate("Dialog", "Gnuplot console", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("Dialog", "Console", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("Dialog", "Command", 0, QApplication::UnicodeUTF8));

    QObject::connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(commandEntered()));
    QMetaObject::connectSlotsByName(this);
}

GnuplotConsole::~GnuplotConsole()
{
    std::string exitCommand = "quit\n";
    if (pipe != NULL)
    {
        writeCommand(exitCommand);
        pclose(pipe);
    }
    if (outputFile.is_open())
    {
        outputFile.clear();
        outputFile.close();
    }
    delete textBrowser;
    delete lineEdit;
    delete groupBox;
    delete groupBox_2;
}

//TODO should be const
bool GnuplotConsole::plotPropertySet(const VariantsSet& set, const std::string& propertyName, const bool logBin)
{
    GrapherUtils utils;
    if (pipe == NULL)
        pipe = popen("gnuplot -persist > /tmp/complexnets_gnuplot_output.txt 2>&1", "w");
    if (pipe == NULL)
        return false;

    std::string command = std::string("plot ").append("\"/tmp/").append(propertyName).append("\"\n");
    std::string file = "/tmp/";
    file.append(propertyName);


    //TODO this should be implemented as a policy. Using default template is only allowed in C++0x.
    if (logBin)
    {
        LogBinningPolicy policy;
        utils.exportPropertySet(policy.transform(set), file);
    }
    else
        utils.exportPropertySet(set, file);

    writeCommand(command);
    return true;
}

void GnuplotConsole::commandEntered()
{
    std::string command = lineEdit->text().toStdString();
    //TODO do nothing when the command is either exit or quit.
    if (!command.empty())
    {
        writeCommand(command);
        lineEdit->clear();
    }
}

void GnuplotConsole::writeCommand(const std::string& command)
{
    std::string _command = command;
    _command.append("\n");

    QString text("gnuplot> ");
    text.append(_command.c_str());
    this->textBrowser->append(text);

    fputs(_command.c_str(), pipe);
    _command = "replot";
    _command.append("\n");
    fputs(_command.c_str(), pipe);
    fflush(pipe);

    /*if(!outputFile.is_open())
    {
        outputFile.open("/tmp/complexnets_gnuplot_output.txt", std::ios_base::in);
        outputFile.clear();
    }
    if(!outputFile.is_open())
        return ;

    QString console;
    std::string line;
    while(std::getline(outputFile,line))
    {
        console.append(line.c_str());
        //console.append("\n");
    }
    this->textBrowser->clear();
    this->textBrowser->append(console);*/
}
