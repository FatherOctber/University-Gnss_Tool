#include <ILogger.h>
#include <AbstractService.h>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QtConcurrent/QtConcurrent>
#include <QMutex>
#include <QThreadPool>
#include <QTime>
#include <cppmicroservices/BundleActivator.h>
#include <iostream>

using namespace cppmicroservices;

class LoggerService : public AbstractService, public ILogger
{
private:
    QFile* file;
    QMutex *mutex;

public:

    LoggerService(): AbstractService("Logger")
    {
        mutex = new QMutex();
        file = new QFile("log.txt");
    }

    ~LoggerService()
    {
        delete mutex;
    }

    void log(const std::string& msg)
    {
        asyncTask( [&](std::string logMsg) {
            QMutexLocker ml(mutex);
            if (file->open(QIODevice::ReadWrite | QIODevice::Append)) {
                QTextStream stream(file);
                QString logString = QTime::currentTime().toString() + ": " + QString::fromStdString(logMsg);
                stream << logString << endl;
                file->close();
            }
        }, msg);
    }
};

class LoggerActivator : public BundleActivator
{
  void Start(BundleContext ctx)
  {
    auto service = std::make_shared<LoggerService>();
    ctx.RegisterService<ILogger>(service);
  }

  void Stop(BundleContext)
  {
  }

};

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(LoggerActivator)
