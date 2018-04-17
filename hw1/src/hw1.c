#include "hw1.h"
#include "instruction.h"
#include <stdbool.h>
#include <stdio.h>

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

/*
 * You may modify this file and/or move the functions contained here
 * to other source files (except for main.c) as you wish.
 */
// returns value of bits 31:26 from opcode
int getMnemonics(){


    return 0;
}
int reverseOpcodeToValue(struct instruction *instr,int opcode, int branchaddr){
    int reversed = 0;
    int first = 0;
    int last = 0;
    int opcodeTableValue = 0;
if (opcode == OP_BLTZ)
{

    if (instr -> regs[1] == 0)
    {


        opcodeTableValue = BCOND;
    }
}
if (opcode == OP_BGEZ)
{
    if (instr -> regs[1] == 1)
    {
       opcodeTableValue = BCOND;
    }
}
if (opcode == OP_BLTZAL)
{
    if (instr -> regs[1] == 16)
    {
      opcodeTableValue = BCOND;
    }
}
if (opcode == OP_BGEZAL)
{
    if (instr -> regs[1] == 17)
    {
        opcodeTableValue = BCOND;
    }
}

if (opcodeTableValue == BCOND)
{


    first = 1;
    last = instr -> extra;
     last = last - branchaddr -4;
    last= last >> 2;



    last = last & 0x000007FF;

    first = 0x04000000;
        int rs = instr -> regs[0];
        int rt = instr -> regs[1];
        int rd = instr -> regs[2];
        rs = rs << 21;
        rs = rs & 0x03E00000;
        rt = rt << 16;
        rt = rt & 0x001F0000;
        rd = rd << 11;
        rd = rd & 0x0000F800;
        last = last & 0x000007FF;
        reversed = first | rs;
        reversed = reversed | rt;
        reversed = reversed | rd;
        reversed = reversed | last;
        return reversed;



}
int specialTableLength = 64;
for (int i = 0; i < specialTableLength; i++)
{
    if (specialTable[i] == opcode)
    {
        last =i;
        first = 0x00000000;
        int rs = instr -> regs[0];
        int rt = instr -> regs[1];
        int rd = instr -> regs[2];
        rs = rs << 21;
        rs = rs & 0x03E00000;
        rt = rt << 16;
        rt = rt & 0x001F0000;
        rd = rd << 11;
        rd = rd & 0x0000F800;
        last = last &0x0000003F;
        reversed = first | rs;
        reversed = reversed | rt;
        reversed = reversed | rd;
        reversed = reversed | last;
        return reversed;


    }


}
for (int i = 0; i < 64; i++)
{
    if (opcodeTable[i] == opcode)
    {
        first = i;
        first = first << 26;
    }
}

if (instr -> info[0].type == ITYP)
{

 if ((opcode == OP_BEQ)||(opcode == OP_BGEZ)||(opcode == OP_BGEZAL)
                || (opcode == OP_BGTZ) ||(opcode == OP_BLEZ) || (opcode == OP_BLTZ) ||
                (opcode == OP_BLTZAL) || (opcode == OP_BNE) )
            {
                last = instr -> extra;
                last = last - branchaddr -4;
                last= last >> 2;

                int rs = instr -> regs[0];
                int rt = instr -> regs[1];
                int rd = instr -> regs[2];
                rs = rs << 21;
                rs = rs & 0x03E00000;
                rt = rt << 16;
                rt = rt & 0x001F0000;
                rd = rd << 11;
                rd = rd & 0x0000F800;
                last = last &0x000007FF;
                reversed = first | rs;
                reversed = reversed | rt;
                reversed = reversed | rd;
                reversed = reversed | last;
                return reversed;

                    }
                    else{
                        last = instr -> extra;
                        last = last & 0x000007FF;

                        int rs = instr -> regs[0];
                        int rt = instr -> regs[1];
                        int rd = instr -> regs[2];
                        rs = rs << 21;
                        rs = rs & 0x03E00000;
                        rt = rt << 16;
                        rt = rt & 0x001F0000;
                        rd = rd << 11;
                        rd = rd & 0x0000F800;
                        last = last &0x000007FF;
                        reversed = first | rs;
                        reversed = reversed | rt;
                        reversed = reversed | rd;
                        reversed = reversed | last;

                        return reversed;

                    }
}
if (instr -> info[0].type == JTYP)
{

        last = instr -> extra;
        branchaddr = branchaddr + 4;
        branchaddr = branchaddr & 0xF0000000;

        last = last - branchaddr;

        last = last >> 2;

        last = last & 0x000007FF;


        int rs = instr -> regs[0];

        int rt = instr -> regs[1];

        int rd = instr -> regs[2];

        rs = rs << 21;
        rs = rs & 0x03E00000;
        rt = rt << 16;
        rt = rt & 0x001F0000;
        rd = rd << 11;
        rd = rd & 0x0000F800;
        last = last &0x000007FF;
        reversed = first | rs;
        reversed = reversed | rt;
        reversed = reversed | rd;
        reversed = reversed | last;
        return reversed;

}




return 0;
}
void parseJType(struct instruction *instr, struct instr_info info, int addr, int branchaddr ){

    int Rs = 0;
    int Rt = 0;

    int Rd = 0;
    int Extra = 0;
    // RS Field
        Rs = addr & 0x03E00000;
        Rs = Rs >> 21;
        instr -> regs[0] = Rs;
    // RT field
        Rt = addr & 0x001F0000;
        Rt = Rt >> 16;
        instr -> regs[1] = Rt;
    // RD field
        Rd = addr &  0x0000F800;
        Rd = Rd >> 11;
        instr -> regs[2] = Rd;


    // 3 is sources length
for (int i = 0; i < 3; i++)
{

    if (info.srcs[i] == NSRC)
    {

        instr -> args[i] = 0;
    }

    if (info.srcs[i] == EXTRA)
    {

        if (info.opcode == OP_BREAK)
        {
            Extra = addr & 0x03FFFC0;
            Extra = Extra >> 6;

            Extra = Extra & 0x0303FFFC;


            instr -> extra = Extra;
            instr -> args[i] = Extra;
        }
        else{
            Extra = addr &  0x03FFFFFF;
            Extra = Extra << 2;
            branchaddr = branchaddr +4;
            branchaddr = branchaddr & 0xF0000000;
            Extra = Extra | branchaddr;

            instr -> extra = Extra;
            instr -> args[i] = Extra;

        }
    }
    if (info.srcs[i] == RS)
    {

        instr -> args[i] = Rs;
    }
    if (info.srcs[i] == RT)
    {


        instr -> args[i] = Rt;
    }
    if (info.srcs[i] == RD)
    {


        instr -> args[i] = Rd;
    }

}




}
void parseIType(struct instruction *instr, struct instr_info info, int addr, int branchaddr ){

    int Rs = 0;
    int Rt = 0;

    int Rd = 0;
    int Extra = 0;
    // RS Field
        Rs = addr & 0x03E00000;
        Rs = Rs >> 21;
        instr -> regs[0] = Rs;
    // RT field
        Rt = addr & 0x001F0000;
        Rt = Rt >> 16;
        instr -> regs[1] = Rt;
    // RD field
        Rd = addr &  0x0000F800;
        Rd = Rd >> 11;
        instr -> regs[2] = Rd;


    // 3 is sources length
for (int i = 0; i < 3; i++)
{

    if (info.srcs[i] == NSRC)
    {
        instr -> args[i] = 0;
    }

    if (info.srcs[i] == EXTRA)
    {

        if (info.opcode == OP_BREAK)
        {
            Extra = addr & 0x03FFFC0;
            Extra = Extra >> 6;

            Extra = Extra & 0x0303FFFC;


            instr -> extra = Extra;
            instr -> args[i] = Extra;
        }
        else{
            short x = addr &  0x0000FFFF;
            Extra =x;


            if ((info.opcode == OP_BEQ)||(info.opcode == OP_BGEZ)||(info.opcode == OP_BGEZAL)
                || (info.opcode == OP_BGTZ) ||(info.opcode == OP_BLEZ) || (info.opcode == OP_BLTZ) ||
                (info.opcode == OP_BLTZAL) || (info.opcode == OP_BNE) )
            {

                branchaddr = branchaddr + 4; // branching
                Extra = Extra << 2;

                 // branch calculation = branchaddr + 4 + immediate << 2

                Extra = Extra + branchaddr;




            }



            instr -> extra = Extra;
            instr -> args[i] = Extra;

        }
    }
    if (info.srcs[i] == RS)
    {

        instr -> args[i] = Rs;
    }
    if (info.srcs[i] == RT)
    {


        instr -> args[i] = Rt;
    }
    if (info.srcs[i] == RD)
    {


        instr -> args[i] = Rd;
    }

}





}
void parseRType(struct instruction *instr, struct instr_info info, int addr ){

    int Rs = 0;
    int Rt = 0;

    int Rd = 0;
    int Extra = 0;
    // RS Field
        Rs = addr & 0x03E00000;
        Rs = Rs >> 21;
        instr -> regs[0] = Rs;
    // RT field
        Rt = addr & 0x001F0000;
        Rt = Rt >> 16;
        instr -> regs[1] = Rt;
    // RD field
        Rd = addr &  0x0000F800;
        Rd = Rd >> 11;
        instr -> regs[2] = Rd;


    // 3 is sources length
for (int i = 0; i < 3; i++)
{

    if (info.srcs[i] == NSRC)
    {

        instr -> args[i] = 0;
    }

    if (info.srcs[i] == EXTRA)
    {

        if (info.opcode == OP_BREAK)
        {
            Extra = addr & 0x03FFFC0;
            Extra = Extra >> 6;

            Extra = Extra & 0x0303FFFC;


            instr -> extra = Extra;
            instr -> args[i] = Extra;
        }
        else{
            Extra = addr &  0x000007C0;
            Extra = Extra >> 6;

            instr -> extra = Extra;
            instr -> args[i] = Extra;

        }
    }
    if (info.srcs[i] == RS)
    {

        instr -> args[i] = Rs;
    }
    if (info.srcs[i] == RT)
    {


        instr -> args[i] = Rt;
    }
    if (info.srcs[i] == RD)
    {


        instr -> args[i] = Rd;
    }

}






}

