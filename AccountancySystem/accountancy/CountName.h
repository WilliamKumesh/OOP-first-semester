#pragma once
#include <string>

class CountName final
{
	std::string count_name;
public:
	CountName(std::string name_count) : count_name(std::move(name_count))
	{
	}

	[[nodiscard]] const std::string& getName() const noexcept
	{
		return count_name;
	} 

	[[nodiscard]] bool operator==(const CountName& str_right) const noexcept = default;
};