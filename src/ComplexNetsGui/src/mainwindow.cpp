#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <cstdlib>

//File ui_mainwindow.h will be generated on compile time. Don't look for it, unless you have already compiled the project.
#include "ComplexNetsGui/inc/ui_mainwindow.h"
#include "ComplexNetsGui/inc/mainwindow.h"
#include "ComplexNetsGui/inc/GraphLoadingValidationDialog.h"

using namespace ComplexNetsGui;

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    graphLoaded(false)
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

    if (!this->graphLoaded)
    {
        //If no network is loaded user may procede to load a new network.
        ui->textBrowser->append("Loading new network...");
        if (fileDialog.exec())
        {
            selectedFiles = fileDialog.selectedFiles();
            //TODO Load graph here.
            this->onNetworkLoad();
            QString text("Network loaded from file: ");
            text.append(selectedFiles[0]);
            text.append(".\n");
            ui->textBrowser->append(text);
        }
        else
            ui->textBrowser->append("Action canceled by user.\n");
    }
    else
    {
        ui->textBrowser->append("Action canceled: Only one network can be loaded at any given time.\n");
        QMessageBox msg(QMessageBox::Information, "Quit", "Only one network can be loaded at any given time. Please close the current network (File->Close all...) before loading another one", QMessageBox::Ok, this);
    }
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
        ui->textBrowser->append("Action canceled by user.\n");
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
        ui->textBrowser->append("Action canceled by user.\n");
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
    this->graphLoaded = true;
    ui->actionClose_current_network->setEnabled(true);
}
void MainWindow::onNetworkUnload()
{
    this->graphLoaded = false;
    ui->actionClose_current_network->setEnabled(false);
}
