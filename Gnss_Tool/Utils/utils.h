#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include "settingsreader.h"
#include <QDir>

class Utils
{
public:
    Utils();

    static QString getSetting(QString file, QString key) {
        return SettingsReader(file).value(key);
    }

    static QString SETTINGS;
};

#endif // UTILS_H
