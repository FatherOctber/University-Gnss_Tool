#ifndef GNSSDATAHANDLER_H
#define GNSSDATAHANDLER_H
#include <QByteArray>
#include "gnssdata.h"

class GnssDataHandler
{
private:
    StandardTime *timeStart;
    StandardTime *timeStop;

public:
    GnssDataHandler();
    GnssData handle(QByteArray data);
    void startTimer();
    void stopTimer();
    QByteArray startCommand();
    QByteArray stopCommand();
    StandardTime getStartTime();
    StandardTime getStopTime();

};

#endif // GNSSDATAHANDLER_H
