// AKwB_Project_ZADII.cpp : Defines the entry point for the console application.
//Maciej Kaczor Bioinformatyka II rok

#include "stdafx.h"
#include <iostream>
#include <list>
#include <fstream>
#include <string>

using namespace std;

class graf
{
public:
	fstream plik;
	graf()
	{
		int n; //ilosc wierzcholkow
		int pom1, pom2; //temp zmienne pomocnicze
		plik.open("X:/Projects/AKwB_Project_ZADII/AKwB_Project_ZADII/graf.txt");
		if (!plik.good())
		{
			cout << "Blad pliku" << endl;
		}
		else
		{
			plik >> n;
			int **graf1 = new int *[n];  //stworzenie tablicy dynamicznej
			for (int i = 0; i < n; i++) //bedzie ona przechowywa³a macierz sasiedztwa 
				graf1[i] = new int[n];  //
			graf1 = macierzsasiedztwa(n, &plik);

			plik.close();
			//list <int> *nastepniki = new list <int>[n + 1]; //lista nastepnikow kazdego wierzcholka
			//nastepniki = listasasiedztwa(graf1, n);
			if (adjoint(graf1, n))
			{
					cout << "graf jest sprzezony" << endl;
			}
			else
				cout << "Graf nie jest sprzezony" << endl;
			
			//wywswietlanie listy
			/*
			list<int>::iterator it; //iterator listy
			for (int i = 0; i < n; i++)
			{
			cout << i+1 << ": ";
			for (it = nastepniki[i].begin(); it != nastepniki[i].end(); ++it)
			{
			cout << *it+1 << " "; //wypisanie listy nastepnikow
			}

			cout << endl;
			}
			*/
			//wyswietlanie macierzy
			
			cout << endl;
			for (pom1 = 0; pom1 < n; pom1++) //zmienna pomocnicza, w tym przypadku bêdzie oznacza³a indeks kolumny
			{
			for (int pom2 = 0; pom2 < n; pom2++) //zmienna pomocnicza, w tym przypadku bêdzie oznacza³a indeks wierszu
			{

			cout << graf1[pom1][pom2] << " ";
			}
			cout << endl;
			}
			
			
		}

		
		

		
	}
	int **macierzsasiedztwa(int n, fstream *file) //gdzie n ilosc wierzcholkow
	{
		int pom3; //temp zmienne pomocnicze
		int **msas = new int *[n];  //msas = macierz sasiedztwa
		for (int i = 0; i < n; i++) // tworzenie tablicy dwuwymiarowej
			msas[i] = new int[n];
		
		for (int pom1 = 0; pom1 < n; pom1++) //zmienna pomocnicza, w tym przypadku bêdzie oznacza³a indeks kolumny
		{
			for (int pom2 = 0; pom2 < n; pom2++) //zmienna pomocnicza, w tym przypadku bêdzie oznacza³a indeks wierszu
			{
				plik >> pom3;
				msas[pom1][pom2] = pom3;
			}
		}

		return msas; // zwracamy macierz
	}
	//tworzenie listy
	/*list <int> *listasasiedztwa(int **macierzsasiedztwa, int n)//tworzy liste nastepnikow z macierzy sasiedztwa
	{

		list <int> *wierzcholki = new list <int>[n + 1]; //utworzenie listy ktora bedzie przechowywa³a wierzcho³ki
		for (int pom = 0; pom < n; pom++)
		{
			for (int pom2 = 0; pom2 < n; pom2++)
			{
				if (macierzsasiedztwa[pom][pom2] == 1)
					wierzcholki[pom].push_back(pom2); //wstawianie na listê nastêpników danego wierzcho³ka
			}
		}

		

		return wierzcholki;
	}
	*/
	bool adjoint(int **graf, int n)
	{
		bool line = true;
		for (int pom1 = 0; pom1 < n; pom1++)
		{
			for (int pom2 = 0; pom2 < n; pom2++)
			{
				for (int pom3 = 0; pom3 < n; pom3++)
				{
					if (graf[pom1][pom3] > 1)
					{
						cout << "Multigraf!!" << endl;
						return false;
					}
					else
					{ 
						if (graf[pom1][pom3] == 1 && graf[pom1][pom3] == graf[pom2][pom3])
						{
							if (row(graf, pom1, pom2, n))
							{
								for (int pom4 = 0; pom4 < n; pom4++)
									if (graf[pom4][pom1] == 1 && graf[pom4][pom1] == graf[pom4][pom1])
										line = false;
							}
							else
								return false;
							break;
						
						}
					}
				}

			}
		}
		if (line)
		{
			cout << "Graf jest liniowy i jest to ";
			return true;
		}
		else
		{
			cout << "Graf nie jest liniowy i jest to ";
			return true;
		}
		
	}
	
	bool row(int **graf, int pom1, int pom2, int n)
	{
		for (int i = 0 ; i < n; i++)
			if (graf[pom1][i] != graf[pom2][i])
				return false;
			else
				return true;
	}
};




int _tmain(int argc, _TCHAR* argv[])
{
	graf *graf1 = new graf();
	system("PAUSE");
	delete graf1;
	return 0;
}

