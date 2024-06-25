#include "Count.h"
#include <iostream>

float Count::start_sum() const noexcept
{
	return start_sum_;
}

const CountName& Count::getName() const noexcept
{
	return count_name_;
}

Date Count::getDate() const noexcept
{
	return date_creation;
}

std::ostream& operator<<(std::ostream& os, const Count& count)
{
	os << "��� �����: " << count.count_name_.getName() << std::endl;
	os << "��������� ���������: " << count.start_sum_ << std::endl;
	os << "���� ��������: " << count.date_creation.getDay() << '.' << count.date_creation.getMonth() << '.'
	<< count.date_creation.getYear() << std::endl;

	return os;
}