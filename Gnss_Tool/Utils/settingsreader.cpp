#include "settingsreader.h"
#include <QDebug>

SettingsReader::SettingsReader(QString fileName)
{
    settingsFile = fileName;
}

QString SettingsReader::value(QString properties)
{
    qDebug()<<"Read Setting file: "<<settingsFile;
    QSettings settings(settingsFile, QSettings::IniFormat);
    QString val = settings.value(properties, "NONE").toString();
    return val;
}
