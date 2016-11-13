#ifndef GPSTATIONSERVER_H
#define GPSTATIONSERVER_H
#include "abstractserver.h"

class GPStationServer : public ITransmittableServer
{
    Q_OBJECT
public:
    explicit GPStationServer(QHostAddress address = QHostAddress::Any, int port=12, QObject *parent = 0);
    ~GPStationServer();

protected slots:
    virtual void slotReadClient();

protected:
    virtual QByteArray response();
};


#endif // GPSTATIONSERVER_H
