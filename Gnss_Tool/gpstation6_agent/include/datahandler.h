#ifndef GNSSDATAHANDLER_H
#define GNSSDATAHANDLER_H
#include <QByteArray>
#include "gnssdata.h"

class Abstracthandler
{
protected:
    StandardTime *timeStart;
    StandardTime *timeStop;

public:
    Abstracthandler();
    ~Abstracthandler();
    virtual GnssData handle(QByteArray data)=0;
    void startTimer();
    void stopTimer();
    QByteArray startCommand();
    QByteArray stopCommand();
    StandardTime getStartTime();
    StandardTime getStopTime();

};

class ConcreteHandler: public Abstracthandler
{
public:
    ConcreteHandler();
    virtual GnssData handle(QByteArray data);
};

class GnssDataHandler: public Abstracthandler
{
private:
    ConcreteHandler handler;

public:
    GnssDataHandler();
    virtual GnssData handle(QByteArray data);

};

#endif // GNSSDATAHANDLER_H
