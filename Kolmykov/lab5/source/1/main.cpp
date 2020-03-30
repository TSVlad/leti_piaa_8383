#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <Windows.h>


struct Result {
	int pos;
	int number;
};


struct Vertex {
	std::map<char, int> next;
	bool isLeaf = false;
	int prev;
	char prevChar;
	int suffix;
	std::map<char, int> go;
	int number;
	int deep;
};


void createBor(std::vector<Vertex>& vertexArr, int count);
int getSuffix(int curr,  std::vector<Vertex>& vertexArr);
int go(int curr, char c, std::vector<Vertex>& vertexArr);
void findTempl(std::string& str, std::vector<Vertex>& vertexArr, std::vector<Result>& res);
bool comp(Result res1, Result res2);
void printAuto(std::vector<Vertex>& vertexArr);


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string str;
	int templCount;
	std::cin >> str;
	std::cin >> templCount;
	std::vector<Vertex> vertexArr;
	createBor(vertexArr, templCount);
	printAuto(vertexArr);
	std::vector<Result> res;
	findTempl(str, vertexArr, res);
	printAuto(vertexArr);
	sort(res.begin(), res.end(), comp);
	if (res.size() == 0) {
		std::cout << "Вхождения не найдены\n";
	}
	for (auto result : res) {
		std::cout << result.pos << " " << result.number << std::endl;
	}
	system("pause");
}


void createBor(std::vector<Vertex>& vertexArr, int count) {//Создание бора
	Vertex root;
	root.prev = root.suffix = -1;
	vertexArr.push_back(root);
	for (int j = 1; j <= count; j++) { // Для каждого шаблона
		std::string str;
		std::cin >> str;
		std::cout << "Добавление в бор шаблона " << str << ":" << std::endl;
		std::cout << "Текущая вершина - корень бора\n";
		int curr = 0; //Изначально текущая вершина - корень
		for (size_t i = 0; i < str.length(); i++) {//Для всех символов шаблона
			std::cout << "Рассматривается символ " << str[i] << std::endl;
			if (vertexArr[curr].next.find(str[i]) == vertexArr[curr].next.end()) { //Если из текущей вершины нет ребра с текущим символом, добавляются новые вершина и ребро
				std::cout << "Ребра бора по этому символу из текущей вершины еще нет. Создана новая вершина и добавлена в словарь переходов\n";
				Vertex ver;
				ver.suffix = -1;
				ver.prev = curr;
				ver.prevChar = str[i];
				vertexArr.push_back(ver);
				vertexArr[curr].next[str[i]] = vertexArr.size() - 1;
			}
			curr = vertexArr[curr].next[str[i]]; //Текущая вершина - вершина, доступная по ребру с текущим символом
			std::cout << "Совершен переход по символу " << str[i] << std::endl;
		}
		std::cout << "Текущая вершина - лист\n";
		vertexArr[curr].number = j; //Последняя добавленная при обработке шаблона вершина - лист. На будущее запоминается глубина и номер шаблона, которому этот лист принадлежит
		vertexArr[curr].isLeaf = true;
		vertexArr[curr].deep = str.length();
	}
}


int getSuffix(int curr, std::vector<Vertex>& vertexArr) {
	std::cout << "Определение вершины для перехода по суффиксной ссылке:\n";
	if (vertexArr[curr].suffix == -1) { //Если суффикс ссылка еще не определена
		std::cout << "Суффикс ссылка еще не определена\n";
		if (curr == 0 || vertexArr[curr].prev == 0) { //Вершина начальная или предок вершины - начальная, суффиксная ссылка ведена на начальную
			std::cout << "Суффиксная ссылка из вершины = 0 (вершина - корень или предок вершины - корень)\n";
			vertexArr[curr].suffix = 0;
		}
		else {
			std::cout << "Поиск суффиксной ссылки путем попытки перехода по символу из вершины предка:\n";
			vertexArr[curr].suffix = go(getSuffix(vertexArr[curr].prev, vertexArr), vertexArr[curr].prevChar, vertexArr); //Иначе суффиксная ссылка ведет в переход из вершины, полученной по суффиксная ссылке предка, по prev-символу
		}
	}
	std::cout << "Вершина для перехода определена\n";
	return vertexArr[curr].suffix;
}


