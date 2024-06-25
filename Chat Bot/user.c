#define _CRT_SECURE_NO_WARNINGS
#include "user.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "new.h"

static void* user_ctor(void* _self, va_list* app)
{
	struct User* self = _self;
	char* temp = va_arg(*app, char*);
	self->name = malloc(strlen(temp)+1);
	if (self->name == NULL)
	{
		return NULL;
	}
	strcpy(self->name, temp);
	return self;
}

static void user_type(const void* _self, Flags* flags)
{
	const struct User* self = _self;
	printf("%s", self->name);
	printf(": ");
	printf("Hey \n");
}

static void* user_dctor(void* _self)
{
	struct User* self = _self;
	free(self->name);
	return self;
}

static const Class _User =
{
	sizeof(struct User), user_ctor, user_dctor, user_type
};

const void* User_ = &_User;