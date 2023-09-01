#include "pch.h"
#include "simplex.h"

const std::vector<std::vector<float>> &transpose(std::vector<std::vector<float>>& A) {
	int rows = A.size();
	if (rows == 0) return { {} };
	int cols = A[0].size();
	static std::vector<std::vector<float>> r(cols, std::vector<float>(rows));
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			r[j][i] = A[i][j];
		}
	}
	return r;
}

bool linear_programming::table_isUniformSize(std::vector<std::vector<float>> table) {
	std::vector<int> lengths = { };
	for (auto &row : table) {
		lengths.push_back(row.size());
	}
	for (int i = 0; i < lengths.size() - 1; i++) {
		if(lengths[i] != lengths[i + 1]){
			return false;
		}
	}
	return true;
}

/*TODO: finish below*/

bool linear_programming::isBase(std::vector<std::vector<float>> table)
{
	int row_amount = table.size();
	for (int i = 1; i < row_amount; i++) {
		if (table[i][0] < 0) return false;
	}
	std::vector<std::vector<float>> a_matrix = retrieveAMatrix(table);
	
	
	std::vector<float> target_function_coefficients = table[0];
	target_function_coefficients.erase(target_function_coefficients.begin()); //deleting -d
	std::vector<int> identity_matrix_columns = linear_programming::getIdentityMatrix(linear_programming::retrieveAMatrix(table));
	for (auto &column : identity_matrix_columns) {
		if (target_function_coefficients[column] != 0) return false;
	}
	return true;
}

std::vector<std::vector<float>> 
linear_programming::rotateTable(std::vector<std::vector<float>> table,
	int rotation_row, int rotation_column)
{
	int row_amount = static_cast<int>(table.size());
	int column_amount = static_cast<int>(table[0].size());
	float rotation_element = table[rotation_row][rotation_column];
	for (int i = 0; i < column_amount; i++) {
		table[rotation_row][i] = (float)table[rotation_row][i] / (float)rotation_element;
	}
	for (int row_index = 0; row_index < row_amount; row_index++) {
		if (row_index == rotation_row) continue;
		float rotation_coefficient =
			table[row_index][rotation_column] /
			table[rotation_row][rotation_column];
		for (int column_index = 0; column_index < column_amount; column_index++) {
			float what_to_subtract = table[rotation_row][column_index] *
				rotation_coefficient;
			table[row_index][column_index] =
				table[row_index][column_index] -
				what_to_subtract;
		}
	}
	return table;
}

std::vector<std::vector<float>>
	linear_programming::retrieveAMatrix(std::vector<std::vector<float>> table)
{
	table.erase(table.begin());
	for (auto &row : table) {
		row.erase(row.begin());
	}
	return table;
}



bool targetFunctionHasPositiveCoefficientsOnly(std::vector<float> target_function_row){
	for (float coeff : target_function_row) {
		if (coeff < 0) return false;
	}
	return true;
}

int getRotationColumn(std::vector<float> target_function_coeffs) {
	int rotation_column = 1;
	const int table_x_variables_offset = 1;
	for (int variable_index = 0; variable_index < static_cast<int>(target_function_coeffs.size()); variable_index++) {
		if (target_function_coeffs[variable_index] < 0) {
			rotation_column = variable_index + table_x_variables_offset;
			break;
		}
	}
	return rotation_column;
}

int getRotationRow(std::vector<std::vector<float>> table, int rotation_column) {
	std::vector<float> ratios = {};
	table.erase(table.begin()); //nie przeprowadzamy obrotu w pierwszym wierszu; usuwam go
		for (std::vector<float> row : table) {
			ratios.push_back(row[0] / row[rotation_column]);
	}
	std::vector<float> ratios_filtered = {}; //ilorazy wierszy, w kt�rych wsp�czynnik w kolumnie obrotu jest dodatni
	for (int tested_row = 0; tested_row < static_cast<int>(table.size()); tested_row++) {
		if (table[tested_row][rotation_column] > 0) {
			ratios_filtered.push_back(ratios[tested_row]);
		}
	}
	float minimum_ratio = *std::min_element(std::begin(ratios_filtered), std::end(ratios_filtered));
	const int restrictions_begin_offset = 1; //ograniczenia zaczynaj� si� jeden wiersz poni�ej funkcji celu
	for (
		int minimal_ratio_row_index = 0;
		minimal_ratio_row_index < static_cast<int>(ratios.size());
		minimal_ratio_row_index++
		)
	{
		if (ratios[minimal_ratio_row_index] == minimum_ratio) {
			return minimal_ratio_row_index + restrictions_begin_offset;
		}
	}
	return -1;
}

