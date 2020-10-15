#include <iostream>
#include <vector>
#include <cmath>
#define Eps 0.00001
using namespace std;

std::vector<double> GaussSeidelMethod(std::vector<std::vector<double>> &Matrix) {

    size_t Size = Matrix.size();

    std::vector<long double> PreviousVariableValues(Size, 0.0);

    while(true){
        std::vector<long double> CurrentVariableValues(Size);

        for(int i = 0; i < Size; i++) {
            CurrentVariableValues[i] = Matrix[i][Size];
            for (int j = 0; j < Size; j++) {
                if(j < i) {
                    CurrentVariableValues[i] -= Matrix[i][j] * CurrentVariableValues[j];
                } else if (j > i) {
                    CurrentVariableValues[i] -= Matrix[i][j] * PreviousVariableValues[j];
                }
            }

            CurrentVariableValues[i] /= Matrix[i][i];
        }

        long double Infelicity = 0.0;

        for (int i = 0; i < Size; i++)
            Infelicity += abs(CurrentVariableValues[i] - PreviousVariableValues[i]);

        if(Infelicity < Eps)
            break;

        PreviousVariableValues = CurrentVariableValues;
    }

    for (int i = 0; i < Size; i++)
        std::cout << "x" << i << ":" << PreviousVariableValues[i] << endl;
}

std::vector<double> SimpleIteration(std::vector<std::vector<double>>& Matrix) {

    size_t Size = Matrix.size();
    // Введем вектор значений неизвестных на прошлой итерации. Размер которого равен числу строк в матрице
    std::vector<long double> PreviousVariableValues(Size, 0.0);
    // Итерации будут идти до тех пор, пока не достигнем нужной точности
    int count = 0;
    while(true) {
        // Введем вектор неизвестных на текущем шаге.
        std::vector<long double> CurrentVariableValues(Size);
        // Будем считать значение неизвестной на текущей итерации. 

        for (size_t i = 0; i < Size; i++) {
            CurrentVariableValues[i] = Matrix[i][Size];
            for (size_t j = 0; j < Size; j++) {
                // Будем вычиать сумму всех неизвестных отличимых от i-ой
                if (i != j)
                    CurrentVariableValues[i] -= Matrix[i][j] * PreviousVariableValues[j];
            }
            // Делим на коэффициент при i-ой неизвестной 
            CurrentVariableValues[i] /= Matrix[i][i];
        }
        // Считаем текущую погрешность относительно предыдущей итерации
        long double Infelicity = 0.0;

        for (int i = 0; i < Size; i++)
            Infelicity += abs(CurrentVariableValues[i] - PreviousVariableValues[i]);
        count++;
        if(Infelicity < Eps)
            break;
        // Переходим к следующей итерации, так что текущее значение становится значением на предыдущей итерации
        PreviousVariableValues = CurrentVariableValues;
    }
    // Выводим найденные значения
    for (size_t i = 0; i < Size; i++)
        std::cout << "x" << i << ":" << PreviousVariableValues[i] << "\n" << count;

}

int main(){
    setlocale(LC_ALL, "Russian");
    int Size;
    std::cout << "Размер матрицы: ";
    std::cin >> Size;
    std::vector<std::vector<double>> Matrix;
    Matrix.resize(Size);

    std::cout << "Введите коэффициенты и свободные вектора" << endl;
    for(int i = 0; i < Matrix.size(); i++) {
        Matrix[i].resize(Size + 1);
        std::cout << "Введите Следующую строку" << endl;
        for (int j = 0; j < Matrix[i].size(); j++) {
            std::cout << "Введите коэффициенты: ";
            std::cin >> Matrix[i][j];
        }
    }

    SimpleIteration(Matrix);

    Matrix.clear();

    system("pause");
    return 0;
}