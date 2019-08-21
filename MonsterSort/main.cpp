#include "header.h"

int main() {
	cout << "5B-10-姜宇祥" << endl;

	MonsterData monster = MonsterData("mns_data.csv");
	monster.Print();
	monster.Run();

	return 0;
}
