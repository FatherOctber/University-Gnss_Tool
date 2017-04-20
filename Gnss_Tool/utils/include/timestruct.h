#ifndef TIMESTRUCT_H
#define TIMESTRUCT_H
#include <string>
#include <iostream>
#include <vector>
#include <QMetaType>
#include <QDate>
#include <QTime>
using namespace std;

struct StandardTime{
    string time;
    string date;

    string toString() {
        return date + " " + time;
    }
};

struct ElapsedTime
{
    StandardTime start;
    StandardTime stop;
    bool started;

    ElapsedTime(): started(false)
    {
    }

    void startTimer()
    {
        QDate date = QDate::currentDate();
        QTime time = QTime::currentTime();
        start.date = date.toString().toStdString();
        start.time = time.toString().toStdString();
        started = true;
    }

    void stopTimer()
    {
        QDate date = QDate::currentDate();
        QTime time = QTime::currentTime();
        stop.date = date.toString().toStdString();
        stop.time = time.toString().toStdString();
        started = false;
    }

};

Q_DECLARE_METATYPE(StandardTime);

#endif // TIMESTRUCT_H
