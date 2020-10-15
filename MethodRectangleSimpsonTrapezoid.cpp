#include <vector>
using namespace std;

double f(double x) {
    return sin(x);
}

double MethodRectangleLeft(double a, double b, int n /*const std::function<double (double)> &f*/) {

    const double gridPitch = (b - a) / n;

    double RectangleLeft = 0.0;
    for (int step = 0; step < n-1; step++) {
        const double x = a + step * gridPitch;

        RectangleLeft += f(x);
    }

    return RectangleLeft;
}

double MethodRectangleRight(double a, double b, int n /*const std::function<double (double)> &f*/) {

    const double gridPitch = (b - a) / n;

    double RectangleRight = 0.0;
    for (int step = 0; step < n; step++) {
        const double x = a + step * gridPitch;

        RectangleRight += f(x);
    }

    return RectangleRight;
}

double MethodRectangleMedium(double a, double b, int n /*const std::function<double (double)> &f*/) {

    const double gridPitch = (b - a) / n;

    double RectangleMedium = 0.0;
    for (int step = 0; step < n; step++) {
        const double x = a + step / 2 * gridPitch;

        RectangleMedium += gridPitch * f(x) ;
    }

    return RectangleMedium;
}

double SimpsonMethod(double a, double b, int n /*const std::function<double (double)> &f*/) {

    const double width = (b - a) / n;

    double SimpsonIntegral = 0.0;

    for(int step = 0; step < n; step++) {
        const double x1 = a + step * width;
        const double x2 = a + (step + 1) * width;

        SimpsonIntegral += (x2 - x1) / 6.0 * (f(x1) + 4.0 * f(0.5 * (x1 + x2)) + f(x2));
    }

    return SimpsonIntegral;
}

double TrapezoidMethod(double a, double b, int n /*const std::function<double (double)> &f*/) {

    const double width = (b - a) / n;

    double TrapezoidIntegral = 0.0;
    for (int step = 0; step < n; step++) {
        const double x1 = a + step * width;
        const double x2 = a + (step + 1) * width;

        TrapezoidIntegral += 0.5 * (x2 - x1) * (f(x1) + f(x2));
    }

    return TrapezoidIntegral;
}

vector<vector<double>> RombergMethod(double a, double b, size_t n) {

    vector<vector<double>> RombergIntegral(n, vector<double>(n));

    RombergIntegral.front().front() = TrapezoidMethod(a, b, 1);

    double width = b - a;

    for (size_t step = 1; step < n; step++) {
        width *= 0.5;

        double TrapezoidIntegral = 0.0;
        size_t stepEnd = pow(2, step - 1);

        for (size_t TrapezoidStep = 1; TrapezoidStep < stepEnd; TrapezoidStep++) {
            const double deltaX = (2 * TrapezoidStep - 1) * width;
            TrapezoidIntegral += f(a + deltaX);
        }

        RombergIntegral[step].front() = 0.5 * RombergIntegral[step - 1].front() + TrapezoidIntegral * width;

        for (size_t RombergStep = 1; RombergStep < n; RombergStep++) {
            const double K = pow(4, RombergStep);

            RombergIntegral[step][RombergStep] = (K * RombergIntegral[step][RombergStep - 1] - RombergIntegral[step - 1][RombergStep - 1]) / (K - 1);
        }

    }

    return RombergIntegral;

}