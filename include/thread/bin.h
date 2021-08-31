#ifndef _BIN_H_
#define _BIN_H_

#define BIN_START_VA 0xf80200000
#define BIN_SIZE 0x40

unsigned int binArray3[] = {
   0xfe010113, //          	addi	sp,sp,-32
   0x00813c23, //          	sd	s0,24(sp)
  	0x02010413, //          	addi	s0,sp,32
   0xfe043423, //          	sd	zero,-24(s0)
   0xfe843783, //          	ld	a5,-24(s0)
  	0x00878793, //          	addi	a5,a5,8
   0x37ab7737, //          	lui	a4,0x37ab7
   0x00271713, //         	slli	a4,a4,0x2
   0xeef70713, //          	addi	a4,a4,-273 # 37ab6eef <__start-0xf48749111>
   0x00e7b023, //          	sd	a4,0(a5)
   0xfe843783, //          	ld	a5,-24(s0)
   0x01078793, //          	addi	a5,a5,16
   0x37ab7737, //          	lui	a4,0x37ab7
   0x00271713, //          	slli	a4,a4,0x2
   0xeef70713, //          	addi	a4,a4,-273 # 37ab6eef <__start-0xf48749111>
   0x00e7b023, //          	sd	a4,0(a5)
   0xfe843783, //          	ld	a5,-24(s0)
   0x01878793, //          	addi	a5,a5,24
   0x37ab7737, //          	lui	a4,0x37ab7
   0x00271713, //          	slli	a4,a4,0x2
   0xeef70713, //          	addi	a4,a4,-273 # 37ab6eef <__start-0xf48749111>
   0x00e7b023, //          	sd	a4,0(a5)
   0xfb9ff06f, //          	j	f80200010 <__start+0x10>
};


#endif 