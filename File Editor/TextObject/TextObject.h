#pragma once
#include <string>
#include <vector>
#include <fstream>

class TextObject final
{
	std::vector<std::string> lines;
public:
	TextObject(std::istream& in);

	bool TryDeleteLines(size_t start_line_pos, size_t stop_line_pos);
	bool TryAddLines(size_t start_line_pos, const std::vector<std::string>& add_lines);

	[[nodiscard]] const std::vector<std::string>& GetLines() const noexcept;

	void WriteToStream(std::ostream& out_stream) const noexcept
	{
		for(const auto& it: lines)
		{
			out_stream << it << std::endl;
		}
	}
};