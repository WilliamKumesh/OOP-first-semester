#pragma once
#include <iomanip>

class PrintHistogram final
{
public:
	static void print(std::ostream& out, const Histogram& histogram)
	{
		const auto num_of_partition = static_cast<double>(histogram.getBinCount());
		const auto partition = (histogram.getMax() - histogram.getMin()) / num_of_partition;
		for (size_t i = 0; i < histogram.getBinCount(); i++)
		{
			out << " Count of value : " << histogram[i] << ' ' << "Partition: " << histogram.getMin() + i * partition << std::setw(12) << std::endl;
		}
		out << std::endl;
	}
};
