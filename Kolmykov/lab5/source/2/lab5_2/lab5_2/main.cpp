#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
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
};


void createBor(std::vector<Vertex>& vertexArr, std::string str, char joker);
int getSuffix(int curr, std::vector<Vertex>& vertexArr, char joker);
int go(int curr, char c, std::vector<Vertex>& vertexArr, char joker);
void findTempl(std::string& str, std::vector<Vertex>& vertexArr, char joker);
void printAuto(std::vector<Vertex>& vertexArr);


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string str;
	std::string templ;
	char joker;
	std::cin >> str >> templ >> joker;
	std::vector<Vertex> vertexArr;
	createBor(vertexArr, templ, joker);
	printAuto(vertexArr);
	findTempl(str, vertexArr, joker);
	system("pause");
}


void createBor(std::vector<Vertex>& vertexArr, std::string str, char joker) {
	std::cout << "���������� � ��� ������� " << str << ":" << std::endl;
	Vertex root;
	root.prev = root.suffix = -1;
	vertexArr.push_back(root);
	int curr = 0;
	std::cout << "������� ������� - ������ ����\n";
	for (size_t i = 0; i < str.length(); i++) {
		std::cout << "��������������� ������ " << str[i] << std::endl;
		if (vertexArr[curr].next.find(str[i]) == vertexArr[curr].next.end()) {
			std::cout << "����� ���� �� ����� ������� �� ������� ������� ��� ���. ������� ����� ������� � ��������� � ������� ���������\n";
			Vertex ver;
			ver.suffix = -1;
			ver.prev = curr;
			ver.prevChar = str[i];
			if (str[i] == joker) {
				vertexArr[curr].isNextJoker = true;
			}
			vertexArr.push_back(ver);
			vertexArr[curr].next[str[i]] = vertexArr.size() - 1;
		}
		curr = vertexArr[curr].next[str[i]];
		std::cout << "�������� ������� �� ������� " << str[i] << std::endl;
	}
	std::cout << "������� ������� - ����\n";
	vertexArr[curr].isLeaf = true;
	vertexArr[curr].deep = str.length();
}


int getSuffix(int curr, std::vector<Vertex>& vertexArr, char joker) {
	std::cout << "����������� ������� ��� �������� �� ���������� ������:\n";
	if (vertexArr[curr].suffix == -1) {
		std::cout << "������� ������ ��� �� ����������\n";
		if (curr == 0 || vertexArr[curr].prev == 0) {
			std::cout << "���������� ������ �� ������� = 0 (������� - ������ ��� ������ ������� - ������)\n";
			vertexArr[curr].suffix = 0;
		}
		else {
			std::cout << "����� ���������� ������ ����� ������� �������� �� ������� �� ������� ������:\n";
			vertexArr[curr].suffix = go(getSuffix(vertexArr[curr].prev, vertexArr, joker), vertexArr[curr].prevChar, vertexArr, joker);
		}
	}
	std::cout << "������� ��� �������� ����������\n";
	return vertexArr[curr].suffix;
}


int go(int curr, char c, std::vector<Vertex>& vertexArr, char joker) {
	std::cout << "����������� ������� ��� ��������:\n";
	if (vertexArr[curr].go.find(c) == vertexArr[curr].go.end()) {
		std::cout << "������� ��� �������� ��� �� ���������� � ������� ���������\n";
		if (vertexArr[curr].isNextJoker) {
			std::cout << "�� ������� ���������� ������� �� ������� �������\n";
			std::cout << "������� ��� �������� ����������\n";
			return vertexArr[curr].next[joker];
		}
		if (vertexArr[curr].next.find(c) != vertexArr[curr].next.end()) {
			std::cout << "� ���� ���������� ������� �� ������� " << c << std::endl;
			vertexArr[curr].go[c] = vertexArr[curr].next[c];
		}
		else {
			std::cout << "����� �������� �� � ������� ���������� ������\n";
			vertexArr[curr].go[c] = curr == 0 ? 0 : go(getSuffix(curr, vertexArr, joker), c, vertexArr, joker);
		}
	}
	std::cout << "������� ��� �������� ����������\n";
	return vertexArr[curr].go[c];
}


void findTempl(std::string& str, std::vector<Vertex>& vertexArr, char joker) {
	bool isFound = false;
	std::cout << "������ ������ �� ��������:\n";
	int curr = 0;
	std::cout << "������� ������� - ������ ����\n";
	for (int i = 0; i < str.length(); i++) {
		std::cout << "���������� �������� �� ������� " << str[i] << ":\n";
		curr = go(curr, str[i], vertexArr, joker);
		if (vertexArr[curr].isLeaf) {
			std::cout << "������� ������� - ����, ��������� �������\n";
			std::cout << i + 2 - vertexArr[curr].deep << std::endl;
			isFound = true;
		}
	}
	if (!isFound) {
		std::cout << "��������� �� ���� �������\n";
	}
}


void printAuto(std::vector<Vertex>& vertexArr) {
	std::cout << "______________________________________\n";
	for (int i = 0; i < vertexArr.size(); i++) {
		Vertex curr = vertexArr[i];
		std::cout << "����� ������� " << i << ":\n";
		if (curr.isLeaf) {
			std::cout << "������� - ���� �� ������� ����� " << curr.number << std::endl;
		}
		if (curr.prev != -1) {
			std::cout << "����� ������� ������ " << curr.prev << ", ������ ������ " << curr.prevChar << "\n";
		}
		if (curr.suffix != -1) {
			std::cout << "����� �������, ��������� �� ���������� ������ " << curr.suffix << std::endl;
		}
		if (!curr.isLeaf) {
			std::cout << "����� ����, ��������� �� �������:\n";
			for (auto v : curr.next) {
				std::cout << "����� " << v.first << ", ����� ������� " << v.second << std::endl;
			}
		}
		std::cout << "��������, ��������� �� �������:\n";
		for (auto v : curr.go) {
			std::cout << "������ " << v.first << ", ����� ������� " << v.second << std::endl;
		}

	}
	std::cout << "______________________________________\n";
}