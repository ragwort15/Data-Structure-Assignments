#ifndef HUGE_NUMBER_H
#define HUGE_NUMBER_H
#include<string>
#include<vector>
#include<iostream>

class HugeNumber {
  private:
    std::vector<int> digits;
    bool isPositive;
    HugeNumber addMagnitudes(const HugeNumber& a, const HugeNumber& b) const;
    HugeNumber subtractMagnitudes(const HugeNumber& a, const HugeNumber& b) const;
    int compareMagnitudes(const HugeNumber& a, const HugeNumber& b) const;

  public:
    HugeNumber(long long num);
    HugeNumber();
    HugeNumber(const std::string& str);
    HugeNumber(const std::vector<char>& arr, size_t n);
    HugeNumber(const std::vector<int>& d, bool sign);

    HugeNumber operator+(const HugeNumber& other) const;
    HugeNumber operator-(const HugeNumber& other) const;
    HugeNumber operator*(const HugeNumber& other) const;
    bool operator==(const HugeNumber& other) const;
    bool operator!=(const HugeNumber& other) const;
    bool operator<(const HugeNumber& other) const;
    bool operator>(const HugeNumber& other) const;
    bool operator<=(const HugeNumber& other) const;
    bool operator>=(const HugeNumber& other) const;
    HugeNumber& operator++();     
    HugeNumber operator++(int);    
    HugeNumber& operator--();
    HugeNumber operator--(int);
    HugeNumber operator~() const; 
    
    bool isZero() const;
    int numDigits() const;
    HugeNumber abs() const;
    void normalize();
    friend std::ostream& operator<<(std::ostream& os, const HugeNumber& other);  
    friend std::istream& operator>>(std::istream& is, HugeNumber& other);      
};
#endif