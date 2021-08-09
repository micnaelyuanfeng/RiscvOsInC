#ifndef _VM_H_
#define _VM_H_

#define VA_PATCH                0xFFFFFFFF00000000
#define PAGE_SIZE               4096

#define PTV(n)

#define VTP(n)

enum PageTableEntryBits {
    Valid = 1 << 0,
    Read = 1 << 1,
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
}VMControl_t;

void fnVmInit();

void _buildPageTable();
void _updatePageTable();
void _registerPageTable();
// void _flushTlb();
uint64_t _kmap(uint64_t _pa);
bool _kunmap(uint64_t _va);


#endif