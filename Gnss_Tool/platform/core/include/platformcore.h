#ifndef PLATFORM_CORE_H
#define PLATFORM_CORE_H

#include <QObject>
#include "platformcore_global.h"
#include <cppmicroservices/FrameworkFactory.h>
#include <cppmicroservices/Framework.h>
#include <cppmicroservices/BundleContext.h>
#include <cppmicroservices/Bundle.h>
#include <cppmicroservices/BundleImport.h>

using namespace cppmicroservices;

class PLATFORM_CORE_DLLSPEC PlatformCore : public QObject
{
    Q_OBJECT

public:
    PlatformCore();
    int load(std::list<std::string> services);
    void runPlatform();
    void stopPlatform();

private:
    Framework* microServicesFw;
    BundleContext bundleContext;

};


#endif // PLATFORM_CORE_H
