#ifndef PLATFORMCONFIG_H
#define PLATFORMCONFIG_H
#include <QObject>
#include <QString>
#include <list>
#include <QJsonDocument>
using namespace std;

struct service_item
{
    QString name;
    string lib;

    service_item(QString name, QString lib) {
        this->name = name;
        this->lib = lib.toStdString();
    }
};

class PlatfromConfig: public QObject
{
    Q_OBJECT
public:
    PlatfromConfig();
    bool loadFile(QString configFile);
    list<service_item> getPlatformServices();

private:
    list<service_item> serviceFileList;
    QJsonDocument config;
};

#endif // PLATFORMCONFIG_H
