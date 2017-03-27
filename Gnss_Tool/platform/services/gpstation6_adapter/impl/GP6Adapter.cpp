#include <IGP6Adapter.h>
#include <AbstractService.h>
#include "GP6Client.h"
#include <QString>
#include <QMutex>
#include <cppmicroservices/BundleActivator.h>
#include <iostream>

using namespace cppmicroservices;

class GP6AdapterService : public AbstractService, public IGP6Adapter
{
private:
    QMutex *mutex;
    GP6Client *gpClient;

public:

    GP6AdapterService(): AbstractService("GP6Adapter")
    {
        mutex = new QMutex();
    }

    ~GP6AdapterService()
    {
        delete mutex;
        delete gpClient;
    }

    void connect(const std::string& host, const int& port, const std::list<std::string>& commands)
    {
        gpClient = new GP6Client();
        gpClient->tryToConnect(QString::fromStdString(host), port, commands);
    }

    std::string getAvailableData()
    {
        std::string result = "";
        QList<QByteArray> dataList = gpClient->getAvailableData();
        for(auto data : dataList) {
            //parse data to gnns data structure
            result += data.toStdString() + "\n";
        }
        return result;
    }
};

class GP6AdapterActivator : public BundleActivator
{
  void Start(BundleContext ctx)
  {
    auto service = std::make_shared<GP6AdapterService>();
    ctx.RegisterService<IGP6Adapter>(service);
  }

  void Stop(BundleContext)
  {
  }

};

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(GP6AdapterActivator)
