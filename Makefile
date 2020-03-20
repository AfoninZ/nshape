ASM_FILES = $(shell find boot -mindepth 1 -maxdepth 4 -name "*.s")
SRC_FILES = $(shell find kernel -mindepth 1 -maxdepth 4 -name "*.c")
HDR_FILES = $(shell find kernel -mindepth 1 -maxdepth 4 -name "*.h")

OBJ_FILES = $(patsubst %.s,%.o,$(ASM_FILES)) $(patsubst %.c,%.o,$(SRC_FILES))

AS = nasm
AS_FLAGS = -felf32

СС = i686-elf-gcc
CC_FLAGS = -std=gnu99 -ffreestanding -c

LD = i686-elf-ld
LD_FLAGS = -T linker.ld

all: nshape.bin

nshape.bin: $(OBJ_FILES)
	$(LD) $(LD_FLAGS) $(OBJ_FILES) -o build/nshape.bin
	cp build/nshape.bin iso/boot

run: nshape.bin
	qemu-system-i386 -kernel build/nshape.bin
	

%.o: %.c
	i686-elf-gcc $(CC_FLAGS) $< -o $@

%.o: %.s
	$(AS) $(AS_FLAGS) $< -o $@

clean:
	rm -rf $(OBJ_FILES) build/*