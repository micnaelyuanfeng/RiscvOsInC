#ifndef _VM_H_
#define _VM_H_

#define VA_PATCH                0xFFFFFFFF00000000
#define PAGE_SIZE               4096

enum PageTableEntryBits {
    Valid = 1 << 0,
    Read = 1 << 1,
};

// enum PageTableEntryMask {
    
// };

bool _kmap();
bool _kunmap();

bool __kmap();
bool __kunmap();

void _flush_tlb();

uint64_t _get_root_pt_pa();

#endif