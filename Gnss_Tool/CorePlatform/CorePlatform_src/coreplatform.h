#ifndef COREPLATFORM_H
#define COREPLATFORM_H

#include "coreplatform_global.h"
#include "controls.h"
using namespace PlatformModule;

class COREPLATFORMSHARED_EXPORT CorePlatform: protected AbstractModule, protected AbstractPlatformConfigurator
{
    Q_OBJECT

public:
    CorePlatform(QObject *bindingParent);
    void startUp();

signals:
    void handover();
    void sentLog(QByteArray data);

protected:
    virtual void configurate();
    virtual bool setup(AbstractPlatformConfigurator *configurator);

protected slots:
    virtual ExecResult execute(QByteArray data);
    virtual ExecResult execute();
};

#endif // COREPLATFORM_H
