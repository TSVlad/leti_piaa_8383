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
		std::cout << "��������� �� �������\n";
	}
	for (auto result : res) {
		std::cout << result.pos << " " << result.number << std::endl;
	}
	system("pause");
}


void createBor(std::vector<Vertex>& vertexArr, int count) {//�������� ����
	Vertex root;
	root.prev = root.suffix = -1;
	vertexArr.push_back(root);
	for (int j = 1; j <= count; j++) { // ��� ������� �������
		std::string str;
		std::cin >> str;
		std::cout << "���������� � ��� ������� " << str << ":" << std::endl;
		std::cout << "������� ������� - ������ ����\n";
		int curr = 0; //���������� ������� ������� - ������
		for (size_t i = 0; i < str.length(); i++) {//��� ���� �������� �������
			std::cout << "��������������� ������ " << str[i] << std::endl;
			if (vertexArr[curr].next.find(str[i]) == vertexArr[curr].next.end()) { //���� �� ������� ������� ��� ����� � ������� ��������, ����������� ����� ������� � �����
				std::cout << "����� ���� �� ����� ������� �� ������� ������� ��� ���. ������� ����� ������� � ��������� � ������� ���������\n";
				Vertex ver;
				ver.suffix = -1;
				ver.prev = curr;
				ver.prevChar = str[i];
				vertexArr.push_back(ver);
				vertexArr[curr].next[str[i]] = vertexArr.size() - 1;
			}
			curr = vertexArr[curr].next[str[i]]; //������� ������� - �������, ��������� �� ����� � ������� ��������
			std::cout << "�������� ������� �� ������� " << str[i] << std::endl;
		}
		std::cout << "������� ������� - ����\n";
		vertexArr[curr].number = j; //��������� ����������� ��� ��������� ������� ������� - ����. �� ������� ������������ ������� � ����� �������, �������� ���� ���� �����������
		vertexArr[curr].isLeaf = true;
		vertexArr[curr].deep = str.length();
	}
}


int getSuffix(int curr, std::vector<Vertex>& vertexArr) {
	std::cout << "����������� ������� ��� �������� �� ���������� ������:\n";
	if (vertexArr[curr].suffix == -1) { //���� ������� ������ ��� �� ����������
		std::cout << "������� ������ ��� �� ����������\n";
		if (curr == 0 || vertexArr[curr].prev == 0) { //������� ��������� ��� ������ ������� - ���������, ���������� ������ ������ �� ���������
			std::cout << "���������� ������ �� ������� = 0 (������� - ������ ��� ������ ������� - ������)\n";
			vertexArr[curr].suffix = 0;
		}
		else {
			std::cout << "����� ���������� ������ ����� ������� �������� �� ������� �� ������� ������:\n";
			vertexArr[curr].suffix = go(getSuffix(vertexArr[curr].prev, vertexArr), vertexArr[curr].prevChar, vertexArr); //����� ���������� ������ ����� � ������� �� �������, ���������� �� ���������� ������ ������, �� prev-�������
		}
	}
	std::cout << "������� ��� �������� ����������\n";
	return vertexArr[curr].suffix;
}


int go(int curr, char c, std::vector<Vertex>& vertexArr) {
	if (vertexArr[curr].go.find(c) == vertexArr[curr].go.end()) { //���� � ������� ��������� ��� �������� �������
		std::cout << "� ������� ��������� ���� ��� �������� �� ������� " << c << std::endl;
		if (vertexArr[curr].next.find(c) != vertexArr[curr].next.end()) { //���� ������ ���� � ������� ����� ����, ��������� ������� �� �����
			std::cout << "���������� ����� ���� � �������� " << c << ". ���� ������� ����������� � ������� ���������\n";
			vertexArr[curr].go[c] = vertexArr[curr].next[c];
		}
		else {
			std::cout << "�� ���������� ����� ���� � �������� " << c << ". ������� ���������� �������� �� �������, ��������� �� ���������� ������\n";
			vertexArr[curr].go[c] = curr == 0 ? 0 : go(getSuffix(curr, vertexArr), c, vertexArr); //����� ������� �� ������ ������
		}
	}
	std::cout << "����������� ������� �� ������� " << c << std::endl;
	return vertexArr[curr].go[c];
}


void findTempl(std::string& str, std::vector<Vertex>& vertexArr, std::vector<Result>& res) { //������� ������ ��������� �������� � ������
	std::cout << "������ ������ �� ��������:\n";
	int curr = 0; //������� ������� - ������ ����
	std::cout << "������� ������� - ������ ����\n";
	for (int i = 0; i < str.length(); i++) {//��� ������� ������� � ������
		std::cout << "���������� �������� �� ������� " << str[i] << ":\n";
		curr = go(curr, str[i], vertexArr); //������� �� ������� ������� �� �������� �������
		std::cout << "�������� �� ���������:\n";
		for (int tmp = curr; tmp != 0; tmp = getSuffix(tmp, vertexArr)) { // ����� �������� �� ������� ������� 
			if (vertexArr[tmp].isLeaf) { //���� ��� ������ ���������� ����, ��������� ������ �������
				std::cout << "����������� ������� - ����. ��������� �������\n";
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