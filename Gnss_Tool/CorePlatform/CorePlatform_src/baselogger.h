#ifndef BASELOGGER_H
#define BASELOGGER_H
#include "platformmodule.h"
#include "QFile"
using namespace PlatformModule;

class BaseLogger: public AbstractModule
{
public:
    BaseLogger(QObject* parent=0);
    ~BaseLogger();
    virtual bool setup(AbstractPlatformConfigurator *configurator);
    virtual ModuleDescriptor getDescriptor();

public slots:
    virtual ExecResult execute(QByteArray data);
    virtual ExecResult execute();

private:
    QFile* logFile;
    void log(QString logString);
};

#endif // BASELOGGER_H
