#include <fstream>
#include "dichotomy.h"

std::ofstream foutDichotomy;
int functionCallsNumberDichotomy = 0;


Limits dichotomyGetNewLimits(Limits limits, double eps) {
    double c = (limits.a + limits.b) / 2;
    double x1 = c - eps / 3;
    double x2 = c + eps / 3;
    double f1 = f(x1);
    functionCallsNumberDichotomy++;
    double f2 = f(x2);
    functionCallsNumberDichotomy++;

    if (f1 > f2)
        return Limits{x1, limits.b};
    else if (f1 < f2)
        return Limits{limits.a, x2};
    return Limits{x1, x2};
}

bool isEnough(Limits limits) {
    return std::abs(limits.a - limits.b) < epsilon;
}

double dichotomyGetMinimum(Limits limits, double eps, std::string file) {
    foutDichotomy.open(file);
    foutDichotomy.clear();

    int iteration = 0;

    while (!isEnough(limits)) {
        limits = dichotomyGetNewLimits(limits, eps);

        foutDichotomy << ++iteration << ";\t" << limits.a << ";\t" << limits.b << ";\t" << functionCallsNumberDichotomy
                      << "\n";
    }

    foutDichotomy.close();
    return limits.a;
}