#pragma once
#include "AbstractCommand.h"

class ChangeCommand final: public AbstractCommand
{
	size_t start;
	size_t end;
	std::vector<std::string> text;
	std::vector<std::string> text_for_undo;
public:
	ChangeCommand(size_t start_line, size_t end_line, std::vector<std::string> new_text) : start(start_line), end(end_line), text(std::move(new_text))
	{
		if(start >= end)
		{
			throw std::invalid_argument("Start more than end");
		}
	}

	void Perform(TextObject& text_object) override;
	void Undo(TextObject& text_object) override;

	~ChangeCommand() override = default;
};