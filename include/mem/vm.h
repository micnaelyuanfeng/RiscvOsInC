#ifndef _VM_H_
#define _VM_H_

#define VA_PATCH                0xFFFFFFFF00000000
#define PAGE_SIZE               4096
#define PT_LEVEL                3

// #define PTV(n)

// #define VTP(n)

#define VPN_MASK_L1 0x1ff
#define VPN_MASK_L2 0x1ff
#define VPN_MASK_L3 0x1ff

#define PPN_MASK_L1 0x1ff
#define PPN_MASK_L2 0x1ff
#define PPN_MASK_L3 0x3ffffff

enum PageTableEntryBits {
    Valid = 1 << 0,
    Read = 1 << 1,
    Write = 1 << 2,
    Execute = 1 << 3,
    User = 1 << 4,
    Global = 1 << 5,
    Access = 1 << 6,
    Dirty = 1 << 7,

    ReadWrite = 1 << 1 | 1 << 2,
    ReadExecute = 1 << 1 | 1 << 3,
    ReadWriteExecute = (1 << 1) | (1 << 2) | (1 << 3),

    //Leaf Page Table
    // // User Convenience Combinations
    // UserReadWrite = 1 << 1 | 1 << 2 | 1 << 4,
    // UserReadExecute = 1 << 1 | 1 << 3 | 1 << 4,
    UserReadWriteExecute = 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4,
};

typedef uint64_t (*__kmap)();
typedef bool (*__kunmap)();
typedef void (*__flushTlb)();
typedef void (*__buildPageTable)();
typedef void (*__updatePageTable)();
typedef void (*__registerPageTable)();
typedef void (*__ptClone)();

typedef struct VMControl {
    __kmap kmap;
    __kunmap kunmap;
    __buildPageTable buildPageTable;
    __updatePageTable updatePageTable;
    __registerPageTable registerPageTable;
    __ptClone ptClone;

    uint64_t ptVa;
    uint64_t ptPa;
}VMControl_t;

void fnVmInit();

void _buildPageTable();
void _updatePageTable(uint64_t _ptVa, uint64_t _ptPa, uint8_t level);
void _registerPageTable();
// void _flushTlb();
uint64_t _kmap(uint64_t _pa);
bool _kunmap(uint64_t _va);


#endif