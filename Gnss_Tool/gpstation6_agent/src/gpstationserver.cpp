#include "gpstationserver.h"
#include <iostream>

GPStationServer::GPStationServer(QSerialPort *receiver, QHostAddress address, int port, QObject *parent)
    : TransmittableServer(address, port, parent)
{
    this->receiver = receiver;
    connect(this->receiver, SIGNAL(readyRead()), this, SLOT(readFromReceiver()));
    connect(this, SIGNAL(transmitDataFromServer(QByteArray)), this, SLOT(writeToReceiver(QByteArray)));
}

GPStationServer::~GPStationServer()
{
}

void GPStationServer::writeToReceiver(const QByteArray &data)
{
    std::cout << "Data to GPStation: " + data.toStdString() << std::endl;
    if(receiver != NULL && receiver->isOpen()) {
        /**
            QByteArray stopLog;
            stopLog.append("UNLOGALL\r\n");
        **/
        receiver->write(data);
    }
}

void GPStationServer::readFromReceiver()
{
    QByteArray data = receiver->readAll();
    transmitDataToServer(data);
}
