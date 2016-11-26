#include "platformmodule.h"
#include "utils.h"
#include <QDebug>

namespace PlatformModule {

    ExecResult ExecResult::UNKNOWN = ExecResult(99);
    ExecResult ExecResult::GOOD = ExecResult(0);
    ExecResult ExecResult::ERROR = ExecResult(1);
    ExecResult ExecResult::ANY = ExecResult(10);

    AbstractPlatformBuilder::AbstractPlatformBuilder()
    {
    }

    AbstractPlatformBuilder::~AbstractPlatformBuilder()
    {
        qDebug() << "Run AbstractPlatformConfigurator destructor:: clear modules";
        modules.clear();
    }

    AbstractModule* AbstractPlatformBuilder::getModule(ModuleDescriptor descriptor)
    {
        return modules[descriptor];
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
