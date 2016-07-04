#ifndef MATRIX_H
#define MATRIX_H

#include <vector>


class Matrix
{
public:
    double At(int row, int column) const; // �������� ������� �� ��������

protected:
    int rows; // ����� �����
    int cols; // ����� ��������
    std::vector< std::vector<double> > matrix; // ������
};

#endif // MATRIX_H
