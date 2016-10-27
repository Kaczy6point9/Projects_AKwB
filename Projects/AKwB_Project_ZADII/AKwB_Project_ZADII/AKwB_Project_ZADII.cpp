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
			list <int> *nastepniki = new list <int>[n + 1]; //lista nastepnikow kazdego wierzcholka
			nastepniki = listasasiedztwa(graf1, n);

			
			//wywswietlanie listy
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
			
			/*
			//wyswietlanie macierzy
			for (pom1 = 0; pom1 < n; pom1++) //zmienna pomocnicza, w tym przypadku bêdzie oznacza³a indeks kolumny
			{
			for (int pom2 = 0; pom2 < n; pom2++) //zmienna pomocnicza, w tym przypadku bêdzie oznacza³a indeks wierszu
			{

			cout << graf1[pom1][pom2] << " ";
			}
			cout << endl;
			}
			*/
			
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
	list <int> *listasasiedztwa(int **macierzsasiedztwa, int n)//tworzy liste nastepnikow z macierzy sasiedztwa
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

};




int _tmain(int argc, _TCHAR* argv[])
{
	graf *graf1 = new graf();
	system("PAUSE");
	delete graf1;
	return 0;
}

