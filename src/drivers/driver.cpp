#include <drivers/driver.h>


//using namespace mykernel::common;
using namespace mykernel::drivers;

Driver::Driver()
{

}
Driver::~Driver()
{

}

void Driver::Activate()
{

}
int Driver::Reset()
{

}
void Driver::Deactivate()
{

}

DriverManager::DriverManager()
{
    numDrivers=0;
}
DriverManager::~DriverManager()
{

}
void DriverManager::AddDriver(Driver *driver)
{
    drivers[numDrivers] = driver;
    numDrivers++;
}
void DriverManager::ActivateAll()
{
    for(int i = 0; i < numDrivers;i++)
        drivers[i]->Activate();
}
void DriverManager::DeactivateAll()
{
    for(int i = 0; i < numDrivers;i++)
        drivers[i]->Deactivate();
}
void DriverManager::ResetAll()
{
    for(int i = 0; i < numDrivers;i++)
        drivers[i]->Reset();
}
