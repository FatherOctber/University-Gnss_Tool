#include "GP6Client.h"
#include <iostream>
#include <QThread>

GP6Client::GP6Client(QObject *parent): QObject(parent)
{
    socket = new QTcpSocket();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connectedTo()));
}

GP6Client::~GP6Client()
{
    delete socket;
}

void GP6Client::readyRead()
{
    std::cout << "Ready read data" << std::endl;
    receivedData.push(socket->readAll());
}

void GP6Client::connectedTo()
{
    std::cout << "Connected with " + dataToSend.toStdString() << std::endl;
    socket->write(dataToSend);
}

void GP6Client::tryToConnect(QString host, int port, std::list<std::string> dataToServer)
{
    dataToSend = getDataBytes(dataToServer);
    socket->connectToHost(host, port);
//    if(socket->waitForConnected(3000)) {
//        socket->write(dataToSend);
//        if(socket->waitForBytesWritten(1000)) {
//            std::cout << "Commands was sended!" << std::endl;
//        }
//    }
}

QByteArray GP6Client::getDataBytes(std::list<std::string> dataToServer)
{
    QByteArray bytes;
    for(auto log : dataToServer) {
        bytes.append(QString::fromStdString(log + "\r\n"));
    }
    return bytes;
}

QList<QByteArray> GP6Client::getAvailableData()
{
    std::cout << "step2" << std::endl;
    int currentSize = receivedData.size();
    QList<QByteArray> resultList;
    while(currentSize) {
        std::cout << "Data exist" << std::endl;
        auto data = receivedData.pop();
        resultList.append(data);
        currentSize--;
    }
    return resultList;
}


