#ifndef TESTPLATFORM_H
#define TESTPLATFORM_H
#include "coreplatform.h"
#include "QString"
using namespace PlatformModule;

#define PEN ModuleDescriptor("Pen")
#define PINEAPPLE ModuleDescriptor("Pineapple")

class AbstractTestModule: public AbstractModule
{
    Q_OBJECT

protected:
    QString testDataResult;

public:
    AbstractTestModule(QObject *parent = 0);
    QString getTestDataResult();
};

/**
 * @brief The TestModule1 class
 */
class TestModule1: public AbstractTestModule
{
    Q_OBJECT

public:
    TestModule1(QObject *parent = 0);

    virtual ModuleDescriptor getDescriptor();

    virtual bool setup(AbstractPlatformBuilder *configurator);

    virtual ExecResult execute(QByteArray data);

    virtual ExecResult execute();


signals:
    void todo();

private:
    AbstractModule* penModule;
    static ModuleDescriptor descriptor;
};

/**
 * @brief The TestModule2 class
 */
class TestModule2: public AbstractTestModule
{
    Q_OBJECT
public:
    TestModule2(QObject *parent = 0);

    virtual ModuleDescriptor getDescriptor();

    virtual bool setup(AbstractPlatformBuilder *configurator);

    virtual ExecResult execute(QByteArray data);

    virtual ExecResult execute();


signals:
    void voice(QByteArray data);

private:
    AbstractModule* pineapleModule;
    static ModuleDescriptor descriptor;
};


class TestPlatform: public CorePlatform
{
    Q_OBJECT

public:
    TestPlatform(QObject* parent, std::list<AbstractTestModule*> testModules);

private:
    std::list<AbstractTestModule*> moduleList;

protected:
    virtual void buildPlatform();
    virtual bool setup(AbstractPlatformBuilder *configurator);
    virtual ModuleDescriptor getDescriptor();
};


#endif // TESTPLATFORM_H
