#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

void main()
{

    setlocale(LC_ALL, "Russian");
    int size;
    cout << "Введите размер матриц" << endl;
    cin >> size;
    TMatrix<int> a(size), b(size), c(2), d(2);
    int i, j;

    for (i = 0; i < size; i++)
        for (j = i; j < size; j++)
        {
            int q, w;
            cout << "Введите " << j + 1 << " элемент " << i + 1 << " строки первой матрицы." << endl;
            cin >> q;
            cout << "Введите " << j + 1 << " элемент " << i + 1 << " строки второй матрицы." << endl;
            cin >> w;
            a[i][j] = q;
            b[i][j] = w;
        }
    c = a + b;
    cout << "Matrix a = " << endl << a << endl;
    cout << "Matrix b = " << endl << b << endl;
    cout << "Matrix c = a + b" << endl << c << endl;
    d = a - b;
    cout << "Matrix d = a - b" << endl << d << endl;
    if (a == b)
    {
        cout << "Матрицы a и b равны." << endl;
    }
    if (a != b)
    {
        cout << "Матрицы a и b не равны." << endl;
    }
}