#include "CommandCreator.h"
#include <stdexcept>
#include "ParsingCommand.h"
#include "ChangeCommand.h"
#include "DeleteCommand.h"
#include "InsertCommand.h"
#include "ReplaceCommand.h"
#include <unordered_map>
#include <functional>
#include <string>

static std::unique_ptr<AbstractCommand> create_delete_command(const CommandDto& dto)
{
	return std::make_unique<DeleteCommand>(dto.GetCommandStartPos(), dto.GetCommandEndPos());
};

static std::unique_ptr<AbstractCommand> create_insert_command(const CommandDto& dto)
{
	return std::make_unique<InsertCommand>(dto.GetCommandStartPos(), dto.GetCommandText());
}

static std::unique_ptr<AbstractCommand> create_change_command(const CommandDto& dto)
{
	return std::make_unique<ChangeCommand>(dto.GetCommandStartPos(), dto.GetCommandEndPos(), dto.GetCommandText());
}

static std::unique_ptr<AbstractCommand> create_replace_command(const CommandDto& dto)
{
	return std::make_unique<ReplaceCommand>(dto.GetCommandStartPos(), dto.GetCommandEndPos(), dto.GetCommandText(), dto.GetReplaceText());
}

namespace
{
	const std::string command_delete_name = "delete";
	const std::string command_insert_name = "insert";
	const std::string command_change_name = "change";
	const std::string command_replace_name = "replace";
	const std::unordered_map<std::string, std::function<std::unique_ptr<AbstractCommand>(const CommandDto& dto)>> dictionary_for_create_command
	{ {command_delete_name, create_delete_command}, {command_insert_name, create_insert_command},
		{command_change_name, create_change_command }, {command_replace_name, create_replace_command}
	};
}

std::unique_ptr<AbstractCommand> CommandCreator::CreateCommand(const CommandDto& dto)
{
	if (dictionary_for_create_command.contains(dto.GetCommandName()))
	{
		return dictionary_for_create_command.find(dto.GetCommandName())->second(dto);
	}

	throw std::invalid_argument("No such command");
}
