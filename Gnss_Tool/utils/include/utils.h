#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include "settingsreader.h"
#include <QDir>
#include <QList>
#include <iostream>

class Utils
{
public:
    Utils();

    static QString getSetting(QString key, QString configFileDir) {
        QString file = configFileDir;
        return IniSettingsReader(file).value(key);
    }

    static QString getSetting(QString key) {
        QString file;
#if defined(TEST_RUN)
        file = QDir::currentPath()+"test_res/test_settings.ini";
#else
        file = QDir::currentPath()+"/settings.ini";
#endif
        return IniSettingsReader(file).value(key);
    }

    static QString getSettingDefault(QString key, QString defaultValue) {
        QString val = Utils::getSetting(key);
        if(val == Utils::nullSettingSymbol()) {
            return defaultValue;
        }
    }

    static QList<service_item> getSettingServices(QString jsonFile) {
        return JSonSettingsReader(jsonFile).getPlatformServices();
    }

    static QList<QString> getSettingCommands(QString jsonFile) {
        return JSonSettingsReader(jsonFile).getCommandsForReceiver();
    }

    static QString nullSettingSymbol() {
        return IniSettingsReader::nullSetting;
    }

    static void consoleLog(std::string msg) {
        std::cout << "CONSOLE_LOGGER:> " << msg << std::endl;
    }
};

#endif // UTILS_H
