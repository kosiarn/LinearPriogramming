#include "pch.h"
#include "simplex.h"

std::vector<std::vector<float>> transpose(std::vector<std::vector<float>>& A) {
	int rows = A.size();
	if (rows == 0) return { {} };
	int cols = A[0].size();
	std::vector<std::vector<float>> r(cols, std::vector<float>(rows));
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
	std::vector<int> identity_matrix_columns = getIdentityMatrix(a_matrix);
	if (identity_matrix_columns.empty()) return false;
	std::vector<float> target_function_coefficients = table[0];
	target_function_coefficients.erase(target_function_coefficients.begin()); //deleting -d
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


std::vector<int> linear_programming::getIdentityMatrix(std::vector<std::vector<float>> input_matrix)
{
	std::vector<std::vector<float>> a_matrix = transpose(input_matrix); //we want data in columns
	int matrix_width = static_cast<int>(a_matrix.size());
	std::vector<int> column_is_from_identity{};
	for (int i = 0; i < matrix_width; i++) {
		column_is_from_identity.push_back(0);
	}
	//for values different than one we add a weight bigger than one
	//the idea is that if we get value above 1, then it can't be a column of
	//identity matrix.
	int row_amount = static_cast<int>(a_matrix[0].size());
	for (int i = 0; i < matrix_width; i++) {
		for (int j = 0; j < row_amount; j++) {
			if (a_matrix[i][j] == static_cast<float>(1)) column_is_from_identity[i] +=1;
			else if (a_matrix[i][j] == static_cast<float>(0)) column_is_from_identity[i] +=0;
			else column_is_from_identity[i] +=matrix_ops::NON_IDENTITY_MATRIX_VALUE_WEIGHT; 
		}
	}
	std::vector<int> identity_indices{};
	for (int i = 0; i < matrix_width; i++) {
		if (column_is_from_identity[i] == 1) identity_indices.push_back(i);
	}
	//return column_is_from_identity;
	if (static_cast<int>(column_is_from_identity.size()) < row_amount) return {};
	std::vector<int> identity_ones_positions{};
	for (auto &index : identity_indices) {
		for (int row_index = 0; row_index < row_amount; row_index++) {
			if (a_matrix[index][row_index] == 1) {
				identity_ones_positions.push_back(row_index);
				continue;
			}
		}
	}
	
	std::sort(identity_ones_positions.begin(), identity_ones_positions.end());
	
	for (int n = 0; n < static_cast<int>(identity_ones_positions.size()) - 1; n++) {
		if (identity_ones_positions[n + 1] != identity_ones_positions[n] + 1)
		{
			return {};
		}
	}
	return identity_indices;
}
