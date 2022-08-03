objects = obj/loader.o \
          obj/gdt.o \
          obj/drivers/driver.o \
          obj/hardwarecommunication/port.o \
          obj/hardwarecommunication/interruptstubs.o \
          obj/hardwarecommunication/interrupts.o \
          obj/drivers/keyboard.o \
          obj/drivers/mouse.o \
          obj/kernel.o


GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-threadsafe-statics -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386


full: clean run

run: nanos.iso
	(killall VirtualBoxVM && sleep 1) || true
	VirtualBoxVM --startvm "NanOS" &

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

nanos.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)
	
nanos.iso: nanos.bin
	mkdir -p isodir/boot/grub
	cp nanos.bin isodir/boot/nanos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o nanos.iso isodir
	@echo "\ndone"


install: nanos.bin
	sudo cp nanos.bin /boot/nanos.bin

clean:
	rm -rf obj nanos.bin nanos.iso
	rm -rf isodir