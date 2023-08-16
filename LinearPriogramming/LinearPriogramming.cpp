// LinearPriogramming.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include "simplex.h"
#include <iomanip>


void printTable(std::vector < std::vector<float>> table) {
	for (auto row : table) {
		for (auto value : row) {
			std::cout << std::setw(7) << value << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
    std::cout << "Hello World!\n";



	std::vector<std::vector<float>> lecture_3_simplex_table
	{
		{-8.0, 0.0,-2.0, 7.0, 0.0, 0.0},
		{ 4.0, 0.0, 2.0,-4.0, 1.0, 0.0},
		{ 6.0, 1.0, 1.0, 5.0, 0.0, 0.0},
		{ 5.0, 0.0,-2.0, 1.0, 0.0, 1.0}
	};

	std::vector<std::vector<float>> lecture_4_simplex_table
	{
		{0, -2,-1, 0, 0, 0},
		{14, 2, 2, 1, 0, 0},
		{20, 4, 0, 0, 1, 0},
		{18, 2, 3, 0, 0, 1}
	};

	std::vector<std::vector<float>> medium_tableau = {
		{0, -4, -6, 0, 0, 0},
		{11, -1, 1, 1, 0, 0},
		{27, 1, 1, 0, 1, 0},
		{90, 2, 5, 0, 0, 1}
	};

	

	std::cout << "Wyjsciowa tablica sympleksowa:" << std::endl;
	printTable(medium_tableau);
	auto lec_3_solution = linear_programming::solveProblem(medium_tableau);
	std::cout << "Tablica w postaci optymalnej:" << std::endl;
	printTable(lec_3_solution);



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
