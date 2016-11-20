#include "utils.h"

Utils::Utils()
{
}

QString Utils::SETTINGS =
        #if defined(TEST_RUN)
                QDir::currentPath()+"/test_settings.ini";
        #else
                QDir::currentPath()+"/settings.ini";
        #endif


