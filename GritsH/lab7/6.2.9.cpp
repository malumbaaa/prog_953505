// 6.2.9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

struct Hotel
{
	char city[20];
	char hotelName[20];
	char address[30];
	char roomClass[20];
	char amountOfFreeRooms[20];
	char roomCost[20];
};

void fillStruct(struct Hotel* hotels, int iter, const char* hotelsInfo, int stringSize);
void createStructArray(struct Hotel* hotels, int size, const char* fname);
int countStrings(const char* fname);
char* processRequest(char* str);
bool reserveRoom(struct Hotel* hotels, int hotelAmount, int index);

int main()
{
	const char* fname = "c:\\Users\\grits\\hotel.txt";
	char choice;
	char str[120];
	char searchRequest[100] = {};
	char searchAddress[20] = {};
	char searchRoom[20] = {};

	int amountOfHotels = countStrings(fname);
	int amountOfPeople = 0;
	int searchPrice = 0;
	int counter = 0;

	struct Hotel* hotels;
	hotels = (Hotel*)malloc(amountOfHotels * sizeof(Hotel));
	createStructArray(hotels, amountOfHotels, fname);
	printf_s("\n\nWelcom to the HotelTracer\nWe will find a suitable room for you\n ");
	printf_s("Press < s > to search for the hotel\nOr press < e > to exit : ");
	while (true)
	{
		scanf_s("%c", &choice);
		if (choice == 's')
		{
			break;
		}
		if (choice == 'e')
		{
			free(hotels);
			return 0;
		}
		else
		{
			printf_s("\nWe don't have this command, please try again\n");
			getchar();
			choice = NULL;
		}
	}
	system("cls");
	printf_s("\nPlease write your request like <Venice lux room for two 100>\n");
	printf_s("Input: ");
	getchar();
	gets_s(str);
	int x = 0;

	while (str[x] != -2)
	{
		x++;
		continue;
	}
	str[x] = '\0';
	strcat(searchRequest, processRequest(str));
	int i = 0;

	while (searchRequest[i] != '/')
	{
		i++;
	}
	strncpy(searchAddress, searchRequest, i);
	searchAddress[i] = '\0';

	for (int j = 0; j < strlen(searchRequest) - i + 1; j++)
	{
		searchRequest[j] = searchRequest[j + i + 1];
	}
	i = 0;

	while (searchRequest[i] != '/')
	{
		i++;
	}
	strncpy(searchRoom, searchRequest, i);
	searchRoom[i] = '\0';

	for (int j = 0; j < strlen(searchRequest) - i + 1; j++)
	{
		searchRequest[j] = searchRequest[j + i + 1];
	}
	i = 0;

	while (searchRequest[i] != '/')
	{
		amountOfPeople = amountOfPeople * 10 + (searchRequest[i] - 48);
		i++;
	}

	for (int j = 0; j < strlen(searchRequest) - i + 1; j++)
	{
		searchRequest[j] = searchRequest[j + i + 1];
	}
	i = 0;

	while (searchRequest[i] != '\0')
	{
		searchPrice = searchPrice * 10 + (searchRequest[i] - 48);
		i++;
	}

	for (int i = 0; i < amountOfHotels; i++)
	{
		int suitability = 0;
		bool flag = false;
		if (strcmp(hotels[i].city, searchAddress) == 0)
		{
			suitability++;
		}
		for (int j = 0; j < strlen(searchRoom); j++)
		{
			if (searchRoom[j] == '1' && strcmp(hotels[i].roomClass, "lux") == 0);
			{
				flag = true;
			}
			if (searchRoom[j] == '2' && strcmp(hotels[i].roomClass, "econom") == 0)
			{
				flag = true;
			}
			if (searchRoom[j] == '3' && strcmp(hotels[i].roomClass, "lux") == 0)
			{
				flag = true;
			}
			if (searchRoom[j] == '4' && strcmp(hotels[i].roomClass, "vip") == 0)
			{
				flag = true;
			}
		}

		int intCost = 0;
		for (int x = 0; x < strlen(hotels[i].roomCost); x++)
		{
			intCost = intCost * 10 + (hotels[i].roomCost[x] - 48);
		}

		int intFreeRoom = 0;
		for (int x = 0; x < strlen(hotels[i].amountOfFreeRooms); x++)
		{
			intFreeRoom = intFreeRoom * 10 + (hotels[i].amountOfFreeRooms[x] - 48);
		}
		if (flag)
		{
			suitability++;
		}
		if (amountOfPeople == intFreeRoom)
		{
			suitability++;
		}
		if (searchPrice >= intCost)
		{
			suitability++;
		}
		if (suitability == 4)
		{
			printf_s("\n\nAccording to our database your match is: \n[%d]\tHotel <%s> with \n\ttype of rooms <%s> for <%s> for one night,\n\tlocated at <%s, %s>\n", i, hotels[i].hotelName, hotels[i].roomClass, hotels[i].roomCost, hotels[i].city, hotels[i].address);
			counter++;
		}
	}
	if (counter == 0)
	{
		printf_s("\nSorry we didn't find any hotel for you\n");
		printf_s("thanks for choosing HotelTracer\n");
		free(hotels);
		return 0;
	}
	printf_s("\nWould you like to book any?\n1.Yes  2.No\nInput: ");
	choice = NULL;
	while (true)
	{
		scanf_s("%c", &choice);
		if (choice == '1')
		{
			break;
		}
		if (choice == '2')
		{
			free(hotels);
			return 0;
		}
		else
		{
			printf_s("\nWe don't have this command, please try again\n");
			getchar();
			choice = NULL;
		}
	}
	printf_s("\nPlease enter the index of the hotel u'd like to book\n");
	printf_s("*index is written in [ ]\nInput: ");
	int bookedIndex = 0;
	while (true)
	{
		scanf_s("%d", &bookedIndex);
		if (bookedIndex < 0)
		{
			free(hotels);
			return 0;
		}
		if (bookedIndex >= 0 && bookedIndex < amountOfHotels)
		{
			break;
		}
		else
		{
			printf_s("\nIndex doesn't exist, try again\n");
			printf_s("If you want to leave the programm enter -1: ");
			getchar();
			bookedIndex = NULL;
		}
	}
	if (reserveRoom(hotels, amountOfHotels, bookedIndex))
	{
		printf_s("Operation complete succsessfully!");
	}
	free(hotels);
	return 0;
}

