#ifndef SETTINGSREADER_H
#define SETTINGSREADER_H
#include <QString>
#include <QSettings>

class SettingsReader
{
private:
    QSettings settings;
    QString settingsFile;

public:
    SettingsReader(QString fileName);
    QString value(QString properties);
};

#endif // SETTINGSREADER_H
