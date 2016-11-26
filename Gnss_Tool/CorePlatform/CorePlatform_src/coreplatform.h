#ifndef COREPLATFORM_H
#define COREPLATFORM_H

#include "platformmodule.h"
using namespace PlatformModule;

class PLATFORMLOGIC_EXPORT CorePlatform: protected AbstractModule, protected AbstractPlatformBuilder
{
    Q_OBJECT

public:
    CorePlatform(QObject *bindingParent);
    void startUp();

signals:
    void handover();
    void sentLog(QByteArray data);

protected:
    virtual void buildPlatform();
    virtual bool setup(AbstractPlatformBuilder *configurator);
    virtual ModuleDescriptor getDescriptor();

protected slots:
    virtual ExecResult execute(QByteArray data);
    virtual ExecResult execute();
};


#endif // COREPLATFORM_H
