C_SRC := $(shell find . -name "*.c") 
ASM_SRC := $(shell find . -name "*.S")

C_OBJ := $(patsubst %.c, %.o, $(C_SRC))
ASM_OBJ := $(patsubst %.S, %.o, $(ASM_SRC))

INCLUDES := -I ./include
INCLUDES += -I ./include/mem
INCLUDES += -I ./include/hw 
INCLUDES += -I ./include/device
INCLUDES += -I ./include/trap 

CC := riscv64-unknown-elf-gcc
CASM := riscv64-unknown-elf-as

CFLAG := -c -g2 -O0 \
			-nostdlib -nostartfiles -nodefaultlibs \
			-fno-builtin -fno-exceptions \
			-march=rv64i -mcmodel=medany

OUTPUT_DIR = ./obj
BIN_DIR = ./bin
ELF_FILE = kernel.elf
BIN_FILE = kernel.bin

.PHONY: build link qemu run clean

%.o:%.c
	$(CC) $(CFLAG) $(INCLUDES) $< -o $@

%.o:%.S
	$(CASM) -g2 -march=rv64i $< -o $@

build: $(ASM_OBJ) $(C_OBJ)

copy:
	riscv64-unknown-elf-ld -T linker.ld $(ASM_OBJ) $(C_OBJ) -o $(BIN_DIR)/$(ELF_FILE)
	riscv64-unknown-elf-objcopy $(BIN_DIR)/$(ELF_FILE) --strip-all -O binary  $(BIN_DIR)/$(BIN_FILE)

KERNEL_LOAD_PA := 0x80200000

qemu:
	qemu-system-riscv64 \
		-machine virt	\
		-nographic	\
		-bios default \
		-m 256M	\
		-device loader,file=$(BIN_DIR)/$(BIN_FILE),addr=$(KERNEL_LOAD_PA)
		

run: build copy qemu

clean:
	rm ./src/asm/*.o
	rm ./src/reg/*.o
	rm ./src/trap/*.o
	rm ./src/main/*.o
	rm ./src/utilities/*.o
	rm ./src/device/*.o
	rm ./src/mm/*.o

	rm $(BIN_DIR)/*bin
	rm $(BIN_DIR)/*elf
	


