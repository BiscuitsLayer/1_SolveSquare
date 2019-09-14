#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define INF -1
#define EPS 1e-4

int SolveSquare(double a, double b, double c, double *x1, double *x2);
int SolveLinear(double a, double b, double *x1);
void UnitTests(void);

int main() {
    UnitTests();
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    int res = scanf("%lg %lg %lg", &a, &b, &c);
    if (res != 3) {
        printf("Something wrong has happened\n");
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
        printf("Something wrong has happened\n");
    return 0;
}

void UnitTests () {
    double x1 = 0, x2 = 0;
    assert(SolveSquare(1, 4, 4, &x1, &x2) == 1);
    assert(x1 == -2.0);
    printf("Test 1 Completed\n");
}

int SolveLinear (double a, double b, double *x1) {
    if (a == 0)
        return (b == 0 ? INF : 0);
    *x1 = (-1 * b) / a;
    return 1;
}

int SolveSquare (double a, double b, double c, double *x1, double *x2) {
    assert(x1 != x2);
    assert(x1 != NULL && x2 != NULL);
    assert(isfinite(a) && isfinite(b) && isfinite(c));

    if (a == 0)
        return SolveLinear(b, c, x1);
    double D = b * b - 4 * a * c;
    if (D < 0 && abs(D) > EPS)
        return 0;
    D = sqrt(D);
    if (abs(D) < EPS) {
        *x1 = (-1 * b) / (2 * a);
        return 1;
    } else {
        *x1 = (-1 * b + D) / (2 * a);
        *x2 = (-1 * b - D) / (2 * a);
        return 2;
    }
}