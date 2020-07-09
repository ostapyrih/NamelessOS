C_SOURCES = $(wildcard src/kernel/*.c src/drivers/*.c src/cpu/*.c src/lib/*.c)
ASM_SOURCES = $(wildcard src/kernel/*.asm src/drivers/*.asm src/cpu/*.asm)
HEADERS = $(wildcard kernel/*.h)
OBJECTS = ${ASM_SOURCES:.asm=asm.o} ${C_SOURCES:.c=.o}

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
			-nostartfiles -nodefaultlibs -Wall -Wextra -c
LDFLAGS = -T link.ld -melf_i386
AS = yasm
ASFLAGS = -felf32

all: kernel.elf os.iso clean

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	#rm tutos.iso
	cp kernel.elf iso/boot/kernel.elf
	grub-mkrescue -o tutos.iso iso

run: os.iso
	bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%asm.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	find . -name "*.o" -type f -delete
	rm -rf kernel.elf