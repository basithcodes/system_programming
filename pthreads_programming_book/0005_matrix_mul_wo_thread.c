#include <stdio.h>

#define SIZE_OF_ROW 2
#define SIZE_OF_COLUMN 2

typedef int matrix_t[SIZE_OF_ROW][SIZE_OF_COLUMN];
matrix_t MA, MB, MC;

void mult(int size, int row, int column, matrix_t MA, matrix_t MB, matrix_t MC);
void print_2d_matrix(int row, int column, matrix_t MA);

// I want to store number of matrices I declared into a variable
matrix_t *M[3] = {
	&MA, &MB, &MC
};

int main(void) {
	int size = SIZE_OF_ROW, row, column;
	int i, j, count = 0;

	// Scanning the values into matrix variables
	for (i = 0; i < SIZE_OF_ROW; ++i) {
		for (j = 0; j < SIZE_OF_COLUMN; ++j) {
			MA[i][j] = MB[i][j] = ++count;
		}
	}

	// Operating on matrices
	for (row = 0; row < SIZE_OF_ROW; row++) {
		for (column = 0; column < SIZE_OF_COLUMN; column++) {
			mult(size, row, column, MA, MB, MC);
		}
	}

	// Printing the result
	print_2d_matrix(SIZE_OF_ROW, SIZE_OF_COLUMN, MC);

	return 0;
}

void mult(int size, int row, int column, matrix_t MA, matrix_t MB, matrix_t MC) {
	int position;
	MC[row][column] = 0;
	for (position = 0; position < size; position++) {
		MC[row][column] = MC[row][column] + (MA[row][position] * MB[position][column]);
	}
}

void print_2d_matrix(int row, int column, matrix_t M) {
	int i, j;
	for (i = 0; i < row; ++i) {
		for (j = 0; j < column; ++j) {
			printf("%8d", M[i][j]);
		}
		printf("\n");
	}
}
