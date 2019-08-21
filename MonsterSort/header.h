#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct DataNode {
	DataNode* next;
	string name;
	int hp;
	int mp;
	int spd;
	int atk;
	int def;
	int exp;
	int gold;
};

class DataList {

public:
	DataList();
	void Insert(string, int*);
	string* Out();
	int* Out(int);
	const void Print(int);
	const int Length() { return length; }
private:
	DataNode *head, *tail;
	int length;
};

class MonsterData {
public:
	MonsterData(string);
	void Print();
	void Print(int*);
	void Run();

private:
	int Input();
	int Order();
	int* Sort(int);		//name sort
	int* Sort(int, int);	//other sort
	template<typename T>
	int* Bubble(int, T*);

private:
	DataList dataList;
	bool isRun;
};
