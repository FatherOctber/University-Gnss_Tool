#include "gpstationserver.h"

GPStationServer::GPStationServer(QHostAddress address, int port, QObject *parent)
    : ITransmittableServer(address, port, parent)
{
}

GPStationServer::~GPStationServer()
{
}

QByteArray GPStationServer::response()
{
    QByteArray response;
    response.append("Test Test\r\n");
    return response;
}

void GPStationServer::slotReadClient() {
    ITransmittableServer::slotReadClient();
}
