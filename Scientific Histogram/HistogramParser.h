#pragma once
#include <stdexcept>
#include <string>
#include <vector>
#include <istream>

class ParsingHistogram final
{
public:
	static std::vector<double> parsing_histogram(std::istream& in)
	{
		std::vector<double> histogram;

		if (in.eof())
		{
			return histogram;
		}

		while (!in.eof() || in.peek() != '\n')
		{
			std::string element;

			in >> element;

			if (!element.empty())
			{
				try
				{
					histogram.push_back(stod(element));
				}
				catch (std::exception& e)
				{
					std::cout << "Invalid element: " << element << std::endl;
				}
			}
			else
			{
				break;
			}
		}
		return histogram;
	}
};