#include "assert.h"

#include "gcd.h"

int main()
{
    int a;
    int b;
    int x;
    int y;
    int gcd;

    a = 12;
    b = 45;
    assert(((gcd = gcdex(a, b, x, y)) == 3) && ((a * x + b * y) == gcd));

    a = -12;
    gcd = gcdex(a, b, x, y);
    assert(((gcd = gcdex(a, b, x, y)) == 3) && ((a * x + b * y) == gcd));

    a = -1071;
    b = -462;
    assert(((gcd = gcdex(a, b, x, y)) == 21) && ((a * x + b * y) == gcd));

    b = 0;
    assert(((gcd = gcdex(a, b, x, y)) == 0) && ((a * x + b * y) == gcd));

    return 0;
}


