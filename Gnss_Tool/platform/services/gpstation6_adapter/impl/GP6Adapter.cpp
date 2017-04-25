#include <IGP6Adapter.h>
#include <AbstractService.h>
#include "GP6Client.h"
#include <QString>
#include <QMutex>
#include <cppmicroservices/BundleActivator.h>
#include <iostream>
#include <QThread>

using namespace cppmicroservices;

class GP6AdapterService : public AbstractService, public IGP6Adapter
{
private:
    BufferedData<SHARED_GNSS_DATA>* dataBuffer;
    GP6Client *gpClient;

public:

    GP6AdapterService(): AbstractService("GP6Adapter")
    {
        dataBuffer = new BufferedData<SHARED_GNSS_DATA>();
    }

    ~GP6AdapterService()
    {
        delete dataBuffer;
    }

    void connect(const std::string& host, const int& port, const std::list<std::string>& commands)
    {
        gpClient = new GP6Client(dataBuffer);
        gpClient->start(QString::fromStdString(host), port, commands);
    }

    std::string getAvailableData()
    {
        QList<SHARED_GNSS_DATA> clientData = dataBuffer->popAvailable();
        std::string result = "";
        for(auto data : clientData) {
            //set data
            result += "Test Data\n";
        }
        return result;
    }

    void disconnect()
    {
        gpClient->stop();
        delete gpClient;
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
