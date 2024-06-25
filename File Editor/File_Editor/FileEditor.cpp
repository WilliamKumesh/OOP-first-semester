#include "FileEditor.h"
#include <iostream>

FileEditor::FileEditor(std::istream& text_stream): text_object(text_stream)
{}

void FileEditor::Perform(std::unique_ptr<AbstractCommand> command)
{
	command->Perform(text_object);
	command_history.push(std::move(command));
}

bool FileEditor::TryUndo() 
{
	if (command_history.empty())
	{
		return false;
	}
	command_history.top()->Undo(text_object);
	command_history.pop();

	return true;
}