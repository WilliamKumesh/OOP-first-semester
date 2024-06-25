#pragma once

class Money final
{
	double sum;

public:
	Money(double sum_) : sum(sum_) {}

	[[nodiscard]]Money operator+(const Money& right) const noexcept
	{
		return { sum + right.sum };
	}

	[[nodiscard]]Money operator-(const Money& right) const noexcept
	{
		return { sum - right.sum };
	}

	[[nodiscard]] Money operator/(const Money& right) const
	{
		if(std::abs(right.sum) < std::numeric_limits<double>::epsilon())
		{
			throw std::invalid_argument("Division by zero");
		}
		return { sum / right.sum };
	}

	[[nodiscard]] Money operator*(const Money& right) const noexcept
	{
		return { sum * right.sum };
	}

	[[nodiscard]]double getSum() const noexcept
	{
		return sum;
	}
};