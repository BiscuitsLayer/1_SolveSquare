#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define INF -1

#define EPS 1e-3

#define \
ASSERT(_a, _b, _c, nRoots, _x1, _x2)                      \
    assert(SolveSquare(_a, _b, _c, &x1, &x2) == nRoots && \
          (abs(_x1 - x1) < EPS)                        && \
          (abs(_x2 - x2) < EPS)),                         \
          x1 = 0, x2 = 0

int SolveSquare(double a, double b, double c, double *x1, double *x2);
int SolveLinear(double a, double b, double *x1);
void UnitTests(void);

int main() {
    UnitTests();

    double a = 0.0, b = 0.0, c = 0.0, x1 = 0.0, x2 = 0.0;
    int res = scanf("%lg %lg %lg", &a, &b, &c);
    if (res != 3) {
        printf("Wrong input\n");
        return 0;
    }
    res = SolveSquare(a, b, c, &x1, &x2);
    if (res == 0)
        printf("No roots\n");
    else if (res == 1)
        printf("One root: %.3f", x1);
    else if (res == 2)
        printf("Two roots: %.3f and %.3f", x1, x2);
    else if (res == INF)
        printf("Infinitely many roots\n");
    else
        printf("Something wrong has happened)\n");
    return 0;
}

//! \brief Unit Tests for quadratic equation

void UnitTests () {
    double x1 = 0.0, x2 = 0.0;
    ASSERT(0, 0, 0, INF, x1, x2);
    ASSERT(1, 3.999999999, 3.999999999, 1, -2, 0);
    ASSERT(0, 0, 1, 0, 0, 0);
    ASSERT(0, 1, -1, 1, 1, 0);
    ASSERT(1, -1, 0, 2, 1, 0);
    printf("Unit Tests Completed\n");
}

//! \brief Solves linear equation: a*x + b = 0
//! \param [in] a The first coef.
//! \param [in] b The second coef.
//! \param [out] x1 The only root (if exists)
//! \return Number of roots

int SolveLinear (double a, double b, double *x1) {
    assert (isfinite (a));
    assert (isfinite (b));
    assert (x1 != nullptr);

    if (a == 0)
        return (b == 0 ? INF : 0);
    *x1 = (-1 * b) / a;
    return 1;
}

//! \brief Solves quadratic equation a*x^2 + b*x + c = 0
//! \param [in] a The first coef.
//! \param [in] b The second coef.
//! \param [in] c The third coef.
//! \param [out] x1 The first root (if exists)
//! \param [out] x2 The second root (if exists)
//! \return Number of roots

int SolveSquare (double a, double b, double c, double *x1, double *x2) {
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(x1 != nullptr);
    assert(x2 != nullptr);
    assert(x1 != x2);

    if (a == 0)
        return SolveLinear(b, c, x1);
    double D = b * b - 4 * a * c;
    if (D < 0 && fabs(D) > EPS)
        return 0;
    D = sqrt(fabs(D));
    if (D < EPS) {
        *x1 = (-1 * b) / (2 * a);
        return 1;
    } else {
        *x1 = (-1 * b + D) / (2 * a);
        *x2 = (-1 * b - D) / (2 * a);
        return 2;
    }
}
