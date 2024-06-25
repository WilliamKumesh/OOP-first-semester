#include <stdlib.h>
#include <assert.h>
#include "new.h"

void* new_(const void* _class, ...)
{
	const Class* class_ = _class;
	void* p = calloc(1, class_->size);
	assert(p);
	*(const Class**)p = class_;

	if (class_->ctor)
	{
		va_list ap;
		va_start(ap, _class);
		p = class_->ctor(p, &ap);
		va_end(ap);
	}
	return p;
}

void delete_(void* self)
{
	const Class** cp = self;

	if (self && *cp && (*cp)->dctor)
	{
		self = (*cp)->dctor(self);
	}

	free(self);
}

void type(const void* self, Flags* flags)
{
	const struct Class* const* cp = self;

	assert(self && *cp && (*cp)->type);

	(*cp)->type(self, flags);
}