#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <ctime>

using namespace std;
char tmp_map[254][254];

char answer;


#pragma region Map
char map[254][254] = {
					  "+#############################+",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "|                             |",
					  "+#############################+"
};

#pragma endregion
char(&ShowMap())[254][254]{
	// В теории сделано для 254*254, но консоль такие размеры не выдерживает
	/*for (int i = 0; i < 254; i++) {
		for (int j = 0; j < 254; j++) {
			map[i][j] = ' ';
		}
}*/
//Ввод координат препятствий
int mk, md;
cout << "Введите координаты препятствия (сначала х, потом y)\n";
back: {
		cout << "Координата Х = ";
		cin >> mk;
		cout << "Координата Y = ";
		cin >> md;
		cout << "Хотите добавить ещё координаты препятствия?(y/n)";
		cin >> answer;
		if (answer == 'y') {
			map[mk][md] = '#';
			goto back;
			 }

		else {
			goto next;
		}
		}
	next:
	  system("cls");
	  //Вывод карты на экран
	for (int gen_x = 0; gen_x < 254; gen_x++) {
		printf("%s\n", map[gen_x]);
	}
	return map;
}
//Прорисовка пути по точкам
void gotoxy(short x, short y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };

	SetConsoleCursorPosition(hStdout, position);
}

class entity {
public:
	entity(int x, int y) {
		this->x = x;
		this->y = y;
	}
private:
	int x;
	int y;
};

struct walk {
	short walk_count;
	short x;
	short y;
	short back;
};

struct target {
	short x;
	short y;
};

vector<target> walk_queue;

vector<walk> BFSArray;
//Проверка на препятствия и прочее
void AddArray(int x, int y, int wc, int back) {

	if (tmp_map[y][x] == ' ' || tmp_map[y][x] == '.') {
		tmp_map[y][x] = '#';
		walk tmp;
		tmp.x = x;
		tmp.y = y;
		tmp.walk_count = wc;
		tmp.back = back;
		BFSArray.push_back(tmp);
	}

}
// Нахождение пути к цели

void FindPath(int sx, int sy, int x, int y) {
	clock_t time;
	time = clock();
	memcpy(tmp_map, map, sizeof(map));
	BFSArray.clear();
	walk tmp;
	tmp.x = sx;
	tmp.y = sy;
	tmp.walk_count = 0;
	tmp.back = -1;
	BFSArray.push_back(tmp);


	int i = 0;
	while (i < BFSArray.size()) {
		//Достижение цели
		if (BFSArray[i].x == x && BFSArray[i].y == y) {
			walk_queue.clear();
			target tmp2;
			while (BFSArray[i].walk_count != 0) {
				tmp2.x = BFSArray[i].x;
				tmp2.y = BFSArray[i].y;
				walk_queue.push_back(tmp2);

				i = BFSArray[i].back;
			}

			break;
		}

		AddArray(BFSArray[i].x + 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
		AddArray(BFSArray[i].x - 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
		AddArray(BFSArray[i].x, BFSArray[i].y + 1, BFSArray[i].walk_count + 1, i);
		AddArray(BFSArray[i].x, BFSArray[i].y - 1, BFSArray[i].walk_count + 1, i);


		i++;
	}
	time = clock() - time;
	BFSArray.clear();
	printf("  Нужная точка достигнута, за:%f", (double)time / CLOCKS_PER_SEC);
}


int main()
{
	setlocale(LC_ALL, "Russian");
	bool running = true;
	int x;
	int y;
	
	int old_x;
	int old_y;

	int ex;
	int ey;

	cout << "Введите координаты начала\n";
	cout << "Координата Х = ";
	cin >> ex;
	cout << "Координата Y = ";
	cin >> ey;
	cout << "Введите координаты конца\n";
	cout << "Координата Х = ";
	cin >> x;
	cout << "Координата Y = ";
	cin >> y;

	system("cls");
	ShowMap();

	gotoxy(x, y); cout << "X";

	int frame = 0;

	FindPath(ex, ey, x, y);
	//Визуализация пути
	while (running) {
		gotoxy(x, y); cout << " ";

		old_x = x;
		old_y = y;

		if (old_x != x || old_y != y) {
			FindPath(ex, ey, x, y);
		}

		gotoxy(x, y); cout << "X";

		map[ey][ex] = '.';
		gotoxy(ex, ey); cout << ".";

		if (walk_queue.size() != 0) {
			ex = walk_queue.back().x;
			ey = walk_queue.back().y;
			walk_queue.pop_back();
		}

		gotoxy(ex, ey); cout << "S";
		if (ex == x && ey == y) {
			break;
		}


		gotoxy(32, 18);
		gotoxy(32, 1);
		Sleep(100);
		frame++;
	}

	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	return 0;
}