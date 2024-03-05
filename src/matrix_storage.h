#pragma once

#include <memory>

class Matrix;

namespace MatrixStorage {
    bool saveMatrix(const Matrix& matrix, int elapsedSeconds);
    bool loadMatrix(Matrix& matrix, int& elapsedSeconds);
}
