#ifndef HW_H
#define HW_H

#include "const.h"
#include "instruction.h"
int reverseOpcodeToValue(struct instruction *instr,int opcode, int branchaddr);
void parseJType(struct instruction *instr, struct instr_info info, int addr, int branchaddr );
void parseIType(struct instruction *instr, struct instr_info info, int addr, int branchaddr );
void parseRType(struct instruction *instr, struct instr_info info, int addr );
int getOpCode(int hexNumber);
struct instr_info * getInstructionInfo(int opcode);
int power(int base, int exponent);
int checkEndianness(int i, int argc, char **argv);
int convertHex(int j, char **argv, int i);
int checkHex(int i,int argc, char **argv);


#endif
