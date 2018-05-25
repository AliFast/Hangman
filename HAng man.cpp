#include<iostream>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include<stdlib.h>
#include<cstdlib>
#include<ctime>
#include<string>
using namespace std;
char GetWhatTheyWant();
int inputcompare(char array1[], char array2[], char alphabet[], char letter, int &correctguess, int wordLenght);
void WatchHighScore();
void letterboard(char array[]);
void hintt(char comparearray[], char outputarray[], char alphabetarray[], int &hint, int &correctguess, int wordLenght);
void randomWordGenerator(ifstream& wordFile, char random[][6], char comparearray[], const int rows);
int score_n_attempts(int lettercount, int &attempts, int &correctguess, int &score);

int main()
{
	system("Color F2");

	int    score = 0, levels = 1, lettercount, hint = 1, wordLenght = 0, tempLength;
	char letter, Continue, choice = '0';
	char name[25] = { '\0' };
	char PreviousPage = '#';



	while (PreviousPage == '#')
	{

		while (choice != '1' && choice != '2'  && choice != '3')
		{
			system("CLS");
			choice = GetWhatTheyWant();//calling the function what they want
			system("CLS");

			if (choice == '2')
			{

				WatchHighScore();
				cout << endl << endl;
				cout << "press # to move to the Previous Page\n";
				 PreviousPage= _getch();

			}

			if (choice == '1' || choice == '3')
				break;
			choice = '0';
		}
		PreviousPage = '@';
	}




	if (choice == '3')
		levels = 11;

	while (levels <= 10 && choice == '1')
	{
		int correctguess = 0, attempts = 9;

		hint = 1;
		char random[60][6] = { '\0' };
		char comparearray[10] = { '\0' };
		char outputarray[10] = { '\0' };


		char alphabetarray[28] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


		if (levels == 1)
		{
			system("Color 3F");
			cout << "Enter Name" << endl;
		//	gets_s(name);
			cin.getline(name, 25);
		}

		if (levels <= 3)
		{
			system("Color 8B");
			hint = 0;
			ifstream wordFile("three letter words.txt");

			if (wordFile.is_open())
			{
				randomWordGenerator(wordFile, random, comparearray, 60);


			}
			else
			{
				cout << "Unable To Open Dictionary" << endl;

			}

			wordFile.close();
		}



		if (levels >= 4 && levels <= 7)
		{

			system("Color F3");
			ifstream wordFile("Four line words.txt");

			if (wordFile.is_open())
			{
				randomWordGenerator(wordFile, random, comparearray, 60);


			}
			else
			{
				cout << "Unable To Open Dictionary" << endl;

			}

			wordFile.close();
		}
		if (levels >7)
		{
			system("Color B8");
			ifstream wordFile("FIVE LINE WORDS.txt");

			if (wordFile.is_open())
			{
				randomWordGenerator(wordFile, random, comparearray, 60);


			}
			else
			{
				cout << "Unable To Open Dictionary" << endl;

			}

			wordFile.close();
		}
		wordLenght = strlen(comparearray);

		tempLength = wordLenght;

		while (correctguess <= wordLenght + 1 && attempts > -1)// loop for one question
		{
			int t = 0;

			system("CLS");

			cout << "Question # " << levels << "       " << "Score=" << score << "       " << "Attempts Left=";
			if (attempts == 0)
				cout << attempts;
			else
				cout << attempts - 1;
			cout << "        " << "Hint=" << hint << endl << endl;
			if (attempts != 0)
			{

				for (int u = 0; u <= wordLenght; u++)
					cout << outputarray[u] << " ";
			}
			else
			{
				for (int u = 0; u <= wordLenght; u++)
					cout << comparearray[u] << " ";
			}
			cout << endl;
			for (int R = 0; R < tempLength; R++)
				cout << "_ ";

			cout << endl << endl;

			letterboard(alphabetarray);// calling the function letterboard

			cout << endl << endl;

			if (correctguess <= wordLenght && attempts > 0)
			{

				cout << "guess letter";
				if (hint == 1)
					cout << " or press * for hint" << endl << endl;
				 letter=_getch();
				if (letter == '*' && hint == 1)
					hintt(comparearray, outputarray, alphabetarray, hint, correctguess, tempLength);

				else
				{
					if (letter >= 97 && letter <= 122)
						letter = letter - 32;
					for (int w = 0; w <= 25; w++)
					{
						if (letter == alphabetarray[w])
							++t;
					}
					if (t != 0)
					{

						if ((letter >= 97 && letter <= 122) || (letter >= 65 && letter <= 91))
						{



							lettercount = inputcompare(comparearray, outputarray, alphabetarray, letter, correctguess, tempLength);// calling the function inputcompare

							score = score_n_attempts(lettercount, attempts, correctguess, score);// calling the function score_n_attempts
						}
					}
				}
			}

			if (correctguess >= wordLenght)
				++correctguess;
			if (attempts <= 1)
				--attempts;
		}
		levels++;
		if (correctguess == wordLenght + 2)
			cout << "Congratulations\n" << endl;
		else if (attempts == -1)
			cout << "It is not a child's game\n" << endl;
		if (correctguess == wordLenght + 2 || attempts == -1)
		{
			cout << "Enter c or C key to continue";
			 Continue=_getch();
			if (Continue == 'c' || Continue == 'C')
				system("CLS");
			else
				levels = 11;
		}


	}
	if (choice != '3')
	{
		int nameLength = strlen(name);

		ofstream scoreFile("High Score.txt", ios::app);
		

		for (int i = 0; i < nameLength; i++)
		{

			scoreFile << name[i];
		}

		

		scoreFile << "        " << score << endl;


		scoreFile.close();
	}

	return 0;
}
void letterboard(char array[])
{
	int i = 0, m = 6;
	for (int j = 0; j <= 3; j++) // to divide letters in three lines
	{
		for (; i <= m; i++)
		{
			cout << array[i] << " ";
		}
		cout << endl << endl;
		m = m + 7;//here m is a counter which helps in traversing the array by changing the condition value for i;
	}
}
int inputcompare(char array1[], char array2[], char alphabet[], char letter, int &correctguess, int wordLenght)//it will return number of times letter is found
{
	int lettercount = 0;
	for (int x = 0; x <= wordLenght - 1; x++)
	{

		if ((array1[x] == letter))//Checking whether the letter is present in array input from file
		{
			array2[x] = letter;//putting it in output array if present
			lettercount++;
			for (int y = 0; y <= 25; y++)//removig letter from the letter keyboard(alphabet array)
			{
				if (alphabet[y] == letter)
				{
					alphabet[y] = '\0';
					break;

				}
			}

		}
	}
	if ((array1[correctguess] != letter))//Checking whether the letter is not present in array input from file

	{


		for (int y = 0; y <= 25; y++)//removig letter from the letter keyboard(alphabet array) because we have to remove in both cases
		{
			if (alphabet[y] == letter)
			{
				alphabet[y] = '\0';
				break;

			}
		}
	}
	return lettercount;
}
int score_n_attempts(int lettercount, int &attempts, int &correctguess, int &score)//it will return score
{

	if (lettercount == 0)
	{
		--attempts;
		score = score - 10;
	}
	else
	{
		correctguess = correctguess + lettercount;
		score = score + (lettercount * 20);
	}
	return score;
}
void randomWordGenerator(ifstream& wordFile, char random[][6], char comparearray[], const int rows)
{

	int count = 0;
	while (!wordFile.eof())
	{


		wordFile >> random[count];
		count++;




	}

	int w = 0;
	int from = 0;
	int to = count;

	srand(time(0));
	int i = from + (rand() % (to - from + 1));

	for (int u = 0; random[i][u] != '\0'; u++)
	{
		if (random[i][u] != '\0')
			w++;
	}
	for (int a = 0; a < w; a++)
	{
		for (int j = 0; j < a + 1; j++)
		{

			comparearray[a] = random[i][j];

		}
	}
}
char GetWhatTheyWant()
{
	char choice;

	cout << "\n1 - To Start Game" << endl;
	cout << "2 - To see Previous Players Score" << endl;
	cout << "3-To Quit the Game" << endl;

	  choice =_getch();


	return choice;
}
void hintt(char comparearray[], char outputarray[], char alphabetarray[], int &hint, int &correctguess, int wordLenght)
{
	int n = 0;
	for (int i = 0; comparearray[i] != '\0'; i++)
	{
		if (outputarray[i] == '\0')
		{
			outputarray[i] = comparearray[i];
			for (int y = 0; y <= wordLenght - 1; y++)
			{
				if (comparearray[i] == comparearray[y])
				{

					outputarray[y] = comparearray[y];
					n++;
				}
			}
			for (int y = 0; y <= 25; y++)
			{
				if (alphabetarray[y] == comparearray[i])
				{
					alphabetarray[y] = '\0';
					break;

				}
			}

			hint--;
			++correctguess;
			if (n > 0)
				correctguess = correctguess + (n - 1);


			break;
		}

	}
}
void WatchHighScore()

{

	string line;
	ifstream scoreFile("High Score.txt");


	if (scoreFile.is_open())
	{

		while (getline(scoreFile, line))
		{
			cout << line << '\n';

		}

		scoreFile.close();

	}
	else
		cout << "Unable To Open High Scores" << endl;
}
