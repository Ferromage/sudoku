#pragma once

#include <iostream>

class MatrixItem {
    friend class Matrix;
    friend class MatrixShuffler;
    friend std::ostream& operator<< (std::ostream& oss, const MatrixItem& item);
    friend std::istream& operator>> (std::istream& iss, MatrixItem& item);

public:
    enum class State {Generated, Hidden, UserSetted};

    MatrixItem();
    void setUserValue(int value);
    int value() const;
    State state() const;
    bool isGuessed() const;

private:
    void setGeneratedValue(int value);
    void setHiddenState();

    int m_generatedValue;
    int m_userValue;
    State m_state;
};

std::ostream& operator<< (std::ostream& oss, const MatrixItem& item);
std::istream& operator>> (std::istream& iss, MatrixItem& item);
