#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

std::vector<int> piecesCounts = {10, 100, 1000, 10000, 100000, 1000000};

const double A = 0.5;
const double B = 3;
const auto F = [](const double x){ return std::exp(x) / x; };
const double boundPoint = 1;

double lowerSumIteration(const double tauPrev, const double tau, const double dTau) {
    if (tau < boundPoint) {
        return dTau * F(tau);
    } else if (tauPrev > boundPoint) {
        return dTau * F(tauPrev);
    }
    return dTau * F(boundPoint);
}

double upperSumIteration(const double tauPrev, const double tau, const double dTau) {
    if (tau < boundPoint) {
        return dTau * F(tauPrev);
    } else if (tauPrev > boundPoint) {
        return dTau * F(tau);
    }
    return dTau * std::max(F(tauPrev), F(tau));
}

int main() {
    int64_t n = 1;
    double lowerSum;
    double upperSum;
    do {
        lowerSum = 0;
        upperSum = 0;
        n *= 10;
        double tauPrev;
        double tau = A;
        const double dTau = (B - A) / n;
        for (int i = 0; i < n; ++i) {
            tauPrev = tau;
            tau += dTau;
            lowerSum += lowerSumIteration(tauPrev, tau, dTau);
            upperSum += upperSumIteration(tauPrev, tau, dTau);
        }
        std::cout << std::fixed << std::setprecision(6) << n << ": " << upperSum - lowerSum << std::endl;
    } while (upperSum - lowerSum > 1e-4);
    std::cout << lowerSum << std::endl;
}
