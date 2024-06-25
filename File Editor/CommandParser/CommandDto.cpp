#include "CommandDto.h"

int CommandDto::GetCommandEndPos() const noexcept
{
	return command_end_pos;
}

int CommandDto::GetCommandStartPos() const noexcept
{
	return command_start_pos;
}

const std::string& CommandDto::GetCommandName() const noexcept
{
	return command_name;
}

const std::vector<std::string>& CommandDto::GetCommandText() const noexcept
{
	return command_text;
}

const std::vector<std::string>& CommandDto::GetReplaceText() const noexcept
{
	return replace_text;
}
