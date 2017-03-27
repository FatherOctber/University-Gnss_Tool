#ifndef GPSTATIONSERVER_H
#define GPSTATIONSERVER_H
#include "abstractserver.h"
#include <QtSerialPort/QSerialPort>

class GPStationServer : public TransmittableServer
{
    Q_OBJECT
public:
    explicit GPStationServer(QSerialPort *receiver, QHostAddress address = QHostAddress::Any, int port=12, QObject *parent = 0);
    ~GPStationServer();

private slots:
    void writeToReceiver(const QByteArray &data);
    void readFromReceiver();

private:
    QSerialPort* receiver;
};


#endif // GPSTATIONSERVER_H
