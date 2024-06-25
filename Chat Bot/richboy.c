#include "richboy.h"
#include "new.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static void* rboy_ctor(void* _self, va_list* app)
{
	struct RichBoy* self = ((const Class*)User_)->ctor(_self, app);
	return self;
}

#define name(p) (((const struct User*)(p))->name)

static void rboy_type(const void* _self, Flags* flags)
{
	const struct RichBoy* self = _self;
	((const Class*)User_)->type(_self, flags);
	printf("%s", name(self));
	printf(": ");
	printf("I have a supercar \n");
	if (flags->dress_flag == true)
	{
		printf("%s", name(self));
		printf(": ");
		printf("Of course, baby. I'm the richest boy in the world! \n");
	}
}

static void* rboy_dctor(void* _self)
{
	return ((const struct Class*)User_)->dctor(_self);
}

static const Class _RBoy =
{
	sizeof(struct RichBoy), rboy_ctor, rboy_dctor, rboy_type
};

const void* Rich_Boy_ = &_RBoy;