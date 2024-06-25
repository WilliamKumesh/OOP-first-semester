#pragma once
#include <string>

class BuyDetail final
{
private:
	std::string day;
	std::string month;
	std::string year;
	std::string count_name;
	std::string transition_count_name;
	std::string sum;
public:
	BuyDetail(std::string day_, std::string month_, std::string year, std::string count_name, std::string transiton_count_name_,
	std::string sum_) : day(std::move(day_)), month(std::move(month_)), year(std::move(year)),
	count_name(std::move(count_name)), transition_count_name(std::move(transiton_count_name_)), sum(std::move(sum_))
	{

	}

	[[nodiscard]] const std::string& getDay() const
	{
		return day;
	}

	[[nodiscard]] const std::string& getMonth() const
	{
		return month;
	}

	[[nodiscard]] const std::string& getYear() const
	{
		return year;
	}

	[[nodiscard]] const std::string& getCountName() const
	{
		return count_name;
	}

	[[nodiscard]] const std::string& getTransitionName() const
	{
		return transition_count_name;
	}

	[[nodiscard]] const std::string& getSum() const
	{
		return  sum;
	}
};