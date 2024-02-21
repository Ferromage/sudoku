#include "matrix.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <condition_variable>
#include <mutex>
#include <string>
#include <optional>
#include <unordered_set>
#include <cctype>


// 1 [2] 3  4  5  6  7  8  9 
// 4  5  6  7  8  9  1  2  3 
// 7  8  9  1  2  3  4  5  6         
//[2] 3  4  5  6  7  8  9  1 
// 5 [6] 7  8  9  1  2  3  4 
// 8  9  1  2  3  4  5  6  7 
// 3  4  5  6  7  8  9  1  2 
// 6  7  8  9  1  2  3  4  5 
// 9  1  2  3  4  5  6  7  8 

//TODO:
//0. переименовать MatrixGenerator в Matrix, стат. метод generate() возвращает матрицу, внутри ничего не хранится; стат. метод isValid(const Matrix&) проверяет
//1. сделать матрицу шаблонной, куда подсовывать свой объект с полями: значение, тип (число задано генератором, число скрытое, число, установленное юзером)
//2. при выводе матрицы раскрашивать цифры: серый - задано генератором, зеленый - установленное юзером
//3. при навигации по матрице прицел ставить только на пустые числа и те, которые уже установил юзер
//4. разобраться, почему мигает экран при очистке и че делать
//5. сделать меню (новая игра, выход, сохранить, загрузить, тайминг)
//6. автоматическая валидация при введении последней цифры
//7. при передаче кодов клавы сделать очередь сообщений

namespace {
    std::mutex cv_mutex;
    std::condition_variable cv;

    enum class ControlKeyCode {Unknown = 0, Up = 72, Down = 80, Left = 75, Right = 77};
    ControlKeyCode key;
}

void printMatrix(Matrix& matrix) {
    static const std::string indent = "    ";
    
    int colCur = 0;
    int rowCur = 0;
    std::optional<int> userValue;
    while (true) {
        system("cls");        
        
        for (int row = 0; row < (int)matrix.rows(); row++) {
            for (int col = 0; col < (int)matrix.columns(); col++) {
                if (col == 0) {
                    std::cout << indent;
                }
                
                const bool isSelected = (row == rowCur && col == colCur);
                auto& item = matrix.getItem(row, col);

                if (isSelected && userValue && (item.state() == MatrixItem::State::Hidden || item.state() == MatrixItem::State::UserSetted)) {
                    item.setUserValue(userValue.value());
                    matrix.setItem(row, col, item);
                }                

                std::cout << (isSelected ? '[' : ' ');
                if (item.state() == MatrixItem::State::Hidden) {
                    std::cout << "-";
                } else {
                    std::cout << item.value();
                }
                std::cout << (isSelected ? ']' : ' ');
            }
            std::cout << "\n";
        }
        std::cout.flush();

        std::unique_lock lock(cv_mutex);
        key = ControlKeyCode::Unknown;
        userValue.reset();
        cv.wait(lock, []() { return key != ControlKeyCode::Unknown; });

        if (key == ControlKeyCode::Up) {
            if (rowCur > 0) {
                rowCur--;
            } else {            
                rowCur = (int)matrix.rows() - 1;
            }
        } else if (key == ControlKeyCode::Down) {
            if (rowCur < (int)matrix.rows() - 1) {
                rowCur++;
            } else {
                rowCur = 0;
            }
        } else if (key == ControlKeyCode::Left) {
            if (colCur > 0) {
                colCur--;
            } else {
                colCur = (int)matrix.columns() - 1;
            }
        } else if (key == ControlKeyCode::Right) {
            if (colCur < (int)matrix.columns() - 1) {
                colCur++;
            } else {
                colCur = 0;
            }
        } else if (const int digit = static_cast<int>(key); std::isdigit(digit) && digit != '0') {
            userValue = digit - '0';
        }
    }
}


void getKey() {
    const std::unordered_set<ControlKeyCode> allowableKeys = {
        ControlKeyCode::Up, ControlKeyCode::Down, ControlKeyCode::Left, ControlKeyCode::Right
    };

    while (true) {
        if (_kbhit())  {
            const auto keyNew = _getch();            
            const bool isGoodButton =   allowableKeys.count(static_cast<ControlKeyCode>(keyNew)) ||
                                        (std::isdigit(keyNew) && keyNew != '0');
                        
            if (isGoodButton) {
                std::unique_lock lock(cv_mutex);
                key = static_cast<ControlKeyCode>(keyNew);
                cv.notify_one();
            }
        }
    }
}


int main() {
    Matrix matrix;
    matrix.shuffle(DifficultLevel::Hard);
    
    // std::cout << std::boolalpha << MatrixGenerator::isMatrixValid(matrixGen.get()) << std::endl;

    std::thread tr1(printMatrix, std::ref(matrix));
    std::thread tr2(getKey);
    tr1.join();
    tr2.join();

    return 0;
}