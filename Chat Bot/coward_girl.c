#include"coward_girl.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "Girl.h"
#include "new.h"

static void* cgirl_ctor(void* _self, va_list* app)
{
	struct Coward_Girl* self = ((const struct Class*)User_)->ctor(_self, app);
	return self;
}

#define name(p) (((const struct User*)(p))->name)

static void cgirl_type(const void* _self, Flags* flags)
{
	const struct Coward_Girl* self = _self;
	((const struct Class*)Girl_)->type(_self, flags);
	flags->dress_flag = true;
	if (flags->rats_flag == true)
	{
		printf("%s", name(self));
		printf(": ");
		printf("AAAAaaa! No! No rats here, pls \n");
	}
}

static void* cgirl_dctor(void* _self)
{
	return ((const struct Class*)User_)->dctor(_self);
}

static const Class _Coward_Girl =
{
	sizeof(struct Coward_Girl), cgirl_ctor, cgirl_dctor, cgirl_type
};

const void* Coward_Girl_ = &_Coward_Girl;