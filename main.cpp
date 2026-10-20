#include <iostream>
//lhs (2x3):     rhs (2x2):      результат (2x5):
//1 2 3          7 8             1 2 3 7 8
//4 5 6          9 0             4 5 6 9 0
void Delet_memory(int** arr, size_t countRows) {
    if (arr == nullptr) return;
    for (size_t i = 0; i < countRows; i++) {
        if ( nullptr != arr[i]) {
            delete[] arr[i];
            arr[i] = nullptr;
        }
    }
    delete[] arr;
}
int ** concat_rows(const int * const * lhs, size_t n1, size_t m1, const int * const * rhs, size_t n2, size_t m2) {

    if (m1 > std::numeric_limits<size_t>::max() - m2) {
        throw std::length_error("too much");
    }
    if (n1 != n2) {
        throw std::runtime_error("Что делать в таком случае?");
    }
    int ** res = new int*[n1]();
    for (size_t i = 0; i < n1; ++i) {
        try {
             res[i] = new int[m1+ m2];
        }
        catch (std::bad_alloc&) {
            Delet_memory(res, n1);
            throw std::runtime_error("bad_alloc");
        }
        for (size_t m = 0; m < m1; ++m) {
            res[i][m] = lhs[i][m];
        }
        for (size_t m = 0; m < m2; ++m) {
            res[i][m+m1] = rhs[i][m];
        }
    }
    return res;
}

int main() {
    int count = 1;
    size_t n1 = 2, m1 = 3, n2 = 2, m2 = 2;
    int ** res1 = new int*[n1]();
    try {
        for (size_t i = 0; i < n1; i++) {
            res1[i] = new int[m1];
        }
    }
    catch (std::bad_alloc&) {
        throw std::runtime_error("bad_alloc");
    }
    int ** res2 = new int*[n1]();
    try {
        for (size_t i = 0; i < n1; i++) {
            res2[i] = new int[m2];
        }
    }
    catch (std::bad_alloc&) {
        throw std::runtime_error("bad_alloc");
    }
    for (size_t i = 0; i < n1; ++i) {
        for (size_t j = 0; j < m1; ++j) {
            res1[i][j] = count;
            count++;
            std::cout << res1[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (size_t i = 0; i < n2; ++i) {
        for (size_t j = 0; j < m2; ++j) {
            res2[i][j] = count;
            count++;
            std::cout << res2[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    int ** res = concat_rows(res1, n1, m1, res2, n2, m2);
    for (size_t i = 0; i < n1; ++i) {
        for (size_t j = 0; j < m1 + m2; ++j) {
            std::cout << res[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}













