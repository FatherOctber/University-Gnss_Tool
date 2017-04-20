#ifndef SETTINGSREADER_H
#define SETTINGSREADER_H
#include <QString>
#include <QJsonDocument>
#include <list>

class IniSettingsReader
{
private:
    QString settingsFile;

public:
    static QString nullSetting;
    IniSettingsReader(QString fileName);
    QString value(QString properties);
};


struct service_item
{
    QString name;
    QString lib;

    service_item(QString name, QString lib) {
        this->name = name;
        this->lib = lib;
    }
};

class JSonSettingsReader
{
public:
    JSonSettingsReader(QString configFile);
    QList<service_item> getPlatformServices();
    QList<QString> getCommandsForReceiver();

private:
    QJsonDocument config;
};
#endif // SETTINGSREADER_H
