#include "boy.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "new.h"

static void* boy_ctor(void* _self, va_list* app)
{
	struct Boy* self = ((const struct Class*)User_)->ctor(_self, app);
	return self;
}

#define name(p) (((const struct User*)(p))->name)

static void boy_type(const void* _self, Flags* flags)
{
	const struct Boy* self = _self;
	((const struct Class*)User_)->type(_self, flags);
	if (flags->dress_flag == true)
	{
		flags->rats_flag = true;
		printf("%s", name(self));
		printf(": ");
		printf("U r such a girl! R u afraid of rats? \n");
	}
}

static void* boy_dctor(void* _self)
{
	return ((const struct Class*)User_)->dctor(_self);
}

static const Class _Boy =
{
	sizeof(struct Boy), boy_ctor, boy_dctor, boy_type
};

const void* Boy_ = &_Boy;