#include "settingsreader.h"
#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

QString IniSettingsReader::nullSetting = "NONE";

IniSettingsReader::IniSettingsReader(QString fileName)
{
    settingsFile = fileName;
}

QString IniSettingsReader::value(QString properties)
{
    qDebug() << "Read Setting file: " << settingsFile;
    QSettings settings(settingsFile, QSettings::IniFormat);
    QString val = settings.value(properties, nullSetting).toString();
    return val;
}


JSonSettingsReader::JSonSettingsReader(QString fileName)
{
    QString val;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        val = file.readAll();
        file.close();
        config = QJsonDocument::fromJson(val.toUtf8());
    } else {
        qDebug() << "Cant read file: " << fileName;
    }
}

QList<service_item> JSonSettingsReader::getPlatformServices()
{
    QList<service_item> items;
    if(!config.isEmpty()) {
        QJsonObject configObj = config.object();
        QJsonValue platformConfigVal = configObj.value(QString("platform_config"));
        QJsonObject platformConfigObj = platformConfigVal.toObject();

        QJsonValue services = platformConfigObj.value(QString("services"));
        QJsonArray serviceList = services.toArray();

        foreach (const QJsonValue & currentService, serviceList) {
            QJsonObject serviceObj = currentService.toObject();
            service_item item = service_item(serviceObj["name"].toString(), serviceObj["lib"].toString());
            items.push_back(item);
        }

    }
    return items;
}

QList<QString> JSonSettingsReader::getCommandsForReceiver()
{
    QList<QString> commands;
    if(!config.isEmpty()) {
        QJsonObject configObj = config.object();
        QJsonValue platformConfigVal = configObj.value(QString("platform_config"));
        QJsonObject platformConfigObj = platformConfigVal.toObject();

        QJsonValue commandsVal = platformConfigObj.value(QString("commands"));
        QJsonArray commandList = commandsVal.toArray();

        foreach (const QJsonValue & commandLog, commandList) {
            commands.push_back(commandLog.toString());
        }
    }
    return commands;
}
