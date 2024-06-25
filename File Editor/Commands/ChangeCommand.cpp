#include "ChangeCommand.h"
#include <iterator>
#include <stdexcept>

void ChangeCommand::Perform(TextObject& text_object)
{
	if (end > text_object.GetLines().size())
	{
		end = text_object.GetLines().size();
	}

	if(start >= end)
	{
		throw std::invalid_argument("Start more than end");
	}

	std::copy(text_object.GetLines().begin() + start, text_object.GetLines().begin() + end, std::back_inserter(text_for_undo));
	text_object.TryDeleteLines(start, end);
	text_object.TryAddLines(start, text);
}

void ChangeCommand::Undo(TextObject& text_object)
{
	text_object.TryDeleteLines(start, start + text.size());
	text_object.TryAddLines(start, text_for_undo);
}