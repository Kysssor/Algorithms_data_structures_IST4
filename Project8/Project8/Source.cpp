#include <iostream>
#include <process.h>
#include <windows.h>

using namespace std;
int main()

{
	int *array, n, temp;
	setlocale(LC_ALL, "Rus");

input:
	cout << "������� ���������� ��������� ������� (������ �����): " << endl;

	cin >> n;	//������ ���������� ���������
	if (n % 2 != 0)	//�������� �� ������ �����
		goto input;
	array = new int[n];	//�������� ������ ��� ����� ������
	cout << "������� �������� �������: " << endl;	//��������� ������
	for (int i = 0; i < n; i++)
	{
		cout << "[" << i << "]=";
		cin >> array[i];

	}
	//��������� ������ ����� �������, ��� a*c+b*d - ��������
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

	cout << "���� ����� � ������������ ������ ������������" << endl; for (int i = 0; i < n; i += 2)
		cout << array[i] << "	" << array[i + 1] << endl;

	cout << "���� ����� � ����������� ������ ������������" << endl; for (int i = 0; i < n / 2; i++)
		cout << array[i] << "	" << array[n - 1 - i] << endl;

	system("pause");
	return 0;
}
