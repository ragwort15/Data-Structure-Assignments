#include <iostream>
#include "hugeNumber.h"

using namespace std;

int main() {
    cout << "=== HugeNumber Class Demonstration ===" << endl;
    
    // 1. CONSTRUCTION
    cout << "\n1. CONSTRUCTION" << endl;
    
    // From string
    HugeNumber a("12345678901234567890");
    cout << "From string: " << a << endl;
    
    // From vector<char>
    string str = "98765432109876543210";
    vector<char> vecArr(str.begin(), str.end());
    HugeNumber b(vecArr, vecArr.size());
    cout << "From vector<char>: " << b << endl;
    
    // From vector<int>
    vector<int> digits;
    digits.push_back(5);
    digits.push_back(4);
    digits.push_back(3);
    digits.push_back(2);
    digits.push_back(1);
    HugeNumber c(digits, false);
    cout << "From vector<int>: " << c << endl;
    
    // 2. ARITHMETIC WITH SPECIFIC TEST CASES
    cout << "\n2. ARITHMETIC" << endl;
    
    // 999999999999 + 1
    HugeNumber t1("999999999999");
    HugeNumber t2("1");
    cout << t1 << " + " << t2 << " = " << (t1 + t2) << endl;
    
    // 1000000000000 - 1
    HugeNumber t3("1000000000000");
    HugeNumber t4("1");
    cout << t3 << " - " << t4 << " = " << (t3 - t4) << endl;
    
    // -2500 + 300
    HugeNumber t5("-2500");
    HugeNumber t6("300");
    cout << t5 << " + " << t6 << " = " << (t5 + t6) << endl;
    
    // -25 * -4
    HugeNumber t7("-25");
    HugeNumber t8("-4");
    cout << t7 << " * " << t8 << " = " << (t7 * t8) << endl;
    
    // -25 * 4
    HugeNumber t9("-25");
    HugeNumber t10("4");
    cout << t9 << " * " << t10 << " = " << (t9 * t10) << endl;
    
    // 3. DIGIT REVERSAL ~
    cout << "\n3. DIGIT REVERSAL (~)" << endl;
    
    HugeNumber rev("123400");
    cout << "~" << rev << " = " << ~rev << endl;
    
    // 4. INCREMENT AND DECREMENT
    cout << "\n4. INCREMENT AND DECREMENT" << endl;
    
    HugeNumber x("10");
    cout << "x = " << x << endl;
    
    cout << "++x = " << (++x) << endl;
    cout << "x after ++x = " << x << endl;
    
    cout << "x++ = " << (x++) << endl;
    cout << "x after x++ = " << x << endl;
    
    cout << "--x = " << (--x) << endl;
    cout << "x after --x = " << x << endl;
    
    cout << "x-- = " << (x--) << endl;
    cout << "x after x-- = " << x << endl;
    
    // 5. COMPARISONS
    cout << "\n5. COMPARISONS" << endl;
    
    // 12345 > 12344
    HugeNumber c1("12345");
    HugeNumber c2("12344");
    cout << c1 << " > " << c2 << " : " << (c1 > c2 ? "true" : "false") << endl;
    
    // -999 < 5
    HugeNumber c3("-999");
    HugeNumber c4("5");
    cout << c3 << " < " << c4 << " : " << (c3 < c4 ? "true" : "false") << endl;
    
    // -100 == -100
    HugeNumber c5("-100");
    HugeNumber c6("-100");
    cout << c5 << " == " << c6 << " : " << (c5 == c6 ? "true" : "false") << endl;
    
    // Additional comparisons
    cout << c1 << " < " << c2 << " : " << (c1 < c2 ? "true" : "false") << endl;
    cout << c5 << " != " << c1 << " : " << (c5 != c1 ? "true" : "false") << endl;
    cout << c3 << " >= " << c3 << " : " << (c3 >= c3 ? "true" : "false") << endl;
    
    // 6. STREAM INSERTION AND EXTRACTION
    cout << "\n6. STREAM INSERTION (<<) AND EXTRACTION (>>)" << endl;
    
    HugeNumber input1, input2;
    
    cout << "Enter first number: ";
    cin >> input1;
    cout << "You entered: " << input1 << endl;
    
    cout << "Enter second number: ";
    cin >> input2;
    cout << "You entered: " << input2 << endl;
    
    cout << input1 << " + " << input2 << " = " << (input1 + input2) << endl;
    
    return 0;
}