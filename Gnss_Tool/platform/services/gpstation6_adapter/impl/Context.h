#ifndef CONTEXT_H
#define CONTEXT_H
#include <QMutex>
#include <QMap>
#include "GnssData.h"
using namespace gnss;

extern "C" {
#include "rtk/rtklib.h"
}

class Context
{
public:
    Context(BESTPOS defaultPosition);
    ~Context();
    void setPosition(BESTPOS position);
    BESTPOS getPosition();
    raw_t* getRaw();
    nav_t* getNav();
    void setTecCal(double tecCal);
    double getTecCal();

public:
    QMap<int,GNSSOBS> obs_tek;
    QMap<int,REDOBS> red_obs;
    QMap<int,TEC> tec_tek;
    QMap<int,TEC_SBAS> sbas_tec;
    double tau_sbas = 0;

private:
    raw_t *raw;
    nav_t *nav;
    double tec_s_cal;
    BESTPOS gp6StationPosition;


};

#endif
