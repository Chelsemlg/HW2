#define _CRT_SECURE_NO_WARNINGS
#define DEBUG 0
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#pragma warning(disable : 4996)

int void main() {
	system("chcp 1251"); // добавляем поддержку русской раскладки
	system("cls"); // очищаем консоль
	char current;  // текущий введенный символ
	int k = 1; // счётчик для выделения памяти
	int i, j, n, p, length = 0; // остальные счетчики, n - количество узлов, length - количество рёбер
	int pos=0;
	int e = 0;
    bool r = true;
	int sum = 1;
	//		Ввод динамической матрицы
	printf("Введите количество вершин n: ");
	scanf("%d", &n);
    
	int* a = (int*)malloc(n * n * sizeof(int*));
	current = getchar();
	for (i = 0; i < n; i++) {
		printf("%d  : ", i+1);
		current = getchar();
		for (j = 0; current != '\n'; j++) {
			if ((current == '1') || (current == '0')) {
                a[i * n + k - 1] = (int)current - '0';
				++k;
			}
			current = getchar();
		}
		current = '\0';
		length = k - 1;
		k = 1;
	}
	printf("\n\n");
	//Вывод  в консоль
	printf("\n\n   ");
	for (j = 1; j <= n; j++) {
		printf("%2d", j);
	}
	printf("\n");
	for (j = 1; j <= ((3 * length) + 2); j++) {
		printf("-");
	}
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("%i| ", (i + 1));
		for (j = 0; j < length; j++) {
			printf("%2d", a[i * n + j]);
		}
		printf("\n");
	}
	//			Работа с dot файлом			//
	FILE* file = fopen("./graph.gv", "w+b"); // Создание файла .gv для записи и сохранения графика
	fputs("graph MySecondHomeWork {\n", file); // 
	for (i = 0;i < n; i++)
		for (j = i; j < n; j++)
			if (a[i * n + j] == 1) // Если мы вводим в матрицу единицы
				fprintf(file, "\t%d -- %d;\n", i + 1, j + 1); // Записываем ссылку в созданный файл						
	fputs("}", file); // Конец ввода
	fclose(file); 
	system("dot -Tpng graph.gv -o graph.png"); // Создание графической визуализации
	//			Проверка		//
	p = pos;
	bool* ch = (bool*)calloc(n, sizeof(bool)); // Создаем индекс для проверки
	for (i = 0; i < n - 1; ++i) {
		ch[p] = true; // Отмечаем верхнюю часть строки
		for (j = 0; j < n; ++j) { // Цикл строки
			if ((ch[j] == false) && (a[i * n + j] == 1)) {
				p = j;
				break;
			}
		}
		if (j == n) //Если j правильная длина, либо количества точек
			r = false; 
	}
	if (a[p * n + pos] == 0)
		r = false;
	for (i = 0; i < n; ++i) {
		for (j = i; j < n; ++j)
			if (a[i * n + j] == 1)
				++e;
	}
	if (e != n) // Если е не равно количеству вершин
		r = false; 
	free(ch);
	if (r == true) // Если r истина, то это цикл
		printf("Воооу, да это цикл");
	else
		printf("Нееее, не цикл");
		// Очистка памяти //
	free(a);
	getchar();
	return 0;
}
