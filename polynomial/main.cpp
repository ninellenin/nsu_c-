#include "assert.h"

#include <vector>
#include <sstream>
#include <string>

#include "polynomial.h"

using std::string;
using std::vector;

int main()
{
    /*
     *0. Конструктор
    */
    //многочлен нулевой степени
    Polynomial <int> polynom(1);
    assert(polynom[0] == 1);

    //последовательность коэффициентов многочлена
    int arr[10];
    for (int i = 0; i < 10; ++i) {
        arr[i] = i + 1;
    }
    polynom = Polynomial<int>(arr, &arr[9]);
    for (int i = 0; i < 10; ++i) {
        assert(polynom[i] == i + 1);
    }
    //другой вид итератора
    vector <double> d_arr;
    for (int i = 0; i < 10; ++i) {
        d_arr.push_back(i - 1);
    }
    Polynomial<double> d_polynom = Polynomial<double>(d_arr.begin(), --d_arr.end());
    for (int i = 0; i < 10; ++i) {
        assert(d_polynom[i] == d_arr[i]);
    }

    /*
     *1. Операторы == и !=
    */
    assert(polynom == polynom);
    assert(!(polynom != polynom));
    Polynomial <int> other(arr, &arr[9]);
    assert(polynom == other);
    other[3] = 100;
    assert(polynom != other);

    /*
     *2. Операторы +, - и *; +=, -= и *=
    */
    for (int i = 0; i < 10; ++i) {
        other[i] = -i;
        polynom[i] = i;
    }
    //polynom == {0, 1, 2, 3, 4, 5, 6, 7, 8, 9} == -other
    assert(polynom + other == 0);

    other *= -1;
    //other == polynom
    other[0] = 10;
    // прибавление скаляра
    polynom += 10;
    assert(polynom == other);

    polynom -= other;
    assert(polynom == 0);

    polynom *= 2;
    assert(polynom == 0);

    polynom[0] = 1;
    polynom[1] = 1;
    other *= 0;
    other[0] = -1;
    other[1] = 1;
    //polynom == x + 1, other == x - 1
    arr[0] = -1;
    arr[1] = 0;
    arr[2] = 1;
    //arr <=> x^2 - 1
    assert((polynom * other) == Polynomial<int>(arr, &arr[2]));

    /*
     *3. Функция Degree
    */
    //polynom == x + 1, Degree == 1
    assert(polynom.Degree() == 1);
    //степень нулевого многочлена равна -1
    assert(Polynomial<int>(0).Degree() == -1);
    assert(Polynomial<int>(1).Degree() == 0);

    /*
     *4. Оператор [] доступа к коэффициентам многочлена
    */

    polynom = Polynomial<int>(1);
    //polynom == 1
    //доступ к коэффициенту, большему текущего максимального
    polynom[3] = 1;
    assert(polynom[3] == 1);
    assert(polynom[100] == 0);
    //доступ к коэффициенту, меньшему текущего максимального
    polynom[1] = 3;

    //polynom = x^3 + 3x + 1
    arr[0] = arr[3] = 1;
    arr[1] = 3;
    arr[2] = 0;

    assert(Polynomial<int>(arr, &arr[3]) == polynom);

    /*
     *5. Оператор () получения значения многочлена в точке
    */
    polynom[0] = polynom[1] = polynom[2] = polynom[3] = polynom[4] = 1;
    //polynom == x^4 + x^3 + x^2 + x + 1
    assert(polynom(2) == 31);
    assert(polynom(-1) == 1);

    /*
     *6. Оператор << для печати многочлена в поток вывода
    */

    polynom[0] = 0;
    polynom[1] = polynom[2] = polynom[4] = -2;
    polynom[3] = 2;
    std::stringstream sstream;
    sstream << polynom;
    assert(  sstream.str() == "-2x^4+2x^3-2x^2-2x");

    /*
     *7. Функции для доступа к итераторам, позволяющим перебрать коэффициенты многочлена
    */
    assert(Polynomial<int>(polynom.begin(), polynom.end()) == polynom);
    for (int i = 0; i < 10; ++i) {
        polynom[i] = i;
    }

    vector<int>::iterator it = polynom.begin();
    vector<int>::iterator end = polynom.end();

    for(int i = 0; it != end; ++it, ++i) {
        assert(*it == i);
    }

    /*
     *8. Операторы / и %
    */
    d_arr[0] = -1;
    d_arr[1] = 3;
    d_arr[2] = -3;
    d_arr[3] = 1;
    //d_polynom == x^3 - 3x^2 + 3x - 1
    d_polynom = Polynomial<double>(d_arr.begin(), d_arr.begin() + 3);
    d_arr[0] = -1;
    d_arr[1] = 1;
    Polynomial<double> d_other(d_arr.begin(), d_arr.begin() + 1);
    assert(d_other * d_other == d_polynom / d_other );
    assert(d_polynom % d_other == 0);
    d_arr[0] = -3;
    d_arr[1] = 1;
    d_other = Polynomial<double>(d_arr.begin(), d_arr.begin() + 1);
    assert(d_polynom % d_other == Polynomial<double>(8.0));

    /*
     *9. Вычисление наибольшего общего делителя
    */

    d_arr[0] = 2;
    d_arr[1] = 1;
    Polynomial <double>mult1(d_arr.begin(), d_arr.begin() +1);
    d_arr[0] = -3;
    d_arr[1] = 1;
    Polynomial <double>mult2(d_arr.begin(), d_arr.begin() +1);
    d_arr[0] = 5;
    d_arr[1] = 1;
    Polynomial <double>mult3(d_arr.begin(), d_arr.begin() +1);
    d_arr[0] = -9;
    d_arr[1] = 1;
    Polynomial <double>mult4(d_arr.begin(), d_arr.begin() +1);

    assert((mult1 * mult2 * mult4, mult1 * mult3 * mult4) == mult1 * mult4);
    assert((mult1 * mult2,  mult3 * mult4) == 1);

    return 0;
}
