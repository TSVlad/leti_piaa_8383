#include <iostream>
#include <string>
#include <Windows.h>


void checkCyclicShift(std::string& firstStr, std::string& secondStr);//������� ���������� ������
int* makePrefix(char* str, int size);//������� ���������� ������� �������


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string firstStr;
	std::string secondStr;
	std::cin >> firstStr;
	std::cin >> secondStr;
	checkCyclicShift(firstStr, secondStr);
	std::cout << std::endl;
	system("pause");
}


void checkCyclicShift(std::string& firstStr, std::string& secondStr) {
	if (firstStr.length() != secondStr.length()) {//���� ������� ����� ������ - �������
		std::cout << "������� ����� ������ - �������\n";
		std::cout << -1;
		return;
	}
	else if (firstStr == secondStr) {//���� ������ ����� - ����� ����� 0
		std::cout << "������ ����� - �������\n";
		std::cout << 0;
		return;
	}
	int size = firstStr.size();
	char* buff = new char[size * 3];//��������� ������ �������� � 3 �������� ������, ������� ����������� ������ ������� � ����� �������
	int i = 0;
	for (; i < size; ++i) {
		buff[i] = secondStr[i];
	}
	for (int k = 0; k < 2; ++k) {
		for (int j = 0; j < size; ++j) {
			buff[i++] = firstStr[j];
		}
	}
	std::cout << "������� ������, ��������� �� ������ ������ � ���� ������:\n";
	for (int i = 0; i < size * 3; i++) {
		std::cout << buff[i];
	}
	std::cout << std::endl;

	int* prefixArr = makePrefix(buff, size * 3);//��� ������� ����������� ������� �������
	for (int i = 2 * size - 2; i < 3 * size; i++) {
		if (prefixArr[i] == size) {
			std::cout << "� ������� � ������ ��� ������� " << i << " (" << buff[i] << ") ������� ������� ����� ����� ����������� ������ " << size << std::endl;
			std::cout << "���������:\n" << i + 1 - 2 * size;
			delete[] buff;
			delete[] prefixArr;
			return;
		}
	}
	std::cout << "�� ���� ������� ������� � ������ ��������� ������� �������\n���������:\n";
	std::cout << -1;
	delete[] buff;
	delete[] prefixArr;
}


int* makePrefix(char* templ, int size) {
	std::cout << "���������� ������� �������:\n";
	int* prefix = new int[size];
	prefix[0] = 0;
	int j = 0; 
	int i = 1;
	std::cout << "������� ������� ��� ������� ������� ����� 0, ������ ������ ����� 1, ������ ������ ����� 0\n";
	while (i < size) {// ���� �� ������ ���� �����
		if (templ[i] == templ[j]) {//���� ������� ���������
			std::cout << "������� � ��������� " << i << " � " << j << " ��������� (" << templ[i] << "). ��� ������� �������������.\n";
			prefix[i] = j + 1;//������� ��� ������� �� ���� ������, ��� ������� �� �����������
			std::cout << "�������� ������� ������� ��� ������� " << templ[i] << " ����� " << prefix[i] << "\n";
			i++;
			j++;
		}
		else if (j == 0) {//���� �� �������� � ������ � ������� ��� 0
			std::cout << "������� � ��������� " << i << " � " << j << " �� ��������� (" << templ[i] << " � " << templ[j] << "). ����� ������ �������������\n";
			prefix[i] = 0;//������� ��� ������� ����� 0
			std::cout << "�������� ������� ������� ��� ������� " << templ[i] << " ����� 0\n";
			i++;
		}
		else {//���� ������ � ������� �� 0
			j = prefix[j - 1];//������ � ������� ����� ������� ������� �� ����������� �������
			std::cout << "������� � ��������� " << i << " � " << j << " �� ��������� (" << templ[i] << " � " << templ[j] << "). ������ ������ ���������� ������ �������� ������� ������� ����������� ������� (" << j << ")\n";
		}
	}

	std::cout << "�������� ������� �������:\n";
	for (int i = 0; i < size; i++) {
		std::cout << i << "\t" << templ[i] << "\t" << prefix[i] << std::endl;
	}
	return prefix;
}