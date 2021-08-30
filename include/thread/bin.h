#ifndef _BIN_H_
#define _BIN_H_

#define BIN_START_VA 0xf80200000
#define BIN_SIZE 0x40

unsigned int binArray3[] = {
   0xff010113, //         	addi	sp,sp,-32
   0x00813423, //          	sd	s0,24(sp)
   0x01010413, //         	addi	s0,sp,32
   0x00100893, //         	lui	a5,0x7c01
   0x05000513, //         	addi	a5,a5,5 # 7c01005 <__start-0xf785feffb>
   0x00000073, //          	sd	a5,-24(s0)
   0xff5ff06f, //          	ld	a5,-24(s0)
};


#endif 