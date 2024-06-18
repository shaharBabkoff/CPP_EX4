#include <ostream>

class Complex {
public:
    double real, imag;
    Complex(double r, double i) : real(r), imag(i) {}

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << "+" << c.imag << "i";
        return os;
    }
};
