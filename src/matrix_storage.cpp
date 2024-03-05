#include "matrix_storage.h"
#include "matrix.h"
#include <fstream>

namespace {
    static const char* filePath = "matrix.txt";
}

namespace MatrixStorage {

bool saveMatrix(const Matrix& matrix, int elapsedSeconds) {
    std::ofstream stream(filePath);
    if (stream.is_open()) {
        for (size_t row = 0; row < matrix.rows(); row++) {
            for (size_t col = 0; col < matrix.columns(); col++) {
                const auto& item = matrix.getItem(row, col);
                stream << item << ' ';
            }
            stream << '\n';
        }        
        stream << elapsedSeconds << '\n';
        return stream.good();
    }

    return false;
}

bool loadMatrix(Matrix& matrix, int& elapsedSeconds) {
    std::ifstream stream(filePath);
    if (stream.is_open()) {
        for (size_t row = 0; row < matrix.rows(); row++) {
            for (size_t col = 0; col < matrix.columns(); col++) {
                MatrixItem item;
                stream >> item;
                matrix.setItem(row, col, item);
            }
        }
        stream >> elapsedSeconds;

        return stream.good();
    }

    return false;
}

} //MatrixSaver
