#ifndef MATRIX_H
#define MATRIX_H

#include <vector>


class Matrix
{
public:
    double At(int row, int column) const; // получить элемент по индексам

protected:
    int rows; // число строк
    int cols; // число столбцов
    std::vector< std::vector<double> > matrix; // данные
};

#endif // MATRIX_H
