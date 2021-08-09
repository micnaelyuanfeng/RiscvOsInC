#include "types.h"
#include "vm.h"

extern VMControl_t VmControl;

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
}

void _buildPageTable(){

}

void _updatePageTable(){

}

void _registerPageTable(){
    
}