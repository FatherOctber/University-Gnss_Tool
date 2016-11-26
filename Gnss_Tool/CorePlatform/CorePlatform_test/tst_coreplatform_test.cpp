#include <QString>
#include <QtTest>
#include "testplatform.h"
#include "baselogger.h"
#include "controls.h"
#include "utils.h"
#include "QDebug"

class CorePlatform_test : public QObject
{
    Q_OBJECT

public:
    CorePlatform_test();
private:
    QFile* getClearFile(QString name);

private Q_SLOTS:
    void testCorePlatform();
    void testPlatformLogger();
};

CorePlatform_test::CorePlatform_test()
{
}

QFile* CorePlatform_test::getClearFile(QString name)
{
    QFile* logFile = new QFile(name);
    if(logFile->open(QFile::WriteOnly)) {
        return logFile;
    } else {
        return NULL;
    }
}


void CorePlatform_test::testCorePlatform()
{
    AbstractTestModule* pineapple = new TestModule1;
    AbstractTestModule* pen = new TestModule2;
    std::list<AbstractTestModule*> moduleList;
    moduleList.push_back(pen);
    moduleList.push_back(pineapple);

    CorePlatform* platform = new TestPlatform(this, moduleList);
    platform->startUp();
    qDebug() << "platform start up";

    QCOMPARE(QString("TEST_PLATFORM was started up successfuly"), pineapple->getTestDataResult());
    QCOMPARE(QString("Ok"), pen->getTestDataResult());
}

void CorePlatform_test::testPlatformLogger()
{
    QFile* logFile = getClearFile(Utils::getSetting("log_file"));
    if(!logFile) {
        QFAIL("log file cant be opened");
    }

    BaseLogger *logger = new BaseLogger(this, logFile);
    logger->setup(NULL);
    std::string text = "some text for test";
    logger->execute(QByteArray::fromStdString( text ));

    if(!logFile->open(QFile::ReadOnly)) {
        QFAIL("log file cant be opened");
    }

    QByteArray actual = logFile->readAll();
    QByteArray expected;
    expected.append(QByteArray::fromStdString(PLATFORM_LOGGER.toStdString()+": Successfuly open log file!\n"));
    expected.append(QByteArray::fromStdString(PLATFORM_LOGGER.toStdString()+": "+text+"\n"));

    QCOMPARE(actual, expected);

    delete logger;
    delete logFile;
}

QTEST_APPLESS_MAIN(CorePlatform_test)

#include "tst_coreplatform_test.moc"