int go(int curr, char c, std::vector<Vertex>& vertexArr) {
	if (vertexArr[curr].go.find(c) == vertexArr[curr].go.end()) { //Если в словаре переходов нет текущего символа
		std::cout << "В словаре переходов пока нет перехода по символу " << c << std::endl;
		if (vertexArr[curr].next.find(c) != vertexArr[curr].next.end()) { //Если символ есть в словаре ребер бора, добавляем переход по ребру
			std::cout << "Существует ребро бора с символом " << c << ". Этот переход добавляется в словарь переходов\n";
			vertexArr[curr].go[c] = vertexArr[curr].next[c];
		}
		else {
			std::cout << "Не существует ребра бора с символом " << c << ". Попытка совершения перехода из вершины, доступной по суффиксной ссылке\n";
			vertexArr[curr].go[c] = curr == 0 ? 0 : go(getSuffix(curr, vertexArr), c, vertexArr); //Иначе переход по суфикс ссылке
		}
	}
	std::cout << "Совершается переход по символу " << c << std::endl;
	return vertexArr[curr].go[c];
}


void findTempl(std::string& str, std::vector<Vertex>& vertexArr, std::vector<Result>& res) { //Функция поиска вхождений шаблонов в строку
	std::cout << "Прогон текста по автомату:\n";
	int curr = 0; //Текущая вершина - корень бора
	std::cout << "Текущая вершина - корень бора\n";
	for (int i = 0; i < str.length(); i++) {//Для каждого символа в строке
		std::cout << "Совершение перехода по символу " << str[i] << ":\n";
		curr = go(curr, str[i], vertexArr); //Переход из текущей вершины по текущему символу
		std::cout << "Проверка на вхождение:\n";
		for (int tmp = curr; tmp != 0; tmp = getSuffix(tmp, vertexArr)) { // Обход автомата по суффикс ссылкам 
			if (vertexArr[tmp].isLeaf) { //Если при обходе встретился лист, вхождение строки найдено
				std::cout << "Проверяемая вершина - лист. Вхождение найдено\n";
				Result result;
				result.number = vertexArr[tmp].number;
				result.pos = i + 2 - vertexArr[tmp].deep;
				res.push_back(result);
			}
		}
	}
}


bool comp(Result res1, Result res2) {
	if (res1.pos != res2.pos) {
		return res1.pos < res2.pos;
	}
	return res1.number < res2.number;
}


void printAuto(std::vector<Vertex>& vertexArr) {
	std::cout << "______________________________________\n";
	for (int i = 0; i < vertexArr.size(); i++) {
		Vertex curr = vertexArr[i];
		std::cout << "Номер вершины " << i << ":\n";
		if (curr.isLeaf) {
			std::cout << "Вершина - лист по шаблону номер " << curr.number << std::endl;
		}
		if (curr.prev != -1) {
			std::cout << "Номер вершины предка " << curr.prev << ", символ предка " << curr.prevChar << "\n";
		}
		if (curr.suffix != -1) {
			std::cout << "Номер вершины, доступной по суффиксной ссылке " << curr.suffix << std::endl;
		}
		if (!curr.isLeaf) {
			std::cout << "Ребра бора, доступные из вершины:\n";
			for (auto v : curr.next) {
				std::cout << "Ребро " << v.first << ", номер вершины " << v.second << std::endl;
			}
		}
		std::cout << "Переходы, доступные из вершины:\n";
		for (auto v : curr.go) {
			std::cout << "Символ " << v.first << ", номер вершины " << v.second << std::endl;
		}

	}
	std::cout << "______________________________________\n";
}