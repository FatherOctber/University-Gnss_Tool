#ifndef ABSTRACTSERVER_H
#define ABSTRACTSERVER_H

#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QList>

/**
 * @brief The AbstractServer class - abstract server
 */
class AbstractServer: public QObject
{
    enum Status { GOOD, ERROR, OFF };

    Q_OBJECT
public:
    explicit AbstractServer(QHostAddress address = QHostAddress::Any, int port=12, QObject *parent = 0);
    ~AbstractServer();

signals:
    void error(QString message);

public slots:
    void startUp();
    void shutDown();

private slots:
    void newuser();
    void slotLostConnection();

protected slots:
    virtual QByteArray slotReadClient() = 0;

protected:
    QTcpServer *tcpServer;
    Status serverStatus;
    QList<QTcpSocket*>clients;

private:
    QHostAddress address;
    int port;
};

/**
 * @brief The ITransmittableServer class - server with transmit functions
 */
class TransmittableServer: public AbstractServer
{
    Q_OBJECT
public:
    explicit TransmittableServer(QHostAddress address = QHostAddress::Any, int port=12, QObject *parent = 0);
    ~TransmittableServer();

signals:
    void transmitDataFromServer(const QByteArray &data);

public slots:
    void transmitDataToServer(const QByteArray &data);

protected slots:
    virtual QByteArray slotReadClient();
};

#endif // ABSTRACTSERVER_H
