#pragma once
#include <memory>
#include "AbstractCommand.h"
#include "ParsingCommand.h"

class CommandCreator final
{
public:
	[[nodiscard]]static std::unique_ptr<AbstractCommand> CreateCommand(const CommandDto& dto);
};
