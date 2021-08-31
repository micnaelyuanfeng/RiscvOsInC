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

#define PPN(addr) (addr) >> 1UL << 3UL
#define P2V(addr) (addr) | 0xFFFFFFFF00000000

#define V2P(add) ({ \
    (addr)UL - 0xFFFFFFFF00000000 \
})

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
typedef void (*__buildPageTable)();
typedef void (*__updatePageTable)(uint64_t _ptVa, uint64_t _ptPa, uint8_t level);
typedef void (*__registerPageTable)();
typedef void (*__buildRootPageTable)();
typedef void (*__mapRange)(uint64_t* _ptVa, uint8_t _sizeInPage, uint8_t level, uint64_t _va);
typedef void (*__ptClone)(uint64_t* _ptVa);
typedef void (*__ptMapCmdBufferMem)();

typedef struct VMControl {
    __kmap kmap;
    __kunmap kunmap;
    __buildPageTable buildPageTable;
    __updatePageTable updatePageTable;
    __registerPageTable registerPageTable;
    __buildRootPageTable buildRootPageTable;
    __mapRange mapRange;
    __ptClone ptClone;
    __ptMapCmdBufferMem ptAllocAndMapCbMem;

    uint64_t ptVa;
    uint64_t ptPa;
}VMControl_t;

void fnVmInit();
void fnPtWalk();
void fnBuildRootPageTable();
void fnMalloMapUtilitiesMem();
void fnBuildPtForHartOne();
void updatePageTableOtherThread(uint64_t* pPt, uint64_t _ptVa, uint64_t _ptPa, uint8_t level);
void fnDebugPrintPtClone();

void fnMallocMapTest();
void fnFreeMapTest();

void _buildPageTable();
void _updatePageTable(uint64_t _ptVa, uint64_t _ptPa, uint8_t level);
void _registerPageTable();
void _buildRootPageTable();
void _mapRange(uint64_t* _ptVa, uint8_t _sizeInPage, uint8_t level, uint64_t _va);
void _ptClone(uint64_t* _ptVa);
void _ptAllocAndMapCbMem();


uint64_t _kmap(uint64_t _pa);
bool _kunmap(uint64_t _va);

#endif