#include "testplatform.h"
#include "QDebug"

AbstractTestModule::AbstractTestModule(QObject *parent): AbstractModule(parent)
{
}

TestModule1::TestModule1(QObject *parent): AbstractTestModule(parent)
{
}

ModuleDescriptor TestModule1::getDescriptor()
{
    return PINEAPPLE;
}

bool TestModule1::setup(AbstractPlatformBuilder *configurator)
{
    AbstractModule* pen = configurator->getModule(PEN);
    if(pen) {
        penModule = pen;
        connect(this, SIGNAL(todo()), penModule, SLOT(execute()));
        return true;
    } else {
        return false;
    }
}

ExecResult TestModule1::execute(QByteArray data)
{
    testDataResult = data.data();
    return ExecResult(5);

}

ExecResult TestModule1::execute()
{
    //nothing
    emit todo();
    return ExecResult(0);
}

TestModule2::TestModule2(QObject *parent): AbstractTestModule(parent)
{
}

ModuleDescriptor TestModule2::getDescriptor()
{
    return PEN;
}

bool TestModule2::setup(AbstractPlatformBuilder *configurator)
{
    AbstractModule* pineaple = configurator->getModule(PINEAPPLE);
    if(pineaple) {
        pineapleModule = pineaple;
        connect(this, SIGNAL(voice(QByteArray)), pineapleModule, SLOT(execute(QByteArray)));
        return true;
    } else {
        return false;
    }
}

ExecResult TestModule2::execute(QByteArray data)
{
    emit voice(data);
    return ExecResult(5);
}

ExecResult TestModule2::execute()
{
    testDataResult = "Ok";
    return ExecResult(0);
}

QString AbstractTestModule::getTestDataResult()
{
    return testDataResult;
}

TestPlatform::TestPlatform(QObject* parent, std::list<AbstractTestModule*> testModules): CorePlatform(parent)
{
    moduleList = testModules;
}

void TestPlatform::buildPlatform()
{
    for(AbstractTestModule* module : moduleList) {
        modules[module->getDescriptor()] = module;
    }
}

bool TestPlatform::setup(AbstractPlatformBuilder *configurator)
{
    try{
        connect(this, SIGNAL(sentLog(QByteArray)), configurator->getModule(PEN), SLOT(execute(QByteArray)));
        connect(this, SIGNAL(handover()), configurator->getModule(PINEAPPLE), SLOT(execute()));
        configurator->getModule(PEN)->setup(configurator);
        configurator->getModule(PINEAPPLE)->setup(configurator);
    }
    catch(std::exception& ex) {
        qDebug() << ex.what();
        return false;
    }

    return true;
}

ModuleDescriptor TestPlatform::getDescriptor()
{
    return ModuleDescriptor("TEST_PLATFORM");
}
