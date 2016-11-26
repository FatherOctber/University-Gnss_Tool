#ifndef PLATFORMMODULE_H
#define PLATFORMMODULE_H
#include <QObject>
#include <map>
#include "QString"
#include "platformlogic_global.h"
using namespace std;

namespace PlatformModule{

    struct PLATFORMLOGIC_EXPORT ExecResult {
        int retCode;

        ExecResult(int code) {
            this->retCode = code;
        }

        bool operator == (const ExecResult& other) const
        {
            return this->retCode == other.retCode;
        }

        static ExecResult UNKNOWN;
        static ExecResult GOOD;
        static ExecResult ERROR;
        static ExecResult ANY;
    };


    struct PLATFORMLOGIC_EXPORT ModuleDescriptor
    {
        QString code;

        ModuleDescriptor(QString code) {
            this->code = code;
        }

        bool operator == (const ModuleDescriptor& other) const
        {
            return this->code.toLower() == other.code.toLower();
        }

        bool operator > (const ModuleDescriptor& other) const
        {
            return this->code.toLower() > other.code.toLower();
        }

        bool operator < (const ModuleDescriptor& other) const
        {
            return this->code.toLower() < other.code.toLower();
        }

        friend ostream& operator << (ostream& os, const ModuleDescriptor& descriptor)
        {
            os << descriptor.code.toStdString();
            return os;
        }

        const std::string toStdString()
        {
            return code.toStdString();
        }

    };

    /**
     * @brief The AbstractPlatformConfigurator class
     * bind modules by descriptor
     */
    class AbstractModule;

    class PLATFORMLOGIC_EXPORT AbstractPlatformBuilder
    {
    protected:
        map<ModuleDescriptor, AbstractModule*> modules;

    public:
        AbstractPlatformBuilder();
        virtual ~AbstractPlatformBuilder();
        virtual void buildPlatform()=0;
        AbstractModule* getModule(ModuleDescriptor descriptor);
    };



    /**
     * @brief The AbstractModule class
     * Basic for all modules
     */
    class PLATFORMLOGIC_EXPORT AbstractModule: public QObject
    {
        Q_OBJECT

    public:
        AbstractModule(QObject *parent = 0);
        virtual ~AbstractModule() {}
        virtual bool setup(AbstractPlatformBuilder *configurator)=0;
        virtual ModuleDescriptor getDescriptor();

    public slots:
        virtual ExecResult execute(QByteArray data)=0;
        virtual ExecResult execute()=0;

    };

}

#endif // PLATFORMMODULE_H
