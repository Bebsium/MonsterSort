#include "header.h"

DataList::DataList() {
	head = NULL;
	tail = NULL;
	length = 0;
}

void DataList::Insert(string name, int* data) {
	DataNode* n = new DataNode();
	n->name = name;
	n->hp = data[0];
	n->mp = data[1];
	n->spd = data[2];
	n->atk = data[3];
	n->def = data[4];
	n->exp = data[5];
	n->gold = data[6];
	n->next = NULL;

	if (length == 0) {
		head = tail = n;
	}
	else {
		tail->next = n;
		tail = n;
	}
	length++;
}

string* DataList::Out() {
	string* temp = new string[length];
	DataNode* data = head;
	for (int i = 0; i < length; i++)
	{
		temp[i] = data->name;
		data = data->next;
	}
	return temp;
}

int* DataList::Out(int t) {
	int* temp = new int[length];
	DataNode* data = head;
	for (int i = 0; i < length; i++)
	{
		switch (t)
		{
		case 1:
			temp[i] = data->hp; break;
		case 2:
			temp[i] = data->mp; break;
		case 3:
			temp[i] = data->spd; break;
		case 4:
			temp[i] = data->atk; break;
		case 5:
			temp[i] = data->def; break;
		case 6:
			temp[i] = data->exp; break;
		case 7:
			temp[i] = data->gold; break;
		}
		data = data->next;
	}
	return temp;
}

const void DataList::Print(int pos) {
	if (pos < length) {
		DataNode* data = head;
		int index = 0;
		while (index < pos)
		{
			data = data->next;
			index++;
		}
		cout << right << setw(20)
			<< data->name << "::\t" << data->hp << "\t"
			<< data->mp << "\t" << data->spd << "\t"
			<< data->atk << "\t" << data->def << "\t"
			<< data->exp << "\t" << data->gold << endl;
	}
}

MonsterData::MonsterData(string file) {
	isRun = true;

	cout.imbue(locale("Japanese"));
	cin.imbue(locale("Japanese"));
	ifstream ifs(file);
	if (!ifs) {
		cout << "ファイル読み込みエラー" << endl;
	}
	string line = "";
	string name = "";
	int* data = new int[7]{ 0 };
	getline(ifs, line);
	while (getline(ifs, line)) {
		string tmp = "";
		istringstream stream(line);
		int n = 0;
		while (getline(stream, tmp, ',')) {
			if (n == 0) {
				name = tmp;
				n++;
			}
			else {
				data[n - 1] = atoi(tmp.c_str());
				n++;
			}
		}
		dataList.Insert(name, data);
	}
}

void MonsterData::Print() {
	cout << right << setw(4) << "";
	cout << right << setw(20) << "モンスター名" << "::\tHP\tMP\t素速さ\t攻撃力\t守備力\t経験値\tゴールド" << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < dataList.Length(); i++) {
		cout << right << setw(4) << i + 1;
		dataList.Print(i);
	}
	cout << endl;
}

void MonsterData::Print(int* o) {
	cout << right << setw(4) << "";
	cout << right << setw(20) << "モンスター名" << "::\tHP\tMP\t素速さ\t攻撃力\t守備力\t経験値\tゴールド" << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < dataList.Length(); i++) {
		cout << right << setw(4) << i + 1;
		dataList.Print(o[i]);
	}
	cout << endl;
}

void MonsterData::Run() {
	while (isRun) {
		int t = Input();
		while (t == 0)
			t = Input();
		if (t == 9) {
			isRun = false;
			break;
		}
		int o = Order();
		while (o == 0)
			o = Order();
		int* ids = NULL;
		if (t == 1) {
			ids = Sort(o);
		}
		else {
			ids = Sort(o, t);
		}
		Print(ids);
	}
}

int MonsterData::Input() {
	cout << ">>>>>>>>>データのソートを行います<<<<<<<<" << endl;
	cout << "1)モンスター名順 2)HP値 3)MP順 4)素早さ 5)攻撃力順 6)守備力順 7)経験値順 8)ゴールド順 9)ソート終わり" << endl;
	cout << "並べ替える要素の番号を選んでください-->";
	int key;
	cin >> key;
	key = key > 0 && key < 10 ? key : 0;
	return key;
}

int MonsterData::Order() {
	cout << "1)大きい順番 2)小さい順番" << endl;
	cout << "昇順が降順が番号を選んでください-->";
	int key;
	cin >> key;
	key = key == 1 || key == 2 ? key : 0;
	return key;
}

int* MonsterData::Sort(int o) {
	string* data = dataList.Out();
	return Bubble(o, data);
}

int* MonsterData::Sort(int o, int t) {
	int* data = dataList.Out(t - 1);
	return Bubble(o, data);
}

template<typename T>
int* MonsterData::Bubble(int o, T* data) {
	int length = dataList.Length();
	int* re = new int[length];
	for (int i = 0; i < length; i++) {
		re[i] = i;
	}

	for (int i = 0; i < length - 1; i++) {
		for (int j = length - 1; j > i; j--) {
			if (o == 1) {//昇順
				if (data[j - 1] > data[j]) {
					T temp = data[j];
					data[j] = data[j - 1];
					data[j - 1] = temp;

					int tempr = re[j];
					re[j] = re[j - 1];
					re[j - 1] = tempr;
				}
			}
			else {//降順
				if (data[j - 1] < data[j]) {
					T temp = data[j];
					data[j] = data[j - 1];
					data[j - 1] = temp;

					int tempr = re[j];
					re[j] = re[j - 1];
					re[j - 1] = tempr;
				}
			}
		}
	}
	return re;
}