/**
@brief Computes the OpCode value for a MIPS instruction set
**/
int getOpCode(int hexNumber){

    int opcode = 0;
    // get bits 31:26
    opcode = hexNumber & 0xFC000000;
    opcode = opcode >> 26;
    opcode = opcode & 0x0000003F;

    // determine what the index is in the instruction table
    int instrTableIndex = opcodeTable[opcode];
    // determine wahat operation it is
    if (instrTableIndex != SPECIAL || instrTableIndex != BCOND)
    {
        opcode = instrTableIndex;

    }
    if (instrTableIndex == SPECIAL)
    {
        // if the instrTable index = special then checj bits 5:0
        //into special index[]
         int specialIndex = hexNumber &0x0000003F;
        opcode = specialTable[specialIndex];





    }
    if (instrTableIndex == BCOND)
    {
        opcode = -70;
        // if its Bcond then check 20:16
        int branchCode = hexNumber &  0x001F0000;
        branchCode = branchCode >> 16;

        branchCode = branchCode & 0x0000001F;


        if (branchCode == 0)
        {
            opcode = OP_BLTZ;
        }
        if (branchCode == 1)
        {
            opcode = OP_BGEZ;
        }
        if (branchCode == 16)
        {
            opcode = OP_BLTZAL;
        }
        if (branchCode == 17)
        {
            opcode = OP_BGEZAL;

        }


    }


return opcode;


}
struct instr_info * getInstructionInfo(int opcode){


return &instrTable[opcode];
}

