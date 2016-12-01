// AKwB_Project_ZADII.cpp : Defines the entry point for the console application.
//Maciej Kaczor Bioinformatyka II rok

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>


using namespace std;

class graf
{
private:
	int n; //ilosc wierzcholkow
	int wielkoscorg; //wielkosc macierzy oryginalnej

public:
	fstream plik;


	graf()
	{

		int pom1, pom2; //temp zmienne pomocnicze
		plik.open("X:/Projects/AKwB_Project_ZADII/AKwB_Project_ZADII/graf2.txt");
		if (!plik.good())
		{
			cout << "Blad pliku" << endl;
		}
		else
		{
			plik >> n;
			this->n = n;
			int **graf1 = new int *[n];  //stworzenie tablicy dynamicznej
			for (int i = 0; i < n; i++) //bedzie ona przechowywała macierz sasiedztwa 
				graf1[i] = new int[n];  //
			graf1 = macierzsasiedztwa(n, &plik); //wywołanie funkcji tworzącej graf

			plik.close();
			//wyswietlanie macierzy

			
			for (pom1 = 0; pom1 < n; pom1++) //zmienna pomocnicza, w tym przypadku będzie oznaczała indeks kolumny
			{
				for (int pom2 = 0; pom2 < n; pom2++) //zmienna pomocnicza, w tym przypadku będzie oznaczała indeks wierszu
				{

					cout << graf1[pom1][pom2] << " ";
				}
				cout << endl;
			}

			cout << endl;

			if (adjoint(graf1, n)) // wywołanie funkcji która sprawdza czy graf jest sprzężony i czy jest liniowy
			{
				cout << "graf jest sprzezony ";
				if (line(graf1, n))
					cout << "i jest liniowy" << endl;

				cout << endl;
				plik.open("X:/Projects/AKwB_Project_ZADII/AKwB_Project_ZADII/graforg.txt", ios::out);
				if (!plik.good())
				{
					cout << "Blad pliku" << endl;
				}
				else
				{
					zapisdopliku(graforyginalny(graf1, n), &plik);
					plik.close();

				}
			}
			else
				cout << "Graf nie jest sprzezony" << endl;


		




		}





	}

	int **macierzsasiedztwa(int n, fstream *file) //gdzie n ilosc wierzcholkow
	{
		int pom3; //temp zmienne pomocnicze
		int **msas = new int *[n];  //msas = macierz sasiedztwa
		for (int i = 0; i < n; i++) // tworzenie tablicy dwuwymiarowej
			msas[i] = new int[n];

		for (int pom1 = 0; pom1 < n; pom1++) //zmienna pomocnicza, w tym przypadku będzie oznaczała indeks kolumny
		{
			for (int pom2 = 0; pom2 < n; pom2++) //zmienna pomocnicza, w tym przypadku będzie oznaczała indeks wierszu
			{
				*file >> pom3;
				msas[pom1][pom2] = pom3;
			}
		}

		return msas; // zwracamy macierz
	}

	bool adjoint(int **graf, int n) //funkcja sprawdzająca czy graf jest grafem sprzeżonym 
	{
		for (int pom1 = 0; pom1 < n; pom1++)//pętla przeskakująca po wierzchołkach
		{
			for (int pom2 = 0; pom2 + 1 < n; pom2++)//pętla przeskakująca po drugim wierzchołku
			{
				for (int pom3 = 0; pom3 < n; pom3++)//pętla skacząca po następnikach wierzchołka
				{
					if (graf[pom1][pom3] > 1)//jeżli w pliku występuje wartość wskazująca, że podany graf jest multigrafem
					{
						cout << "Multigraf!! " << endl;
						return false; //zwracamy że graf nie jest sprzężony
					}
					else
					{
						if (graf[pom1][pom3] == 1 && graf[pom1][pom3] == graf[pom2][pom3] && pom1 != pom2)//Sprawdzamy czy dwa wierzchołki mają wspólnych następników 
						{
							if (!row(graf, pom1, pom2, n))//Jeśli wierzchołki mają wspólnych następników, sprawdzamy czy wszystkie następniki są takie same
								return false; //jeśli następniki nie są takie same zwracamy, że graf nie jest sprzężony
							break;//jeśli sprawdziło następniki i zwróciło true, przerywamy sprawdzanie reszty kolumny i przechodzimy do kolejnych wierzchołków

						}
					}
				}

			}
		}

		return true;
	}

	bool line(int **graf, int n)
	{
		for (int pom1 = 0; pom1 < n; pom1++)//pętla przeskakująca po wierzchołkach
		{
			for (int pom2 = 0; pom2 + 1 < n; pom2++)//pętla przeskakująca po drugim wierzchołku
			{
				for (int pom3 = 0; pom3 < n; pom3++)//pętla skacząca po następnikach wierzchołka
				{
					if ((row(graf, pom1, pom2, n) && graf[pom1][pom3] == 1 && graf[pom1][pom3] == graf[pom2][pom3]) && (graf[pom3][pom1] == 1 && graf[pom3][pom1] == graf[pom3][pom2]))
						return false; //jeżeli poprzedniki są zbiorem niepustym wtedy graf nie jest liniowy

				}
			}
		}
		return true;
	}

