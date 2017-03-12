#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>

class IServerResponder
{
public:
    virtual QByteArray response() = 0;
};


class AbstractServer: public QObject, protected IServerResponder
{
    enum Status { GOOD, ERROR, OFF };

    Q_OBJECT
public:
    explicit AbstractServer(QHostAddress address = QHostAddress::Any, int port=12, QObject *parent = 0);
    ~AbstractServer();
    QByteArray getClientLastData(); //echo

signals:
    void error(QString message);

public slots:
    void startUp();
    void shutDown();

private slots:
    void newuser();
    void slotLostConnection();

protected slots:
    virtual void slotReadClient();

protected:
    QTcpServer *tcpServer;
    Status serverStatus;
    QTcpSocket *client; // only one
    QByteArray clientData;
    virtual QByteArray response();
    QHostAddress address;
    int port;

};

class ITransmittableServer: public AbstractServer
{
    Q_OBJECT
public:
    explicit ITransmittableServer(QHostAddress address = QHostAddress::Any, int port=12, QObject *parent = 0);
    ~ITransmittableServer();

signals:
    void transmitData(QByteArray data);

protected slots:
    virtual void slotReadClient();

protected:
    virtual QByteArray response();
};

#endif // ABSTRACTSERVER_H
