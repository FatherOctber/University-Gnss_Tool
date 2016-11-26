#include "coreplatform.h"
#include "controls.h"
#include "baselogger.h"

CorePlatform::CorePlatform(QObject* bindingParent): AbstractModule(bindingParent)
{
}

void CorePlatform::buildPlatform()
{
    AbstractModule* logger = new BaseLogger;

    modules[PLATFORM_LOGGER] = logger;
    modules[PLATFORM_CORE] = this;
    //todo other modules
}

ModuleDescriptor CorePlatform::getDescriptor()
{
    return PLATFORM_CORE;
}

bool CorePlatform::setup(AbstractPlatformBuilder *configurator)
{
    //bind modules
    connect(this, SIGNAL(sentLog(QByteArray)), configurator->getModule(PLATFORM_LOGGER), SLOT(execute(QByteArray))); // test only
    connect(this, SIGNAL(handover()), this, SLOT(execute())); // test only

    return true;
}

ExecResult CorePlatform::execute(QByteArray data)
{
    //todo core instructions
    emit sentLog(QByteArray("Core Platform doesnt support any execute method"));
    return ExecResult::ANY;
}


ExecResult CorePlatform::execute()
{
    //todo core instructions
    emit sentLog(QByteArray("Core Platform doesnt support any execute method"));
    return ExecResult::ANY;
}

void CorePlatform::startUp()
{
    //lazy initialize
    buildPlatform();
    if(setup(this)) {
        emit sentLog(QByteArray::fromStdString(getDescriptor().toStdString() + " was started up successfuly"));
    }

    emit handover();
}


