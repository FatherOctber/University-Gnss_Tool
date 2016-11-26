#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include "settingsreader.h"
#include <QDir>

class Utils
{
public:
    Utils();

    static QString getSetting(QString key) {
        QString file;
        #if defined(TEST_RUN)
            file = QDir::currentPath()+"/test_settings.ini";
        #else
            file = QDir::currentPath()+"/settings.ini";
        #endif
        return SettingsReader(file).value(key);
    }   
};

#endif // UTILS_H
