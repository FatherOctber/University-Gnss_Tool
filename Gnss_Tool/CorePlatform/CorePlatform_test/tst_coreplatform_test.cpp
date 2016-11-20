#include <QString>
#include <QtTest>
#include "testplatform.h"
#include "QDebug"

#define TEST_RUN //switch global to test

class CorePlatform_test : public QObject
{
    Q_OBJECT

public:
    CorePlatform_test();

private Q_SLOTS:
    void testCorePlatform();
};

CorePlatform_test::CorePlatform_test()
{
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

    QCOMPARE(QString("Test Data"), pineapple->getTestDataResult());
    QCOMPARE(QString("Ok"), pen->getTestDataResult());

}

QTEST_APPLESS_MAIN(CorePlatform_test)

#include "tst_coreplatform_test.moc"
