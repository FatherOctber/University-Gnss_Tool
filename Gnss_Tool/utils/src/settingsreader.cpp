#include "settingsreader.h"
#include <QDebug>

QString SettingsReader::nullSetting = "NONE";

SettingsReader::SettingsReader(QString fileName)
{
    settingsFile = fileName;
}

QString SettingsReader::value(QString properties)
{
    qDebug() << "Read Setting file: " << settingsFile;
    QSettings settings(settingsFile, QSettings::IniFormat);
    QString val = settings.value(properties, nullSetting).toString();
    return val;
}
