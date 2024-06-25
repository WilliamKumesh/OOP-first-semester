#include "InsertCommand.h"

void InsertCommand::Perform(TextObject& text_object)
{
	if (start > text_object.GetLines().size())
	{
		start = text_object.GetLines().size();
	}

	text_object.TryAddLines(start, inserted);
}

void InsertCommand::Undo(TextObject& text_object)
{
	text_object.TryDeleteLines(start, start + inserted.size());
}

