#ifndef __DRIVERS_DRIVER_H
#define __DRIVERS_DRIVER_H

namespace mykernel
{
namespace drivers
{
class Driver
{
public:
    Driver();
    ~Driver();

    virtual void Activate();
    virtual int Reset();
    virtual void Deactivate();
};

class DriverManager
{
public:
    DriverManager();
    ~DriverManager();
    void AddDriver(Driver *);
    void ActivateAll();
    void DeactivateAll();
    void ResetAll();
private:
    Driver *drivers[255];
    int numDrivers;
};
}
}
#endif // __DRIVER_H
