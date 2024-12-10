#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iomanip> // For setw
#include <climits> // For INT_MAX
#include <map>

using namespace std;



class BigInt {
private:
    std::vector<char> v;

public:
    // Constructors
    BigInt(std::string val) {
        for (char c : val) {
            if (!isdigit(c)) throw std::invalid_argument("Invalid digit");
            v.push_back(c);
        }
    }
    BigInt(int val) {
        std::string s = std::to_string(val);
        v.assign(s.begin(), s.end());
    }
    BigInt() : v{'0'} {}

    // Pre-increment
    BigInt& operator++() {
        int carry = 1;
        for (int i = v.size() - 1; i >= 0; --i) {
            int digit = v[i] - '0' + carry;
            if (digit > 9) {
                v[i] = '0';
                carry = 1;
            } else {
                v[i] = digit + '0';
                carry = 0;
                break;
            }
        }
        if (carry == 1) v.insert(v.begin(), '1');
        return *this;
    }

    // Post-increment
    BigInt operator++(int) {
        BigInt temp = *this;
        ++(*this);
        return temp;
    }

    // Addition
    BigInt operator+(BigInt other) {
        BigInt result;
        result.v.clear();

        int carry = 0;
        int i = v.size() - 1;
        int j = other.v.size() - 1;

        while (i >= 0 || j >= 0 || carry > 0) {
            int digit1 = (i >= 0) ? (v[i] - '0') : 0;
            int digit2 = (j >= 0) ? (other.v[j] - '0') : 0;

            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.v.push_back((sum % 10) + '0');

            --i;
            --j;
        }

        std::reverse(result.v.begin(), result.v.end());
        return result;
    }

