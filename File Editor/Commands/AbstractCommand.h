#pragma once
#include "TextObject.h"

class AbstractCommand 
{
public:
	virtual void Perform(TextObject& text_object) = 0;
	virtual void Undo(TextObject& text_object) = 0;

	virtual ~AbstractCommand() = default;
};