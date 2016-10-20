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

private:
	int n; //ilosc wierzcholkow
	list <int> *wierzcholki = new list <int>[n + 1]; //lista nastêpnikow wierzcholka
	fstream plik;
public:
	graf(fstream& plik)
	{
		int n; //ilosc wierzcholkow
		plik.open("graf.txt");

	}

};




int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

