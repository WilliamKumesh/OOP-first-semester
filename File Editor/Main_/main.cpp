#include "FileEditor.h"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

namespace 
{
	std::string entering_the_file_name(const std::string& string)
	{
		std::string name_file;
		while (true) {
			std::cout << string << std::endl;
			std::cin >> name_file;
			if (std::ifstream file(name_file); file.good())
			{
				file.close();
				std::cout << std::endl;
				return name_file;
			}
			std::cout << "you have entered a non-existent file name" << std::endl << std::endl;
		}
	}
}

unique_ptr<AbstractCommand> create_command(string const& command_line)
{
	const auto dto = ParseCommand(command_line);
	return CommandCreator::CreateCommand(dto);
}

int main(int argc, char** argv)
{
	const string input_file_name = entering_the_file_name("Enter file_name: ");

	ifstream file_in(input_file_name);

	FileEditor editor(file_in);

	const string command_file_name = entering_the_file_name("Enter command line: insert or delete or change or replace or undo: ");

	ifstream file_command_in(command_file_name);

	string command;

	while(getline(file_command_in, command))
	{
		if(command == "undo")
		{
			editor.TryUndo();
		}
		else
		{
			editor.Perform(CommandCreator::CreateCommand(ParseCommand(command)));
		}
	}

	editor.GetText().WriteToStream(cout);

	return 0;
}
