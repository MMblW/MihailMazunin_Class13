#pragma once
#include "Pair.h"
#include <iostream>
#include <list>
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

void DoFirstTask()
{
	int size;
	cout << "Выполнение первого задания..." << endl;
	cout << "Введите размер списка: ";
	do {
		cin >> size;
	} while (size < 1);
	list<Pair> List_One(size);
	generate(List_One.begin(), List_One.end(), RandomPair);
	cout << endl << endl << "Список сгенерирован: ";
	for_each(List_One.begin(), List_One.end(), [](Pair& p) {cout << " > " << p; });
	Pair TempPair(0, 0);
	for_each(List_One.begin(), List_One.end(), [&TempPair](Pair& p) { TempPair += p; });
	TempPair.SetFirst(TempPair.getFirst() / size);
	TempPair.SetSecond(TempPair.getSecond() / size);
	List_One.push_back(TempPair);
	cout << endl << endl << "Добавление ср. арифм. в конец списка: ";
	for_each(List_One.begin(), List_One.end(), [](Pair& p) {cout << " > " << p; });
	double LW, HG;
	cout << endl << endl << "Введите границы удаления: ";
	cout << endl << "Нижняя граница: ";
	cin >> LW;
	cout << endl << "Верхняя граница: ";
	cin >> HG;
	list<Pair>::iterator iter = remove_if(List_One.begin(), List_One.end(), [LW, HG](Pair& p) {
			return p.getFirst() + p.getSecond() > LW && p.getFirst() + p.getSecond() < HG; });
	List_One.erase(iter, List_One.end());
	cout << endl << endl << "Элементы удалены";
	cout << endl << endl << "Отсортирванный по возрастанию список: ";
	List_One.sort();
	for_each(List_One.begin(), List_One.end(), [](Pair& p) {cout << " > " << p; });
	cout << endl << endl << "Отсортирванный по убыванию список: ";
	List_One.sort([](Pair& a, Pair& b) {return a.getSum() > b.getSum(); });
	for_each(List_One.begin(), List_One.end(), [](Pair& p) {cout << " > " << p; });
	int K;
	cout << endl << endl << "Введите ключ для поиска: ";
	cin >> K;
	auto Found = find_if(List_One.begin(), List_One.end(), [K](Pair& p) { return K == p.getFirst(); });
	if (Found != List_One.end()) { cout << endl << "Пара найдена: " << *Found << endl; }
	else { cout << endl << "Пара не найдена."; }
	Pair MX(0, 0);
	for_each(List_One.begin(), List_One.end(), [&MX](Pair& p) { if (p.getSum() > MX.getSum()) MX = p; });
	Pair MN(11, 11);
	for_each(List_One.begin(), List_One.end(), [&MN](Pair& p) { if (p.getSum() < MN.getSum()) MN = p; });
	Pair PairToAdd = MX + MN;
	cout << endl << endl << "Сумма минимального и максимального значений списка: " << PairToAdd;
	cout << endl << endl << "Добавление к каждому элементу списка этой суммы: ";
	for_each(List_One.begin(), List_One.end(), [PairToAdd](Pair& p) {
		p += PairToAdd;
		cout << " > " << p;
	});
}