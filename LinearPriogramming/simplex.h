#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>
#include <algorithm>



namespace linear_programming{
	bool table_isUniformSize(std::vector<std::vector<float>> table);
	bool isBase(std::vector<std::vector<float>> table);
	bool isOptimal(std::vector<std::vector<float>> table);
	std::vector<std::vector<float>> 
		solveSubproblem(std::vector<std::vector<float>> table,
			int subproblem_indices[ ]);
	std::vector<std::vector<float>> rotateTable(std::vector<std::vector<float>> table, int rotation_row, int rotation_column);
	std::vector<std::vector<float>> 
		retrieveAMatrix(std::vector<std::vector<float>> table);
	std::vector<int> getIdentityMatrix(std::vector<std::vector<float>> b_matrix);
}

namespace matrix_ops {
	constexpr int NON_IDENTITY_MATRIX_VALUE_WEIGHT = 2;
	std::vector<std::vector<float>> transpose_direction(std::vector<std::vector<float>> matrix);
}



#endif // !SIMPLEX_H
