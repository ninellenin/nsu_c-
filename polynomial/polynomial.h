#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <ostream>
#include <string>
#include <vector>

using std::ostream;
using std::string;
using std::vector;

template <class T> class Polynomial
{
private:
    vector<T> coefficients;

public:
    Polynomial<T>(const T &scalar);
    template <class S> Polynomial<T>(S begin,  S end);
    Polynomial<T>(Polynomial <T> const &other);

    Polynomial <T>& operator =(Polynomial <T> const &other);
    bool operator == (const Polynomial <T>  &other) const;
    bool operator != (const Polynomial <T>  &other) const;
    T& operator[] (size_t index);
    const T& operator[] (size_t index) const;
    int Degree() const;
    Polynomial <T> operator +( Polynomial <T> const &summand) const;
    Polynomial <T> &operator +=(Polynomial<T> const &summand);
    Polynomial <T> operator -( Polynomial <T> const &subtrahend) const;
    Polynomial <T> operator -() const;
    Polynomial <T> &operator -=(Polynomial<T> const &subtrahend);
    Polynomial <T> operator *( Polynomial <T> const &mult) const;
    Polynomial <T> &operator *=(Polynomial<T> const &mult);
    Polynomial <T> operator /(Polynomial<T> const &div) const;
    Polynomial <T> &operator /=(Polynomial<T> const &mult);
    Polynomial <T> operator %(Polynomial<T> const &div) const;
    Polynomial <T> &operator %=(Polynomial<T> const &div);
    T operator()(T point) const;
    Polynomial <T> operator , (Polynomial <T> const &other) const;
    ostream & operator <<(ostream &out) const;
    typename vector<T>::iterator begin();
    typename vector<T>::iterator end();
};

template <class T>
Polynomial<T>::Polynomial(const T &scalar)
{
    coefficients.push_back(scalar);
}
template <class T>
template <class S> Polynomial<T>::Polynomial(S begin, S end)
{
    int size = end - begin + 1;

    for (int i = 0; i < size; ++i) {
        coefficients.push_back(begin[i]);
    }
}
template <class T> Polynomial<T>::Polynomial(Polynomial <T> const &other)
{
   coefficients = other.coefficients;
}

