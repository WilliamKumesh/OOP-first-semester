#pragma once
#include <string>
#include <utility>
#include <vector>


class CommandDto final
{
	std::string command_name;
	std::vector<std::string> command_text;
	std::vector<std::string> replace_text;
	int command_start_pos{};
	int command_end_pos{};
public:
	CommandDto(std::string command_name_, int start, int end, std::vector<std::string> insert_text, std::vector<std::string> replace_text_) :
		command_name(std::move(command_name_)), command_text(std::move(insert_text)),
		replace_text(std::move(replace_text_)), command_start_pos(start), command_end_pos(end)
	{}

	[[nodiscard]] const std::string& GetCommandName() const noexcept;
	[[nodiscard]] int GetCommandStartPos() const noexcept;
	[[nodiscard]] int GetCommandEndPos() const noexcept;
	[[nodiscard]] const std::vector<std::string>& GetCommandText() const noexcept;
	[[nodiscard]] const std::vector<std::string>& GetReplaceText() const noexcept;
};
