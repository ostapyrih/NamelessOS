CPP_SOURCES = $(wildcard core/*.c arch/x86/*.c drivers/*.c)
ASM_SOURCES = $(wildcard arch/x86/*.asm)
HEADERS = $(wildcard *.h)
OBJECTS = ${CPP_SOURCES:.c=.o} ${ASM_SOURCES:.asm=asm.o}

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -felf32

all: kernel.elf os.iso clean

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	rm ../os.iso
	cp kernel.elf ../iso/boot/kernel.elf
	grub-mkrescue -o ../os.iso ../iso

%.o: %.cc
	$(CC) $(CFLAGS)  $< -o $@

%asm.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	find . -name "*.o" -type f -delete
	rm -rf kernel.elf