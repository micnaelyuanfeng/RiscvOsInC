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

    // printf("Allocte 0x%x%x\n", ptVa >> 31 & 0xFFFFFFFF, ptVa & 0xFFFFFFFF);

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
    uint64_t pa = 0UL;
    uint64_t* nextLevelPtVaEntryVa = (uint64_t*)&root[vpn[2]];

    printf("%d\n",vpn[2]);
    printf("%d\n",vpn[1]);
    printf("%d\n",vpn[0]);

    for (int i = level - 1; i >= 0; i--){
        if(!(*nextLevelPtVaEntryVa) & Valid){
            CoreMemBlkInfo_t blkInf = {0};
            blkInf.numOfPage = 1;
            
            pa = CoreMapControl.kmalloc(&blkInf);

            *nextLevelPtVaEntryVa = (pa >> 2) | Valid;
        }

        uint64_t* nextLevelPtVa = (uint64_t*)(pa | 0xFFFFFFFF00000000);

        nextLevelPtVaEntryVa = &nextLevelPtVa[vpn[i]];
    }

    uint64_t pageTableEntryVal = (ppn[2] << 28) |   // PPN[2] = [53:28]
        (ppn[1] << 19) |   // PPN[1] = [27:19]
        (ppn[0] << 10) |   // PPN[0] = [18:10]
        Valid | ReadWriteExecute;

    *nextLevelPtVaEntryVa = pageTableEntryVal;
    
    for(int i = 0; i <= 511; i++){
        if(root[i] & Valid){
            printf("====> PD0 --> Entry value is %d 0x%x%x\n", i, root[i] >> 32, root[i]);
            uint64_t* ppt = (uint64_t*)(((root[i]) >> 1 << 3) | 0xFFFFFFFF00000000);
            
            for(int j = 0; j <= 511; j++){
                if(ppt[j] & Valid){
                    printf("====>   PD1 --> Entry value is %d 0x%x%x\n", j, ppt[j] >> 32, ppt[j]);

                    uint64_t* ppe = (uint64_t*)(((ppt[j]) >> 1 << 3) | 0xFFFFFFFF00000000);

                    for(int k = 0; k <= 511; k++){
                        if(ppe[k] & Valid){
                            printf("====>      PE ---> Entry value is %d 0x%x%x\n", k, ppe[k] >> 32, ppe[k]);
                        }
                    }
                }
            }
        }
    }

}

void _registerPageTable(){
    
}

void fnPtWalk(){

}

void fnMapPaToVaTest(){
    
}