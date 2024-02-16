/*
3.1. Что в имени твоем?
В алфавите племени мумба-юмба только три буквы, которые обозначаются как A, B и D. Юношам в день совершеннолетия принято давать взрослые имена, состоящие 
ровно из N букв (1 ≤ N ≤ 35). Повторение букв в имени не ограничивается. Если юноша не может представить вождю скальп врага, то в имени присутствует подстрока
BAD (возможно, в нескольких экземплярах), иначе такие имена категорически запрещаются. Сколько разных имен может быть в племени мумба-юмба для юношей, запоздавших 
в развитии (не представивших скальп)?
Ввод из файла INPUT.TXT. Единственная строка содержит целое положительное число N.
Вывод  в файл OUTPUT.TXT. Выводится единственное число - количество имен длины N,  содержащих подстроку BAD.
Пример
Ввод
8
Вывод
1404

Среда разработки: Visual Studio 2022
*/

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <iostream>
using namespace std;

long long NumberOfName(int lenghtName)
{
	if (lenghtName < 3)
	{
		return 0;
	}
	vector<long long> variantsWithSymbolB;
	variantsWithSymbolB.push_back(1);
	variantsWithSymbolB.push_back(3);
	variantsWithSymbolB.push_back(9);
	long long allVariants = 3;
	long long allNeedVariants = 9;
	allVariants = pow(3, lenghtName);

	for (int i = 2; i < lenghtName; i++)
	{
		allNeedVariants = allNeedVariants * 3 - variantsWithSymbolB[0];
		variantsWithSymbolB.erase(variantsWithSymbolB.begin());
		variantsWithSymbolB.push_back(allNeedVariants);
	}
	return allVariants - allNeedVariants;
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n;
	in >> n;
	out << NumberOfName(n);
	return 0;
}