#include <igp6adapter_export.h>
#include <string>
#include <list>

struct IGP6ADAPTER_EXPORT IGP6Adapter
{
    virtual ~IGP6Adapter();

    /**
     * @brief connect to gpstation6-agent
     * @param host - host name
     * @param port
     * @param commans - commands to send to receiver
     */
    virtual void connect(const std::string& host, const int& port, const std::list<std::string>& commands) = 0;

    /**
     * @brief getAvailableData
     * @return data structure
     */
    virtual std::string getAvailableData() = 0;

};
