#include "histogram.hpp"
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <set>

static bool is_equal(double x, double y) {
	return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

Histogram::Histogram(const std::vector<double>& in_vec, size_t bin_count):bins(bin_count,0)
{
	if(bin_count == 0)
	{
		throw std::invalid_argument("Bin count can't be zero");
	}

	if(in_vec.empty())
	{
		throw std::invalid_argument("Empty input");
	}

	const auto min_max = std::minmax_element(in_vec.begin(), in_vec.end());
	_min = *min_max.first;
	_max = *min_max.second;

	for(const auto it: in_vec)
	{
		add(it);
	}
}

std::vector<size_t>::const_iterator Histogram::begin() const noexcept
{
	return bins.begin();
}

std::vector<size_t>::const_iterator Histogram::end() const noexcept
{
	return bins.end();
}

Histogram Histogram::operator+(const Histogram& right) const
{
	CheckEqualsMainParameters(right);

	Histogram new_histogram{ *this };

	std::transform(right.begin(), right.end(), bins.begin(), 
		new_histogram.bins.begin(), std::plus<size_t>());

	return new_histogram;
}

Histogram Histogram::operator-(const Histogram& right) const
{
	CheckEqualsMainParameters(right);

	Histogram new_histogram{ *this };

	std::transform(right.begin(), right.end(), bins.begin(),
		new_histogram.bins.begin(), [](size_t first, size_t second) 
		-> size_t { return first > second ? 0 : second - first; });

	return new_histogram;
}

size_t Histogram::operator[] (size_t index) const
{
	if(index > getBinCount())
	{
		throw std::out_of_range("Index out of range");
	}

	return bins[index];
}

double Histogram::getMin() const noexcept
{
	return _min;
}

double Histogram::getMax() const noexcept
{
	return _max;
}

size_t Histogram::getBinCount() const noexcept
{
	return bins.size();
}

void Histogram::add(double num)
{
	const auto new_num = std::clamp(num, _min, _max);

	const auto num_of_partition = static_cast<double>(bins.size());
	const auto partition = (_max - _min) / num_of_partition;

	const auto index = static_cast<size_t>((new_num - _min) / partition);

	const auto find_it = std::clamp(index, static_cast < size_t>(0), bins.size()-1);

	bins[find_it]++;
}

void Histogram::CheckEqualsMainParameters(const Histogram& right) const
{
	if(is_equal(_min, right._min) && is_equal(_max, right._max) && 
		bins.size() == right.bins.size())
	{
		return;
	}

	throw std::invalid_argument("Main parameters are different");
}