int power(int base, int exponent){
    int answer = 1;
    for (int i = 0; i < exponent; i++)
    {
        answer *= base;
    }
    return answer;
}
int checkEndianness(int i, int argc, char **argv){


if (i >= argc)
    {
        return 0;
    }
    int j=0;
    while(argv[i][j] != 0){
        j++;

    }
    if (j >1)
    {
        return 0;
    }
    j =0;
    if (argv[i][j] != 'b' && argv[i][j] != 'l')
    {
        return 0;
    }
    if (argv[i][j] == 'b')
    {
        global_options = global_options | 0x00000004;
    }
    else{
        global_options = global_options & 0xFFFFFFFB;
    }




return 1;
}
int convertHex(int j, char **argv, int i){
    int multiplier = 1;
    int exponent = 0;
    int answer = 0;
while(j>0){
    j--;
    if(argv[i][j] < 58){
        if (argv[i][j] > 47)
        {

            multiplier = argv[i][j] - 48;

        }
    }
    if (argv[i][j] < 71)
    {
        if (argv[i][j] > 64)
        {

            multiplier = argv[i][j] - 55;
        }
    }
    if (argv[i][j] < 103)
    {
        if (argv[i][j] > 96)
        {
            multiplier = argv[i][j] - 87;
        }
    }
    multiplier = multiplier * power(16,exponent);
    answer += multiplier;
    exponent++;

}
return answer;

}
int checkHex(int i,int argc, char **argv){
    if (i >= argc)
    {
        return 0;
    }
    int j = 0;
    while(argv[i][j] != 0){
        j++;
    }
    if(j >8){
        return 0;
       }
       int convertNum = convertHex(j,argv,i);
       int length = j-1;
       int end = length -3;
       if (length>=2)
       {
           /* code */
       while(length > end){
        if(argv[i][length] != 48){

            return 0;
             // if its not 0
        }
        length--;

       }
   }

    j = 0;


    int answer =1;
    if (i< argc)
    {
        // if there is another argument check if its hex
       while(argv[i][j] != 0){

        if(argv[i][j] < 48){

            answer = 0; // if its not 0-9 return false
        }
        if (argv[i][j] > 57) // if it is bigger than the numbers on ascci
        {
            if (argv[i][j] < 65) // check if its a letter if not return false
            {

                answer =  0;
            }
            if (argv[i][j] > 70) // if its greater than range A-F
            {
                if (argv[i][j] < 97) // if its less than 97 return 0
                {

                    answer =  0;
                }
                if (argv[i][j] > 102) // if its greater than f return false
                {

                    answer =  0;
                }

            }

        }
        j++;


       }


    }
    else{
        answer =  0;  // return false
    }
    global_options = convertNum | global_options;

    return answer;
}

