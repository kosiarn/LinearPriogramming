// LinearPriogramming.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include "simplex.h"

int main()
{
    std::cout << "Hello World!\n";

	std::vector<std::vector<float>> a_matrix
	{ 
		{0, 0, 0, 0,-5, 0,-6, 1, 5},
		{1, 0, 0,-1, 0, 0, 0, 0, 1},
		{0, 1, 0, 1,-1, 1,-1, 0, 0},
		{0, 0, 1,-1, 2, 1, 2, 0,-1}
	};

	std::vector<std::vector<float>> simplex_table
	{
		{-8.0, 0.0,-2.0, 7.0, 0.0, 0.0},
		{ 4.0, 0.0, 2.0,-4.0, 1.0, 0.0},
		{ 6.0, 1.0, 1.0, 5.0, 0.0, 0.0},
		{ 5.0, 0.0,-2.0, 1.0, 0.0, 1.0}
	};

	std::vector<std::vector<float>> simplex_table2
	{
		{0, -2,-1, 0, 0, 0},
		{14, 2, 2, 1, 0, 0},
		{20, 4, 0, 0, 1, 0},
		{18, 2, 3, 0, 0, 1}
	};
	/*
	std::vector<int> indices = linear_programming::getIdentityMatrix(a_matrix);

	for (auto index : indices) {
		std::cout << index << std::endl;
	}
	*/
	std::vector<std::vector<float>> rotated_table = linear_programming::rotateTable(simplex_table, 1, 2);
	//std::vector<std::vector<float>> rotated_table = linear_programming::rotateTable(simplex_table2, 2, 1);



	std::cout << "this is the end" << std::endl;

	return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
