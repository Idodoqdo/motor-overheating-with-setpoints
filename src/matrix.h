#ifndef SRC__MATRIX_OOP_H_
#define SRC__MATRIX_OOP_H_
#include <iostream>
#include <math.h>

#define EPS 1e-7

class Matrix {
 private:
    unsigned int rows = 3, cols = 3;
    double ** matrix;

 public:
    Matrix(unsigned int r, unsigned int c);

    Matrix();

    Matrix(const Matrix &other);

    Matrix(Matrix&& other);

    ~Matrix();

    void operator = (const Matrix &other);

    Matrix operator + (const Matrix &other);

    Matrix operator - (const Matrix &other);

    Matrix operator * (const Matrix &other);

    Matrix operator * (const double);

    bool operator == (const Matrix &other);

    void operator += (const Matrix &other);

    void operator -= (const Matrix & other);

    void operator *= (const Matrix & other);

    void operator *= (const double num);

    double & operator ()(unsigned int i, unsigned int j);

    void operator = (Matrix &&other);

    bool eq_matrix(const Matrix& other);

    void sum_matrix(const Matrix& other);

    void sub_matrix(const Matrix& other);

    void mul_number(const double num);

    void mul_matrix(const Matrix& other);

    Matrix transpose();

    Matrix minor(unsigned int i, unsigned int j);

    double determinant();

    Matrix calc_complements();

    Matrix inverse_matrix();

    int get_rows() const;

    int get_cols() const;
};

Matrix::~Matrix() {
    for (unsigned int i = 0; i < rows; i++)
    delete [] matrix[i];
    delete [] matrix;
    matrix = nullptr;
}

Matrix::Matrix(unsigned int r, unsigned int c) {
        rows = r;
        cols = c;
        matrix = new double *[r]();
        for (unsigned int i = 0; i < r; i++) {
        matrix[i] = new double[c]();
        }
}

Matrix::Matrix() {
    rows = 3;
    cols = 3;
    matrix = new double *[rows]();
    for (unsigned int i = 0; i < rows; i++) {
    matrix[i] = new double[cols]();
    }
}



Matrix::Matrix(Matrix &&other) {
    matrix = other.matrix;
    cols = other.cols;
    rows = other.rows;
    other.matrix = nullptr;
    other.cols = 0;
    other.rows = 0;
}

void Matrix::operator = (Matrix &&other) {
    for (unsigned int i = 0; i < rows; i++) {
    delete [] matrix[i];
    }
    delete [] matrix;
    matrix = other.matrix;
    cols = other.cols;
    rows = other.rows;
    other.matrix = nullptr;
    other.cols = 0;
    other.rows = 0;
}

int Matrix::get_rows() const {
    return rows;
}

int Matrix::get_cols() const {
    return cols;
}

