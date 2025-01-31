/* { dg-do compile } */
/* { dg-options "-mdejagnu-cpu=power10 -O3 -dp" } */

#include <altivec.h>
#include <stdint.h>

#define ADD(a,b) ((a)+(b))
#define SUB1(a,b) ((a)-(b))
#define SUB2(a,b) ((b)-(a))

/* and/andc/eqv/nand/nor/or/orc/xor */
#define AND(a,b) ((a)&(b))
#define NAND(a,b) (~((a)&(b)))
#define NOR(a,b) (~((a)|(b)))
#define OR(a,b) ((a)|(b))
#define TEST1(type, func)							\
  type func ## _add_T_     ## type (type a, type b, type c) { return ADD(func(a,b),c); } \
  type func ## _sub1_T_    ## type (type a, type b, type c) { return SUB1(func(a,b),c); } \
  type func ## _sub2_T_    ## type (type a, type b, type c) { return SUB2(func(a,b),c); } \
  type func ## _rev_add_T_     ## type (type a, type b, type c) { return ADD(c,func(a,b)); } \
  type func ## _rev_sub1_T_    ## type (type a, type b, type c) { return SUB1(c,func(a,b)); } \
  type func ## _rev_sub2_T_    ## type (type a, type b, type c) { return SUB2(c,func(a,b)); }
#define TEST2(type, func)							\
  type func ## _and_T_     ## type (type a, type b, type c) { return  AND(func(a,b),c); } \
  type func ## _nand_T_    ## type (type a, type b, type c) { return NAND(func(a,b),c); } \
  type func ## _or_T_      ## type (type a, type b, type c) { return   OR(func(a,b),c); } \
  type func ## _nor_T_     ## type (type a, type b, type c) { return  NOR(func(a,b),c); } \
  type func ## _rev_and_T_     ## type (type a, type b, type c) { return  AND(c,func(a,b)); } \
  type func ## _rev_nand_T_    ## type (type a, type b, type c) { return NAND(c,func(a,b)); } \
  type func ## _rev_or_T_      ## type (type a, type b, type c) { return   OR(c,func(a,b)); } \
  type func ## _rev_nor_T_     ## type (type a, type b, type c) { return  NOR(c,func(a,b)); }
#define TEST(type)    \
  TEST1(type,AND)     \
  TEST1(type,NAND)    \
  TEST1(type,NOR)     \
  TEST1(type,OR)      \
  TEST2(type,ADD)     \
  TEST2(type,SUB1)    \
  TEST2(type,SUB2)

typedef vector bool char vboolchar_t;
typedef vector unsigned int vuint_t;

TEST(uint8_t);
TEST(int8_t);
TEST(uint16_t);
TEST(int16_t);
TEST(uint32_t);
TEST(int32_t);
TEST(uint64_t);
TEST(int64_t);
  
/* { dg-final { scan-assembler-times "fuse_nand_rsubf/0"   2 } } */
/* { dg-final { scan-assembler-times "fuse_nand_rsubf/2"   2 } } */
/* { dg-final { scan-assembler-times "fuse_nor_rsubf/0"    2 } } */
/* { dg-final { scan-assembler-times "fuse_nor_rsubf/2"    2 } } */
/* { dg-final { scan-assembler-times "fuse_add_nand/0"     4 } } */
/* { dg-final { scan-assembler-times "fuse_add_nor/0"      4 } } */
/* { dg-final { scan-assembler-times "fuse_add_or/0"       4 } } */
/* { dg-final { scan-assembler-times "fuse_and_rsubf/0"    4 } } */
/* { dg-final { scan-assembler-times "fuse_and_subf/0"     4 } } */
/* { dg-final { scan-assembler-times "fuse_nand_add/0"     4 } } */
/* { dg-final { scan-assembler-times "fuse_nand_subf/0"    4 } } */
/* { dg-final { scan-assembler-times "fuse_nor_add/0"      4 } } */
/* { dg-final { scan-assembler-times "fuse_nor_subf/0"     4 } } */
/* { dg-final { scan-assembler-times "fuse_or_rsubf/0"     4 } } */
/* { dg-final { scan-assembler-times "fuse_or_subf/0"      4 } } */
/* { dg-final { scan-assembler-times "fuse_subf_nand/0"    4 } } */
/* { dg-final { scan-assembler-times "fuse_subf_nand/1"    4 } } */
/* { dg-final { scan-assembler-times "fuse_subf_nor/0"     4 } } */
/* { dg-final { scan-assembler-times "fuse_subf_nor/1"     4 } } */
/* { dg-final { scan-assembler-times "fuse_subf_or/0"      4 } } */
/* { dg-final { scan-assembler-times "fuse_subf_or/1"      4 } } */
/* { dg-final { scan-assembler-times "fuse_and_add/0"      6 } } */
/* { dg-final { scan-assembler-times "fuse_or_add/0"       6 } } */
/* { dg-final { scan-assembler-times "fuse_add_and/0"      8 } } */
/* { dg-final { scan-assembler-times "fuse_add_and/2"      8 } } */
/* { dg-final { scan-assembler-times "fuse_subf_and/0"     8 } } */
/* { dg-final { scan-assembler-times "fuse_subf_and/1"     8 } } */
/* { dg-final { scan-assembler-times "fuse_add_nand/2"    12 } } */
/* { dg-final { scan-assembler-times "fuse_add_nor/2"     12 } } */
/* { dg-final { scan-assembler-times "fuse_add_or/2"      12 } } */
/* { dg-final { scan-assembler-times "fuse_and_rsubf/2"   12 } } */
/* { dg-final { scan-assembler-times "fuse_and_subf/2"    12 } } */
/* { dg-final { scan-assembler-times "fuse_nand_add/2"    12 } } */
/* { dg-final { scan-assembler-times "fuse_nand_subf/2"   12 } } */
/* { dg-final { scan-assembler-times "fuse_nor_add/2"     12 } } */
/* { dg-final { scan-assembler-times "fuse_nor_subf/2"    12 } } */
/* { dg-final { scan-assembler-times "fuse_or_rsubf/2"    12 } } */
/* { dg-final { scan-assembler-times "fuse_or_subf/2"     12 } } */
/* { dg-final { scan-assembler-times "fuse_subf_and/2"    16 } } */
/* { dg-final { scan-assembler-times "fuse_and_add/2"     22 } } */
/* { dg-final { scan-assembler-times "fuse_or_add/2"      22 } } */
/* { dg-final { scan-assembler-times "fuse_subf_nand/2"   24 } } */
/* { dg-final { scan-assembler-times "fuse_subf_nor/2"    24 } } */
/* { dg-final { scan-assembler-times "fuse_subf_or/2"     24 } } */

