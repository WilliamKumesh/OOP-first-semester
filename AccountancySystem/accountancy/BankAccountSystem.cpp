#include "BankAccountSystem.h"
#include <utility>

namespace 
{
	enum addition{plus, minus, all_sum, before_period};
}

void BankAccountSystem::add_buy(const Buy& buy)
{
	const auto& it_name = buys_for_count.find(buy.getName());

	if(it_name != buys_for_count.end())
	{
		it_name->second.insert(buy);
	}
	else
	{
		std::multiset<Buy, BuyCompareByDate> buys;
		buys.insert(buy);
		buys_for_count.insert(std::make_pair(buy.getName(), buys));
	}
}

Money BankAccountSystem::CurrentSum(const CountName& count_name) const noexcept
{
	const auto it_count = buys_for_count.find(count_name);

	if(it_count == buys_for_count.end())
	{
		return { 0 };
	}

	const auto& buys = it_count->second;

	const Period period{ buys.rbegin()->getDate(), (--buys.rend())->getDate() };

	return TakeIn(buys, period, all_sum);
}

Money BankAccountSystem::TakeIn(const std::multiset<Buy, BuyCompareByDate>& buys, const Period& period, const int addition_type) noexcept
{
 	double positive_sum = 0;
	double negative_sum = 0;
	double sum_before_period = 0;

	for (auto it = buys.rbegin(); it != buys.rend(); ++it)
	{
		if (period.CheckDateContains(it->getDate()))
		{
			if(it->getSum() < 0)
			{
				negative_sum += it->getSum();
				continue;
			}
			positive_sum += it->getSum();
		}
		else
		{
			sum_before_period += it->getSum();

			if(period.CheckDateContains(it->getDate()))
			{
				break;
			}
		}
	}

	if(addition_type == before_period)
	{
		return { sum_before_period };
	}

	if (addition_type == plus)
	{
		return { positive_sum };
	}

	if(addition_type == minus)
	{
		return { negative_sum };
	}

	return { positive_sum + negative_sum };
}

Money BankAccountSystem::InResidueSum(const CountName& count_name, const Period& period) const noexcept
{
	const auto& it_count = buys_for_count.find(count_name);

	if (it_count == buys_for_count.end())
	{
		return { 0 };
	}

	const auto& buys = it_count->second;

	return TakeIn(buys, period, before_period);
}

Money BankAccountSystem::OutResidueSum(const CountName& count_name, const Period& period) const noexcept
{
	return AdditionSum(count_name, period) + InResidueSum(count_name, period) + ConsumptionSum(count_name, period);
}

Money BankAccountSystem::AdditionSum(const CountName& count_name, const Period& period) const noexcept
{
	const auto& it_count = buys_for_count.find(count_name);

	if (it_count == buys_for_count.end())
	{
		return { plus };
	}

	const auto& buys = it_count->second;

	return TakeIn(buys, period, plus);
}

Money BankAccountSystem::ConsumptionSum(const CountName& count_name, const Period& period) const noexcept
{
	const auto& it_count = buys_for_count.find(count_name);

	if (it_count == buys_for_count.end())
	{
		return { 0 };
	}

	const auto& buys = it_count->second;

	return TakeIn(buys, period, minus);
}