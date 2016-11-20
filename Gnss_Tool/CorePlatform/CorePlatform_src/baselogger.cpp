#include "baselogger.h"
#include "controls.h"
#include <QDebug>

BaseLogger::BaseLogger(QObject *parent):AbstractModule(parent)
{
    QString settings = Utils::SETTINGS;
    logFile = new QFile( Utils::getSetting(settings, "log_file"));
    if(!logFile->open(QFile::WriteOnly | QFile::Append)) {
        qDebug() << "!!!Cant open log file!!!";
    } else {
        log("Successfuly open log file!");
    }
}

BaseLogger::~BaseLogger()
{
    if(logFile != 0 && logFile->isOpen()) {
        logFile->close();
    }
}

bool BaseLogger::setup(AbstractPlatformConfigurator *configurator)
{
    //nothing to bind
    return true;
}

void BaseLogger::log(QString logString)
{
    logFile->write(QByteArray::fromStdString("BASE_LOGGER:: "+logString.toStdString()));
}


ModuleDescriptor BaseLogger::getDescriptor()
{
    return PLATFORM_LOGGER;
}

ExecResult BaseLogger::execute(QByteArray data)
{
    log(QString(data));
    return ExecResult::GOOD;
}

ExecResult BaseLogger::execute()
{
    log("execute() is not enable for "+getDescriptor().code+". Use execute(QbyteArray) to log some data");
    return ExecResult::ANY;
}





