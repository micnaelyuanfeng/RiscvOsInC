OUTPUT_ARCH(riscv)

ENTRY(_start)

/*BASE_ADDRESS = 0x80200000;*/  /*Bare Mode*/
BASE_ADDRESS = 0xffffffff80200000;

SECTIONS
{
    /* __ipi_mem_start = .;
    PROVIDE(pRoqMem = .);
    .ipi_sect : {
        *(*.ipi_sect)
    }
    . = 0x2000;
    __ipi_mem_end = .;

    __share_mem_uq_start = .;
    PROVIDE(ProcessArray = .);
    .uq_info_sect : {
        *(*.uq_info_sect)
    }
    . = 0xA000;
    __share_mem_uq_end = .;
    
    PROVIDE(lock_mem = .);
    . += 8;
    PROVIDE(pLogMemMgr = .);
    . += 16;
    PROVIDE(log_lock_mem = .);
    . += 8;
    PROVIDE(pLogMem = .);
    . += 0xF000;
    . = ALIGN(4096);
    PROVIDE(pLogMemEnd = .); */

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