/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the
 * program, returning 1 if validation succeeds and 0 if validation fails.
 * Upon successful return, the selected program options will be set in the
 * global variable "global_options", where they will be accessible
 * elsewhere in the program.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return 1 if validation succeeds and 0 if validation fails.
 * Refer to the homework document for the effects of this function on
 * global variables.
 * @modifies global variable "global_options" to contain a bitmap representing
 * the selected options.
 */

int validargs(int argc, char **argv)
{



    /*
    check the number of arguments too few or too many
    */
    if(argc <= 1){
        return 0;
    }
     if (argc > 6)
     {
         return 0;
     }
     /*
     check order of args
     */
     int length = argc;
     char* arg = "-h";
     char* argB = "-b";
     char* argE = "-e";
     char* argA = "-a";
     char* argD = "-d";
     int check = 0;
     int index =0;
     int countOfPositional =0;
     int indexOfPositional =0;
     int indexOfOptional =0;
       for (int i = 0; i < length; i++)
       {



        if ((argA[0] - argv[i][0]) == 0)
            {
                if ((argA[1] - argv[i][1]) == 0)
                {
                    /* code */


                countOfPositional++;
                if (countOfPositional > 1)
                {
                    return 0;
                }
                indexOfPositional = i;
                if (indexOfOptional != 0)
                {


                 if (indexOfOptional < indexOfPositional)
            {
                return 0;
            }
        }

            global_options = global_options & 0xFFFFFFFD;
            getMnemonics();


            }



        }
            if ((argD[0] - argv[i][0]) == 0)
            {

                if ((argD[1] - argv[i][1]) == 0)
                {
                    /* code */




                countOfPositional++;
                if (countOfPositional > 1)
                {
                    return 0;
                }

                if (indexOfOptional != 0)


            {
                indexOfPositional = i;
                 if (indexOfOptional < indexOfPositional)
            {
                return 0;
            }


        }
global_options = global_options | 0x0000002;

            }


        }

            if ((argB[0] - argv[i][0]) == 0)
            {
                if ((argB[1] - argv[i][1]) == 0)
                {



                indexOfOptional = i;
                if(checkHex(i+1,argc,argv) == 0){


                // checked if its parameter is false then return 0
                    return 0;

                }




            }
        }
            if ((argE[0] - argv[i][0]) == 0)
            {
                if ((argE[1] - argv[i][1]) == 0)
                {
                    if (checkEndianness(i+1,argc,argv) == 0)
                    {
                        return 0;
                    }


                indexOfOptional = i;
            }
            }





        int j =0;

        while(arg[j] != 0 || argA[j] !=0 || argD[j] != 0 || argB[j] != 0 || argE[j] != 0){
            if ((arg[j] - argv[i][j]) == 0)
            {
                check = 1;
                index = i;
                j++;
            }
            else
            {
            check = 0;
            j++;
            }




        }
        if (check == 1)
        {
            if (index != 1)
            {
                return 0;
            }


            global_options = global_options | 0x00000001;



        }

       }





     return 1;

}


