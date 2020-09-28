#include "HWheader.h"

/*Print error message if needed*/
void Error_Msg(char* msg)
{
	printf("\n%s", msg);
	exit(1);
}
int CheckItem(pkitchen menu, char *name)
{
	pkitchen tmp = menu;
	int i = 1;
	if (tmp->dish.name == NULL)
		return 0;
	while (tmp->next != NULL)
	{
		if (strcmp(tmp->dish.name, name) == 0)
			return i;
		tmp = tmp->next;
		i++;
	}
	return 0;
}
pkitchen CreateNod()
{
	kitchen* tmp = (kitchen*)malloc(sizeof(kitchen));
	if (!tmp)
		Error_Msg("Memory allocation error!");
	return tmp;
}
pkitchen CreateProducts(FILE* in, FILE* out)
{
	int price, quantity,flag;
	char premium, name[101];
	pkitchen menu = (kitchen*)malloc(sizeof(kitchen));
	if (!menu)
		Error_Msg("Memory allocation error!");
	menu->dish.name = NULL;
	menu->next = NULL;
	pkitchen tmp;
	while (fscanf(in, "%s %d %d %c", name, &price, &quantity,&premium)==4)
	{
		flag = 1;
		if (price < 0)
			fprintf(out, "Please enter price larger then 0!\n",flag=0);
		if(quantity<0)
			fprintf(out, "Please enter quantity larger then 0!\n",flag=0);
		if (CheckItem(menu, name))
			fprintf(out, "The dish %s is already on the menu!\n",name,flag=0);
		if (flag)
		{
			tmp = CreateNod();
			tmp->dish.name = (char*)malloc(strlen(name));
			strcpy(tmp->dish.name, name);
			tmp->dish.premium = premium;
			tmp->dish.price = price;
			tmp->dish.quan = quantity;
			tmp->next = menu;
			menu= tmp;
		}
	}
	fprintf(out, "The kitchen was created\n");
	return menu;
}
void AddItems(pkitchen menu, char *name, int quantity, FILE*out)
{
	pkitchen tmp = menu;
	int i,flag=1,j;
	i = CheckItem(menu, name);
	if (quantity < 0)
		fprintf(out, "Please enter quantity larger then 0!\n", flag = 0);
	if (i == 0)
		fprintf(out, "The dish is NOT in the menu!\n", flag = 0);
	if (flag)
	{
		for (j = 0; j < i-1; j++)
			tmp = tmp->next;
		tmp->dish.quan += quantity;
		fprintf(out, "%d %s were added to the kitchen\n", quantity, tmp->dish.name);
	}
}
void OrderItem(pkitchen menu,Table* table,int tableNum ,char *name, int quantity, FILE*out)
{
	int dishnum,flag=1,i;
	Table* tmp=(Table*)malloc(sizeof(Table));
	pkitchen tmpMenu = menu;
	Table* tmp2 = &table[tableNum];
	dishnum = CheckItem(menu, name);
	if (dishnum == 0)
		fprintf(out, "We don’t have %s, sorry!\n",name, flag = 0);
	if (flag)
	{
		tmp->order.name = (char*)malloc(strlen(name));
		strcpy(tmp->order.name, name);
		tmp->order.quan = quantity;
		for (i = 0; i < dishnum - 1; i++)
			tmpMenu = tmpMenu->next;
		tmp->order.price = tmpMenu->dish.price;
		tmp->order.premium=tmpMenu->dish.premium;
		while (tmp2 != NULL)
			tmp2 = tmp2->next;
		table[tableNum].next = tmp;
		tmp->prev = &table[tableNum];
		fprintf(out, "%d %s  were added to the table number %d", quantity, name, tableNum);	
	}
}