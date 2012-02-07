#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <cstdlib>

#include "ComplexNetsGui/inc/mainwindow.h"

//File ui_mainwindow.h will be generated on compile time. Don't look for it, unless you have already compiled the project.
#include "ComplexNetsGui/inc/ui_mainwindow.h"

using namespace ComplexNetsGui;

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->onNetworkUnload();
    ui->textBrowser->setOpenExternalLinks(true);
    ui->textBrowser->append("Welcome to ComplexNets++!!\nIf you are a developer feel free to visit our Google Code site:");
    ui->textBrowser->append("<a href='http://code.google.com/p/complexnets/'>ComplexNets++ - Google Code</a>");
    ui->textBrowser->append("\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent* e)
{
    QMainWindow::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setDirectory(QDir::homePath());
    QStringList selectedFiles;
    // TODO if a network has already been loaded ask the user to close the current network before loading a new one.
    // only one network can be open at a given moment.
    ui->textBrowser->append("Loading new network...");
    if (fileDialog.exec())
    {
        selectedFiles = fileDialog.selectedFiles();

        this->onNetworkLoad();
        QString text("Network loaded from file: ");
        text.append(selectedFiles[0]);
        text.append(".\n");
        ui->textBrowser->append(text);
    }
    else
        ui->textBrowser->append("Action canceled!\n");
}

void MainWindow::on_actionQuit_triggered()
{
    QMessageBox msg(QMessageBox::Question, "Quit", "Are you sure you want to quit?", QMessageBox::Ok | QMessageBox::Cancel, this);
    ui->textBrowser->append("About to quit ComplexNets++...");
    if (msg.exec() == QMessageBox::Ok)
    {
        ui->textBrowser->append("Bye bye.\n");
        exit(EXIT_SUCCESS);
    }
    else
        ui->textBrowser->append("Action canceled.\n");
}

void MainWindow::on_actionClose_current_network_triggered()
{
    ui->textBrowser->append("About to close the current network...");
    QMessageBox msg(QMessageBox::Question, "Close current network", "Are you sure you want to close the current network?", QMessageBox::Ok | QMessageBox::Cancel, this);
    if (msg.exec() == QMessageBox::Ok)
    {
        //TODO delete graph
        this->onNetworkUnload();
        ui->textBrowser->append("Done.\n");
    }
    else
        ui->textBrowser->append("Action canceled!\n");
}

void MainWindow::on_actionDegree_distribution_triggered()
{
    int systemRet = 0;
    ui->textBrowser->append("Ploting degree distribution...");
    systemRet = system("gnuplot -persist ./command.tmp");
    if (systemRet == 0)
        ui->textBrowser->append("Done.\n");
}

void MainWindow::onNetworkLoad()
{
    ui->actionClose_current_network->setEnabled(true);
}
void MainWindow::onNetworkUnload()
{
    ui->actionClose_current_network->setEnabled(false);
}
