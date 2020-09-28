#pragma once
#ifndef _HWHEADER_H
#define _HWHEADER_H
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLES 15

typedef struct item {
	char* name;
	int price, quan;
	char premium;
}Item;

typedef struct table {
	Item order;
	struct table *next, *prev;
}Table;

typedef struct kitchen {
	Item dish;
	struct kitchen* next;
}kitchen, *pkitchen;

void Error_Msg(char* msg);
int CheckItem(pkitchen supply, char* name); //check if item is on the menu
kitchen* CreateNod();
pkitchen CreateProducts(FILE* in, FILE* out);//load menu from file
void AddItems(pkitchen menu, char*name, int quantity, FILE*out); //add existing item to the menu
void OrderItem(pkitchen menu,Table table[TABLES],int tableNum, char *name, int quantity, FILE*out);
#endif