void Matrix::operator = (const Matrix &other) {
if (this != &other) {
for (unsigned int i = 0; i < rows; i++) {
    delete [] matrix[i];
}
    delete [] matrix;
    cols = other.cols;
    rows = other.rows;
    matrix = new double *[other.rows]();
    for (unsigned int i = 0; i < other.rows; i++) {
        matrix[i] = new double[other.cols]();
        for (unsigned int j = 0; j < other.cols; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}
}

Matrix Matrix::operator + (const Matrix & other) {
    Matrix C = *this;
    C.sum_matrix(other);
    return C;
}

Matrix Matrix::operator - (const Matrix & other) {
    Matrix C = *this;
    C.sub_matrix(other);
    return C;
}

Matrix Matrix::operator * (const Matrix & other) {
    Matrix C = *this;
    C.mul_matrix(other);
    return C;
}

Matrix Matrix::operator * (const double num) {
    Matrix C = *this;
    C.mul_number(num);
    return C;
}

bool Matrix::operator==(const Matrix &other) {
    return eq_matrix(other);
}

void Matrix::operator+=(const Matrix &other) {
    return sum_matrix(other);
}

void Matrix::operator-=(const Matrix &other) {
    return sub_matrix(other);
}

void Matrix::operator*=(const Matrix &other) {
    return mul_matrix(other);
}

void Matrix::operator*=(const double num) {
    return mul_number(num);
}

double & Matrix::operator ()(unsigned int i, unsigned int j) {
    if (i >= rows || j >= cols) {
        throw std::out_of_range("Matrix indices entered incorrectly");
    }
    return matrix[i][j];
}

Matrix::Matrix(const Matrix &other) {
    cols = other.cols;
    rows = other.rows;
    matrix = new double *[other.rows]();
    for (unsigned int i = 0; i < other.rows; i++) {
        matrix[i] = new double[other.cols]();
        for (unsigned int j = 0; j < other.cols; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

bool Matrix::eq_matrix(const Matrix & other) {
bool flag = true;
if (rows == other.rows && cols == other.cols) {
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            if (abs(matrix[i][j] - other.matrix[i][j]) >= 0.000001) {
                flag = false;
                break;
            }
        }
    }
} else {
    flag = false;
}
return flag;
}

bool equal(const Matrix &first, const Matrix &second) {
    bool flag = true;
    if (first.get_cols() != second.get_cols() || first.get_rows() != second.get_rows()) flag = false;
    return flag;
}

void Matrix::sum_matrix(const Matrix& other) {
    if (equal(*this, other)) {
        for (unsigned int i = 0; i < other.rows; i++) {
            for (unsigned int j = 0; j < other.cols; j++) {
                matrix[i][j] += other.matrix[i][j];
            }
        }
    }
}

void Matrix::sub_matrix(const Matrix& other) {
    if (equal(*this, other)) {
         for (unsigned int i = 0; i < other.rows; i++) {
            for (unsigned int j = 0; j < other.cols; j++) {
                matrix[i][j] -= other.matrix[i][j];
            }
        }
    }
}

void Matrix::mul_number(const double num) {
    for (unsigned int i = 0; i < rows; i++) {
       for (unsigned int j = 0; j < cols; j++) {
           matrix[i][j] *= num;
       }
    }
}

void Matrix::mul_matrix(const Matrix& other) {
  Matrix C(rows, other.cols);
  for (unsigned int i = 0; i < C.rows; i++) {
    for (unsigned int j = 0; j < C.cols; j++) {
        for (unsigned int k = 0; k < other.rows; k++) {
            C.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
        }
    }
  }
  *this = std::move(C);
}

Matrix Matrix::transpose() {
    Matrix B(cols, rows);
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            B.matrix[j][i] = matrix[i][j];
        }
    }
    return B;
}

Matrix Matrix::minor(unsigned int i, unsigned int j) {
    Matrix B(rows - 1, cols - 1);
    unsigned int str = 0;
    unsigned int stb = 0;
    for (unsigned int k = 0; k < rows; k++) {
        for (unsigned int m = 0; m < cols; m++) {
            if (k != i && m != j) {
                B.matrix[str][stb] = matrix[k][m];
                stb++;
                if (stb == cols - 1) str++;
            }
        }
        stb = 0;
    }
    return B;
}

double Matrix::determinant() {
    double rez = 0;
    if (rows == cols) {
        if (cols == 1) {
            rez = matrix[0][0];
        } else if (cols == 2) {
            rez = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
        } else {
            int i = 0;
            Matrix B;
            for (unsigned int j = 0; j < cols; j++) {
                B = minor(i, j);
                rez += pow(-1, i+j) * matrix[i][j] * B.determinant();
            }
        }
    }
    return rez;
}

Matrix Matrix::calc_complements() {
    Matrix C(rows, cols);
    if (rows == cols) {
        Matrix B;
        for (unsigned int i = 0; i < rows; i++) {
            for (unsigned int j = 0; j < cols; j++) {
                double rez = 0;
                B = minor(i, j);
                rez = pow(-1, i+j) * B.determinant();
                C.matrix[i][j] = rez;
            }
        }
    }
    return C;
}

Matrix Matrix::inverse_matrix() {
    Matrix B;
    if (rows == cols && determinant() != 0) {
        Matrix C = calc_complements();
        B = C.transpose();
        B.mul_number(1/determinant());
    }
    return B;
}

#endif  // SRC__MATRIX_OOP_H_
