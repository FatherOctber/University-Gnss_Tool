#include "Context.h"
#include <QMutexLocker>

Context::Context(BESTPOS defaultPosition)
{
    raw_t *raw = new raw_t;
    nav=new nav_t;
    gp6StationPosition = defaultPosition;
    nav->nmax=64;
    nav->sbssat.nsat=4;
    init_raw(raw);
    tec_s_cal = 0;
}

Context::~Context()
{
    delete raw;
}

void Context::setPosition(BESTPOS position)
{
    this->gp6StationPosition = position;
}

BESTPOS Context::getPosition()
{
    return gp6StationPosition;
}

raw_t* Context::getRaw()
{
    return raw;
}

nav_t* Context::getNav()
{
    return nav;
}

void Context::setTecCal(double tecCal)
{
    tec_s_cal = tecCal;
}

double Context::getTecCal()
{
    return tec_s_cal;
}

