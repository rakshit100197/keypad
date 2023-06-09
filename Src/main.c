#include<stdio.h>
#include<stdint.h>
void delay(void){

}
int main(){
	uint32_t volatile *const pclkreg =(uint32_t*)(0x40023800+0x30);
	uint32_t volatile *const pgpiodmode =(uint32_t*)(0x40020C00);
	uint32_t volatile *const pInputreg =(uint32_t*)(0x40020C00+0x10);
	uint32_t volatile *const pOutputreg =(uint32_t*)(0x40020C00+0x14);
	uint32_t volatile *const pPullupdownreg =(uint32_t*)(0x40020C00+0x0C);

//enable clock
	*pclkreg |= (1<<3);
//enable PDO PD1 ,PD2 ,PD3 as output
	*pgpiodmode &= ~(0xFF);
	*pgpiodmode|= 0x55;
//enable PD8,9,10,11 as input 00shifted cause its 8th pin
	*pgpiodmode &=~(0xFF<<16);

//Enable pull up reg which is 01 for pull up on 8,9,10,11 bit
	*pPullupdownreg &= ~(0xFF<<16);
	*pPullupdownreg |= (0X55<<16);
while(1){
//make outputdata reg high
*pOutputreg|= 0x0F;
//make R1 low=PD0////////////////////////////////////////////////////////////////////////////////////////
*pOutputreg&=~(1<<0);
//check C1 (pd8)
if(	!(*pInputreg & (1<<8))){
	delay();
	printf("1\n");
}
//c2
else if(!(*pInputreg & (1<<9))){
	delay();
	printf("2\n");
}
//c3
if(	!(*pInputreg & (1<<10))){
	delay();
	printf("3\n");
}
//c4
if(	!(*pInputreg & (1<<11))){
	delay();
	printf("anode\n");
	//lifeos
}

//////////////////////////////////////make R2 low/////////////////////////////////////////////////////////
//make outputdata reg high
*pOutputreg|= 0x0F;
//make R1 low=PD0
*pOutputreg&=~(1<<1);
//check C1 (pd8)
if(	!(*pInputreg & (1<<8))){
	delay();
	printf("4\n");
}
//c2
else if(!(*pInputreg & (1<<9))){
	delay();
	printf("5\n");
}
//c3
if(	!(*pInputreg & (1<<10))){
	delay();
	printf("6\n");
}
//c4
if(	!(*pInputreg & (1<<11))){
	delay();
	printf("b\n");
}
////////////////////////////////////////r3 low////////////////////////
//make outputdata reg high
*pOutputreg|= 0x0F;
//make R1 low=PD0
*pOutputreg&=~(1<<2);
//check C1 (pd8)
if(	!(*pInputreg & (1<<8))){
	delay();
	printf("7\n");
}
//c2
else if(!(*pInputreg & (1<<9))){
	delay();
	printf("8\n");
}
//c3
if(	!(*pInputreg & (1<<10))){
	delay();
	printf("9\n");
}
//c4
if(	!(*pInputreg & (1<<11))){
	delay();
	printf("c\n");
}
///////////////////////////////////R4 Low/////////////////////////////////////
//make outputdata reg high
*pOutputreg|= 0x0F;
//make R1 low=PD0
*pOutputreg&=~(1<<3);
//check C1 (pd8)
if(	!(*pInputreg & (1<<8))){
	delay();
	printf("*\n");
}
//c2
else if(!(*pInputreg & (1<<9))){
	delay();
	printf("0\n");
}
//c3
if(	!(*pInputreg & (1<<10))){
	delay();
	printf("#\n");
}
//c4
if(	!(*pInputreg & (1<<11))){
	delay();
	printf("d\n");
}
}
	return 0;
}
