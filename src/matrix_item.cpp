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

void MatrixItem::setGeneratedValue(int value) {
    if (1 <= value && value <= 9) {
        m_generatedValue = value;
        m_state = State::Generated;
    }
}

void MatrixItem::setHiddenState() {
    m_state = State::Hidden;
}