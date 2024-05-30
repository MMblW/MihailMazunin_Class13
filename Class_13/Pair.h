#pragma once
#include <iostream>
using namespace std;

class Pair {
private:
	int first;
	double second;
public:
	void SetFirst(int x);
	void SetSecond(double y);
	int getFirst();
	double getSecond();
	double getSum();
	void print();
	Pair() {}
	Pair(int f, double s) {
		SetFirst(f);
		SetSecond(s);
	}
	Pair(const Pair& p) {
		this->first = p.first;
		this->second = p.second;
	}
	~Pair() {}
	//перегруженные операции 
	Pair operator+(const int& x) const {
		return Pair(this->first + x, this->second);
	}
	Pair operator+(Pair x) const {
		return Pair(this->first + x.first, this->second + x.second);
	}
	Pair operator+(const double& y) const {
		return Pair(this->first, this->second + y);
	}
	Pair operator-(const Pair& p) const {
		return Pair(this->first - p.first, this->second - p.second);
	}
	friend Pair operator+(const int& x, const Pair& p) {
		return p + x;
	}
	Pair& operator+=(Pair pair)
	{
		first += pair.first;
		second += pair.second;
		return *this;
	}
	Pair& operator*=(Pair& pair) 
	{
		first *= pair.first;
		second *= pair.second;
		return *this;
	}
	Pair& operator/=(Pair& pair)
	{
		first /= pair.first;
		second /= pair.second;
		return *this;
	}
	Pair& operator/=(int n)
	{
		first /= n;
		second /= n;
		return *this;
	}
	bool operator> (const Pair& p) {
		if (this->first > p.first && this->second > p.second ||
			this->first + this->second > p.first + p.second ||
			this->first > p.first + p.second ||
			this->second > p.first + p.second) {
			return true;
		}
		return false;
	}
	bool operator< (const Pair& p)
	{
		if (this->first < p.first && this->second < p.second ||
			p.first + p.second > this->first + this->second ||
			p.first > this->first + this->second ||
			p.second > this->first + this->second) {
			return true;
		}
		return false;
	}
	friend Pair operator+(const double& y, const Pair& p) {
		return p + y;
	}
	friend ostream& operator<<(ostream& str, Pair& p) {
		str << p.first << " : " << p.second;
		return str;
	}
	friend istream& operator>>(istream& stream, Pair& p) {
		cout << "Первое число: " << p.first << endl;
		stream >> p.first;
		cout << "Второе число: " << p.second << endl;
		stream >> p.second;
		return stream;
	}
};


int Pair::getFirst() { return this->first; }
void Pair::SetFirst(int x) { this->first = x; }
double Pair::getSecond() { return this->second; }
double Pair::getSum() { return this->first + this->second;  }
void Pair::SetSecond(double y) { this->second = y; }
void Pair::print() { cout << this->first << " : " << this->second << endl; }
