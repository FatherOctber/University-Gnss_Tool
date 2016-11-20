#include "coreplatform.h"

CorePlatform::CorePlatform(QObject* bindingParent): AbstractModule(bindingParent)
{
}

void CorePlatform::configurate()
{
    AbstractModule* logger = new BaseLogger;

    modules[PLATFORM_LOGGER] = logger;
    //todo other modules
}

bool CorePlatform::setup(AbstractPlatformConfigurator *configurator)
{
    //bind modules
    connect(this, SIGNAL(sentLog(QByteArray)), configurator->getModule(PLATFORM_LOGGER), SLOT(execute(QByteArray))); // test only
    //connect(this, SIGNAL(handover()), this, SLOT(execute())); // test only

    return true;
}

ExecResult CorePlatform::execute(QByteArray data)
{
    emit sentLog(QByteArray("Core Platform doesnt support any execute method"));
    return ExecResult::ANY;
}


ExecResult CorePlatform::execute()
{
    emit sentLog(QByteArray("Core Platform doesnt support any execute method"));
    return ExecResult::ANY;
}

void CorePlatform::startUp()
{
    //lazy initialize
    configurate();
    if(setup(this)) {
        emit sentLog(QByteArray("Core Platform was started up successfuly"));
    }

    emit handover();
}

