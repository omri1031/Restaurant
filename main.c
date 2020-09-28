#include "HWheader.h"

int main()
{
	int action,quantity,tableNum,i;
	pkitchen menu=NULL;
	Table arr[TABLES];
	char name[101];
	FILE* order = fopen("Instructions.txt", "rt");//open file for orders
	FILE* in = fopen("Manot.txt", "rt"); //open file for menu
	FILE* out = fopen("Output.txt", "w"); //create file for output
	for (i = 0; i < TABLES; i++)
	{
		arr[i].next = NULL;
		arr[i].prev = NULL;
	}

	
	fcloseall();
}