#include <string>
#include <vector>
#include "parser.h"
#include "BuyDetail.h"

namespace
{
	const std::string date_delimeter_1 = ".";
	const std::string date_delimeter_2 = "-";
	constexpr short int string_year_length = 4, string_day_length = 2;

	const std::string count_delimeter = " ";

	constexpr short int details_size = 3;
	constexpr short int all_details_size = 6;
	enum details {count_name, transition_name, sum};
	enum date_details { day, month, year };
}

static std::vector<std::string> DateParser(std::string& input_str)
{
	std::vector<std::string> date;

	size_t pos;

	if (input_str.find(date_delimeter_1) != std::string::npos && input_str.find(date_delimeter_1) <= string_day_length)
	{
		while ((pos = input_str.find(date_delimeter_1)) != std::string::npos)
		{
			date.push_back(input_str.substr(0, pos));
			input_str.erase(0, pos + date_delimeter_1.length());
		}
		date.push_back(input_str.substr(0, string_year_length));
		input_str.erase(0, pos + string_year_length + 2);
	}

	if (input_str.find(date_delimeter_2) != std::string::npos && input_str.find(date_delimeter_2) <= string_year_length)
	{
		while ((pos = input_str.find(date_delimeter_2)) != std::string::npos)
		{
			date.push_back(input_str.substr(0, pos));
			input_str.erase(0, pos + date_delimeter_2.length());
		}
		date.push_back(input_str.substr(0, string_day_length));
		input_str.erase(0, pos + string_day_length + 2);

		std::reverse(date.begin(), date.end());
	}

	return date;
}

static std::vector<std::string> MainDetailParser(std::string& input_str)
{
	std::vector<std::string> details;

	for (int i = 0; i < details_size; i++)
	{
		const size_t pos = input_str.find(count_delimeter);

		if (pos != std::string::npos)
		{
			details.push_back(input_str.substr(0, pos));
			input_str.erase(0, pos + count_delimeter.length());
		}
	}

	return details;
}

BuyDetail BuyDetailParser(std::string input_str)
{
	std::vector<std::string> date = DateParser(input_str);

	std::vector<std::string> main_details = MainDetailParser(input_str);

	if (date.size() + main_details.size() == all_details_size)
	{
		return { date[day], date[month], date[year],
			main_details[count_name], main_details[transition_name], main_details[sum]};
	}
	date.clear();
	return { "", "", "", "", "", ""};
}