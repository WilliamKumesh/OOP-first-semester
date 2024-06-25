#include <iostream>
#include "BankAccountSystem.h"
#include <fstream>
#include "Creator.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout << "Not enough arguments";
		return -1;
	}

	fstream file_in(argv[1]);

	const BankAccountSystem base = CreateBase(file_in);

	Date first(2, 3, 2013);
	Date second(4, 6, 2014);
	Date third(1, 7, 2016);

	Period period1(first, second);
	Period period2(first, third);
	CountName name("Карточка");

	cout << base.AdditionSum(name, period1).getSum() << endl;
	cout << base.ConsumptionSum(name, period1).getSum() << endl;
	cout << base.ConsumptionSum(name, period2).getSum();

	return 0;
}