#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;
class Matrix
{
public:
    Matrix() : row(0), col(0) {}
    Matrix(int num_rows, int num_cols)
    {
        Reset(num_rows, num_cols);
    }
    void Reset(int num_rows, int num_cols)
    {
        if (num_rows < 0 || num_cols < 0)
        {
            throw out_of_range("dimension can't be negative");
        }
        if (num_rows == 0 || num_cols == 0)
        {
            row = col = 0;
        }
        else
        {
            row = num_rows;
            col = num_cols;
        }
        matrix.assign(num_rows, vector<int>(num_cols));
    }
    int At(int row_idx, int col_idx) const
    {
        if (row_idx < 0 || row_idx >= row)
        {
            throw out_of_range("rows number is bigger than matrix size");
        }
        if (col_idx < 0 || col_idx >= col)
        {
            throw out_of_range("col number is bigger than matrix size");
        }

        return matrix[row_idx][col_idx];
    }
    int &At(int row_idx, int col_idx)
    {
        if (row_idx < 0 || row_idx >= row)
        {
            throw out_of_range("rows number is bigger than matrix size");
        }
        if (col_idx < 0 || col_idx >= col)
        {
            throw out_of_range("col number is bigger than matrix size");
        }
        return matrix[row_idx][col_idx];
    }
    int GetNumRows() const
    {
        return row;
    }
    int GetNumColumns() const
    {
        return col;
    }

private:
    int row;
    int col;
    vector<vector<int>> matrix;
};

istream &operator>>(istream &in, Matrix &matrix)
{
    int row, col;
    in >> row >> col;
    matrix.Reset(row, col);
    for (auto i = 0; i < row; i++)
    {
        for (auto j = 0; j < col; j++)
        {
            in >> matrix.At(i, j);
        }
    }
    return in;
}

ostream &operator<<(ostream &out, const Matrix &matrix)
{
    out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
    for (auto i = 0; i < matrix.GetNumRows(); i++)
    {
        for (auto j = 0; j < matrix.GetNumColumns(); j++)
        {
            out << matrix.At(i, j) << " ";
        }
        out << endl;
    }
    return out;
}

bool operator==(const Matrix &lhs, const Matrix &rhs)
{
    if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns())
    {
        return false;
    }
    for (auto i = 0; i < lhs.GetNumRows(); i++)
    {
        for (auto j = 0; j < lhs.GetNumColumns(); j++)
        {
            if (lhs.At(i, j) != rhs.At(i, j))
            {
                return false;
            }
        }
    }
    return true;
}
Matrix operator+(const Matrix &lhs, const Matrix &rhs)
{
    if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns())
    {
        throw invalid_argument("matrices of different dimensions cann't be added");
    }
    int row = lhs.GetNumRows();
    int col = lhs.GetNumColumns();
    Matrix matrix(row, col);
    for (auto i = 0; i < row; i++)
    {
        for (auto j = 0; j < col; j++)
        {
            matrix.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }
    return matrix;
}

int main()
{
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}