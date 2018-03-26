#ifndef __GDT_H
#define __GDT_H

#include <common/types.h>

namespace mykernel
{
class GlobalDescriptorTable
{
public:
    class SegmentDescriptor
    {
    private:
        mykernel::common::uint16_t limit_lo;
        mykernel::common::uint16_t base_lo;
        mykernel::common::uint8_t base_hi;
        mykernel::common::uint8_t type;
        mykernel::common::uint8_t flags_limit_hi;
        mykernel::common::uint8_t base_vhi;
    public:
        SegmentDescriptor(mykernel::common::uint32_t base, mykernel::common::uint32_t limit, mykernel::common::uint8_t type);
        mykernel::common::uint32_t Base();
        mykernel::common::uint32_t Limit();
    } __attribute__((packed));


    SegmentDescriptor nullSegmentSelector;
    SegmentDescriptor unusedSegmentSelector;
    SegmentDescriptor codeSegmentSelector;
    SegmentDescriptor dataSegmentSelector;


public:
    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    mykernel::common::uint16_t CodeSegmentSelector();
    mykernel::common::uint16_t DataSegmentSelector();
};
}

#endif // __GDT_H
