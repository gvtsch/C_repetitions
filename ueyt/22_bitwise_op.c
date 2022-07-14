#include <stdio.h>
#include <stdlib.h>
#define BIT 0x02


int main () {

	unsigned char bit = 0x0;
	int i = 0;

	bit |= BIT;
	bit |= 1<<5;
	bit &= ~(1<<5);

	for (i = sizeof(bit)*8; i > 0; i--){
		if(((bit>>7)%2) == 0){
			printf("0");
		}else{
			printf("1");
		}
		bit<<=1;
	}
		

	printf("\n\n\n");
	system("PAUSE");
	return 0;
}