std::vector<std::vector<float>> 
	linear_programming::solveProblem(std::vector<std::vector<float>> table) {
	if (!linear_programming::isBase(table)) {
		throw std::invalid_argument("Tablica nie jest w postaci bazowej");
	}
	std::vector<std::vector<float>> current_table = table;
	std::vector<std::vector<float>> current_table_rotated = table;
	while (true) {
		std::vector<float> target_function_row = current_table[0];
		target_function_row.erase(target_function_row.begin()); //usuwam -d
		if (targetFunctionHasPositiveCoefficientsOnly(target_function_row)) break;
		int rotation_column = getRotationColumn(target_function_row);
		int rotation_row = getRotationRow(current_table, rotation_column);
		current_table_rotated = linear_programming::rotateTable(
			current_table, rotation_row, rotation_column);
		current_table = current_table_rotated;
	}
	return current_table;
}


std::vector<int> linear_programming::getIdentityMatrix(std::vector<std::vector<float>> table) {
	const int no_identity_value_index = -1;
	std::vector<std::vector<float>> table_columns = transpose(table);
	std::vector<int> column_identity_value_position{};
	for (int column = 0; column < static_cast<int>(table_columns.size()); column++) {
		column_identity_value_position.push_back(no_identity_value_index);
	}
	for (int column_index = 0;
		column_index < static_cast<int>(table_columns.size());
		column_index++) {
		for (int row_index = 0; row_index < static_cast<int>(table_columns[column_index].size()); row_index++) {
			float value = table_columns[column_index][row_index];
			if (value != 0 && value != 1) {
				column_identity_value_position[column_index] = no_identity_value_index;
				break;
			}
			if (value == 1) {
				if (column_identity_value_position[column_index] != no_identity_value_index) {
					column_identity_value_position[column_index] = no_identity_value_index;
					break;
				}
				else {
					column_identity_value_position[column_index] = row_index;
				}
			}
		}
	}
	/*
	uzyskanie indeks�w wierszy, w kt�rych znajduj� si� jedynki macierzy jednostkowej
	*/
	std::vector<int> column_identity_value_position_filtered = column_identity_value_position;
	std::vector<int>::iterator ip;
	int vector_size = static_cast<int>(column_identity_value_position_filtered.size());
	std::sort(column_identity_value_position_filtered.begin(), column_identity_value_position_filtered.begin() + vector_size);
	ip = std::unique(column_identity_value_position_filtered.begin(), column_identity_value_position_filtered.end());
	column_identity_value_position_filtered.resize(std::distance(column_identity_value_position_filtered.begin(), ip));
	if (column_identity_value_position_filtered[0] == no_identity_value_index) {
		column_identity_value_position_filtered.erase(column_identity_value_position_filtered.begin());
	}
	int identity_matrix_column_amount = static_cast<int>(column_identity_value_position_filtered.size());
	int table_row_amount = static_cast<int>(table.size());
	if (identity_matrix_column_amount < table_row_amount) {
		return {};
	}
	else {
		std::vector<int> identity_indices{};
		int table_column_amount = static_cast<int>(table_columns.size());
			for (int identity_row_index : column_identity_value_position_filtered) {
				for (int column_index = 0; column_index < table_column_amount; column_index++) {
					if (column_identity_value_position[column_index] == identity_row_index) {
						identity_indices.push_back(column_index);
						break;
					}
				}
			}
			return identity_indices;
	}
}
