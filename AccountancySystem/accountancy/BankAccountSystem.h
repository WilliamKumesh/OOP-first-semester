#pragma once
#include <unordered_map>
#include "Count.h"
#include "Buy.h"
#include <set>
#include "Money.h"
#include "Period.h"
#include "Date.h"

class BankAccountSystem final
{
	class HashCount final
	{
	public:
		size_t operator()(const CountName& key) const noexcept
		{
			return std::hash<std::string>{}(key.getName());
		}
	};

	class BuyCompareByDate final
	{
	public:
		bool operator()(const Buy& left, const Buy& right) const noexcept
		{
			return left.DateCompareLarger(right);
		}
	};

	std::unordered_map<CountName, std::multiset<Buy, BuyCompareByDate>, HashCount> buys_for_count;
	static Money TakeIn(const std::multiset<Buy, BuyCompareByDate>& buys, const Period& period, const int addition_type) noexcept;
public:
	void add_buy(const Buy& buy);
	[[nodiscard]] Money CurrentSum(const CountName& count_name) const noexcept;
	[[nodiscard]] Money InResidueSum(const CountName& count_name, const Period& period) const noexcept;
	[[nodiscard]] Money OutResidueSum(const CountName& count_name, const Period& period) const noexcept;
	[[nodiscard]] Money AdditionSum(const CountName& count_name, const Period& period) const noexcept;
	[[nodiscard]] Money ConsumptionSum(const CountName& count_name, const Period& period) const noexcept;
	[[nodiscard]] size_t getNumCounts() const noexcept 
	{
		return buys_for_count.size();
	}
};
