#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include "settingsreader.h"
#include <QDir>
#include <QList>

class Utils
{
    struct ErrorBox
    {

    public:
        void appendEror(QString error)
        {
            errorList.append(error);
        }

        QString getLastError() {
            return errorList.last();
        }

        QString getErrors() {
            QString errors = "";
            for(QString error : errorList) {
                errors += error + "\n";
            }
            return errors;
        }

    private:
        QList<QString> errorList;
    };

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

    static QString nullSettingSymbol() {
        return SettingsReader::nullSetting;
    }
};

#endif // UTILS_H
