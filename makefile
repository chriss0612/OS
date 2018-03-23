
GPPPARMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARMS = --32
LDPARMS = -melf_i386

objects = obj/loader.o obj/kernel.o obj/terminal.o obj/gdt.o obj/port.o

obj/%.o: src/%.cpp
	g++ $(GPPPARMS) -o $@ -c $<

obj/%.o: src/%.s
	as $(ASPARMS) -o $@ $<

bin/mykernel.bin: src/linker.ld $(objects)
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
#	make clean
run: mykernel.iso
	VirtualBox --startvm mykernel &
.PHONY: clean
clean:
	rm -rf obj
	rm -rf bin
	mkdir obj
	mkdir bin
#	rm -f $(objects) bin/mykernel.bin mykernel.iso
#	rm -rf obj/Debug/
#	rm -rf bin/Debug/
