#include "ReplaceCommand.h"
#include <stdexcept>

bool ReplaceCommand::CheckDeletedText(const TextObject& text_object) noexcept
{
	size_t count_same_lines = 0;

	for (auto i = start; i < end; i++)
	{
		if (text_object.GetLines()[i] == deleted[count_same_lines])
		{
			count_same_lines++;
		}
		else
		{
			count_same_lines = 0;
		}

		if (count_same_lines == deleted.size())
		{
			line_to_delete = i - count_same_lines + 1;
			return true;
		}
	}
	return false;
}

void ReplaceCommand::Perform(TextObject& text_object)
{
	if (end > text_object.GetLines().size())
	{
		end = text_object.GetLines().size();
	}

	if (start >= end)
	{
		throw std::invalid_argument("Start more than end");
	}

	if(CheckDeletedText(text_object) == false)
	{
		throw std::invalid_argument("No such text in file");
	}

	text_object.TryDeleteLines(line_to_delete, line_to_delete + deleted.size());
	text_object.TryAddLines(line_to_delete, inserted);
}

void ReplaceCommand::Undo(TextObject& text_object)
{
	text_object.TryDeleteLines(line_to_delete, line_to_delete + inserted.size());
	text_object.TryAddLines(line_to_delete, deleted);
}
