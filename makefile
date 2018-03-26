
GPPPARMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wall -Wextra
ASPARMS = --32
LDPARMS = -melf_i386

objects = 	obj/loader.o \
			obj/gdt.o \
			obj/drivers/driver.o \
			obj/common/terminal.o\
			obj/hardwarecommunication/port.o \
			obj/hardwarecommunication/interruptstub.o \
			obj/hardwarecommunication/interrupts.o \
			obj/drivers/keyboard.o \
			obj/drivers/mouse.o\
			obj/kernel.o

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(GPPPARMS) -o $@ -c $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARMS) -o $@ $<

bin/mykernel.bin: linker.ld $(objects)
	mkdir -p $(@D)
	ld $(LDPARMS) -T $< -o $@ $(objects)

install: bin/mykernel.bin
	sudo cp $< /boot/mykernel.bin

mykernel.iso: bin/mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso
.PHONY: clean
clean:
	rm -rf obj bin
	rm -f mykernel.iso
