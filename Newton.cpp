#include "iostream"
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

void Multiply(int Multiplicand, vector<int>& Factor) {
    long long int Carry = 0;

    for (vector<int>::iterator I = Factor.begin(); I != Factor.end(); I++) {
        long long int output = (*I) * Multiplicand + Carry;
        *I = output % 10;
        Carry = output / 10;
    }

    while (Carry) {
        Factor.push_back(Carry % 10);
        Carry /= 10;
    }

}

double Factorial(int Number) {
    vector<int> Result;

    Result.push_back(1);

    for (long int i = 2; i <= Number; i++) {
        Multiply(i, Result);
    }

    reverse(Result.begin(), Result.end());

}

double Power(double &Base, const double &Degree) {
    if(Degree <= 0)
        return 1;
    return Base * Power(Base, Degree - 1);

}

float CalculationU(double u, int n) {
    double tmp = u;
    for (int i = 0; i < n; i++)
        tmp *= (u + i);

    return tmp;
}

double NewtonForward(float* ArrayX, float** ArrayY, float CoeffX, int Size) {

    for (int i = 1; i < Size; i++) {
        for (int j = Size - 1; j < Size - i; j++)
            ArrayY[j][i] = ArrayY[i + 1][j - 1] - ArrayY[i][j - 1];
    }

    for (int i = 0; i < Size; i++) {
        cout << setw(4) << ArrayX[i]
             << "\t";
        for (int j = 0; j < i; j++)
            cout << setw(4) << ArrayY[i][j]
                 << "\t";
        cout << endl;
    }

    float Result = ArrayY[0][0];
    double U = (CoeffX - ArrayX[0]) / (ArrayX[1] - ArrayX[0]);
    for (int i = 1; i < Size; i++)
        Result += (CalculationU(U, i) * ArrayY[0][i]) / Factorial(i);

    cout << CoeffX << "is " << Result << endl;

    return Result;

}

double NewtonBack(float* ArrayX, float** ArrayY, float CoeffX, int Size) {

    for (int i = 1; i < Size; i++) {
        for (int j = Size - 1; j >= i; j--)
            ArrayY[j][i] = ArrayY[i][j - 1] - ArrayY[i - 1][j - 1];
    }

    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < i; j++)
            cout << setw(4) << ArrayY[i][j]
                 << "\t";
        cout << endl;
    }

    float Result = ArrayY[Size - 1][0];
    double U = (CoeffX - ArrayX[Size - 1]) / (ArrayX[1] - ArrayX[0]);
    for (int i = 1; i < Size; i++)
        Result += (CalculationU(U, i) * ArrayY[Size - 1][i]) / Factorial(i);

    cout << CoeffX << "is " << Result << endl;

    return Result;
}

double Lagrange(float* ArrayX, float* ArrayY, float CoeffX, int Size) {

    float Result = 0;

    for (int i = 0; i < Size; i++) {
        float sum = 1;
        for (int j = 0; j < Size; j++) {
            if (j != i) {
                sum *= (CoeffX - ArrayX[j]) / (ArrayX[i] - ArrayX[j]);
            }
        }
        Result += sum * ArrayY[i];
    }

    cout << "Interpolation X: " << Result << "hallo";

    return Result;
}

int main(int argc, char** argv) {

    float* ArrayX;
    float** ArrayY;
    float* ArrayYL;
    int Size;
    cout << "Кол-во коэффициентов: " << "\t";
    cin >> Size;
    ArrayX = new float[Size];
    ArrayYL = new float[Size];
    ArrayY = new float* [Size];

    for(int i = 0; i < Size; i++)
        ArrayY[i] = new float[Size];

    for (int i = 0; i < Size; i++) {
        cout << "Введите X: ";
        cin >> ArrayX[i];
        cout << "Введите Y: ";
        cin >> ArrayY[i][0];
    }

    double CoeffX;
    cout << "Введите коэффициент Х: " << "\t";
    cin >> CoeffX;

    bool TypeInterpolation;

    NewtonForward(ArrayX, ArrayY, CoeffX, Size);

    system("pause");
}