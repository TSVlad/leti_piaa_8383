#include <iostream>
#include <string>
#include <Windows.h>


void checkCyclicShift(std::string& firstStr, std::string& secondStr);//Функция вычисления сдвига
int* makePrefix(char* str, int size);//Функция вычисления префикс функции


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
	if (firstStr.length() != secondStr.length()) {//Если размеры строк разные - возврат
		std::cout << "Размеры строк разные - возврат\n";
		std::cout << -1;
		return;
	}
	else if (firstStr == secondStr) {//Если строки равны - сдвиг равен 0
		std::cout << "Строки равны - возврат\n";
		std::cout << 0;
		return;
	}
	int size = firstStr.size();
	char* buff = new char[size * 3];//Создается буффер размером с 3 поданные строки, который заполняется второй строкой и двумя первыми
	int i = 0;
	for (; i < size; ++i) {
		buff[i] = secondStr[i];
	}
	for (int k = 0; k < 2; ++k) {
		for (int j = 0; j < size; ++j) {
			buff[i++] = firstStr[j];
		}
	}
	std::cout << "Создана строка, состоящая из второй строки и двух первых:\n";
	for (int i = 0; i < size * 3; i++) {
		std::cout << buff[i];
	}
	std::cout << std::endl;

	int* prefixArr = makePrefix(buff, size * 3);//Для буффера вычисляется префикс функция
	for (int i = 2 * size - 2; i < 3 * size; i++) {
		if (prefixArr[i] == size) {
			std::cout << "У символа в строке под номером " << i << " (" << buff[i] << ") префикс функция равна длине изначальной строки " << size << std::endl;
			std::cout << "Результат:\n" << i + 1 - 2 * size;
			delete[] buff;
			delete[] prefixArr;
			return;
		}
	}
	std::cout << "Не было найдено символа с нужным значением префикс функции\nРезультат:\n";
	std::cout << -1;
	delete[] buff;
	delete[] prefixArr;
}


int* makePrefix(char* templ, int size) {
	std::cout << "Вычисление префикс функции:\n";
	int* prefix = new int[size];
	prefix[0] = 0;
	int j = 0; 
	int i = 1;
	std::cout << "Префикс функция для первого символа равна 0, первый индекс равен 1, второй индекс равен 0\n";
	while (i < size) {// Пока не прошли весь образ
		if (templ[i] == templ[j]) {//Если символы совпадают
			std::cout << "Символы с индексами " << i << " и " << j << " совпадают (" << templ[i] << "). Оба индекса увеличиваются.\n";
			prefix[i] = j + 1;//функция для символа на один больше, чем функция от предыдущего
			std::cout << "Значение префикс функции для символа " << templ[i] << " равно " << prefix[i] << "\n";
			i++;
			j++;
		}
		else if (j == 0) {//Если не овпадают и индекс в массиве уже 0
			std::cout << "Символы с индексами " << i << " и " << j << " не совпадают (" << templ[i] << " и " << templ[j] << "). Первы индекс увеличивается\n";
			prefix[i] = 0;//Функция для символа равна 0
			std::cout << "Значение префикс функции для символа " << templ[i] << " равно 0\n";
			i++;
		}
		else {//Если индекс в массиве не 0
			j = prefix[j - 1];//Индекс в массиве равен префикс функции от предыдущего символа
			std::cout << "Символы с индексами " << i << " и " << j << " не совпадают (" << templ[i] << " и " << templ[j] << "). Второй индекс становится равным значению префикс функции предыдущего символа (" << j << ")\n";
		}
	}

	std::cout << "Значение префикс функции:\n";
	for (int i = 0; i < size; i++) {
		std::cout << i << "\t" << templ[i] << "\t" << prefix[i] << std::endl;
	}
	return prefix;
}