// lab4.2.22.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*По правилам пунктуации пробел может стоять после, а не перед
каждым из следующих знаков: . , ; : ! ? ) ] } ...;
перед, а не после знаков: ( [ {. Заданный текстовый файл
проверить на соблюдение этих правил и при необходимости
исправить.*/

#include <stdio.h>
#include <string>
const char pered[] = ".,;:!?)]}";
const char posle[] = "([{";
void my_erase(char A[], int size, int place)
{
	for (int i = place; i < size - 1; ++i)
	{

		A[i] = A[i + 1];
	}
	A[size - 1] = '\0';
	size--;
}
int main()
{
	FILE* in;
	char s[300];
	errno_t err;
	err = fopen_s(&in, "test.txt", "rt");
	if (!in) 
	{
		printf("Error: Can't open file\n");
	}
	fgets(s, 300, in);
	printf("begin\n%s", s);
	int size = strlen(s);
	int sizepe = strlen(pered);
	int sizepo = strlen(posle);
	for (int i = size; i > 0; i--)
	{
		for (int j = sizepe; j > -1; j--)
		{
			if (s[i] == ' ' && s[i + 1] == pered[j])
			{
				my_erase(s, size, i);
			}
		}
		for (int j = sizepo; j > -1; j--)
		{
			if (s[i] == ' ' && s[i - 1] == posle[j])
			{
				my_erase(s, size, i);
			}
		}
	}
	printf("\nresult\n%s", s);
	fclose(in);

}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
