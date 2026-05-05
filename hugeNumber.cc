#include"hugeNumber.h"
#include<stdexcept>
#include<algorithm>

HugeNumber::HugeNumber(long long num) {
    if (num < 0) {
        isPositive = false;
        num = -num;
    } else {
        isPositive = true;
    }
    
    if (num == 0) {
        digits.push_back(0);
        return;
    }
    
    while (num > 0) {
        digits.push_back(num % 10);
        num /= 10;
    }
    
    std::reverse(digits.begin(), digits.end());
}

HugeNumber::HugeNumber(): isPositive(true) {
    digits.push_back(0);
}

HugeNumber::HugeNumber(const std::string& str) {
    if(str.empty()) {
        throw std::invalid_argument("Empty string is not allowed");
    }
    size_t start_index = 0;
    if(str[start_index] == '-') {
        isPositive = false;
        start_index = 1;
    }
    else if(str[start_index] == '+') {
        isPositive = true;
        start_index = 1;
    } else {
        isPositive = true;

    }
    if(start_index >= str.length()) {
        throw std::invalid_argument("Sign must be followed by digits");
    }
    for(size_t i = start_index; i < str.length(); i++) {
        if(!isdigit(str[i])) {
            throw std::invalid_argument("Non-digit argument found");
        }
        digits.push_back(str[i]-'0');
    }
}

HugeNumber::HugeNumber(const std::vector<char>& arr, size_t n) {
    if(arr.empty() || n == 0 || n > arr.size()) {
        throw std:: invalid_argument ("invalid or empty array");
    }
    size_t start_index = 0;
    if(arr[start_index] == '-') {
        isPositive = false;
        start_index = 1;
    }
    else if(arr[start_index] == '+') {
        isPositive = true;
        start_index = 1;
    } else {
        isPositive = true;
    }
    if(start_index >= n) {
        throw std::invalid_argument("Sign must be followed by digits");
    }
    for(size_t i = start_index;i < n; i++) {
        if(!isdigit(arr[i])) {
            throw std::invalid_argument("Non-digit argument found");
        }
        digits.push_back(arr[i]-'0');
    }
}    

HugeNumber::HugeNumber(const std::vector<int>& d,bool sign) {
    if(d.empty()) {
        throw std:: invalid_argument("Empty vector is not allowed");
    }
    for(int digit: d) {
        if(digit < 0 || digit > 9) {
            throw std::invalid_argument("Invalid digit value");
        } 
    }
    digits = d;
    isPositive = !sign;
}

HugeNumber HugeNumber::operator+(const HugeNumber& other)const {
    
    if (this->isPositive == other.isPositive) {
        HugeNumber result = addMagnitudes(*this, other);
        result.isPositive = this->isPositive;
        return result;
    }
    int compare = compareMagnitudes(*this, other);
    
    if (compare == 0) {
        return HugeNumber();
    } 
    else if (compare > 0) {
        HugeNumber result = subtractMagnitudes(*this, other);
        result.isPositive = this->isPositive;
        return result;
    } else {
        HugeNumber result = subtractMagnitudes(other, *this);
        result.isPositive = other.isPositive;
        return result;
    }
}

HugeNumber HugeNumber::operator-(const HugeNumber& other) const {

    HugeNumber negative = other;
    negative.isPositive = !negative.isPositive;
    return *this + negative;
}

HugeNumber HugeNumber::operator*(const HugeNumber& other) const {

    if ((this->digits.size() == 1 && this->digits[0] == 0) ||
        (other.digits.size() == 1 && other.digits[0] == 0)) {
        return HugeNumber();
    }
    std::vector<int> result(this->digits.size() + other.digits.size(), 0);
    
    for (int i = this->digits.size() - 1; i >= 0; i--) {
        for (int j = other.digits.size() - 1; j >= 0; j--) {
            int mul = this->digits[i] * other.digits[j];
            int p1 = i + j;
            int p2 = i + j + 1;
            int sum = mul + result[p2];
            result[p2] = sum % 10;
            result[p1] += sum / 10;
        }
    }
    
    size_t start = 0;
    while (start < result.size() - 1 && result[start] == 0) {
        start++;
    }
    std::vector<int> finalResult(result.begin() + start, result.end());
    HugeNumber product(finalResult, false);
    product.isPositive = (this->isPositive == other.isPositive);
    return product;
}

