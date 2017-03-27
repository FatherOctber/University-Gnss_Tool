#include "abstractserver.h"
#include <iostream>

AbstractServer::AbstractServer(QHostAddress address, int port, QObject *parent)
    : QObject(parent), address(address), port(port)
{
    serverStatus = AbstractServer::Status::OFF;
}

AbstractServer::~AbstractServer()
{
    shutDown();
    clients.clear();
    delete tcpServer;
}

void AbstractServer:: startUp()
{
    if(serverStatus == AbstractServer::Status::OFF)
    {
        tcpServer = new QTcpServer(parent());
        connect(tcpServer, &QTcpServer::newConnection, this, &AbstractServer::newuser);
        if (!tcpServer->listen(address, port)) {
            serverStatus = AbstractServer::Status::ERROR;
            QString err = QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
            std::cout <<  err.toStdString() << std::endl;;
            emit error(err);
        } else {
            serverStatus = AbstractServer::Status::GOOD;
            std::cout << "Server socket listen on port " << port << std::endl;
            std::cout << "Server startup!" << std::endl;
        }
    } else {
        std::cout << "Server is not shuted down";
    }
}


void AbstractServer::newuser()
{
    if(serverStatus == AbstractServer::Status::GOOD){
        std::cout << "New connection" << std::endl;
        QTcpSocket* clientSocket = tcpServer->nextPendingConnection();
        if(clients.indexOf(clientSocket) < 0) {
            clients.push_back(clientSocket);
            connect(clientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
        }
    }
}

void AbstractServer::slotLostConnection()
{
    std::cout <<"Client connection has been lost" << std::endl;
}

void AbstractServer::shutDown()
{
    if(serverStatus == AbstractServer::Status::GOOD){
        if(!clients.empty()) {
            for(QTcpSocket* client : clients) {
                QTextStream os(client);
                os.setAutoDetectUnicode(true);
                os << "Shutdown server: " << QDateTime::currentDateTime().toString() << "\n";
                client->close();
            }
        }
        tcpServer->close();
        std::cout << "Server shutdown: " << QDateTime::currentDateTime().toString().toStdString() << std::endl;
        serverStatus = AbstractServer::Status::OFF;
    }
}


TransmittableServer::TransmittableServer(QHostAddress address, int port, QObject *parent) : AbstractServer(address, port, parent)
{
}

TransmittableServer::~TransmittableServer()
{
}

QByteArray TransmittableServer::slotReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QByteArray clientData = clientSocket->readAll();
    emit transmitDataFromServer(clientData);
    return clientData;
}

void TransmittableServer::transmitDataToServer(const QByteArray &data)
{
    if(!clients.empty()) {
        for(QTcpSocket* client : clients) {
            QTextStream os(client);
            os.setAutoDetectUnicode(true);
            os << data.data() << endl;
        }
    }
}



