#include "matrix.h"
#include <assert.h>


double Matrix::At(int row, int column) const
{
    assert(row >= 0 && row < rows);
    assert(column >= 0 && column < cols);
    return matrix[row][column];
}
