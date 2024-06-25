#include "TextObject.h"
#include <sstream>

bool TextObject::TryAddLines(size_t start_line_pos, const std::vector<std::string>& add_lines)
{
	if (start_line_pos > lines.size())
	{
		return false;
	}

	lines.insert(lines.begin() + start_line_pos, add_lines.begin(), add_lines.end());
	return true;
}

bool TextObject::TryDeleteLines(size_t start_line_pos, size_t stop_line_pos)
{
	if(start_line_pos >= stop_line_pos || stop_line_pos > lines.size())
	{
		return false;
	}

	lines.erase(lines.begin() + start_line_pos, lines.begin() + stop_line_pos);
	return true;
}

TextObject::TextObject(std::istream& in)
{
	std::string line;

	while (std::getline(in, line))
	{
		if (!line.empty())
		{
			lines.push_back(line);
		}
	}
}

const std::vector<std::string>& TextObject::GetLines() const noexcept
{
	return lines;
}