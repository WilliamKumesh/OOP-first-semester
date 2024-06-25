#include "ParsingCommand.h"

namespace
{
	const std::string tab_symbol = "\\n";
	const std::string slash_symbol = "\\\\";
	const std::string quote_symbol = "\\\"";

	const std::string new_slash_symbol = "\\";
	const std::string new_quote_symbol = "\"";


	constexpr int buffer_size_for_search = 30;

	const std::string insert_key_word = "after";
	const std::string interval_key_word_start = "from";
	const std::string interval_key_word_end = "to";

	constexpr char text_delimeter = ' ';
	constexpr char bracket_left = '(';
	constexpr char bracket_right = ')';

}

static std::string ParsingElement(const std::string& command_line, size_t& line_position)
{
	const auto pos = command_line.find(text_delimeter, line_position);

	std::string element = command_line.substr(line_position, pos);

	line_position = pos + 1;

	return element;
}

static std::pair<int, int> ParsingInterval(const std::string& command_line, size_t& line_position)
{
	const std::string search_key_word(command_line, line_position, buffer_size_for_search);
	std::pair<int, int> interval;

	if (search_key_word.find(insert_key_word) != std::string::npos)
	{
		ParsingElement(command_line, line_position);
		interval.first = stoi(ParsingElement(command_line, line_position));
		return interval;
	}

	if (search_key_word.find(interval_key_word_start) != std::string::npos)
	{
		ParsingElement(command_line, line_position);
		interval.first = stoi(ParsingElement(command_line, line_position));
	}
	else
	{
		interval.first = 0;
	}

	if (search_key_word.find(interval_key_word_end) != std::string::npos)
	{
		ParsingElement(command_line, line_position);
		interval.second = stoi(ParsingElement(command_line, line_position));
	}
	else
	{
		interval.second = std::numeric_limits<int>::max();
	}

	return interval;
}

static void ConvertSymbol(std::string& text, const std::string& convert_value, const std::string& new_value)
{
	auto pos = text.find(convert_value);
	while (pos != std::string::npos)
	{
		text.replace(pos, convert_value.size(), new_value);
		pos = text.find(convert_value);
	}
}

static std::vector<std::string> ParsingText(const std::string& command_line, size_t& line_position)
{
	std::vector<std::string> new_text;

	line_position = command_line.find(bracket_left, line_position) + sizeof(bracket_left);

	size_t tab_pos = 0;

	while (tab_pos != std::string::npos)
	{
		tab_pos = command_line.find(tab_symbol, line_position);
		const size_t pos_bracket = command_line.find(bracket_right, line_position);

		if (tab_pos >= pos_bracket)
		{
			std::string new_text_line = command_line.substr(line_position, pos_bracket - line_position);
			ConvertSymbol(new_text_line, slash_symbol, new_slash_symbol);
			ConvertSymbol(new_text_line, quote_symbol, new_quote_symbol);
			new_text.push_back(new_text_line);
			break;
		}

		std::string new_text_line = command_line.substr(line_position, tab_pos - line_position);
		ConvertSymbol(new_text_line, slash_symbol, new_slash_symbol);
		ConvertSymbol(new_text_line, quote_symbol, new_quote_symbol);
		new_text.push_back(new_text_line);

		line_position = tab_pos + tab_symbol.length();
	}

	return new_text;
}

CommandDto ParseCommand(const std::string& command_line)
{
	size_t line_position = 0;

	std::string name = ParsingElement(command_line, line_position);

	auto interval = ParsingInterval(command_line, line_position);

	auto text_insert = ParsingText(command_line, line_position);

	auto deleted_text = ParsingText(command_line, line_position);

	return {name, interval.first, interval.second, text_insert, deleted_text};
}