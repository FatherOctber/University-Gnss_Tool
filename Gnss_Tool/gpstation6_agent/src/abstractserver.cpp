#include "abstractserver.h"

AbstractServer::AbstractServer(QHostAddress address, int port, QObject *parent)
    : QObject(parent), address(address), port(port)
{
    serverStatus = AbstractServer::Status::OFF;
    client = NULL;
}

AbstractServer::~AbstractServer()
{
    shutDown();
    delete client;
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
            qDebug() <<  err;
            emit error(err);
        } else {
            serverStatus = AbstractServer::Status::GOOD;
            qDebug() << tcpServer->isListening() << "Server socket listen on port " << port;
            qDebug() << QString::fromUtf8("Server startup!");
        }
    } else {
        qDebug() << QString::fromUtf8("Server is not shuted down");
    }
}


void AbstractServer::newuser()
{
    if(serverStatus == AbstractServer::Status::GOOD){
        qDebug() << QString::fromUtf8("New connection");
        QTcpSocket* clientSocket = tcpServer->nextPendingConnection();
        if(client == NULL || !client->isOpen()) {
            client = clientSocket;
            connect(client, SIGNAL(readyRead()),this, SLOT(slotReadClient()));
        }
    }
}

void AbstractServer::slotReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    clientData = clientSocket->readAll();
    qDebug()<<"Client data: "<<clientData.data();
    QTextStream os(clientSocket);
    os.setAutoDetectUnicode(true);
    os << response().data() << "\n";
}

void AbstractServer::slotLostConnection()
{
    qDebug()<<"Client connection has been lost";
}

void AbstractServer::shutDown()
{
    if(serverStatus == AbstractServer::Status::GOOD){
        if(client != NULL) {
            QTextStream os(this->client);
            os.setAutoDetectUnicode(true);
            os << "Shut down server: " << QDateTime::currentDateTime().toString() << "\n";
            client->close();
        }
        tcpServer->close();
        qDebug() << QString::fromUtf8("Server shutdown");
        serverStatus = AbstractServer::Status::OFF;
    }
}

QByteArray AbstractServer::getClientLastData()
{
    return clientData;
}


QByteArray AbstractServer::response()
{
    QByteArray response;
    response.append("Good Evening!\r\n");
    return response;
}

ITransmittableServer::ITransmittableServer(QHostAddress address, int port, QObject *parent) : AbstractServer(address, port, parent)
{
}

ITransmittableServer::~ITransmittableServer()
{
}

QByteArray ITransmittableServer::response()
{
    return AbstractServer::response();
}

void ITransmittableServer::slotReadClient() {
    AbstractServer::slotReadClient();
    emit transmitData(clientData);
}




