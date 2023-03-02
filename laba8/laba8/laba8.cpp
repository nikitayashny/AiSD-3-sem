#include <iostream>
#include <algorithm>
#include <Windows.h>

using namespace std;

void result(int* backpack[], int weight[], int i, int j, int items[]);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int count;
	int maxWeight;

	cout << "Введите количество предметов: ";
	cin >> count;
	cout << "Введите вес рюкзака: ";
	cin >> maxWeight;
	
	int* weight = new int[count];
	int* price = new int[count];
	string* name = new string[count];

	cout << "Введите название, вес и стоимость предметов: " << endl;
	
	for (int i = 0; i < count; i++)
	{
		cin >> name[i] >> weight[i] >> price[i];
	}

	int** backpack;						// матрица оптимальных стоимостей [количество][вес рюкзака]
	backpack = new int* [count + 1];

	for (int i = 0; i < count + 1; i++)
	{
		backpack[i] = new int[maxWeight + 1];
	} 

	for (int i = 0; i <= count; i++)
	{ 
		for (int j = 0; j <= maxWeight; j++)
		{
			if (i == 0 || j == 0)
			{
				backpack[i][j] = 0;
			}
			else
			{
				if (j >= weight[i - 1])	// текущий размер рюкзака больше или равен размеру текущего предмета
				{
					backpack[i][j] = max(backpack[i - 1][j], backpack[i - 1][j - weight[i - 1]] + price[i - 1]);	// выбираем что больше (положить или не положить)
				}
				else
				{
					backpack[i][j] = backpack[i - 1][j];	// оставляем прошлую оптимальную стоимость
				}
			}
		}
	}
	
	int totalPrice = backpack[count][maxWeight];	// лучшая стоимость
	int* items = new int[count];

	result(backpack, weight, count, maxWeight, items);

	cout << endl << "В рюкзак положили:" << endl;

	for (int i = 0; i <= count; i++)
	{
		if (items[i] > 0)
		{
			cout << name[items[i] - 1] << " стоимтостью " << price[items[i] - 1] << endl;
		}
	}

	cout << endl << "Общая стоимость рюкзака: " << totalPrice << endl;

	system("pause");
}

void result(int* backpack[], int weight[], int i, int j, int items[])		
{							
	if (backpack[i][j] == 0)
	{
		return;
	}
	if (backpack[i - 1][j] == backpack[i][j])
	{
		result(backpack, weight, i - 1, j, items);
	}
	else
	{
		result(backpack, weight, i - 1, j - weight[i - 1], items);
		items[i] = i;
	}
}