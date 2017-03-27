#include <cppmicroservices/BundleActivator.h>
#include <cppmicroservices/BundleContext.h>
#include <cppmicroservices/GetBundleContext.h>
#include <QtConcurrent/QtConcurrent>
#include "utils.h"
#include "ServiceList.h"

#include <iostream>

using namespace cppmicroservices;

class Transport : public BundleActivator
{
    typedef ServiceReference<ILogger> LoggerRef;
    typedef ServiceReference<IGP6Adapter> GP6AdapterRef;

    void Start(BundleContext ctx)
    {
        stillActive = true;
        loggerServiceRef = ctx.GetServiceReference<ILogger>();
        gp6AdapterServiceRef = ctx.GetServiceReference<IGP6Adapter>();
        QtConcurrent::run(this, &Transport::dispatch);
    }

    void Stop(BundleContext)
    {
        stillActive = false;
    }

    bool checkAvailability() const
    {
        if (!loggerServiceRef)
        {
            std::cout << "ILogger reference invalid" << std::endl;
            return false;
        }
        if (!gp6AdapterServiceRef)
        {
            std::cout << "IGP6Adapter reference invalid" << std::endl;
            return false;
        }
        return true;
    }

public:

    /**
     * @brief dispatch - workflow for services
     */
    void dispatch()
    {
        if(!checkAvailability()) {
            return;
        }
        auto ctx = GetBundleContext();

        // Get services
        auto logger = ctx.GetService(loggerServiceRef);
        auto gp6adapter = ctx.GetService(gp6AdapterServiceRef);

        if (!logger || !gp6adapter) {
            std::cout << "WARNING: Some services are not available" << std::endl;
        } else {
            std::list<std::string> testCommands;
            testCommands.push_back("Hello Server");
            testCommands.push_back("I`m Bob");

            logger->log("GP6Adapter try to connect to agent: "
                        + Utils::getSetting("gpstation_agent_host").toStdString()
                        + " port: " + Utils::getSetting("gpstation_agent_port").toStdString());

            gp6adapter->connect(Utils::getSetting("gpstation_agent_host").toStdString(),
                                Utils::getSetting("gpstation_agent_port").toInt(),
                                testCommands);

            while (stillActive) {
                auto receiverData = gp6adapter->getAvailableData();
                if(receiverData.size()) {
                    logger->log("GP6Adapter receive data: " + receiverData);
                }
            }
        }
    }

private:
    LoggerRef loggerServiceRef;
    GP6AdapterRef gp6AdapterServiceRef;
    volatile bool stillActive;
};

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(Transport)
