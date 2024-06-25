#pragma once
#include <compare>

class Date final
{
	int year;
	int month;
	int day;
public:
	Date();
	Date(int day_,int month_,int year_);
	static bool IsLeapYear(int year) noexcept;

	[[nodiscard]] int getMonth() const noexcept;
	[[nodiscard]] int getDay() const noexcept;
	[[nodiscard]] int getYear() const noexcept;

	[[nodiscard]]auto operator<=>(const Date& rdate) const noexcept = default;

	[[nodiscard]]bool operator==(const Date& rdate) const noexcept = default;
};