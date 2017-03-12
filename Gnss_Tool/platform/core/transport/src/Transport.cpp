#include <cppmicroservices/BundleActivator.h>
#include <cppmicroservices/BundleContext.h>
#include <cppmicroservices/GetBundleContext.h>
#include "ServiceList.h"

#include <iostream>

using namespace cppmicroservices;

class Transport : public BundleActivator
{

    typedef ServiceReference<ILogger> LoggerRef;

    void Start(BundleContext ctx)
    {
        auto ref = ctx.GetServiceReference<ILogger>();
        control(ref);
    }

    void Stop(BundleContext)
    {
        // Nothing to do
    }

    void control(const LoggerRef& ref) const
    {
        if (!ref)
        {
            std::cout << "ILogger reference invalid" << std::endl;
            return;
        }

        // We can also get the bundle context like this
        auto ctx = GetBundleContext();

        // Get the ServiceTime service
        auto logger = ctx.GetService(ref);
        if (!logger)
        {
            std::cout << "Logger not available" << std::endl;
        }
        else
        {
            std::cout << "Start send log" << std::endl;
            const std::string logMsg = "Hello, this is test msg";
            logger->log(logMsg);
            std::cout << "Finish send log" << std::endl;
        }
    }
};

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(Transport)
