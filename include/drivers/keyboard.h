
#ifndef __nanos__DRIVERS__KEYBOARD_H
#define __nanos__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace nanos
{
    namespace drivers
    {
    
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };
        
        class KeyboardDriver : public nanos::hardwarecommunication::InterruptHandler, public Driver
        {
            nanos::hardwarecommunication::Port8Bit dataport;
            nanos::hardwarecommunication::Port8Bit commandport;
            
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(nanos::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            virtual nanos::common::uint32_t HandleInterrupt(nanos::common::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif