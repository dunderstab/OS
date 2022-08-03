
#ifndef __nanos__DRIVERS__MOUSE_H
#define __nanos__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>

namespace nanos
{
    namespace drivers
    {
    
        class MouseEventHandler
        {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(nanos::common::uint8_t button);
            virtual void OnMouseUp(nanos::common::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };
        
        
        class MouseDriver : public nanos::hardwarecommunication::InterruptHandler, public Driver
        {
            nanos::hardwarecommunication::Port8Bit dataport;
            nanos::hardwarecommunication::Port8Bit commandport;
            nanos::common::uint8_t buffer[3];
            nanos::common::uint8_t offset;
            nanos::common::uint8_t buttons;

            MouseEventHandler* handler;
        public:
            MouseDriver(nanos::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual nanos::common::uint32_t HandleInterrupt(nanos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif
