#include <QString>
#include <QtTest>

class TestMain : public QObject
{
    Q_OBJECT

public:
    TestMain();

private Q_SLOTS:
    void testCase1();
};

//test_impl

TestMain::TestMain()
{
}

void TestMain::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestMain)

#include "tst_testmain.moc"
