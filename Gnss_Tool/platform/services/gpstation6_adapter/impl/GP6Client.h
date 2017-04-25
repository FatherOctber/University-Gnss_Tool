#ifndef GP6CLIENT_H
#define GP6CLIENT_H

#include <QTcpSocket>
#include <QtNetwork>
#include <QStack>
#include <QMutex>
#include "GP6Parser.h"

template <typename T> class BufferedData
{
public:
    BufferedData() {}
    ~BufferedData() {}

    void push(T data) {
        QMutexLocker locker(&mutex);
        dataStack.push(data);
    }

    T pop() {
        QMutexLocker locker(&mutex);
        return dataStack.pop();
    }

    QList<T> popAvailable() {
        QMutexLocker locker(&mutex);
        QList<T> result;
        int size = dataStack.size();
        while(size > 0) {
            result.append(dataStack.pop());
            size--;
        }
        return result;
    }

private:
    mutable QMutex mutex;
    QStack<T> dataStack;
};

class GP6Client: public QObject
{
    Q_OBJECT

public:
    explicit GP6Client(BufferedData<SHARED_GNSS_DATA> *dataBuffer, QObject *parent = 0);
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
    BufferedData<SHARED_GNSS_DATA>* receivedDataBuffer;
    QByteArray incomingReceiverData;
    QByteArray dataToSend;
    GP6Parser parser;
    Context* ctx;
    QString host;
    int port;
    std::list<std::string> commands;
};

#endif
