#include "gnssdatahandler.h"
#include <QTime>
#include <QDate>
#include <QDebug>

GnssDataHandler::GnssDataHandler()
{
    timeStart = NULL;
    timeStop = NULL;
}

GnssData GnssDataHandler::handle(QByteArray data)
{
    //TODO: handle algorithm
    GnssData someData;
    someData.data.push_back(1.1);
    someData.data.push_back(1.2);
    return someData;
}


QByteArray GnssDataHandler::startCommand()
{
    QByteArray timeLog;
    /** for example log command **/
    timeLog.append("UNLOGALL\r\n");
    timeLog.append("log timea ontime 1\r\n");
    /** ----------------------- **/
    return timeLog;
}

void GnssDataHandler::startTimer()
{
    if(timeStart == NULL) {
        timeStart = new StandardTime();
        QDate date = QDate::currentDate();
        QTime time = QTime::currentTime();
        timeStart->date = date.toString().toStdString();
        timeStart->time = time.toString().toStdString();
        qDebug()<<"Current start time: "<<date.toString()<<" "<<time.toString();
    }
    else {
        qDebug()<<"Start time has been already set";
    }
}

void GnssDataHandler::stopTimer()
{
    if(timeStop == NULL) {
        timeStop = new StandardTime();
        QDate date = QDate::currentDate();
        QTime time = QTime::currentTime();
        timeStop->date = date.toString().toStdString();
        timeStop->time = time.toString().toStdString();
        qDebug()<<"Current stop time: "<<date.toString()<<" "<<time.toString();
    }
    else {
        qDebug()<<"Stop time has been already set";
    }
}

QByteArray GnssDataHandler::stopCommand()
{
    QByteArray stopLog;
    stopLog.append("UNLOGALL\r\n");
    return stopLog;
}

StandardTime GnssDataHandler::getStartTime()
{
    return *this->timeStart;
}

StandardTime GnssDataHandler::getStopTime()
{
    return *this->timeStop;
}

