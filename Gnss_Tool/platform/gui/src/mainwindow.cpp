#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "platformcore.h"
#include "QMessageBox"
#include "QTime"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    console = new Console;
    console->setEnabled(false);
    platformCore = new PlatformCore;
    setCentralWidget(console);
    initActionsConnections();
    print("GUI Application started");
}

MainWindow::~MainWindow()
{
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About GNSS Platform App"),
                       tr("The <b>GNSS Platform App 0.1</b> is gui application to start service platfrom "));
}

void MainWindow::print(QString data)
{
    QString log = QTime::currentTime().toString() + ": " + data + "\n";
    console->putData(log.toUtf8());
}

void MainWindow::start()
{
    QList<service_item> availableServices = Utils::getSettingServices(Utils::getSetting("servicesFile"));
    std::list<std::string> serviceFiles;
    for(service_item item : availableServices ) {
        serviceFiles.push_back(item.lib.toStdString());
        print("Load "+ item.name + " service");
    }
    if(platformCore->load(serviceFiles)) {
        print("Platform Core was successfully loaded");
        platformCore->runPlatform();
    } else {
        print("Platform Core loading failed");
    }
}

void MainWindow::stop()
{
    platformCore->stopPlatform();
    print("Platform Core was stoped");
}

void MainWindow::initActionsConnections()
{
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(start()));
    connect(ui->actionStop, SIGNAL(triggered()), this, SLOT(stop()));
}
