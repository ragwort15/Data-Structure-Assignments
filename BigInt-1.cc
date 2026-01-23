#include "BigInt.h"
 
void removeLeadingZeros(std::vector<int>& v) {
    while (v.size() > 1 && v.back() == 0) {
        v.pop_back();
    }
}

BigInt::BigInt(int val) {
    *this = BigInt(std::to_string(val));
}

BigInt::BigInt() : negative_(false) {
    digits_.push_back(0);
}

BigInt::BigInt(const std::string& num) {
    negative_ = false;
    int start = 0;
    if (num[0] == '-') {
        negative_ = true;
        start = 1;
    }
    for (int i = num.size() - 1; i >= start; --i) {
        digits_.push_back(num[i] - '0');
    }
    removeLeadingZeros(digits_);
}

BigInt::BigInt(const char num[]) {
    std::string s(num);
    *this = BigInt(s);
}

BigInt::BigInt(const std::string& num, int size) {
    std::string s = num.substr(0, size);
    *this = BigInt(s);
}

BigInt::BigInt(const BigInt& other) {
    digits_ = other.digits_;
    negative_ = other.negative_;
}

BigInt BigInt::operator+(const BigInt& other) const {
    if (negative_ == other.negative_) {
        BigInt result;
        result.negative_ = negative_;
        result.digits_.clear();
        int carry = 0;
        int n = std::max(digits_.size(), other.digits_.size());
        for (int i = 0; i < n; ++i) {
            int d1 = (i < digits_.size()) ? digits_[i] : 0;
            int d2 = (i < other.digits_.size()) ? other.digits_[i] : 0;
            int sum = d1 + d2 + carry;
            result.digits_.push_back(sum % 10);
            carry = sum / 10;
        }
        if (carry) {
            result.digits_.push_back(carry);
        }
        return result;
    } else {
        if (negative_) {
            BigInt tmp = *this;
            tmp.negative_ = false;
            return other - tmp;
        } else {
            BigInt tmp = other;
            tmp.negative_ = false;
            return *this - tmp;
        }
    }
}

BigInt BigInt::operator-(const BigInt& other) const {
    if (negative_ != other.negative_) {
        BigInt tmp = other;
        tmp.negative_ = !tmp.negative_;
        return *this + tmp;
    }

    bool flip = false;
    const BigInt *a = this;
    const BigInt *b = &other;
    if (*this < other) {
        std::swap(a, b);
        flip = true;
    }

    BigInt result;
    result.digits_.clear();
    int borrow = 0;
    for (size_t i = 0; i < a->digits_.size(); ++i) {
        int d1 = a->digits_[i];
        int d2 = (i < b->digits_.size()) ? b->digits_[i] : 0;
        int sub = d1 - d2 - borrow;
        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits_.push_back(sub);
    }
    removeLeadingZeros(result.digits_);
    result.negative_ = flip ? !a->negative_ : a->negative_;
    if (result.digits_.size() == 1 && result.digits_[0] == 0) {
        result.negative_ = false;
    }
    return result;
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result;
    result.digits_.assign(digits_.size() + other.digits_.size(), 0);
    for (size_t i = 0; i < digits_.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.digits_.size(); ++j) {
            int sum = result.digits_[i + j] + digits_[i] * other.digits_[j] + carry;
            result.digits_[i + j] = sum % 10;
            carry = sum / 10;
        }
        if (carry) {
            result.digits_[i + other.digits_.size()] += carry;
        }
    }
    removeLeadingZeros(result.digits_);
    result.negative_ = negative_ != other.negative_;
    if (result.digits_.size() == 1 && result.digits_[0] == 0) {
        result.negative_ = false;
    }
    return result;
}

bool BigInt::operator==(const BigInt& other) const {
    return digits_ == other.digits_ && negative_ == other.negative_;
}

bool BigInt::operator<(const BigInt& other) const {
    if (negative_ != other.negative_) {
        return negative_;
    }
    if (digits_.size() != other.digits_.size()) {
        return negative_ ? digits_.size() > other.digits_.size() : digits_.size() < other.digits_.size();
    }
    for (int i = digits_.size() - 1; i >= 0; --i) {
        if (digits_[i] != other.digits_[i]) {
            return negative_ ? digits_[i] > other.digits_[i] : digits_[i] < other.digits_[i];
        }
    }
    return false;
}

bool BigInt::operator>(const BigInt& other) const {
    return other < *this;
}

bool BigInt::operator<=(const BigInt& other) const {
    return !(other < *this);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

// ++a --> prints after assigning
BigInt BigInt::operator++() {
    *this = *this + BigInt("1");
    return *this;
}

// a++ --> prints before assigning
BigInt BigInt::operator++(int) {
    BigInt tmp = *this;
    ++(*this);
    return tmp;
}

BigInt BigInt::operator--() {
    *this = *this - BigInt("1");
    return *this;
}

BigInt BigInt::operator--(int) {
    BigInt tmp = *this;
    --(*this);
    return tmp;
}

std::ostream& operator<<(std::ostream& os, const BigInt& obj) {
    if (obj.negative_) {
        os << '-';
    }

    for (int i = obj.digits_.size() - 1; i >= 0; --i) {
        os << obj.digits_[i];
    }
    return os;
}
