OUTPUT_ARCH(riscv)

ENTRY(_start)

/*BASE_ADDRESS = 0x80200000;*/  /*Bare Mode*/
BASE_ADDRESS = 0xffffffff80200000;

SECTIONS
{
    __CommandQueueMemStart = .;
    PROVIDE(__commandBuffMem = .);
  
    . += 0x1000;
    __CommandQueueMemEnd = .;
    
    __LockMemStart = .;
    PROVIDE(__consoleLock = .);
    . += 8;
    PROVIDE(__queueMemLock = .);
    . += 8;
    __LockMemEnd = .;
    
    __PrinfBuffStart = .;
    . += 2048;
    . = ALIGN(4096);
    __HartInfoArray = .;

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
    _bss_end = .;
    __KernelEndAddr = .;
}
