#include "matrix_item.h"

MatrixItem::MatrixItem() : m_generatedValue{1}, m_userValue{0}, m_state{State::Generated} {}

void MatrixItem::setUserValue(int value) {
    if (1 <= value && value <= 9) {
        m_userValue = value;
        m_state = State::UserSetted;
    }
}

MatrixItem::State MatrixItem::state() const {
    return m_state;
}

int MatrixItem::value() const {
    if (m_state == State::UserSetted) {
        return m_userValue;
    }
    return m_generatedValue;
}

bool MatrixItem::isGuessed() const {
    if (m_state == State::Generated) {
        return true;
    }
    if (m_state == State::UserSetted) {
        return m_userValue == m_generatedValue;
    }
    return false;
}

bool MatrixItem::operator== (const MatrixItem& rhs) const {
    return  m_generatedValue == rhs.m_generatedValue &&
            m_userValue == rhs.m_userValue &&
            m_state == rhs.m_state;
}

bool MatrixItem::operator!= (const MatrixItem& rhs) const {
    return !(*this == rhs);
}

void MatrixItem::setGeneratedValue(int value) {
    if (1 <= value && value <= 9) {
        m_generatedValue = value;
        m_state = State::Generated;
    }
}

void MatrixItem::setHiddenState() {
    m_state = State::Hidden;
}

std::ostream& operator<< (std::ostream& oss, const MatrixItem& item) {
    oss << item.m_generatedValue << item.m_userValue << static_cast<int>(item.m_state);
    return oss;
}

std::istream& operator>> (std::istream& iss, MatrixItem& item) {
    int num;
    iss >> num;

    item.m_generatedValue = num / 100;
    item.m_userValue = (num % 100) / 10;
    item.m_state = static_cast<MatrixItem::State>(num % 10);

    return iss;
}
