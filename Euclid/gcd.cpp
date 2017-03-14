#include "gcd.h"
#include "BezoutForm.h"

int gcdex(int a, int b, int &x, int &y)
{
    BezoutForm r[3];
    int q;
    /*
        q(i+1) = r(i) / r(i+1)
        r(i+2) = r(i) - (q(i+1) * r(i+1))
        if (r(i+2) == 0) then (r(i) == gcd)
    */
    r[0].value = a;
    r[0].x = 1;
    r[0].y = 0;

    r[1].value = b;
    r[1].x = 0;
    r[1].y = 1;

    do{
        q = r[0].value / r[1].value;
        r[2] = r[0] - (q * r[1]);
        r[0] = r[1];
        r[1] = r[2];
    } while (r[1].value);

    if (r[0].value > 0) {
        x = r[0].x;
        y = r[0].y;

        return r[0].value;
    }
    x = -r[0].x;
    y = -r[0].y;

    return -r[0].value;
}
