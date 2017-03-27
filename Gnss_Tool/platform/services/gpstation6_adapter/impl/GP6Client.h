#ifndef GP6CLIENT_H
#define GP6CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QStack>

class GP6Client: public QObject
{
    Q_OBJECT
public:
    explicit GP6Client(QObject *parent = 0);
    ~GP6Client();

    void tryToConnect(QString host, int port, std::list<std::string> dataToServer);
    QList<QByteArray> getAvailableData();

private slots:
    void readyRead();
    void connectedTo();

private:
    QByteArray getDataBytes(std::list<std::string> dataToServer);

private:
    QTcpSocket *socket;
    QStack<QByteArray> receivedData;
    QByteArray dataToSend;
};

#endif
