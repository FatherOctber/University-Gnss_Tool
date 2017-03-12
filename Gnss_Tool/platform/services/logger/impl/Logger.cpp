#include <ILogger.h>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <cppmicroservices/BundleActivator.h>

using namespace cppmicroservices;

class Logger : public ILogger
{

private:
    /**
     * @brief file - log file
     */
    QFile* file;

public:

    Logger()
    {
        file = new QFile("log.txt");
    }

    void log(const std::string& msg) const
    {
        if (file->open(QIODevice::ReadWrite | QIODevice::Append)) {
            QTextStream stream(file);
            stream << msg.c_str() << endl;
            file->close();
        }

    }

};

class LoggerActivator : public BundleActivator
{
  void Start(BundleContext ctx)
  {
    auto service = std::make_shared<Logger>();
    ctx.RegisterService<ILogger>(service);
  }

  void Stop(BundleContext)
  {
  }

};

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(LoggerActivator)
