#pragma once
#include <vector>
#include <stdexcept>

class Histogram final
{
	std::vector<size_t> bins;
	double _min;
	double _max;
	void CheckEqualsMainParameters(const Histogram& right) const;
public:
	Histogram(double min_, double max_, size_t bin_count_) :bins(bin_count_, 0), _min(min_), _max(max_)
	{
		if (bin_count_ == 0)
		{
			throw std::invalid_argument("Bin count can't be zero");
		}
		if(min_ > max_)
		{
			throw std::invalid_argument("Min more then max");
		}
	}
	Histogram(const std::vector<double>& in_vec, size_t bin_count);

	[[nodiscard]] size_t operator[] (size_t index) const;

	[[nodiscard]]Histogram operator+(const Histogram& right) const;
	[[nodiscard]]Histogram operator-(const Histogram& right) const;

	[[nodiscard]] bool operator==(const Histogram& right) const = default;

	[[nodiscard]] std::vector<size_t>::const_iterator begin() const noexcept;
	[[nodiscard]] std::vector<size_t>::const_iterator end() const noexcept;

	[[nodiscard]] double getMin() const noexcept;
	[[nodiscard]] double getMax() const noexcept;
	[[nodiscard]] size_t getBinCount() const noexcept;

	void add(double num);

	[[nodiscard]] bool SizeCompare(const Histogram& right) const noexcept
	{
		return right.getBinCount() == bins.size();
	}
};