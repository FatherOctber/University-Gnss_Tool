#ifndef GP6CLIENT_H
#define GP6CLIENT_H

#include <QTcpSocket>
#include <QtNetwork>
#include <QStack>
#include <QMutex>
class BufferedData
{
public:
    BufferedData();
    ~BufferedData();

    void push(QByteArray data);
    QByteArray pop();
    QList<QByteArray> popAvailable();

private:
    mutable QMutex mutex;
    QStack<QByteArray> dataStack;
};

class GP6Client: public QObject
{
    Q_OBJECT

public:
    explicit GP6Client(BufferedData* dataBuffer, QObject *parent = 0);
    ~GP6Client();

public slots:
    void start(QString host, int port, std::list<std::string> commands);
    void stop();

private:
    QByteArray getDataBytes(std::list<std::string> dataToServer);

signals:
    void finished();

private slots:
    void readyRead();
    void connectedTo();
    void tryToConnect();

private:
    QTcpSocket *socket;
    QThread *thread;
    BufferedData* receivedDataBuffer;
    QByteArray dataToSend;
    QString host;
    int port;
    std::list<std::string> commands;
};

#endif
