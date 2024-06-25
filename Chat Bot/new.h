#pragma once

#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h> // bool

typedef struct Flags
{
	bool rats_flag;
	bool dress_flag;
}Flags;

typedef struct Class
{
	size_t size;
	void* (*ctor)(void* self, va_list* app);
	void* (*dctor)(void* self);
	void (*type)(const void* self, Flags* flags);
}Class;

void* new_(const void* Class, ...);
void delete_(void* self);
void type(const void* self, Flags* flags);
