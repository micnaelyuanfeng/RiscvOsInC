#include "types.h"
#include "coremap.h"
#include "vm.h"
#include "printf.h"

extern VMControl_t VmControl;
extern CoreMapCntl_t CoreMapControl;

uint64_t _kmap(uint64_t _pa){
    return true;
}

bool _kunmap(uint64_t _va){
    return true;
}

void fnVmInit(){
    VmControl.buildPageTable = _buildPageTable;
    VmControl.kmap = _kmap;
    VmControl.kunmap = _kunmap;
    VmControl.registerPageTable = _registerPageTable;
    VmControl.ptVa = 0;
    VmControl.ptPa = 0;
}

void _buildPageTable(){
    CoreMemBlkInfo_t blkInf = {0};

    blkInf.numOfPage = 1;

    uint64_t ptPa = CoreMapControl.kmalloc(&blkInf);

    VmControl.ptPa = ptPa;

    uint64_t ptVa = 0xFFFFFFFF00000000 | ptPa;

    VmControl.ptVa = ptVa;

    printf("Allocte 0x%x%x\n", ptVa >> 31 & 0xFFFFFFFF, ptVa & 0xFFFFFFFF);

    _updatePageTable(VmControl.ptVa, VmControl.ptPa, PT_LEVEL - 1);
}

void _updatePageTable(uint64_t _ptVa, uint64_t _ptPa, uint8_t level){
    uint64_t vpn[PT_LEVEL] = {
        _ptVa >> 12 & VPN_MASK_L1,
        _ptVa >> 21 & VPN_MASK_L2,
        _ptVa >> 30 & VPN_MASK_L3
    };

    uint64_t ppn[PT_LEVEL] = {
        _ptPa >> 12 & PPN_MASK_L1,
        _ptPa >> 21 & PPN_MASK_L2,
        _ptPa >> 30 & PPN_MASK_L3
    };

    uint64_t* root = (uint64_t*)VmControl.ptVa;

    printf("%x\n", *root);

    for (int i = level; i >= 0; i--){
        if(!root[vpn[i]] & Valid){
            printf("Not Allocated\n");
        }else{
            printf("Allocated\n");
        }
        // printf("%x\n", vpn[i]);
    }


}

void _registerPageTable(){
    
}