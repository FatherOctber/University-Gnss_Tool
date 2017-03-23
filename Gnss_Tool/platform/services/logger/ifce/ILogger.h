#include <ilogger_export.h>
#include <string>

struct ILOGGER_EXPORT ILogger
{
  virtual ~ILogger();

  //log message
  virtual void log(const std::string& msg) = 0;
};
