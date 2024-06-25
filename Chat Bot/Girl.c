#include"Girl.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "new.h"

static void* girl_ctor(void* _self, va_list* app)
{
	struct Girl* self = ((const struct Class*)User_)->ctor(_self, app);
	return self;
}

#define name(p) (((const struct User*)(p))->name)

static void girl_type(const void* _self, Flags* flags)
{
	const struct Girl* self = _self;
	((const struct Class*)User_)->type(_self, flags);
	flags->dress_flag = true;
	printf("%s", name(self));
	printf(": ");
	printf("I want a dress. Will somebody buy it for me? \n");
}

static void* girl_dctor(void* _self)
{
	return ((struct Class*)User_)->dctor(_self);
}

static const Class _Girl =
{
	sizeof(struct Girl), girl_ctor, girl_dctor, girl_type
};

const void* Girl_ = &_Girl;