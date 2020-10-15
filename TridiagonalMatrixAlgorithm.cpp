#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void printArr(std::vector<double> Matrix) {
    for (int i = 0; i < Matrix.size(); i++) {
        cout << Matrix[i] << " ";
    }
    cout << endl;
}
/*
	System example:
	b[0] * x[0] + c[0] * x[1]                             = d[0]
	a[0] * x[0] + b[1] * x[1] + c[1] * x[2]               = d[1]
				  a[1] * x[1] + b[2] * x[2] + c[2] * x[3] = d[2]
								a[2] * x[2] + b[3] * x[3] = d[3]
*/
vector<double> TDMA(std::vector<std::vector<double>> &Matrix, std::vector<double> &FreeVector){
    size_t SizeMatrix = Matrix.size();
    std::vector<double> Alpha(SizeMatrix - 1);
    std::vector<double> Beta(SizeMatrix - 1);
    std::vector<double> Interim(SizeMatrix - 2);

    Alpha[0] = Matrix[0][1] / Matrix[0][0] * (-1);
    Beta[0] = FreeVector[0] / Matrix[0][0];

    for(int i = 0; i < SizeMatrix - 1; i++) {
        Interim[i - 1] = Matrix[i][i - 1] * Alpha[i - 1] + Matrix[i][i];
        Alpha[i] = Matrix[i][i+1] / Interim[i - 1] * (-1);
        Beta[i] = (FreeVector[i] - Matrix[i][i-1] * Beta[i - 1]) / Interim[i - 1];
    }

    std::vector<double> Result(SizeMatrix);

    Result[SizeMatrix - 1] = (FreeVector[SizeMatrix -1] - Matrix[SizeMatrix - 1][SizeMatrix - 2] * Beta[SizeMatrix - 2]) /
                             (Matrix[SizeMatrix - 1][SizeMatrix - 1] + Matrix[SizeMatrix - 1][SizeMatrix - 2] * Alpha[SizeMatrix - 2]);


    for (int i = SizeMatrix - 2; i > -1; i--) {
        Result[i] = Alpha[i] * Result[i + 1] + Beta[i];
    }

    for (auto& Row : Result) {
        std::cout << Row << endl;
    }
}

int main(int argc, char* argv) {
    setlocale(LC_ALL, "Russian");
    int Row, Col;
    cout << "Введите количество неизвестных: ";
    std::cin >> Row;
    Col = Row;
    std::vector<std::vector<double>> Matrix(Row, std::vector<double>(Col));
    std::vector<double> FreeVector(Row);

    std::cout << "Введите коэффициенты и свободные члены:" << endl;

    for(auto i = 0; i < Matrix.size(); i++) {
        for(auto j = 0; j < Matrix[i].size(); j++) {
            std::cout << "Коэффициент: ";
            std::cin >> Matrix[i][j];
        }
        std::cout << "Свободный вектор: ";
        std::cin >> FreeVector[i];
    }

    TDMA(Matrix, FreeVector);
    Matrix.clear();

    system("pause");
    return 0;
}