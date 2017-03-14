#ifndef BEZOUTFORM_H
#define BEZOUTFORM_H

struct BezoutForm {
    int value;
    int x;
    int y;
    BezoutForm();
    BezoutForm(int number, int x_value, int y_value);

    BezoutForm & operator = (const BezoutForm other);
    BezoutForm operator * (const int &mult);
    BezoutForm operator + (const BezoutForm &summand);
};

BezoutForm operator + (BezoutForm summand1, BezoutForm summand2);
BezoutForm operator * (BezoutForm number, int mult);
BezoutForm operator * (int mult, BezoutForm number);
BezoutForm operator - (BezoutForm summand1, BezoutForm summand2);

#endif // BEZOUTFORM_H
