#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"
#include "timegraph.h"

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
    dataHandler = new GnssDataHandler;

    settings = new SettingsDialog;
    timeGraph = new TimeGraph;

    QString parametres = QDir::currentPath()+"/settings.ini";
    server = new GPStationServer( QHostAddress(Utils::getSetting(parametres, "host")),
                                                Utils::getSetting(parametres, "port").toInt());
    server->startUp();

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);

    initActionsConnections();
}

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
    delete timeGraph;
    delete dataHandler;
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

void MainWindow::writeData(const QByteArray &data)
{
    QByteArray dataToCom;
    dataToCom.append("Data to GPStation: "+QString(data));
    console->putData(dataToCom);
    serial->write(data);
}

void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    QByteArray dataFromCom;
    dataFromCom.append("Data from GPStation: "+QString(data));
    console->putData(data);
    dataHandler->handle(data);
}

void MainWindow::seansStart()
{
    dataHandler->startTimer();
    QByteArray dataToReceiver = dataHandler->startCommand();
    emit sendLog(dataToReceiver);
}

void MainWindow::seansStop()
{
    dataHandler->stopTimer();
    QByteArray dataToReceiver = dataHandler->stopCommand();
    emit sendLog(dataToReceiver);
}

void MainWindow::transferDataToGraphics()
{
    qDebug()<<"Send data to Graphic";

    StandardTime start = dataHandler->getStartTime();
    StandardTime stop = dataHandler->getStopTime();

    std::vector<double> t_data;
    std::vector<double> f_data;
    for(int i=0; i<100; i++)
    {
        t_data.push_back((double)i);
        f_data.push_back(i*2.34);
    }
    emit sendData(t_data, f_data, start, stop);
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
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(this, SIGNAL(sendLog(QByteArray)), this, SLOT(writeData(QByteArray)));

    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(seansStart()));
    connect(ui->actionStop, SIGNAL(triggered()), this, SLOT(seansStop()));
    connect(ui->actionGraph, SIGNAL(triggered()), this, SLOT(transferDataToGraphics()));
    connect(this, SIGNAL(sendData(std::vector<double>,std::vector<double>, const StandardTime&, const StandardTime&)),
            timeGraph, SLOT(dataset(std::vector<double>, std::vector<double>,  const StandardTime&, const StandardTime&)));
    connect(server, SIGNAL(error(QString)), this, SLOT(errorNotification(QString)));
    connect(server, SIGNAL(transmitData(QByteArray)), this, SLOT(writeData(QByteArray)));
}

void MainWindow::errorNotification(QString message)
{
    QMessageBox::information(
                this,
                tr("Server condition"),
                message );
    exit(1);
}
