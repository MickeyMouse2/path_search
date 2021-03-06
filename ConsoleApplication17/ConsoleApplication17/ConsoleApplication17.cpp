#include <iostream>
#include <queue>
#include <ctime>
using namespace std;

// нахождение пути
void find_path(int n, int row, int col, char** lab, int** visited, int** path, queue<int>& plan) {
	
		if (!visited[row][col]) {
			/* проверяем не вышли ли мы за границы лабиринта, есть ли клетка
			в массиве посещенных и можно ли через нее пройти*/
			if (lab[row + 1] != "#" && (row + 1) >= 0 && !visited[row + 1][col] &&
				(lab[row + 1][col] == ' ' || lab[row + 1][col] == 'X')) {
				path[row + 1][col] = path[row][col] + 1;
				plan.push(row + 1);
				plan.push(col);
			}
			if (lab[row - 1] != "#" && (row - 1) >= 0 && !visited[row - 1][col] &&
				(lab[row - 1][col] == ' ' || lab[row - 1][col] == 'X')) {
				path[row - 1][col] = path[row][col] + 1;
				plan.push(row - 1);
				plan.push(col);
			}
			if (lab[col + 1] != "#" && (col + 1) >= 0 && !visited[row][col + 1] &&
				(lab[row][col + 1] == ' ' || lab[row][col + 1] == 'X')) {
				path[row][col + 1] = path[row][col] + 1;
				plan.push(row);
				plan.push(col + 1);
			}
			if (lab[col - 1] != "#" && (col - 1) >= 0 && !visited[row][col - 1] &&
				(lab[row][col - 1] == ' ' || lab[row][col - 1] == 'X')) {
				path[row][col - 1] = path[row][col] + 1;
				plan.push(row);
				plan.push(col - 1);
			}
			visited[row][col] = 1; /* отмечаем клетку в которой побывали */
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
start:
	int n, x_start, y_start, x_end, y_end, x, y, x_obs, y_obs;
	char que;
	queue <int> plan;
	cout << "Введите координаты начала\n";
	cout << "X = ";
	cin >> x_start;
	cout << "Y = ";
	cin >> y_start;
	cout << "Введите координаты конца\n";
	cout << "X = ";
	cin >> x_end;
	cout << "Y = ";
	cin >> y_end;
	cout << "Введите размеры области\n";
	cin >> n;
	char** lab = new char*[n];
	int** visited = new int *[n];
	int** path = new int *[n];

	for (int i = 0; i<n; i++) {
		lab[i] = new char[n];   /* массив для хранения лабиринта */
		visited[i] = new int[n]; /* массив для хранения информации о посещении клеток*/
		path[i] = new int[n];  /* массив для хранения найденных путей */

		for (int j = 0; j<n; j++) {
			visited[i][j] = 0;
			path[i][j] = -1;
			lab[i][j] = ' ';
			/* находим начало пути*/
			if (i == 0 || i == n - 1 || j == 0 || j == n - 1 )
				lab[i][j] = '#';
			if (i == x_start && j == y_start) {
				lab[i][j] = '@';
				path[i][j] = 1;
				plan.push(i);
				plan.push(j);
			}
			else if (i == x_end && j == y_end) {
				lab[i][j] = 'X';
			}

		}
	}
back:
	cout << "Введите координаты препятствий\n";
	cout << "X = ";
	cin >> x_obs;
	cout << "Y = ";
	cin >> y_obs;
	lab[x_obs][y_obs] = '#';
	cout << "Хотите добавить ещё препятствий?(y/n)\n";
	cin >> que;
	if (que == 'y')
		goto back;
	system("cls");
	
	clock_t time;
	time = clock();
	 /* пока очередь посещения клеток непустая*/
	while (!plan.empty()) {
		x = plan.front();
		plan.pop();
		y = plan.front();
		plan.pop();
		find_path(n, x, y, lab, visited, path, plan); /* продолжаем поиск пути*/
	}
	time = clock() - time;
	printf("  Нужная точка достигнута, за:%f\n", (double)time / CLOCKS_PER_SEC);
	if (!visited[x_end][y_end]) {
		cout << "N" << endl;
	}
	else {
		cout << "Y" << endl;
		x = x_end;
		y = y_end;
		lab[x][y] = '+';
		while (path[x][y] != 2) { /* восстановление пути*/
			if ((x - 1) >= 0 && (x - 1) < n && (path[x - 1][y] == path[x][y] - 1)) {
				x = x - 1;
				lab[x][y] = '|';
			}
			else if ((x + 1) >= 0 && (x + 1) < n && (path[x + 1][y] == path[x][y] - 1)) {
				x = x + 1;
				lab[x][y] = '|';
			}
			else if ((y - 1) >= 0 && (y - 1) < n && (path[x][y - 1] == path[x][y] - 1)) {
				y = y - 1;
				lab[x][y] = '>';
			}
			else if ((y + 1) >= 0 && (y + 1) < n && (path[x][y + 1] == path[x][y] - 1)) {
				y = y + 1;
				lab[x][y] = '<';
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == x_end && j == y_end) {
					lab[i][j] = 'X';
				}
				cout << lab[i][j];
			}
			cout << endl;
		}
	}
	cout << "Хотите ввести другие значения?(y/n)";
	cin >> que;
	if (que == 'y') {
		system("cls");
		goto start;
	}
	return 0;
}
