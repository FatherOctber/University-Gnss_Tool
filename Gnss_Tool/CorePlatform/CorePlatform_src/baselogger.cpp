#include "baselogger.h"
#include "controls.h"
#include "utils.h"
#include <QDebug>

BaseLogger::BaseLogger(QObject *parent, QFile *logFile):AbstractModule(parent)
{
    if(logFile) {
        this->logFile = logFile;
        if(!openLogFile(false)) {
            qDebug() << "!!!Cant open log file!!!";
        } else {
            log("Successfuly open log file!");
        }
    } else {
        this->logFile = new QFile( Utils::getSetting("log_file"));
        if(!openLogFile(true)) {
            qDebug() << "!!!Cant open log file!!!";
        } else {
            log("Successfuly open log file!");
        }
    }
}

BaseLogger::~BaseLogger()
{
    if(logFile != 0 && logFile->isOpen()) {
        logFile->close();
    }
}

bool BaseLogger::setup(AbstractPlatformBuilder *configurator)
{
    //nothing to bind
    return true;
}

void BaseLogger::log(QString logString)
{
    if(openLogFile(false)) {
        logFile->write(QByteArray::fromStdString(getDescriptor().toStdString() + ": " + logString.toStdString() + "\n"));
        logFile->close();
    } else {
        qDebug() << "!!!Can not write log to file!!!";
    }
}

bool BaseLogger::openLogFile(bool truncate)
{
    logFile->close();
    if(truncate) {
        return logFile->open(QFile::WriteOnly | QFile::Append | QFile::Truncate);
    }
    else {
        return logFile->open(QFile::WriteOnly | QFile::Append);
    }
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





