#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QLabel>
#include <QPixmap>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    console = new Console;
    console->setEnabled(false);
    setCentralWidget(console);

    serial = new QSerialPort(this);
    settings = new SettingsDialog;
    server = new GPStationServer( serial,
                                  QHostAddress(Utils::getSetting("gpstation_agent_host")),
                                  Utils::getSetting("gpstation_agent_port").toInt());
    server->startUp();

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);

    initActionsConnections();
    emit sendLog(QByteArray::fromStdString("GPStation-6 agent started"));
}

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
    delete serial;
    delete server;
}

void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    if (serial->open(QIODevice::ReadWrite)) {
        if (serial->setBaudRate(p.baudRate)
                && serial->setDataBits(p.dataBits)
                && serial->setParity(p.parity)
                && serial->setStopBits(p.stopBits)
                && serial->setFlowControl(p.flowControl)) {

            console->setEnabled(true);
            console->setLocalEchoEnabled(p.localEchoEnabled);
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

        } else {
            serial->close();
            QMessageBox::critical(this, tr("Error"), serial->errorString());

            ui->statusBar->showMessage(tr("Open error"));
        }
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Configure error"));
    }
}

void MainWindow::closeSerialPort()
{
    if(serial->isOpen()){
        serial->close();
        console->setEnabled(false);
        ui->actionConnect->setEnabled(true);
        ui->actionDisconnect->setEnabled(false);
        ui->actionConfigure->setEnabled(true);
        ui->statusBar->showMessage(tr("Disconnected"));
        seansStop();
    } else {
        ui->statusBar->showMessage(tr("Serial port wasn`t open"));
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About GPStation Server 0.1"),
                       tr("The <b>GPStation Server 0.1</b> is server for manipulate with "
                          "Novatel GPStation 6 receiver. Serve one connection (hardware limitation)."));
}

void MainWindow::printToConsole(const QByteArray &data)
{
    QByteArray dataToCom;
    dataToCom.append("Message: " + QString(data) + "\r\n");
    std::cout << "GP6Agent: " << QString(data).toStdString() << std::endl;
    console->putData(dataToCom);
}

void MainWindow::seansStart()
{
    if(!timer.started) {
        timer.startTimer();
        emit sendLog(QByteArray::fromStdString("Seans started: " + timer.start.toString()));
        if(Utils::getSetting("test_run").toUpper() == "TRUE") {
            emit sendLog(QByteArray::fromStdString("Send test message"));
            server->transmitDataToServer(QByteArray::fromStdString("Hello! This is test run."));
        }
    } else {
        emit sendLog(QByteArray::fromStdString("Seans has been already started!"));
    }
}

void MainWindow::seansStop()
{
    if(timer.started) {
        timer.stopTimer();
        emit sendLog(QByteArray::fromStdString("Seans stoped: " + timer.stop.toString()));
    } else {
        emit sendLog(QByteArray::fromStdString("Seans not started!"));
    }
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::initActionsConnections()
{
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));
    connect(this, SIGNAL(sendLog(QByteArray)), this, SLOT(printToConsole(QByteArray)));

    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(seansStart()));
    connect(ui->actionStop, SIGNAL(triggered()), this, SLOT(seansStop()));
    connect(server, SIGNAL(error(QString)), this, SLOT(errorNotification(QString)));
    connect(server, SIGNAL(transmitDataFromServer(QByteArray)), this, SLOT(printToConsole(QByteArray)));
}

void MainWindow::errorNotification(QString message)
{
    QMessageBox::information(
                this,
                tr("Server condition"),
                message );
    exit(1);
}
