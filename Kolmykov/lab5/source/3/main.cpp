#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <Windows.h>


struct Vertex {
	std::map<char, int> next;
	bool isLeaf = false;
	int prev;
	char prevChar;
	int suffix;
	std::map<char, int> go;
	int number;
	int deep;
	bool isNextJoker = false;
	char joker;
};


void createBor(std::vector<Vertex>& vertexArr, std::string str, std::set<char> noJokers);
int getSuffix(int curr, std::vector<Vertex>& vertexArr);
int go(int curr, char c, std::vector<Vertex>& vertexArr);
void findTempl(std::string& str, std::vector<Vertex>& vertexArr);
void printAuto(std::vector<Vertex>& vertexArr);


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string str;
	std::string templ;
	char noJoker;
	std::cin >> str >> templ >> noJoker;
	std::vector<Vertex> vertexArr;
	std::set<char> noJokers;
	noJokers.insert(noJoker);
	for (auto c : str) {
		if (noJokers.find(c) == noJokers.end()) {
			noJokers.insert(c);
		}
	}
	createBor(vertexArr, templ, noJokers);
	printAuto(vertexArr);
	findTempl(str, vertexArr);
	system("pause");
}


void createBor(std::vector<Vertex>& vertexArr, std::string str, std::set<char> noJokers) {
	std::cout << "Добавление в бор шаблона " << str << ":" << std::endl;
	Vertex root;
	root.prev = root.suffix = -1;
	vertexArr.push_back(root);
	int curr = 0;
	std::cout << "Текущая вершина - корень бора\n";
	for (size_t i = 0; i < str.length(); i++) {
		std::cout << "Рассматривается символ " << str[i] << std::endl;
		if (vertexArr[curr].next.find(str[i]) == vertexArr[curr].next.end()) {
			std::cout << "Ребра бора по этому символу из текущей вершины еще нет. Создана новая вершина и добавлена в словарь переходов\n";
			Vertex ver;
			ver.suffix = -1;
			ver.prev = curr;
			ver.prevChar = str[i];
			if (noJokers.find(str[i]) == noJokers.end()) {
				std::cout << "Данный переход может выполняться всегда, так как " << str[i] << "может являться джокером\n";
				vertexArr[curr].isNextJoker = true;
				vertexArr[curr].joker = str[i];
			}
			vertexArr.push_back(ver);
			vertexArr[curr].next[str[i]] = vertexArr.size() - 1;
		}
		curr = vertexArr[curr].next[str[i]];
		std::cout << "Совершен переход по символу " << str[i] << std::endl;
	}
	std::cout << "Текущая вершина - лист\n";
	vertexArr[curr].isLeaf = true;
	vertexArr[curr].deep = str.length();
}


int getSuffix(int curr, std::vector<Vertex>& vertexArr) {
	std::cout << "Определение вершины для перехода по суффиксной ссылке:\n";
	if (vertexArr[curr].suffix == -1) {
		std::cout << "Суффикс ссылка еще не определена\n";
		if (curr == 0 || vertexArr[curr].prev == 0) {
			std::cout << "Суффиксная ссылка из вершины = 0 (вершина - корень или предок вершины - корень)\n";
			vertexArr[curr].suffix = 0;
		}
		else {
			std::cout << "Поиск суффиксной ссылки путем попытки перехода по символу из вершины предка:\n";
			vertexArr[curr].suffix = go(getSuffix(vertexArr[curr].prev, vertexArr), vertexArr[curr].prevChar, vertexArr);
		}
	}
	std::cout << "Вершина для перехода определена\n";
	return vertexArr[curr].suffix;
}


int go(int curr, char c, std::vector<Vertex>& vertexArr) {
	if (vertexArr[curr].go.find(c) == vertexArr[curr].go.end()) {
		if (vertexArr[curr].isNextJoker) {
			return vertexArr[curr].next[vertexArr[curr].joker];
		}
		if (vertexArr[curr].next.find(c) != vertexArr[curr].next.end()) {
			vertexArr[curr].go[c] = vertexArr[curr].next[c];
		}
		else {
			vertexArr[curr].go[c] = curr == 0 ? 0 : go(getSuffix(curr, vertexArr), c, vertexArr);
		}
	}
	return vertexArr[curr].go[c];
}


void findTempl(std::string& str, std::vector<Vertex>& vertexArr) {
	bool isFound = false;
	std::cout << "Прогон текста по автомату:\n";
	int curr = 0;
	std::cout << "Текущая вершина - корень бора\n";
	for (int i = 0; i < str.length(); i++) {
		std::cout << "Совершение перехода по символу " << str[i] << ":\n";
		curr = go(curr, str[i], vertexArr);
		if (vertexArr[curr].isLeaf) {
			std::cout << "Текущая вершина - лист, вхождение найдено\n";
			isFound = true;
			std::cout << i + 2 - vertexArr[curr].deep << std::endl;
		}
	}
	if (!isFound) {
		std::cout << "Вхождение не было найдено\n";
	}
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