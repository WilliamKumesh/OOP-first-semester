#define _CRT_SECURE_NO_WARNINGS
#include "prasers.h"
#include"user.h"
#include"new.h"
#include"Girl.h"
#include"coward_girl.h"
#include"boy.h"
#include"richboy.h"
#include <stdlib.h>
#include <string.h>
#define buffer_size 50

typedef struct member_info
{
	char* user_name;
	char* user_type;

}member_info;

void free_users_list(users_list* list)
{
	for (int i = 0; i < list->count; i++)
	{
		delete_(list->users[i]);
	}
	free(list->users);
	list->count = 0;
	list->users = NULL;
}

static void free_member(member_info* member)
{
	free(member->user_name);
	free(member->user_type);
	member->user_name = NULL;
	member->user_type = NULL;
}

static member_info create_member_info(char* name, char* type)
{
	member_info member;

	member.user_name = malloc(strlen(name) + 1);
	member.user_type = malloc(strlen(type) + 1);

	if(member.user_name == NULL || member.user_type == NULL)
	{
		free_member(&member);
		return member;
	}
	strcpy(member.user_name, name);
	strcpy(member.user_type, type);



	return member;
}

static member_info pars_member(FILE* fin)
{
	char buffer[buffer_size];

	char delimiter_name[2] = " ";
	char delimiter_type[2] = "\n";

	member_info member;
	member.user_name = NULL;
	member.user_type = NULL;

	if (fgets(buffer, buffer_size, fin))
	{
		char* temp_name = strtok(buffer, delimiter_name);
		char* temp_type = strtok(NULL, delimiter_type);

		if(temp_name == NULL || temp_type == NULL)
		{
			free_member(&member);
			return member;
		}
		member = create_member_info(temp_name, temp_type);
	}

	return member;
}

static void* create_user(member_info member)
{
	if (strcmp(member.user_type, "CowardGirl") == 0)
	{
		void* c_g = new_(Coward_Girl_, member.user_name);
		return c_g;
	}
	if (strcmp(member.user_type, "User") == 0)
	{
		void* u = new_(User_, member.user_name);
		return u;
	}
	if (strcmp(member.user_type, "Girl") == 0)
	{
		void* g = new_(Girl_, member.user_name);
		return g;
	}
	if (strcmp(member.user_type, "Boy") == 0)
	{
		void* b = new_(Boy_, member.user_name);
		return b;
	}
	if (strcmp(member.user_type, "RichBoy") == 0)
	{
		void* rb = new_(Rich_Boy_, member.user_name);
		return rb;
	}
	return NULL;
}

users_list create_user_list(FILE* fin)
{
	users_list users_list_;
	users_list_.count = 0;
	users_list_.users = NULL;

	while (!feof(fin))
	{
		member_info member = pars_member(fin);

		free_member(&member);

		if(member.user_name == NULL || member.user_type == NULL)
		{
			continue;
		}

		void* user = create_user(member);

		if (user == NULL)
		{
			free_member(&member);
			continue;
		}

		void** users_temp = realloc(users_list_.users, (users_list_.count + 1) * sizeof(void*));

		if (users_temp != NULL)
		{
			users_list_.users = users_temp;
			users_list_.users[(users_list_.count)++] = user;
		}
		else
		{
			free_users_list(&users_list_);
			delete_(user);
			break;
		}
	}

	return users_list_;
}