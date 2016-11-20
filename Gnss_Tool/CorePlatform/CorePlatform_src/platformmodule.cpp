#include "platformmodule.h"
#include "utils.h"
#include <QDebug>

namespace PlatformModule {

    ExecResult ExecResult::UNKNOWN = ExecResult(99);
    ExecResult ExecResult::GOOD = ExecResult(0);
    ExecResult ExecResult::ERROR = ExecResult(1);
    ExecResult ExecResult::ANY = ExecResult(10);

    AbstractPlatformConfigurator::AbstractPlatformConfigurator()
    {
    }

    AbstractPlatformConfigurator::~AbstractPlatformConfigurator()
    {
        qDebug() << "Run AbstractPlatformConfigurator destructor:: clear modules";
        modules.clear();
    }

    AbstractModule* AbstractPlatformConfigurator::getModule(ModuleDescriptor descriptor)
    {
        return modules[descriptor];
    }

    list<AbstractModule*> AbstractPlatformConfigurator::getModules()
    {
        std::list<AbstractModule*> moduleList;
        std::for_each(modules.begin(), modules.end(), [&](const std::pair<ModuleDescriptor, AbstractModule*>& mapModule) {
            moduleList.push_back(mapModule.second);
        });
        return moduleList;
    }

    AbstractModule::AbstractModule(QObject *parent)
        : QObject(parent)
    {
    }

    ModuleDescriptor AbstractModule::getDescriptor()
    {
        return ModuleDescriptor("ABSTRACT");
    }

}
