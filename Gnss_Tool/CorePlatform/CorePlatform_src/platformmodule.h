#ifndef PLATFORMMODULE_H
#define PLATFORMMODULE_H
#include <QObject>
#include <map>
#include "QString"
using namespace std;

namespace PlatformModule{

    struct ExecResult {
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


    struct ModuleDescriptor
    {
        QString code;

        ModuleDescriptor(QString code) {
            this->code = code;
        }

        bool operator == (const ModuleDescriptor& other) const
        {
            return this->code == other.code;
        }

        bool operator > (const ModuleDescriptor& other) const
        {
            return this->code > other.code;
        }

        bool operator < (const ModuleDescriptor& other) const
        {
            return this->code < other.code;
        }
    };

    /**
     * @brief The AbstractPlatformConfigurator class
     * bind modules by descriptor
     */
    class AbstractModule;

    class AbstractPlatformConfigurator
    {
    protected:
        map<ModuleDescriptor, AbstractModule*> modules;

    public:
        AbstractPlatformConfigurator();
        virtual ~AbstractPlatformConfigurator();
        virtual void configurate()=0;
        AbstractModule* getModule(ModuleDescriptor descriptor);
        list<AbstractModule*> getModules();
    };



    /**
     * @brief The AbstractModule class
     * Basic for all modules
     */
    class AbstractModule: public QObject
    {
        Q_OBJECT

    public:
        AbstractModule(QObject *parent = 0);
        virtual ~AbstractModule() {}
        virtual bool setup(AbstractPlatformConfigurator *configurator)=0;
        virtual ModuleDescriptor getDescriptor();

    public slots:
        virtual ExecResult execute(QByteArray data)=0;
        virtual ExecResult execute()=0;

    };

}

#endif // PLATFORMMODULE_H
