#include <iostream>
#include <process.h>
#include <windows.h>

using namespace std;
int main()

{
	int *array, n, temp;
	setlocale(LC_ALL, "Rus");

input:
	cout << "Введите количество элементов массива (четное число): " << endl;

	cin >> n;	//Вводим количество элементов
	if (n % 2 != 0)	//Проверка на четное число
		goto input;
	array = new int[n];	//Выделяем память под новый массив
	cout << "Введите элементы массива: " << endl;	//Заполняем массив
	for (int i = 0; i < n; i++)
	{
		cout << "[" << i << "]=";
		cin >> array[i];

	}
	//Сортируем массив таким образом, что a*c+b*d - максимум
	for (int i = 0; i < n; i++)

	{
		for (int j = n - 1; j >= i + 1; j--)
			if (array[j] < array[j - 1])

			{
				temp = array[j];
				array[j] = array[j - 1];

				array[j - 1] = temp;
			}

	}

	cout << "Пары чисел с максимальной суммой произведения" << endl; for (int i = 0; i < n; i += 2)
		cout << array[i] << "	" << array[i + 1] << endl;

	cout << "Пары чисел с минимальной суммой произведения" << endl; for (int i = 0; i < n / 2; i++)
		cout << array[i] << "	" << array[n - 1 - i] << endl;

	system("pause");
	return 0;
}
