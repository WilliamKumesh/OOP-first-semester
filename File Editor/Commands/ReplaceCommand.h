#pragma once
#include "AbstractCommand.h"
#include "stdexcept"

class ReplaceCommand final : public AbstractCommand
{
	size_t start;
	size_t end;
	size_t line_to_delete;
	std::vector<std::string> inserted;
	std::vector<std::string> deleted;
	std::vector<std::string> text_for_undo;
	[[nodiscard]] bool CheckDeletedText(const TextObject& text_object) noexcept;
public:
	ReplaceCommand(size_t start_line, size_t end_line, std::vector<std::string> insert_lines, 
		std::vector<std::string> deleted_text) : start(start_line), end(end_line),
	line_to_delete(0), inserted(std::move(insert_lines)) , deleted(std::move(deleted_text))
	{
		if(start_line >= end_line)
		{
			throw std::invalid_argument("Start more than stop");
		}
	}

	void Perform(TextObject& text_object) override;
	void Undo(TextObject& text_object) override;

	~ReplaceCommand() override = default;
};