#include <assert.h>

#include <vector>

using std::swap;
using std::vector;


typedef double      TYPE;

template <typename T> void rotate(T begin , T end, int k);

int main()
{
    // j < 0, j == 0, j > 0, j > length
    int offset;
    for (int j = -7 ; j < 7; ++j) {
        TYPE a[] = {0, 1, 2, 3};
        TYPE *p_start = &(a[0]);
        TYPE *p_end = &(a[3]);
        rotate(p_start, p_end, j);
        for (int i = 0; i < 4; i++) {
            offset = (4 + (j % 4)) % 4;
            assert(a[i] == (i + 4 - offset) % 4);
        }
    }
    //single element
    for (int i = -1; i < 2; ++i){
        TYPE a[1] = {4};
        TYPE *p_start = &(a[0]);
        TYPE *p_end = &(a[0]);
        rotate(p_start, p_end, i);
        assert(a[0] == 4);
    }
    // j < 0, j == 0, j > 0, j > length
    for (int j = -7 ; j < 7; ++j) {
        vector <TYPE> a;
        a.push_back(0);
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        a.push_back(4);
        //end inclusive
        rotate(a.begin(), a.end().operator --(), j);
        for (int i = 0; i < 4; i++) {
            offset = (5 + (j % 5)) % 5;
            assert(a[i] ==  (i + 5 - offset) % 5);
        }
    }

    return 0;
}

 template <typename T> void rotate(T begin , T end, int k)
{
    if (0 == k) {
        return;
    }

    int  length = end - begin + 1;
    k = k % length;
    if (k < 0)  {
        k = length + k;
    }

    int number_blocks;
    int modulo = 1;

    while (modulo) {
        number_blocks = length / k;
        modulo = length % k;

        //поменять блоками по k
        for (int i = 0; i < number_blocks; ++i) {
            for (int j = 0; j < k; ++j) {
                swap(begin[j], begin[k*i + j]);
            }
        }
        //поменять остаток
        for (int i = 0; i < modulo; ++i) {
            swap(begin[i], begin[number_blocks * k + i]);
        }
        //сдвинуть начало последовательности из k элементов на (k - modulo)
        length = k;
        k = k - modulo;
    };
}