	bool row(int **graf, int pom1, int pom2, int n)//funkcja sprawdzająca wszystkich następników
	{
		for (int i = 0; i < n; i++)
		{
			if (graf[pom1][i] != graf[pom2][i]) //jeżeli następniki są różne zwraca fałsz
				return false;
		}
				return true; //jeżeli wzsystkie są takie same to prawdę
	}

	int **graforyginalny(int **graf, int n)
	{
		vector <tuple<int, int, int>> graforg;
		int x = 0, y = x + 1;
		for (int pom1 = 0; pom1 < n; pom1++)
		{
			x = pom1 * 2;
			y = x + 1;
			graforg.push_back(make_tuple(pom1, x, y));

		}
		for (int pom1 = 0; pom1 < n; pom1++)
		{
			for (int pom2 = 0; pom2 < n; pom2++)
			{

				if (graf[pom1][pom2] == 1) //jeżeli istnieje krawędź między dwoma wierzchołkami w grafie sprzężonym
				{
					for (auto& x : graforg) //szukamy tych dwóch odpowiednich krawędzi
					{
						if (get<0>(x) == pom1) //jeżeli indeks krawędzi zgadza się z sprawdzaną krawędzią
						{
							for (auto& y : graforg)
							{
								if (get<0>(y) == pom2) //jeżeli indeks drugiej krawędzi zgadza się z sprawdzaną krawędzią 
								{
									if (get<2>(x) < get<1>(y)) //jeżeli indeks wierzchołka wejściowego pierwszej krawędzi jest mniejszy od wierzchołka wyjściowego drugiej krawędzi
									{
										get<1>(y) = get<2>(x); //to oznacza to, że wierzchołkiem wyjściowym drugiej krawędzi staje się wierchołek wejściowy pierwszej krawędzi
									}
									else
										get<2>(x) = get<1>(y);//w przeciwnym wypadku oznacza to, że wierzchołkiem wejściowym pierwszej krawędzi, staje się wierzchołek wyjściowy drguiej krawędzie.
								}
							}
						}

					}
				}
			}
		}

		vector <pair<int, int>> final_graph;


		for (auto& i : graforg)
		{
			final_graph.push_back(make_pair(get<1>(i), get<2>(i)));
		}

		int min = 0;
		int max = 0;
		int tmp = 0;
		for (int pom1 = 0; pom1 < final_graph.size(); pom1++)
		{
			if (final_graph[pom1].first > max)
				max = final_graph[pom1].first;
			if (final_graph[pom1].second > max)
				max = final_graph[pom1].second;
		}

		while (min <= max)
		{
			for (int pom1 = 0; pom1 < final_graph.size(); pom1++)
			{
				if (final_graph[pom1].second == min || final_graph[pom1].first == min)
				{
					for (pom1 = 0; pom1 < final_graph.size(); pom1++)
					{
						if (final_graph[pom1].first == min)
							final_graph[pom1].first = tmp;
						if (final_graph[pom1].second == min)
							final_graph[pom1].second = tmp;
					}
					min++;
					tmp++;

					break;
				}
				else if (pom1 == final_graph.size() - 1)
					min++;
			}
		}
		max = 0;
		for (int pom1 = 0; pom1 < final_graph.size(); pom1++)
		{
			if (final_graph[pom1].first > max)
				max = final_graph[pom1].first;
			if (final_graph[pom1].second > max)
				max = final_graph[pom1].second;
		}
		this->wielkoscorg = max + 1;
		int **graforyginalny = new int *[max + 1];  //stworzenie tablicy dynamicznej
		for (int i = 0; i < max + 1; i++) //bedzie ona przechowywała macierz sasiedztwa 
			graforyginalny[i] = new int[max + 1];

		for (int i = 0; i < max + 1; i++)
		{
			for (int j = 0; j < max + 1; j++)
				graforyginalny[i][j] = 0;
		}

		for (auto& i : final_graph)
		{
			graforyginalny[get<0>(i)][get<1>(i)] += 1;
		}

		for (const auto& i : final_graph)
		{
			cout << get<0>(i) << " " << get<1>(i) << " " << endl;
		}

		cout << endl;
		for (int pom1 = 0; pom1 < max + 1; pom1++) //zmienna pomocnicza, w tym przypadku będzie oznaczała indeks kolumny
		{
			for (int pom2 = 0; pom2 < max + 1; pom2++) //zmienna pomocnicza, w tym przypadku będzie oznaczała indeks wierszu
			{

				cout << graforyginalny[pom1][pom2] << " ";
			}
			cout << endl;
		}



		return graforyginalny;
	}

	void zapisdopliku(int **graf, fstream *file)
	{



		*file << wielkoscorg << endl;
		for (int pom1 = 0; pom1 < wielkoscorg; pom1++)
		{
			for (int pom2 = 0; pom2 < wielkoscorg; pom2++)
			{
				*file << graf[pom1][pom2] << " ";
			}
			*file << endl;
		}


		cout << "graf zapisany" << endl;

	}
};





int _tmain(int argc, _TCHAR* argv[])
{
	graf *graf1 = new graf();
	system("PAUSE");
	delete graf1;
	return 0;
}