    // Subtraction
    BigInt operator-(BigInt other) {
        BigInt result;
        result.v.clear();

        int borrow = 0;
        int i = v.size() - 1;
        int j = other.v.size() - 1;

        while (i >= 0 || j >= 0) {
            int digit1 = (i >= 0) ? (v[i] - '0') : 0;
            int digit2 = (j >= 0) ? (other.v[j] - '0') : 0;

            int sub = digit1 - digit2 - borrow;

            if (sub < 0) {
                sub += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.v.push_back(sub + '0');
            --i;
            --j;
        }

        // Remove leading zeros
        while (result.v.size() > 1 && result.v.back() == '0') {
            result.v.pop_back();
        }

        std::reverse(result.v.begin(), result.v.end());
        return result;
    }

    // Multiplication
    BigInt operator*(BigInt other) {
        BigInt result("0");

        int shift = 0;

        for (int j = other.v.size() - 1; j >= 0; --j) {
            int carry = 0;
            BigInt temp;
            temp.v.clear();

            for (int i = 0; i < shift; ++i) {
                temp.v.push_back('0');
            }

            for (int i = v.size() - 1; i >= 0; --i) {
                int digit1 = v[i] - '0';
                int digit2 = other.v[j] - '0';

                int product = digit1 * digit2 + carry;
                carry = product / 10;
                temp.v.push_back((product % 10) + '0');
            }

            if (carry > 0) {
                temp.v.push_back(carry + '0');
            }

            std::reverse(temp.v.begin(), temp.v.end());
            result = result + temp;
            ++shift;
        }

        return result;
    }

    bool operator<(const BigInt& other) const {
        // Compare sizes first
        if (v.size() != other.v.size()) {
            return v.size() < other.v.size();
        }

        // If sizes are equal, compare digit by digit
        for (size_t i = 0; i < v.size(); ++i) {
            if (v[i] != other.v[i]) {
                return v[i] < other.v[i];
            }
        }

        // Numbers are equal
        return false;
    }

    bool operator>(const BigInt& other) const {
        // Compare sizes first
        if (v.size() != other.v.size()) {
            return v.size() > other.v.size();
        }

        // Sizes are equal; compare digit by digit
        for (size_t i = 0; i < v.size(); ++i) {
            if (v[i] != other.v[i]) {
                return v[i] > other.v[i];
            }
        }

        // If all digits are equal
        return false;
    }

    // Factorial (Recursive)
    BigInt factDivideAndConquer(BigInt low, BigInt high) {
        if (low > high) {
            return BigInt("1"); // Base case: empty range
        }
        if (low == high) {
            return low; // Base case: single number
        }
        if (low + BigInt("1") == high) {
            return low * high; // Base case: two numbers
        }

        BigInt mid = (low + high) / BigInt("2");
        return factDivideAndConquer(low, mid) * factDivideAndConquer(mid + BigInt("1"), high);
    }

    BigInt fact() {
        return factDivideAndConquer(BigInt("1"), *this);
    }



    // Fibonacci (Recursive)

    BigInt fibo() {
        // Static map for memoization
        static std::map<BigInt, BigInt> fiboCache;

        // Check if the result is already cached
        if (fiboCache.find(*this) != fiboCache.end()) {
            return fiboCache[*this];
        }

        // Base cases
        if (*this == BigInt("0")) return BigInt("0");
        if (*this == BigInt("1")) return BigInt("1");

        BigInt one("1");
        BigInt two("2");

        // Recursive computation with memoization
        BigInt result = (*this - one).fibo() + (*this - two).fibo();

        // Cache the result
        fiboCache[*this] = result;

        return result;
    }



    // Printing all digits
    void print() const {
        for (char c : v) std::cout << c;
        std::cout << std::endl;
    }

    // Size of the BigInt
    int size() const { return v.size(); }

   
    friend std::ostream& operator<<(std::ostream& os, const BigInt& num) {
        if (num.v.size() <= 12) {
            // Directly output if size is small
            for (char c : num.v) os << c;
        } else {
            // Exponential notation
            os << num.v[0] << '.';
            for (size_t i = 1; i < 7 && i < num.v.size(); ++i) {
                os << num.v[i];
            }
            os << "e" << num.v.size() - 1;
        }
        return os;
    }


    // Equality operator
    bool operator==(const BigInt& other) const {
        return this->v == other.v;
    }
    BigInt operator/(BigInt divisor) {
        if (divisor == BigInt("0")) {
            throw std::invalid_argument("Division by zero");
        }

        BigInt dividend = *this;
        BigInt quotient("0");
        BigInt current("0");

        for (char digit : dividend.v) {
            current.v.push_back(digit);

            // Remove leading zeros from the current value
            while (current.v.size() > 1 && current.v[0] == '0') {
                current.v.erase(current.v.begin());
            }

            int count = 0;
            while (current >= divisor) {
                current = current - divisor;
                count++;
            }

            quotient.v.push_back(count + '0');
        }

        // Remove leading zeros from the quotient
        while (quotient.v.size() > 1 && quotient.v[0] == '0') {
            quotient.v.erase(quotient.v.begin());
        }

        return quotient;
    }

    BigInt operator%(BigInt divisor) {
        if (divisor == BigInt("0")) {
            throw std::invalid_argument("Division by zero");
        }

        BigInt dividend = *this;
        BigInt current("0");

        for (char digit : dividend.v) {
            current.v.push_back(digit);

            // Remove leading zeros from the current value
            while (current.v.size() > 1 && current.v[0] == '0') {
                current.v.erase(current.v.begin());
            }

            while (current >= divisor) {
                current = current - divisor;
            }
        }

        return current;
    }

    bool operator>=(const BigInt& other) const {
        if (v.size() != other.v.size()) {
            return v.size() > other.v.size();
        }
        for (size_t i = 0; i < v.size(); ++i) {
            if (v[i] != other.v[i]) {
                return v[i] > other.v[i];
            }
        }
        return true;
    }

    friend BigInt operator+(int num, BigInt bigInt) {
        BigInt numBigInt(std::to_string(num)); // Convert int to BigInt
        return numBigInt + bigInt;            // Use existing BigInt operator+
    }




};

void testUnit()
{
    int space = 10;
    cout << "\a\nTestUnit:\n"<<flush;
    // system("whoami");
    // system("date");
    // initialize variables
    BigInt n1(25);
    BigInt s1("25");
    BigInt n2(1234);
    BigInt s2("1234");
    BigInt n3(n2);
    BigInt fibo(12345);
    BigInt fact(50);
    BigInt imax = INT_MAX;
    BigInt big("9223372036854775807");
    // display variables
    cout << "n1(int) :"<<setw(space)<<n1<<endl;
    cout << "s1(str) :"<<setw(space)<<s1<<endl;
    cout << "n2(int) :"<<setw(space)<<n2<<endl;
    cout << "s2(str) :"<<setw(space)<<s2<<endl;
    cout << "n3(n2) :"<<setw(space + 1)<<n3<<endl;
    cout << "fibo(12345):"<<setw(space - 3)<<fibo<<endl;
    cout << "fact(50) :"<<setw(space - 1)<<fact<<endl;
    cout << "imax :"<<setw(space)<<imax<<endl;
    cout << "big :"<<setw(space)<<big<<endl;
    cout << "big.print(): "; big.print(); cout << endl;

    cout << n2 << "/"<< n1<< " = "<< n2/n1 <<" rem "<<n2%n1<<endl;
    cout << "fibo("<<fibo<<") = "<<fibo.fibo() << endl;
    cout << "fact("<<fact<<") = "<<fact.fact() << endl;
    cout << "10 + n1 = " << 10+n1 << endl;
    cout << "n1 + 10 = " << n1+10 << endl;
    cout << "(n1 == s1)? --> "<<((n1==s1)?"true":"false")<<endl;
    cout << "n1++ = ? --> before:"<<n1++<<" after:"<<n1<<endl;
    cout << "++s1 = ? --> before:"<<++s1<<" after:"<<s1<<endl;
    cout << "s2 * big = ? --> "<< s2 * big<<endl;
    cout << "big * s2 = ? --> "<< big * s2<<endl;
}


int main() {
    testUnit();
    return 0;
}