/**
 * @brief Computes the binary code for a MIPS machine instruction.
 * @details This function takes a pointer to an Instruction structure
 * that contains information defining a MIPS machine instruction and
 * computes the binary code for that instruction.  The code is returne
 * in the "value" field of the Instruction structure.
 *
 * @param ip The Instruction structure containing information about the
 * instruction, except for the "value" field.
 * @param addr Address at which the instruction is to appear in memory.
 * The address is used to compute the PC-relative offsets used in branch
 * instructions.
 * @return 1 if the instruction was successfully encoded, 0 otherwise.
 * @modifies the "value" field of the Instruction structure to contain the
 * binary code for the instruction.
 */
int encode(Instruction *ip, unsigned int addr) {

ip-> value =  reverseOpcodeToValue(ip, ip-> info[0].opcode,addr);





    return 1;
}

/**
 * @brief Decodes the binary code for a MIPS machine instruction.
 * @details This function takes a pointer to an Instruction structure
 * whose "value" field has been initialized to the binary code for
 * MIPS machine instruction and it decodes the instruction to obtain
 * details about the type of instruction and its arguments.
 * The decoded information is returned by setting the other fields
 * of the Instruction structure.
 *
 * @param ip The Instruction structure containing the binary code for
 * a MIPS instruction in its "value" field.
 * @param addr Address at which the instruction appears in memory.
 * The address is used to compute absolute branch addresses from the
 * the PC-relative offsets that occur in the instruction.
 * @return 1 if the instruction was successfully decoded, 0 otherwise.
 * @modifies the fields other than the "value" field to contain the
 * decoded information about the instruction.
 */
int decode(Instruction *ip, unsigned int addr) {

// addr is PC value


    int opcode = getOpCode(ip -> value);

    if (opcode == -70)
    {
        // if get opcode returns -70 its an error so return error
        return 0;
    }
   ip -> info = getInstructionInfo(opcode);

   if (ip -> info[0].type == ITYP)
   {
       parseIType(ip,ip -> info[0], ip -> value, addr);

   }
   if (ip -> info[0].type == JTYP)
   {
      parseJType(ip,ip -> info[0], ip -> value, addr);
   }

   if (ip -> info[0].type == RTYP)
   {
      parseRType(ip,ip -> info[0], ip -> value);
   }




    return 1;
}
