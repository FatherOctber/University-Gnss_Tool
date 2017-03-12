#include "platformcore.h"

PlatformCore::PlatformCore() : QObject()
{
    this->microServicesFw = new Framework(FrameworkFactory().NewFramework());
}

int PlatformCore::load(std::list<std::string> services)
{
    try
    {
        microServicesFw->Init();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 0;
    }

    bundleContext = microServicesFw->GetBundleContext();
    if (!bundleContext)
    {
        std::cerr << "Invalid framework context" << std::endl;
        return -1;
    }

    // Install all bundles contained in the shared libraries
    for (std::string service : services)
    {
        try
        {
            bundleContext.InstallBundles(service);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return 0;
        }
    }
    return 1;
}

void PlatformCore::runPlatform()
{
    try
    {
        microServicesFw->Start();

        auto bundles = bundleContext.GetBundles();
        auto iter = std::find_if(bundles.begin(), bundles.end(), [](Bundle& b) {
                return b.GetSymbolicName() == "logger";
        });
        if (iter != bundles.end())
        {
            iter->Start();
        }

        // Now start all bundles.
        for (auto& bundle : bundles)
        {
            bundle.Start();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}


