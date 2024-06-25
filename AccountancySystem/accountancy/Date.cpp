#include"Date.h"
#include <vector>
#include <string>
#include <stdexcept>


namespace 
{
	const std::vector<short int> day_in_months = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	bool check_date(int day, int month, int year)
	{
		if(month > 12 || month < 1 || day < 0 || year < 0)
		{
			return  false;
		}

		if(month == 2 && Date::IsLeapYear(year))
		{
			return day_in_months[1] + 1 >= day;
		}

		return day_in_months[month - 1] >= day;
	}
}

Date::Date(): year(0), month(1), day(0)
{}

Date::Date(int day_ = 0, int month_ = 1, int year_ = 0)
{
	if(year_ < 0)
	{
		throw std::out_of_range("Year out of range");
	}

	if(!check_date(day_, month_, year_))
	{
		throw std::out_of_range("Day or month out of range");
	}

	month = month_;
	day = day_;
	year = year_;
}

int Date::getMonth() const noexcept
{
	return month;
}

int Date::getDay() const noexcept
{
	return day;
}

int Date::getYear() const noexcept
{
	return year;
}

bool Date::IsLeapYear(int year) noexcept
{
	if ((year % 400) == 0)
	{
		return true;
	}

	if ((year % 100) == 0)
	{
		return false;
	}

	if ((year % 4) == 0)
	{
		return true;
	}

	return false;
}