template <class T> Polynomial <T>& Polynomial<T>::operator =(Polynomial <T> const &other)
{
    coefficients = other.coefficients;

    return *this;
}
template <class T> bool Polynomial<T>::operator == (const Polynomial <T> &other) const
{
    if (this == &other) {
        return true;
    }

    int degree = Degree();
    if (degree != other.Degree()) {
        return false;
    }

    for (int deg = 0; deg <= degree; ++deg) {
        if((*this)[deg] != other[deg]) {
            return false;
        }
    }

    return true;
}
template <class T> bool Polynomial<T>::operator != (const Polynomial <T> &other) const
{
    return !(other == *this);
}
template <class T> T& Polynomial<T>::operator[] (size_t index)
{
    int size = coefficients.size();

    if (index >= size) {
        coefficients.resize(index + 1, T(0));
    }

    return coefficients[index];
}
template <class T> const T& Polynomial<T>::operator[] (size_t index) const
{

    if (index <= Degree()) {
        return coefficients[index];
    } else {
        const static T null_element(0);
        return null_element;
    }
}
template <class T>  int Polynomial<T>::Degree() const
{
    for (int i = coefficients.size() - 1; i >= 0; --i) {
        if (coefficients[i]) {
            return i;
        }
    }
    return -1;
}
template <class T> Polynomial <T> Polynomial<T>::operator +( Polynomial <T> const &summand) const
{
    Polynomial <T> temp = *this;
    temp += summand;

    return temp;
}
template <class T> Polynomial <T> & Polynomial<T>::operator +=(Polynomial<T> const &summand)
{
    int degree = summand.Degree();

    for (int i = 0; i <= degree; ++i) {
        operator[](i) += summand[i];
    }

    return *this;
}
template <class T> Polynomial <T> Polynomial<T>::operator -( Polynomial <T> const &subtrahend) const
{
    return operator +(- subtrahend);
}
template <class T> Polynomial <T> Polynomial<T>::operator -() const
{
    return (*this * (-1));
}
template <class T> Polynomial <T> & Polynomial<T>::operator -=( Polynomial <T> const &subtrahend)
{
    return *this += (-subtrahend);
}
template <class T> Polynomial <T> Polynomial<T>::operator *( Polynomial <T> const &mult) const
{
    Polynomial <T> temp = *this;
    temp *= mult;

    return temp;
}
template <class T> Polynomial <T> & Polynomial<T>::operator *=( Polynomial <T> const &mult)
{
    int degree = Degree();
    int mult_degree = mult.Degree();
    Polynomial <T> temp(*this);

    coefficients.clear();
    for (int i = 0; i <= degree; ++i) {
        for (int j = 0; j <= mult_degree; ++j) {
            operator[](i + j) += temp[i] * mult[j];
        }
    }

    return *this;
}
template <class T> Polynomial <T> Polynomial<T>::operator /(Polynomial<T> const &div) const
{
    Polynomial <T> temp = *this;
    temp /= div;

    return temp;
}
template <class T> Polynomial <T> & Polynomial<T>::operator /=(Polynomial<T> const &div)
{
    int degree = Degree();
    int div_degree = div.Degree();

    if (degree < div_degree) {
        return *this = 0;
    }

    int result_size = degree - div_degree + 1;
    vector<T> result;

    result.assign(result_size, 0);

    while (degree >= div_degree) {
        result[degree - div_degree] = operator[](degree) / div[div_degree];
        Polynomial <T> mult(result.begin(), result.begin() + degree - div_degree);
        operator -=(mult * div);
        degree = Degree();
    }

    *this = Polynomial(result.begin(), --result.end());

    return *this;
}
template <class T> Polynomial <T> Polynomial<T>::operator %(Polynomial<T> const &div) const
{
    Polynomial <T> temp = *this;
    temp %= div;

    return temp;
}
template <class T> Polynomial <T> & Polynomial<T>::operator %=(Polynomial<T> const &div)
{
    Polynomial <T> mult(*this / div);
    *this -= (div * mult);

    return *this;
}
template <class T> T Polynomial<T>::operator()(T point) const
{
    T result = 0;
    T mult(1);
    int degree = Degree();

    for (int i = 0; i <= degree; ++i) {
        result += mult * coefficients[i];
        mult *= point;
    }

    return result;
}
template <class T> Polynomial<T> Polynomial<T>::operator , (Polynomial <T> const &other) const
{
    Polynomial <T> a(*this);
    Polynomial <T> b(other);
    Polynomial <T> r(0);

    while (b.Degree() != -1) {
        r = a % b;
        a = b;
        b = r;
    }

    return a / a[a.Degree()];
}
template <class T> ostream & Polynomial<T>::operator <<(ostream &out) const
{
    int degree = Degree();

    if (degree > -1) {
        for (int i = degree; i >=  0; --i) {
            if (coefficients[i]) {
                if (i > 1) {
                    out << (((coefficients[i] > 0) && (i != degree)) ? "+" : "");
                    if (coefficients[i] != 1) {
                        out << coefficients[i];
                    }
                    out << "x^" <<  i;
                } else if (i == 1){
                    out << ((coefficients[i] > 0) ? "+" : "");
                    if (coefficients[i] != 1) {
                        out << coefficients[i];
                    }
                    out << "x";
                } else {
                    out << ((coefficients[i] > 0) ? "+" : "") << coefficients[i];
                }
            }
        }
    } else {
        out << "0";
    }

    return out;
}
template <class T> ostream & operator <<(ostream &out, Polynomial <T> polynomial)
{
    return polynomial.operator <<(out);
}
template <class T> typename vector<T>::iterator Polynomial<T>::begin()
{
    return coefficients.begin();
}
template <class T> typename vector<T>::iterator Polynomial<T>::end()
{
    return coefficients.begin() + Degree() + 1;
}

#endif // POLYNOMIAL_H
