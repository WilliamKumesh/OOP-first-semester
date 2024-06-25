#pragma once
#include"Date.h"
#include"CountName.h"

class Buy final
{
	double sum;
	CountName count_name;
	Date date;
public:
	Buy(double sum_, CountName count_name_, const Date& date_) : sum(sum_), count_name(std::move(count_name_)), date(date_)
	{
		if(count_name.getName().empty())
		{
			throw std::invalid_argument("Empty name");
		}
	}

	[[nodiscard]] double getSum() const noexcept
	{
		return sum;
	}
	[[nodiscard]] const CountName& getName() const noexcept
	{
		return count_name;
	}
	[[nodiscard]] const Date& getDate() const noexcept
	{
		return date;
	}

	[[nodiscard]]bool DateCompareLarger(const Buy& right) const noexcept
	{
		return date > right.date;
	}
};
