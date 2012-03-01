#include "ComplexNetsGui/inc/GnuplotConsole.h"
#include "ComplexNetsGui/inc/GrapherUtils.h"

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
        std::cerr << "ACA" << std::endl;
        writeCommand(exitCommand);
        pclose(pipe);
    }
    delete textBrowser;
    delete lineEdit;
    delete groupBox;
    delete groupBox_2;
}

//TODO should be const
bool GnuplotConsole::plotPropertySet(const VariantsSet& set, const std::string& propertyName)
{
    GrapherUtils utils;
    if (pipe == NULL)
        pipe = popen("gnuplot -persist", "w");
    if (pipe == NULL)
        return false;
    std::string command = std::string("plot ").append("\"/tmp/").append(propertyName).append("\"\n");
    std::string file = "/tmp/";
    file.append(propertyName);
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
    //char response[128];
    std::string _command = command;
    _command.append("\n");
    fputs(_command.c_str(), pipe);
    _command = "replot";
    _command.append("\n");
    fputs(_command.c_str(), pipe);
    fflush(pipe);
    /*QString console;
    bool quit=false;
    while(!feof(pipe) && !quit)
    {
        if(fgets(response, 128, pipe) != NULL)
            console += response;
        else
            quit=true;
    }*/
    //this->textBrowser->append(console);
}
