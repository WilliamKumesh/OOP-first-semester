#pragma once
#include <ostream>
#include "Date.h"
#include "CountName.h"

class Count final
{
private:
	float start_sum_;
	CountName count_name_;
	Date date_creation;
public:
	Count(float start_sum_, const CountName& name_count_, Date date) : start_sum_(start_sum_),
	count_name_(name_count_), date_creation(date)
	{
		if(count_name_.getName().empty())
		{
			throw std::invalid_argument("Count name is empty");
		}
	}

	Count(const std::string& name) : Count(0, name, Date{})
	{
		
	}

	[[nodiscard]] float start_sum() const noexcept;

	[[nodiscard]] const CountName& getName() const noexcept;

	[[nodiscard]] Date getDate() const noexcept;

	friend std::ostream& operator<<(std::ostream& os, const Count& count);
};