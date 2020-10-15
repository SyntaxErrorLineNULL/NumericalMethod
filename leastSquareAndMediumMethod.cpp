#define PolinomynalPower 3
using namespace std;

template<typename T> std::vector<std::vector<T>> MethodleastSquare(std::vector<T>& ArrayX, std::vector<T>& ArrayY) {

    size_t Size = (int) ArrayX.size();

    if (Size == 0)
        throw string("Empty matrix");

    std::vector<std::vector<double>> Solution(Size);


    return Solution;

}

template<typename T> std::vector<std::vector<T>> MethodMediumSquare(std::vector<T>& ArrayX, std::vector<T>& ArrayY) {

    size_t Size = (int)ArrayX.size();

    if (Size == 0)
        throw string("Empty matrix");


    std::vector<std::vector<T>> Matrix(Size);

    int NumberofEquations = Size / PolinomynalPower;
    int NumberofExtraEquations = Size % PolinomynalPower;
    int NumberofExtraEquationsTMP = NumberofEquations;
    int NumberofExtraEquationsCounter = 0;

    if (NumberofExtraEquations)
        NumberofExtraEquationsTMP++;

    for(int i = 0; i < PolinomynalPower; i++) {
        for(int j = 0; j < PolinomynalPower; j++) {
            if(!NumberofExtraEquations) {
                if(NumberofExtraEquationsCounter = NumberofExtraEquations)
                    NumberofExtraEquationsTMP = NumberofEquations;
            }
            Matrix.resize(Size + 1);
            for (int k = 0; k < NumberofExtraEquationsTMP; k++) {
                Matrix[i][0] += pow(ArrayX[i * NumberofEquations + k + NumberofExtraEquationsCounter], j);

            }
        }


        for(int k = 0; k < NumberofExtraEquationsCounter; k++) {
            Matrix[i][0] += ArrayY[i * NumberofEquations + k + NumberofExtraEquationsCounter];
        }

        if (NumberofExtraEquationsCounter != NumberofExtraEquations) {
            NumberofExtraEquationsCounter++;

        }
    }

    size_t n = Matrix.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << Matrix[i][j];
        }
    }

    return Matrix;

}

template<typename T>
vector<T> GaussSolving(vector<vector<T>> &Matrix, double &Coeff) {
    size_t Size = Matrix.size();

    for (int i = 0; i < Size; i++) {
        // Search for maximum in this column
        double maxEl = abs(Matrix[i][i]);
        int maxRow = i;
        for (int j = i + 1; j < Size; j++) {
            if (abs(Matrix[j][i]) > maxEl) {
                maxEl = abs(Matrix[j][i]);
                maxRow = j;
            }
        }

        // Swap maximum row with current row (column by column)
        for (int k = i; k < Size + 1; k++) {
            T tmp = Matrix[maxRow][k];
            Matrix[maxRow][k] = Matrix[i][k];
            Matrix[i][k] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int k = i + 1; k < Size; k++) {
            T c = -Matrix[k][i] / Matrix[i][i];
            for (int j = i; j < Size + 1; j++) {
                if (i == j) {
                    Matrix[k][j] = 0;
                }
                else {
                    Matrix[k][j] += c * Matrix[i][j];
                }
            }
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    vector<T> Solution(Size);
    for (int i = Size - 1; i >= 0; i--) {
        Solution[i] = Matrix[i][Size] / Matrix[i][i];
        for (int k = i - 1; k >= 0; k--) {
            Matrix[k][Size] -= Matrix[k][i] * Solution[i];
        }
    }

    cout << "Result:\t";
    for (int i = 0; i < Size; i++)
        cout << Solution[i] << " ";

    cout << endl;



    return Solution;
}

int main() {

    /* Ok, add boost and create boost unit test */
    /* Test unit */

    std::vector<double> ArrayX = {2.7, 4.05, 5.4, 6.75, 8.1, 9.45};
    std::vector<double> ArrayY = {3.78, 9.05, 17.23, 28.33, 50.44, 59.27};

    //MethodMediumSquare(ArrayX, ArrayY);

    std::vector<std::vector<double>> Matrix = {
            {2.0, 6.71, 23.69, 12.83},
            {2.0, 12.15, 74.72, 45.56},
            {2.0, 17.55, 154.91, 109.71}
    };

    double Coeff = 3.375;

    GaussSolving(Matrix, Coeff);

    system("pause");
    return 0;
}