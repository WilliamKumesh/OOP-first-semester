#pragma once
#include <stdio.h>

typedef struct users_list
{
	void** users;
	int count;
}users_list;

void free_users_list(users_list* list);

users_list create_user_list(FILE* fin);