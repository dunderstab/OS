
#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "keyboard.h"

void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;
    
    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\b':
                switch (x)
                {
                    case 0:
                        y++;
                        break;
                    default:
                        x = x - 1;
                }
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
                break;
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }
        
        if(x >= 80)
        {
            x = 0;
            y++;
        }
        
        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

void print(char* str)
{
	printf(str);
	printf("\n");
}

void printinput(char* str)
{
	printf("$ ");
	printf(str);
	printf("\n");
}



typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}



extern "C" void kernelMain(const void* multiboot_structure, uint32_t)
{
    print("Welcome to NanOS!\n");

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(0x20, &gdt);

    KeyboardDriver keyboard(&interrupts);

    interrupts.Activate();

    while(1);
}