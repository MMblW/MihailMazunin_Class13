#pragma once
#include "Pair.h"
#include <iostream>
#include <queue>
#include <random>
#include <numeric>

using namespace std;

class PrioCondition {
public:
	bool operator()(Pair a, Pair b) {
		return a > b;
	}
};

Pair RandomPair() {
	int a = rand() % 10;
	double b = rand() % 1000 * 0.01;
	Pair newPair;
	newPair.SetFirst(a);
	newPair.SetSecond(b);
	return newPair;
}

void ShowQ(priority_queue<Pair, vector<Pair>, PrioCondition> Queue)
{
	while (!Queue.empty()) { cout << " > " << Queue.top(); Queue.pop(); }
}

void MidValue(priority_queue<Pair, vector<Pair>, PrioCondition> Queue, Pair& TempPair)
{
	Pair p = Queue.top();
	
	while (!Queue.empty())
	{
		p = Queue.top();
		Queue.pop();
		TempPair += p;
	}
}

void Remove(priority_queue<Pair, vector<Pair>, PrioCondition>& Queue, int LW, int HG)
{
	priority_queue<Pair, vector<Pair>, PrioCondition> TempQueue;
	while (!Queue.empty())
	{
		Pair p = Queue.top();
		if (!(p.getFirst() + p.getSecond() > LW && p.getFirst() + p.getSecond() < HG))
		{
			TempQueue.push(p);
		}
		Queue.pop();
	}
	Queue = TempQueue;
}

bool SearchByKey(priority_queue<Pair, vector<Pair>, PrioCondition> Queue, int key, Pair& TempPair)
{
	while (!Queue.empty())
	{
		Pair p = Queue.top();
		Queue.pop();
		if (p.getFirst() == key)
		{
			TempPair = p;
			return true;
		}
	}
	return false;
}

void AddValue(priority_queue<Pair, vector<Pair>, PrioCondition> Queue, Pair& TempPair)
{
	Pair p = Queue.top();
	int maxIntVal = p.getFirst(), minIntVal = p.getFirst();
	double maxDoubleVal = p.getSecond(), minDoubleVal = p.getSecond();

	while (!Queue.empty())
	{
		p = Queue.top();
		Queue.pop();
		if (p.getFirst() > maxIntVal) maxIntVal = p.getFirst();
		if (p.getFirst() < minIntVal) minIntVal = p.getFirst();
		if (p.getSecond() > maxIntVal) maxDoubleVal = p.getSecond();
		if (p.getSecond() < minIntVal) minDoubleVal = p.getSecond();
	}

	TempPair.SetFirst(minIntVal + maxIntVal);
	TempPair.SetSecond(minDoubleVal + maxDoubleVal);
}

void AddAddValue(priority_queue<Pair, vector<Pair>, PrioCondition>& Queue, Pair TempPair)
{
	priority_queue<Pair, vector<Pair>, PrioCondition> TempQueue;
	while (!Queue.empty())
	{
		Pair p = Queue.top();
		TempQueue.push(p + TempPair);
		Queue.pop();
	}
	Queue = TempQueue;
}

void DoSecondTask()
{
	int size;
	cout << "Выполнение первого задания..." << endl;
	cout << "Введите размер списка: ";
	do {
		cin >> size;
	} while (size < 1);
	priority_queue<Pair, vector<Pair>, PrioCondition> Queue_One;
	for (int i = 0; i < size; i++) { Queue_One.push(RandomPair()); }
	cout << endl << endl << "Очередь сгенерирована: ";
	ShowQ(Queue_One);
	Pair TempPair(0, 0);
	MidValue(Queue_One, TempPair);
	TempPair.SetFirst(TempPair.getFirst() / size);
	TempPair.SetSecond(TempPair.getSecond() / size);
	Queue_One.push(TempPair);
	cout << endl << endl << "Добавление ср. арифм. в конец очереди: ";
	ShowQ(Queue_One);
	double LW, HG;
	cout << endl << endl << "Введите границы удаления: ";
	cout << endl << "Нижняя граница: ";
	cin >> LW;
	cout << endl << "Верхняя граница: ";
	cin >> HG;
	Remove(Queue_One, LW, HG);
	ShowQ(Queue_One);
	int K;
	cout << endl << endl << "Введите ключ для поиска: ";
	cin >> K;
	if (SearchByKey(Queue_One, K, TempPair)) { cout << endl << "Пара найдена: " << TempPair << endl; }
	else { cout << endl << "Пара не найдена."; }
	AddValue(Queue_One, TempPair);
	cout << endl << endl << "Сумма минимального и максимального значений списка: " << TempPair;
	cout << endl << endl << "Добавление к каждому элементу списка этой суммы: ";
	AddAddValue(Queue_One, TempPair);
	ShowQ(Queue_One);
}