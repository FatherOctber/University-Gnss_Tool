#ifndef ABSTRACTSERVICE_H
#define ABSTRACTSERVICE_H
#include <QMutex>
#include <QThreadPool>
#include <QtConcurrent/QtConcurrent>

class AbstractService
{
protected:
    QThreadPool *pool;
    QString serviceName;

public:
    AbstractService(QString serviceName = "Abstract", int maxThread = 10)
    {
        pool = new QThreadPool();
        pool->setMaxThreadCount(maxThread);
        this->serviceName = serviceName;
    }

    virtual ~AbstractService()
    {
        delete pool;
    }

protected:
    /**
     * Highly recommended to use async task for hard calculations
     */
    template<typename Func> void asyncTask(Func f)
    {
        QtConcurrent::run(pool, f);
    }

    template <typename Func, typename Arg1> void asyncTask(Func f, const Arg1 &arg1)
    {
        QtConcurrent::run(pool, f, arg1);
    }

    template <typename Func, typename Arg1, typename Arg2> void asyncTask(Func f, const Arg1 &arg1, const Arg2 &arg2)
    {
        QtConcurrent::run(pool, f, arg1, arg2);
    }

};
#endif
