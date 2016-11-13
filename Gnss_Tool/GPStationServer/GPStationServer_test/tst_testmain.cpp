#include <QtWidgets/QApplication>
#include <QString>
#include <QtTest>
#include "datahandler.h"
#include "utils.h"

using namespace std;

class TestMain : public QObject
{
    Q_OBJECT

public:
    TestMain();

private Q_SLOTS:
    void testGnssDataHandle();
};

//test_impl

TestMain::TestMain()
{
}

void TestMain::testGnssDataHandle()
{
    Abstracthandler *handler = new GnssDataHandler();
    /**test only**/
    GnssData testData;
    testData.data.push_back(1.1);
    testData.data.push_back(1.2);
    QCOMPARE(handler->handle(QByteArray("")),testData);
}

QTEST_APPLESS_MAIN(TestMain)

#include "tst_testmain.moc"
