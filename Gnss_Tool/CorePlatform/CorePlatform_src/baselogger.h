#ifndef BASELOGGER_H
#define BASELOGGER_H
#include "platformmodule.h"
#include "QFile"
using namespace PlatformModule;

class PLATFORMLOGIC_EXPORT BaseLogger: public AbstractModule
{
public:
    BaseLogger(QObject* parent=0, QFile* logFile=0);
    ~BaseLogger();
    virtual bool setup(AbstractPlatformBuilder *configurator);
    virtual ModuleDescriptor getDescriptor();

public slots:
    virtual ExecResult execute(QByteArray data);
    virtual ExecResult execute();

private:
    QFile* logFile;
    void log(QString logString);
    bool openLogFile(bool truncate);
};

#endif // BASELOGGER_H
