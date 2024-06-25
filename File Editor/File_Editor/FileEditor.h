#pragma once
#include <vector>
#include <stack>
#include "AbstractCommand.h"
#include "CommandCreator.h"
#include "ostream"

class FileEditor final
{
	std::vector<std::string> command_lines;
	std::stack<std::unique_ptr<AbstractCommand>> command_history;
	TextObject text_object;

public:
	FileEditor(std::istream& text_stream);

	void Perform(std::unique_ptr<AbstractCommand> command);

	bool TryUndo();

	[[nodiscard]] const TextObject& GetText() const noexcept
	{
		return text_object;
	}
};