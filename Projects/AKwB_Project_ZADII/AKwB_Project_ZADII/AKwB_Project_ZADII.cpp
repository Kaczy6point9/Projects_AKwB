// AKwB_Project_ZADII.cpp : Defines the entry point for the console application.
//Maciej Kaczor Bioinformatyka II rok

#include "stdafx.h"
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#define  _crt_secure_no_warnings

using namespace std;

class graf
{

private:
	int n; //ilosc wierzcholkow
	
	

public:
	fstream plik;
	graf()
	{
		int n; //ilosc wierzcholkow
		string linia;
		int dlugosc_lini;
		int pom1, pom2;
		plik.open("C:/Users/Kaczy/Documents/Visual Studio 2013/Projects/AKwB_Project_ZADII/AKwB_Project_ZADII/graf.txt");
		if (!plik.good())
		{
			cout << "Blad pliku" << endl;
		}
		else
		{
			plik >> n;
			this->n = n;
			list <int> *wierzcholki = new list <int>[n + 1]; //lista następnikow wierzcholka
			while (getline(plik, linia))
			{
				dlugosc_lini = linia.length();

				char *buffer_lini = new char[dlugosc_lini];
				//strcpy(buffer_lini, linia.c_str());
				//for (int j = 0; j < n; j++)
				for (int i = 3; i < dlugosc_lini; i += 2)
				{

					pom1 = atoi(&linia[0]);
					pom2 = atoi(&linia[i]);
					wierzcholki[pom1].push_back(pom2);
				}

			};
			list<int>::iterator it; //iterator listy
			for (int i = 0; i < n; i++)
			{
				cout << i << ": ";
				for (it = wierzcholki[i].begin(); it != wierzcholki[i].end(); ++it)
				{
					cout << *it << " "; //wypisanie listy nastepnikow
				}

				cout << endl;
			}

			cout << endl;
		}

		plik.close();
	}
	

};




int _tmain(int argc, _TCHAR* argv[])
{ 
	graf *graf1 = new graf();
	getchar();
	delete graf1;
	return 0;
}

