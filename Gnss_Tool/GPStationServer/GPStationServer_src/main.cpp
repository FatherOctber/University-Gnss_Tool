#include "mainwindow.h"
#include <QSettings>
#include <QApplication>
#include "version.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName(VER_PRODUCTNAME_STR);
    a.setOrganizationName(VER_COMPANYNAME_STR);
    a.setOrganizationDomain(VER_COMPANYDOMAIN_STR);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    MainWindow w;
    w.show();

    return a.exec();
}
