#include "DeleteCommand.h"
#include <stdexcept>
#include "iterator"

void DeleteCommand::Perform(TextObject& text_object)
{
	if (end > text_object.GetLines().size())
	{
		end = text_object.GetLines().size();
	}

	if (start >= end)
	{
		throw std::invalid_argument("Start more than end");
	}

	std::copy(text_object.GetLines().begin() + start, text_object.GetLines().begin() + end, std::back_inserter(text_for_undo));
	text_object.TryDeleteLines(start, end);
}

void DeleteCommand::Undo(TextObject& text_object)
{
	text_object.TryAddLines(start, text_for_undo);
}
