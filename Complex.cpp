#include "Complex.hpp"
using namespace std;

Complex::Complex(double re=0, double im=0)
{
    _re = re;
    _im = im;
}

Complex &Complex::setReal(double r)
{
    _re = r;
    return *this;
}

Complex &Complex::setImag(double i)
{
    _im = i;
    return *this;
}

// Complex &Complex::add(const Complex &c)
// {
//     _re += c._re;
//     _im += c._im;
//     return *this;
// }

string Complex::to_string()
{ // inline method
    return std::to_string(_re) + "+" + std::to_string(_im) + "i";
}