char* processRequest(char* str)
{
	char lastWord[100];
	*lastWord = '\0';
	char prevWord[100];
	*prevWord = '\0';
	int j = 0;
	bool isAll = false;
	for (int i = 0; i < strlen(str); i++)
	{
		if (i == 0 || str[i] == ' ')
		{
			if (str[i] == ' ')
			{
				i++;
			}
			j = i;
			while (str[j] != ' ')
			{
				if (j == strlen(str))
				{
					break;
				}
				j++;
				continue;
			}
			if (j != strlen(str))
			{
				j--;
			}
			char word[60] = {};
			for (int k = i; k <= j; k++)
			{
				word[k - i] = str[k];
			}
			int k = 0;
			if (i == 0)
			{
				strcat(lastWord, word);
				strcat(lastWord, "/");
			}
			if (!strcmp(word, "room"))
			{
				if (strcmp(prevWord, "vip") == 0 || strcmp(prevWord, "VIP") == 0)
				{
					strcat(lastWord, "34/");
				}
				if (strcmp(prevWord, "lux") == 0 || strcmp(prevWord, "luxurious") == 0)
				{
					strcat(lastWord, "2/");
				}
				if (strcmp(prevWord, "econom") == 0)
				{
					strcat(lastWord, "1/");
				}
				if (strcmp(prevWord, "any") == 0)
				{
					strcat(lastWord, "0/");
				}
			}
			if (!strcmp(prevWord, "for"))
			{
				if (!strcmp(word, "one"))
				{
					strcat(lastWord, "1/");
				}
				else
				{
					if (!strcmp(word, "two"))
					{
						strcat(lastWord, "2/");
					}
					else
					{
						if (!strcmp(word, "three"))
						{
							strcat(lastWord, "3/");
						}
						else
						{
							if (!strcmp(word, "four"))
							{
								strcat(lastWord, "4/");
							}
							else
							{
								if (!strcmp(word, "five"))
								{
									strcat(lastWord, "5/");
								}
							}
						}
					}
				}
			}
			if (word[0] > 47 && word[0] < 59)
			{
				strcat(lastWord, word);
				isAll = true;
			}
			int x = 0;
			while (word[x] != '\0')
			{
				prevWord[x] = word[x];
				x++;
			}
			prevWord[x] = '\0';
		}
		if (isAll)
		{
			return lastWord;
		}
	}
	return lastWord;
}

