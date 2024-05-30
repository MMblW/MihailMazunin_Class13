#pragma once
#include "Pair.h"
#include <iostream>
#include <map>
#include <random>
#include <numeric>

using namespace std;

Pair RandomPair() {
	int a = rand() % 10;
	double b = rand() % 1000 * 0.01;
	Pair newPair;
	newPair.SetFirst(a);
	newPair.SetSecond(b);
	return newPair;
}

void ShowIterator(pair<int, Pair> p)
{
	cout << "(" << p.first << ")" << " : " << p.second << " > ";
}

void ShowMap(map<int, Pair> Map)
{
	map<int, Pair>::const_iterator I = Map.begin();
	while (I != Map.end())
	{
		ShowIterator(*I++);
	}
}

void Remove(map<int, Pair>& Map, int LW, int HG)
{
	map<int, Pair>::iterator I = Map.begin();
	int tmp;
	while (I != Map.end())
	{
		tmp = I->first;
		if (!(tmp > LW && tmp < HG))
		{
			++I;
		} else {
			I = Map.erase(I);
		}
	}
}

void DoThirdTask()
{
	int size;
	cout << "Выполнение первого задания..." << endl;
	cout << "Введите размер списка: ";
	do {
		cin >> size;
	} while (size < 1);
	map<int, Pair> Map_One;
	for (int i = 0; i < size; i++)
	{
		Pair p = RandomPair();
		Map_One[p.getFirst()] = p;
	}
	cout << endl << endl << "Словарь сгенерирован: ";
	ShowMap(Map_One);
	Pair TempPair(0, 0);
	for_each(Map_One.begin(), Map_One.end(), [&TempPair](pair<int, Pair> p) { TempPair = TempPair + p.second; });
	TempPair.SetFirst(TempPair.getFirst() / size);
	TempPair.SetSecond(TempPair.getSecond() / size);
	Map_One[TempPair.getFirst()] = TempPair;
	cout << endl << endl << "Добавление ср. арифм. в конец очереди: ";
	ShowMap(Map_One);
	double LW, HG;
	cout << endl << endl << "Введите границы удаления: ";
	cout << endl << "Нижняя граница: ";
	cin >> LW;
	cout << endl << "Верхняя граница: ";
	cin >> HG;
	Remove(Map_One, LW, HG);
	ShowMap(Map_One);
	int K;
	cout << endl << endl << "Введите ключ для поиска: ";
	cin >> K;
	auto tmp = find_if(Map_One.begin(), Map_One.end(), [K](pair<int, Pair> p) { return K == p.first; });
	if(tmp != Map_One.end())
	{
		cout << endl << "Пара найдена: " << tmp->second << endl;
	} else {
		cout << endl << "Пара не найдена.";
	}
	int MXF = Map_One.begin()->second.getFirst();
	int MNF = Map_One.begin()->second.getFirst();
	double MXS = Map_One.begin()->second.getSecond();
	double MNS = Map_One.begin()->second.getSecond();
	for_each(Map_One.begin(), Map_One.end(), [&MXF, &MNF, &MXS, &MNS](pair<int, Pair> p)
	{
		if (p.second.getFirst() > MXF) MXF = p.second.getFirst();
		if (p.second.getFirst() < MNF) MNF = p.second.getFirst();
		if (p.second.getSecond() > MXF) MXS = p.second.getSecond();
		if (p.second.getSecond() < MNF) MNS = p.second.getSecond();
	});
	TempPair.SetFirst(MNF + MXF);
	TempPair.SetSecond(MNS + MXS);
	cout << endl << endl << "Сумма минимального и максимального значений списка: " << TempPair;
	cout << endl << endl << "Добавление к каждому элементу списка этой суммы: ";
	for_each(Map_One.begin(), Map_One.end(), [&Map_One, TempPair](pair<int, Pair> p) {Map_One[p.first] = p.second + TempPair; });
	ShowMap(Map_One);
}