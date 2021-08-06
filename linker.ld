OUTPUT_ARCH(riscv)

ENTRY(_start)

BASE_ADDRESS = 0x80200000;

SECTIONS
{
    . = BASE_ADDRESS;

    __KernelStartAddr = .;

    .text : {
        *(.text.init)
        *(.text) 
        *(.text.*)
    } 
    
    . = ALIGN(4096);
    _rodata_start = .;

    .rodata : {
        *(.rodata)
        *(.rodata.*)
    }

    . = ALIGN(4096);
    .data : {
        *(.data)
        *(.data.*)
    }

    . = ALIGN(4096);
    _bss_start = .;

    .bss : {
        *(.sbss)
        *(.bss) 
        *(.bss.*)
    }

    . = ALIGN(4096);

    __KernelEndAddr = .;
}