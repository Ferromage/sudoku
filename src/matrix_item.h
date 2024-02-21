#pragma once

class MatrixItem {
    friend class Matrix;
    friend class MatrixShuffler;
    
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
