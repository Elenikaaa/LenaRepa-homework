
#include <iostream>
// функция на проверку потока ввода
bool InputError() {
    if (std::cin.fail()) {
        std::cerr << "Input error" << std::endl;
        return false;
    }
    return true;
}
// функция на зачистку памяти
void freeMatrix(int** matrix, size_t allocatedRows) {
    if (matrix == nullptr) return;
    for (size_t i = 0; i < allocatedRows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    size_t row=0, columns = 0;
    std::cin >> row >> columns;
    if (!InputError() || row <= 0 || columns <= 0) {
        return 1;
    }
    int** matrix = nullptr; // зануляем матрицу
    try {
        matrix = new int*[row];
    }
    catch (std::bad_alloc&) {
        std::cerr << "bad_alloc" << std::endl;
        return 2;
    }
    for (size_t i = 0; i < row; i++) {
        try {
            matrix[i] = new int[columns];
        }
        catch (std::bad_alloc&) {
            freeMatrix(matrix, i); // Очищаем только уже выделенные i строк и сам массив

            return 2;
        }
        }
    for(size_t i = 0; i < row; i++) {
        for(int j = 0; j < columns; j++) {
            int c = 0;
            std::cin >> c;
            if (std::cin.fail()) {
                std::cerr << "fail" << std::endl;
            }
            matrix[i][j] = c;
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // 1 2 3
    // 4 5 6

    // 1 4
    // 2 5
    // 3 6
    std::cout << "Транспонированная матрица:" << std::endl;
    for (int j = 0; j < columns; j++) {
        for (int i = 0; i < row; i++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < row; i++) {
        delete[] matrix[i];
    }
    freeMatrix(matrix, row);
    return 0;
}
