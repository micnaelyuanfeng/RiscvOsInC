#include "types.h"
#include "coremap.h"
#include "reg.h"
#include "vm.h"
#include "device.h"
#include "printf.h"

extern VMControl_t VmControl;
extern CoreMapCntl_t CoreMapControl;
extern RegisterRoute_t RegisterAccess;

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
    VmControl.buildRootPageTable = _buildRootPageTable;
    VmControl.mapRange = _mapRange;

    VmControl.ptVa = 0;
    VmControl.ptPa = 0;
}

void _buildRootPageTable(){
    uint64_t kernelStart = CoreMapControl.kernelStartAddr;
    uint64_t kernelEnd = CoreMapControl.kernelEndAddr;

    uint64_t numOfKernelPages = (kernelEnd - kernelStart) / PAGE_SIZE; 

    CoreMemBlkInfo_t blkInf = {0};

    blkInf.numOfPage = 1;

    uint64_t ptPa = CoreMapControl.kmalloc(&blkInf);

    VmControl.ptPa = ptPa;

    VmControl.ptVa = 0xFFFFFFFF00000000 | ptPa;

    _updatePageTable(VmControl.ptVa, VmControl.ptPa, 2);

    uint64_t paStart = CoreMapControl.coremapStartAddr;

    uint64_t kernekStartPa = kernelStart & ~0xFFFFFFFF00000000;

    // printf("Page Table  0x%x%x\n", VmControl.ptPa >> 32 & 0xFFFFFFFF, VmControl.ptPa & 0xFFFFFFFF);
    // printf("Kernel Starts 0x%x%x\n", kernelStart >> 32 & 0xFFFFFFFF, kernelStart & 0xFFFFFFFF);
    // printf("Kernel Starts 0x%x%x\n", kernekStartPa >> 32 & 0xFFFFFFFF, kernekStartPa & 0xFFFFFFFF);

    for (uint64_t i = 0; i < numOfKernelPages; i++){
        _updatePageTable(kernelStart, kernekStartPa, PT_LEVEL - 1);

        kernelStart += PAGE_SIZE;
        kernekStartPa += PAGE_SIZE;
    }
}


void _buildPageTable(){
    CoreMemBlkInfo_t blkInf = {0};

    blkInf.numOfPage = 1;

    uint64_t ptPa = CoreMapControl.kmalloc(&blkInf);

    VmControl.ptPa = ptPa;

    VmControl.ptVa = 0xFFFFFFFF00000000 | ptPa;

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

    for (int i = level - 1; i >= 0; i--){
        if(!(*nextLevelPtVaEntryVa) & Valid){
            CoreMemBlkInfo_t blkInf = {0};
            blkInf.numOfPage = 1;
            
            pa = CoreMapControl.kmalloc(&blkInf);

            *nextLevelPtVaEntryVa = (pa >> 2) | Valid;
    
            _updatePageTable(0xFFFFFFFF00000000UL | pa, pa, 2);
        }

        uint64_t ptEntryValue = *nextLevelPtVaEntryVa;

        uint64_t* nextLevelPtVa = (uint64_t*)(P2V(PPN(ptEntryValue)));
        // uint64_t* nextLevelPtVa = (uint64_t*)(((*nextLevelPtVaEntryVa) >> 1 << 3) | 0xFFFFFFFF00000000);

        nextLevelPtVaEntryVa = &nextLevelPtVa[vpn[i]];
        
    }
    uint64_t pageTableEntryVal = (ppn[2] << 28) |   // PPN[2] = [53:28]
        (ppn[1] << 19) |   // PPN[1] = [27:19]
        (ppn[0] << 10) |   // PPN[0] = [18:10]
        Valid | ReadWriteExecute;

    *nextLevelPtVaEntryVa = pageTableEntryVal;
}

void _mallocAndMap(uint64_t _sizeInBytes){
    uint8_t numOfPage = (_sizeInBytes / PAGE_SIZE == 0) ? 
                            1 : (_sizeInBytes /PAGE_SIZE + (_sizeInBytes % PAGE_SIZE == 0) ? 0 : 1);
    
    
    // for(uint32_t i = 0; i < numOfPage; i++){
    //     CoreMapControl.kmalloc();
    // }
}

void _mapRange(uint64_t* _ptVa, uint8_t _sizeInPage, uint8_t level, uint64_t _va){
    
    uint64_t pa = _va - 0xFFFFFFFF00000000UL;

    _updatePageTable(_va, pa, PT_LEVEL - 1);

}

void _registerPageTable(){
    uint64_t value = ((8UL << 60) | (VmControl.ptPa >> 12));

    RegisterAccess.writeSatp(value);
    RegisterAccess.flushTlb();
}


void fnPtWalk(){
    uint64_t* root = (uint64_t*)VmControl.ptVa;

    printf("Page Table PA 0x%x%x\n", VmControl.ptPa >> 32, VmControl.ptPa);

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

void fnMapPaToVaTest(){
    
}

void fnVMTest(){

}

void fnBuildRootPageTable(){
    VmControl.buildRootPageTable();
    VmControl.mapRange(_nullptr, 0, PT_LEVEL - 1, UART_BASE);
    VmControl.registerPageTable();
}