bool HugeNumber::operator==(const HugeNumber& other) const {
    if (this->isPositive != other.isPositive) return false;
    if (this->digits.size() != other.digits.size()) return false;
    return this->digits == other.digits;
}

bool HugeNumber::operator!=(const HugeNumber& other) const {
    return !(*this == other);
}

bool HugeNumber::operator<(const HugeNumber& other) const {
    if (this->isPositive != other.isPositive) {
        return !this->isPositive; 
    }
    
    if (this->isPositive) { 
        if (this->digits.size() != other.digits.size()) {
            return this->digits.size() < other.digits.size();
        }
        return this->digits < other.digits;
    } else {  
        if (this->digits.size() != other.digits.size()) {
            return this->digits.size() > other.digits.size();
        }
        return this->digits > other.digits;
    }
}

bool HugeNumber::operator<=(const HugeNumber& other) const {
    return *this < other || *this == other;
}

bool HugeNumber::operator>(const HugeNumber& other) const {
    return !(*this <= other);
}

bool HugeNumber::operator>=(const HugeNumber& other) const {
    return !(*this < other);
}

HugeNumber& HugeNumber::operator++() {
    *this = *this + HugeNumber(1);
    return *this;
}

HugeNumber HugeNumber::operator++(int) {
    HugeNumber temp = *this;
    *this = *this + HugeNumber(1);
    return temp;
}

HugeNumber& HugeNumber::operator--() {
    *this = *this - HugeNumber(1);
    return *this;
}

HugeNumber HugeNumber::operator--(int) {
    HugeNumber temp = *this;
    *this = *this - HugeNumber(1);
    return temp;
}

std::ostream& operator<<(std::ostream& os, const HugeNumber& other) {
    if (!other.isPositive) {
        os << "-";
    }
    for (int digit : other.digits) {
        os << digit;
    }
    return os;
}

std::istream& operator>>(std::istream& is, HugeNumber& other) {
    std::string str;
    is >> str;
    other = HugeNumber(str);
    return is;
}

HugeNumber HugeNumber::operator~() const {
    std::vector<int> reversedDigits;

    for (int i = this->digits.size() - 1; i >= 0; i--) {
        reversedDigits.push_back(this->digits[i]);
    }
    HugeNumber result(reversedDigits, !this->isPositive);
    result.normalize();
    return result;
}

bool HugeNumber::isZero() const {
    return this->digits.size() == 1 && this->digits[0] == 0;
}

int HugeNumber:: numDigits() const {
    return this->digits.size();

}

HugeNumber HugeNumber:: abs() const {
    HugeNumber result = *this;
    result.isPositive = true;
    return result;
}

void HugeNumber:: normalize() {
    while (this->digits.size() > 1 && this->digits[0] == 0) {
        this->digits.erase(this->digits.begin());
    }
    if (this->digits.size() == 1 && this->digits[0] == 0) {
        this->isPositive = true;
    }
}

HugeNumber HugeNumber::addMagnitudes(const HugeNumber& lhs, const HugeNumber& rhs) const {
    std::vector<int> result;
    int carry = 0;
    
    int i = lhs.digits.size() - 1;
    int j = rhs.digits.size() - 1;
    
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        
        if (i >= 0) {
            sum += lhs.digits[i];
            i--;
        }
        if (j >= 0) {
            sum += rhs.digits[j];
            j--;
        }
        result.push_back(sum % 10);
        carry = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    HugeNumber sum(result, false); 
    sum.normalize();
    return sum;
}

HugeNumber HugeNumber::subtractMagnitudes(const HugeNumber& lhs, const HugeNumber& rhs) const {
    std::vector<int> result;
    int borrow = 0;
    int i = lhs.digits.size() - 1;
    int j = rhs.digits.size() - 1;
    while (i >= 0) {
        int diff = lhs.digits[i] - borrow;
        
        if (j >= 0) {
            diff -= rhs.digits[j];
            j--;
        }
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(diff);
        i--;
    }
    
    std::reverse(result.begin(), result.end());

    HugeNumber difference(result, false);  
    difference.normalize(); 
    
    return difference;
}

int HugeNumber::compareMagnitudes(const HugeNumber& a, const HugeNumber& b) const {
    if (a.digits.size() != b.digits.size()) {
        return a.digits.size() > b.digits.size() ? 1 : -1;
    }
    if (a.digits > b.digits) return 1;
    if (a.digits < b.digits) return -1;
    return 0;
}

