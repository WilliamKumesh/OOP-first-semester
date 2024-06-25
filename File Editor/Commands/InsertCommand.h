#pragma once
#include "AbstractCommand.h"

class InsertCommand final : public AbstractCommand
{
	size_t start;
	std::vector<std::string> inserted;
public:
	InsertCommand(size_t start_line, std::vector<std::string> text_for_insert) :
		start(start_line), inserted(std::move(text_for_insert))
	{}

	void Perform(TextObject& text_object) override;
	void Undo(TextObject& text_object) override;

	~InsertCommand() override = default;
};