#pragma once

class Period final
{
	Date start;
	Date end;
public:
	Period(const Date& first, const Date& second)
	{
		if (first > second)
		{
			throw std::invalid_argument("First date more than second");
		}
		start = first;
		end = second;
	}

	[[nodiscard]] bool CheckDateContains(const Date& date) const noexcept
	{
		return date > start && date < end;
	}

	[[nodiscard]] const Date& getStart() const noexcept
	{
		return start;
	}

	[[nodiscard]] const Date& getEnd() const noexcept
	{
		return end;
	}
};