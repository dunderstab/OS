#ifndef __nanos__GDT_H
#define __nanos__GDT_H

#include <common/types.h>

namespace nanos
{
    
    class GlobalDescriptorTable
    {
        public:

            class SegmentDescriptor
            {
                private:
                    nanos::common::uint16_t limit_lo;
                    nanos::common::uint16_t base_lo;
                    nanos::common::uint8_t base_hi;
                    nanos::common::uint8_t type;
                    nanos::common::uint8_t limit_hi;
                    nanos::common::uint8_t base_vhi;

                public:
                    SegmentDescriptor(nanos::common::uint32_t base, nanos::common::uint32_t limit, nanos::common::uint8_t type);
                    nanos::common::uint32_t Base();
                    nanos::common::uint32_t Limit();
            } __attribute__((packed));

        private:
            SegmentDescriptor nullSegmentSelector;
            SegmentDescriptor unusedSegmentSelector;
            SegmentDescriptor codeSegmentSelector;
            SegmentDescriptor dataSegmentSelector;

        public:

            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            nanos::common::uint16_t CodeSegmentSelector();
            nanos::common::uint16_t DataSegmentSelector();
    };

}
    
#endif