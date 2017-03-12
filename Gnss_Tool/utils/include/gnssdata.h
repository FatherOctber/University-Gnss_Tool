#ifndef GNSSDATA_H
#define GNSSDATA_H
#include <string>
#include <iostream>
#include <vector>
#include <QMetaType>
using namespace std;

struct StandardTime{
    string time;
    string date;
};

struct GnssData{
    std::vector<double> data; //some collection of data

    bool operator==(const GnssData &other) const
    {
        return this->data==other.data;
    }

    //etc
};

Q_DECLARE_METATYPE(StandardTime);
Q_DECLARE_METATYPE(GnssData);

#endif // GNSSDATA_H
