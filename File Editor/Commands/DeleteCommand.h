#pragma once
#include <string>
#include <vector>
#include "AbstractCommand.h"

class DeleteCommand final : public AbstractCommand
{
	size_t start;
	size_t end;
	std::vector<std::string> text_for_undo;
public:
	DeleteCommand(size_t start_line, size_t end_line) : start(start_line), end(end_line)
	{
		if(start >= end)
		{
			throw std::invalid_argument("Start more than end");
		}
	}

	void Perform(TextObject& text_object) override;
	void Undo(TextObject& text_object) override;

	~DeleteCommand() override = default;
};