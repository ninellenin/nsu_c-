#include "BezoutForm.h"

/*
    Bezout form: number = a*x + b*y
*/

BezoutForm::BezoutForm()
{
    value = 0;
    x = 0;
    y = 0;
}

BezoutForm::BezoutForm(int number, int x_value, int y_value)
    : value(number),
      x(x_value),
      y(y_value)
{

}

BezoutForm & BezoutForm::operator = (const BezoutForm other)
{
    this->value = other.value;
    this->x = other.x;
    this->y = other.y;

    return *this;
}

BezoutForm BezoutForm::operator * (const int &mult) {
    return BezoutForm(mult * this->value, mult * this->x, mult * this->y);
}

BezoutForm BezoutForm::operator + (const BezoutForm &summand) {
    return(BezoutForm(this->value + summand.value,
        this->x + summand.x,
        this->y + summand.y));
}

BezoutForm operator + (BezoutForm summand1, BezoutForm summand2) {
    return summand1.operator +(summand2);
}
BezoutForm operator * (BezoutForm number, int mult) {
    return number.operator *(mult);
}
BezoutForm operator * (int mult, BezoutForm number) {
    return number.operator *(mult);
}
BezoutForm operator - (BezoutForm summand1, BezoutForm summand2) {
    return summand1.operator +((-1) * summand2);
}
