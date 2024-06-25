#include <string>
#include "Creator.h"
#include "BankAccountSystem.h"
#include "Parser.h"

namespace 
{
	const std::string start_accountancy_name = "Start";
}

static Date CreateDate(const BuyDetail& in_detail)
{
	if (!in_detail.getDay().empty() && !in_detail.getMonth().empty() && !in_detail.getYear().empty())
	{
		return { std::stoi(in_detail.getDay()), std::stoi(in_detail.getMonth()), std::stoi(in_detail.getYear()) };
	}

	return {};
}

static Buy CreateBuy(const BuyDetail& in_detail, const CountName& count_name, const bool check_transition)
{
	const Date date = CreateDate(in_detail);
	const double sum_temp = std::stod(in_detail.getSum());

	if (check_transition == true)
	{
		Buy temp_buy = Buy(-sum_temp, count_name, date);
		return temp_buy;
	}
	Buy temp_buy = Buy(sum_temp, count_name, date);

	return temp_buy;
}

BankAccountSystem CreateBase(std::istream& fin)
{
	std::vector<CountName> counts;
	BankAccountSystem base;
	std::string parsing_string;

	while (std::getline(fin, parsing_string))
	{
		BuyDetail buy_detail = BuyDetailParser(parsing_string);

		if (buy_detail.getCountName() == start_accountancy_name)
		{
			counts.emplace_back(buy_detail.getTransitionName());
			Buy buy = CreateBuy(buy_detail, counts.back(), false);
			base.add_buy(buy);
			continue;
		}

		if (buy_detail.getDay().empty())
		{
			continue;
		}

		CountName first{ buy_detail.getCountName() };
		CountName second{ buy_detail.getTransitionName() };

		bool check_transition = true;

		if (std::ranges::find(counts, first) != counts.end())
		{
			Buy buy = CreateBuy(buy_detail, first, check_transition);
			base.add_buy(buy);
		}

		if (std::ranges::find(counts, second) != counts.end())
		{
			check_transition = false;
			Buy buy = CreateBuy(buy_detail, second, check_transition);
			base.add_buy(buy);
		}
	}

	return base;
}