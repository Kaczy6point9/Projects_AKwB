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
public:
	fstream plik;
	int n; //ilosc wierzcholkow
	
	graf()
	{
		
		int pom1, pom2; //temp zmienne pomocnicze
		plik.open("C:/Users/Kaczy/Documents/Visual Studio 2013/Projects/AKwB_Project_ZADII/AKwB_Project_ZADII/graf.txt");
		if (!plik.good())
		{
			cout << "Blad pliku" << endl;
		}
		else
		{
			plik >> n;
			int **graf1 = new int *[n];  //stworzenie tablicy dynamicznej
			for (int i = 0; i < n; i++) //bedzie ona przechowywała macierz sasiedztwa 
				graf1[i] = new int[n];  //
			graf1 = macierzsasiedztwa(n, &plik); //wywołanie funkcji tworzącej graf

			plik.close();
			if (adjointline(graf1, n)) // wywołanie funkcji która sprawdza czy graf jest sprzężony i czy jest liniowy
			{
					cout << "graf jest sprzezony" << endl;
			}
			else
				cout << "Graf nie jest sprzezony" << endl;
			
			
			//wyswietlanie macierzy
			
			cout << endl;
			for (pom1 = 0; pom1 < n; pom1++) //zmienna pomocnicza, w tym przypadku będzie oznaczała indeks kolumny
			{
			for (int pom2 = 0; pom2 < n; pom2++) //zmienna pomocnicza, w tym przypadku będzie oznaczała indeks wierszu
			{

			cout << graf1[pom1][pom2] << " ";
			}
			cout << endl;
			}
			
			cout << endl;
			graforyginalny(graf1, n);
			
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
				plik >> pom3;
				msas[pom1][pom2] = pom3;
			}
		}

		return msas; // zwracamy macierz
	}
	
	
	bool adjointline(int **graf, int n) //funkcja sprawdzająca czy graf jest grafem sprzeżonym 
	{
		bool line = true; //Zakładamy że graf jest liniowy od początku
		for (int pom1 = 0; pom1 < n; pom1++)//pętla przeskakująca po wierzchołkach
		{
			for (int pom2 = 0; pom2+1 < n; pom2++)//pętla przeskakująca po drugim wierzchołku
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
						if (graf[pom1][pom3] == 1 && graf[pom1][pom3] == graf[pom2][pom3])//Sprawdzamy czy dwa wierzchołki mają wspólnych następników 
						{
							if (row(graf, pom1, pom2, n))//Jeśli wierzchołki mają wspólnych następników, sprawdzamy czy wszystkie następniki są takie same
							{
								for (int pom4 = 0; pom4 < n; pom4++) 
									if (graf[pom4][pom1] == 1 && graf[pom4][pom1] == graf[pom4][pom2])//jeśli wszystkie następniki są takie same, sprawdzamy czy ich poprzedniki są zbiorem niepustym
										line = false; //jeżeli poprzedniki są zbiorem niepustym wtedy graf nie jest liniowy
							}
							else
								return false; //jeśli następniki nie są takie same zwracamy, że graf nie jest sprzężony
							break;//jeśli sprawdziło następniki i zwróciło true, przerywamy sprawdzanie reszty kolumny i przechodzimy do kolejnych wierzchołków
						
						}
					}
				}

			}
		}
		if (line) //co ma wypisywać na ekran jeśli jest linowy, a co jeśli nie
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
	
	bool row(int **graf, int pom1, int pom2, int n)//funkcja sprawdzająca wszystkich następników
	{
		for (int i = 0 ; i < n; i++)
			if (graf[pom1][i] != graf[pom2][i]) //jeżeli następniki są różne zwraca fałsz
				return false;
			else
				return true; //jeżeli wzsystkie są takie same to prawdę
	}

	
	
	int **graforyginalny(int **graf, int n)
	{
		vector <tuple<int, int, int>> graforg;
		int x = 0, y = x+1;
		for (int pom1 = 0; pom1 < n; pom1++)
		{ 
			graforg.push_back(make_tuple(pom1, x, y));
			x++;
			y++;
		}
		for (int pom1 = 0; pom1 < n; pom1++)
		{
			for (int pom2 = 0; pom2 < n; pom2++)
			{
				
				if (graf[pom1][pom2] == 1)
				{
					for (auto& x : graforg)
					{
						if (get<0>(x) == pom1)
						{
							for (auto& y : graforg)
							{
								if (get<0>(y) == pom2)
								{
									if (get<2>(x) < get<1>(y))
									{
										get<1>(y) = get<2>(x);
									}
									else
										get<2>(x) = get<1>(y);
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
					 tmp++;
					 min++;
					 break;
				 }
				 else if (pom1 == final_graph.size() - 1)
					 min++;
			 }
		 }
		 max = 0;
		 for(int pom1 = 0; pom1 < final_graph.size(); pom1++)
		 {
			 if (final_graph[pom1].first > max)
				 max = final_graph[pom1].first;
			 if (final_graph[pom1].second > max)
				 max = final_graph[pom1].second;
		 }

		 int **graforyginalny = new int *[max];  //stworzenie tablicy dynamicznej
		 for (int i = 0; i < max; i++) //bedzie ona przechowywała macierz sasiedztwa 
			 graforyginalny[i] = new int[max]; 

		 for (int i = 0; i < max; i++)
		 {
			 for (int j = 0; j < max; j++)
				 graforyginalny[i][j] = 0;
		 }
			
		 for (auto& i : final_graph)
		 {
			 graforyginalny[get<0>(i)][get<1>(i)]+=1;
		 }
		
		 for (const auto& i : final_graph)
		 {
			 cout << get<0>(i) << " " << get<1>(i) << " " << endl;
		 }
		 
		 for (int pom1 = 0; pom1 < max; pom1++) //zmienna pomocnicza, w tym przypadku będzie oznaczała indeks kolumny
		 {
			 for (int pom2 = 0; pom2 < max; pom2++) //zmienna pomocnicza, w tym przypadku będzie oznaczała indeks wierszu
			 {

				 cout << graforyginalny[pom1][pom2] << " ";
			 }
			 cout << endl;
		 }
		
	
		
		return graforyginalny;
	}

	
};





int _tmain(int argc, _TCHAR* argv[])
{
	graf *graf1 = new graf();
	system("PAUSE");
	delete graf1;
	return 0;
}