void fillStruct(struct Hotel* hotels, int iter, const char* hotelsInfo, int stringSize)
{
	int fieldNumber = 0;

	for (int i = 0, j = 0; i < stringSize; i++, j++)
	{
		if (fieldNumber == 0)
		{
			if (hotelsInfo[i + 1] != ',')
			{
				hotels[iter].city[j] = hotelsInfo[i];
			}
			else
			{
				hotels[iter].city[j] = '\0';
				fieldNumber++;
				i += 2;
				j = -1;
			}
		}
		else if (fieldNumber == 1)
		{
			if (hotelsInfo[i + 1] != ',')
			{
				hotels[iter].hotelName[j] = hotelsInfo[i];
			}
			else
			{
				hotels[iter].hotelName[j] = '\0';
				fieldNumber++;
				i += 2;
				j = -1;
			}
		}
		else if (fieldNumber == 2)
		{
			if (hotelsInfo[i + 1] != ',')
			{
				hotels[iter].address[j] = hotelsInfo[i];
			}
			else
			{
				hotels[iter].address[j] = '\0';
				fieldNumber++;
				i += 2;
				j = -1;
			}
		}
		else if (fieldNumber == 3)
		{
			if (hotelsInfo[i + 1] != ',')
			{
				hotels[iter].roomClass[j] = hotelsInfo[i];
			}
			else
			{
				hotels[iter].roomClass[j] = '\0';
				fieldNumber++;
				i += 2;
				j = -1;
			}
		}
		else if (fieldNumber == 4)
		{
			if (hotelsInfo[i + 1] != ',')
			{
				hotels[iter].amountOfFreeRooms[j] = hotelsInfo[i];
			}
			else
			{
				hotels[iter].amountOfFreeRooms[j] = '\0';
				fieldNumber++;
				i += 2;
				j = -1;
			}
		}
		else if (fieldNumber == 5)
		{
			if (hotelsInfo[i + 1] != '\n')
			{
				hotels[iter].roomCost[j] = hotelsInfo[i];
			}
			else
			{
				hotels[iter].roomCost[j] = '\0';
				return;
			}
		}
	}
}

int countStrings(const char* fname)
{
	FILE* file;
	int counter = 0;
	char ch[100];
	errno_t fileOpenError;
	fileOpenError = fopen_s(&file, fname, "rb");
	if (fileOpenError != 0)
	{
		printf_s("File is not opened");
		return 0;
	}
	else
	{
		printf_s("Yeah, it's opened");
	}
	while (!feof(file))
	{
		if (fgets(ch, 100, file))
		{
			counter++;
		}
	}
	fclose(file);
	return counter;
}

void createStructArray(struct Hotel* hotels, int size, const char* fname)
{
	FILE* file;
	char info[60];
	int iter = 0;
	int arrSize = sizeof(info) / sizeof(info[0]);

	errno_t fileOpenError;
	fileOpenError = fopen_s(&file, fname, "rb");
	if (fileOpenError != 0)
	{
		printf_s("File is not opened");
		return;
	}
	else
	{
		printf_s("...");
	}

	while (!feof(file) && iter < size)
	{
		if (fgets(info, arrSize, file))
		{
			fillStruct(hotels, iter, info, arrSize);
			iter++;
		}
	}
	fclose(file);
	return;
}

bool reserveRoom(struct Hotel* hotels, int hotelAmount, int index)
{
	char const *reserved = "reserved\n";
	char const *n = "\n";
	char delim[] = " / ";
	for (int i = 0; i < hotelAmount; i++)
	{
		if (index == i)
		{
			FILE* f = fopen("C:\\Users\\grits\\reservedH.txt", "a");
			if (!f)
			{
				printf_s("Error");
				return 0;
			}
			fwrite(n, sizeof(char), strlen(n), f);
			fwrite(hotels[i].hotelName, sizeof(char), strlen(hotels[i].hotelName), f);
			fwrite(delim, sizeof(char), strlen(delim), f);
			fwrite(hotels[i].city, sizeof(char), strlen(hotels[i].city), f);
			fwrite(delim, sizeof(char), strlen(delim), f);
			fwrite(hotels[i].address, sizeof(char), strlen(hotels[i].address), f);
			fwrite(delim, sizeof(char), strlen(delim), f);
			fwrite(reserved, sizeof(char), strlen(reserved), f);
			fclose(f);
			return true;
		}
	}
	return false;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
