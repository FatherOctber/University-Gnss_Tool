#include "platformconfig.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

PlatfromConfig::PlatfromConfig(): QObject()
{
}

bool PlatfromConfig::loadFile(QString configFile)
{
    QString val;
    QFile file(configFile);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        val = file.readAll();
        file.close();
        config = QJsonDocument::fromJson(val.toUtf8());
        return true;
    }
    else return false;
}

list<service_item> PlatfromConfig::getPlatformServices()
{
    if(this->serviceFileList.size()==0 && !config.isEmpty()) {
        QJsonObject configObj = config.object();
        QJsonValue services = configObj.value(QString("services"));
        QJsonObject servicesItem = services.toObject();

        QJsonValue service = servicesItem.value(QString("service"));
        QJsonArray serviceList = service.toArray();

        foreach (const QJsonValue & currentService, serviceList) {
            QJsonObject serviceObj = currentService.toObject();
            service_item item = service_item(serviceObj["name"].toString(), serviceObj["lib"].toString());
            this->serviceFileList.push_back(item);
        }
    }
    return this->serviceFileList;
}
