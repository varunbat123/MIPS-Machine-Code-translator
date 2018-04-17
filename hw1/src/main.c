#include <stdlib.h>
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

#include "hw1.h"
#include "instruction.h"

#include "debug.h"

int main(int argc, char **argv)
{
    struct instruction ip;
   int byteOne;
  int byteTwo;
  int byteThree;
  int byteFour;
   int num =0;
 char  buf[190] ;
 char answer[190];
 int arg1 =0;
 int arg2=0;
 int arg3 =0;




    if(!validargs(argc, argv))
        USAGE(*argv, EXIT_FAILURE);
    debug("Options: 0x%X", global_options);
    if(global_options & 0x1) {
        USAGE(*argv, EXIT_SUCCESS);
    }

 if(global_options & 0x2) {
    if ((global_options & 0x00000004) == 4 )

    {

        if (global_options & 0xFFFF000)
    {
        global_options = global_options & 0xFFFF000;
    }
    else{
        global_options = 0;
    }




        while(fread(&byteOne, 1,1,stdin)==1){
        fread(&byteTwo, 1,1,stdin);
        fread(&byteThree, 1,1,stdin);
        fread(&byteFour, 1,1,stdin);
        byteOne = byteOne & 0x000000FF;
        byteOne = byteOne << 24;
        byteTwo = byteTwo & 0x000000FF;
        byteTwo = byteTwo << 16;
        byteThree = byteThree & 0x000000FF;
        byteThree = byteThree << 8;

        byteFour = byteFour & 0x000000FF;
        num = byteOne | byteTwo;

        num = num | byteThree;
        num = num |byteFour;




        ip.value = num;
        decode(&ip, global_options);


        printf(ip.info -> format, ip.args[0], ip.args[1], ip.args[2] );
        printf("%s\n","" );
        global_options = global_options +4;
    }



    }
    if (global_options & 0xFFFF000)
    {

        global_options = global_options & 0xFFFF000;
    }
    else{
        global_options = 0;
    }




        while(fread(&byteOne, 1,1,stdin)==1){
        fread(&byteTwo, 1,1,stdin);
        fread(&byteThree, 1,1,stdin);
        fread(&byteFour, 1,1,stdin);
        byteFour = byteFour & 0x000000FF;
        byteFour = byteFour << 24;
        byteThree = byteThree & 0x000000FF;
        byteThree = byteThree << 16;
        byteTwo = byteTwo & 0x000000FF;
        byteTwo = byteTwo << 8;

        byteOne = byteOne & 0x000000FF;
        num = byteFour | byteThree;

        num = num | byteTwo;
        num = num |byteOne;




        ip.value = num;
        decode(&ip, global_options);


        printf(ip.info -> format, ip.args[0], ip.args[1], ip.args[2] );
        printf("%s\n","" );
        global_options = global_options +4;
    }




    }
    int instructionNumber = 0;

while(fgets(answer,190,stdin)!=NULL){


for (int i = 0; i < 64; i++)
{


        if(sscanf(answer,instrTable[i].format,&arg1, &arg2, &arg3)!=0){
            ip.info = &instrTable[i];



    }

}
ip.args[0] =arg1;
ip.args[1] =arg2;
ip.args[2] =arg3;


ip.regs[0]= 0;
ip.regs[1]= 0;
ip.regs[2]= 0;
ip.extra= 0;

for (int i = 0; i <3; i++)
{
   if (ip.info[0].srcs[i]== RS)
    {

       ip.regs[0]=ip.args[i];
    }
     if (ip.info[0].srcs[i]== RT)
    {
       ip.regs[1]=ip.args[i];
    }
     if (ip.info[0].srcs[i]== RD)
    {
       ip.regs[2]=ip.args[i];
    }
     if (ip.info[0].srcs[i]== EXTRA)
    {
       ip.extra=ip.args[i];
    }
}

 encode(&ip,global_options);


 if ((global_options & 0x00000004)==4 )

    {

        if (global_options & 0xFFFF000)
    {
        global_options = global_options & 0xFFFF000;
    }
    else{
        global_options = 0;
    }
byteOne = ip.value & 0xFF000000;
byteOne = byteOne >>24;
byteOne = byteOne &0x000000FF;

byteTwo = ip.value & 0x00FF0000;
byteTwo = byteTwo >> 16;
byteTwo = byteTwo & 0x000000FF;

byteThree = ip.value & 0x0000FF00;
byteThree = byteThree >> 8;
byteThree = byteThree &0x000000FF;

byteFour = ip.value & 0x000000FF;
putc(byteOne,stdout);
putc(byteTwo,stdout);
putc(byteThree,stdout);
putc(byteFour,stdout);

}
else{

byteOne = ip.value & 0xFF000000;
byteOne = byteOne >>24;
byteOne = byteOne &0x000000FF;

byteTwo = ip.value & 0x00FF0000;
byteTwo = byteTwo >> 16;
byteTwo = byteTwo & 0x000000FF;

byteThree = ip.value & 0x0000FF00;
byteThree = byteThree >> 8;
byteThree = byteThree &0x000000FF;

byteFour = ip.value & 0x000000FF;
putc(byteFour,stdout);
putc(byteThree,stdout);
putc(byteTwo,stdout);
putc(byteOne,stdout);
}


}
    return EXIT_SUCCESS;
}

/*
 * Just a reminder: All non-main functions should
 * be in another file not named main.c
 */
