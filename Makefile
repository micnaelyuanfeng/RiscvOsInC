C_SRC = $(shell find . -name "*.c") 
ASM_SRC = $(shell find . -name "*.asm")

C_OBJ = $(patsubst %.c, %.o, $(C_SRC))
ASM_OBJ = $(patsubst %.asm, %.o, $(ASM_SRC))

INCLUDES = 

