#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include "settingsreader.h"

class Utils
{

public:
    Utils();

    static QString getSetting(QString file, QString key) {
        return SettingsReader(file).value(key);
    }
};

#endif // UTILS_H
