#include <iostream>
#include <string>


class Complex {
    double _re, _im;

public:
    
    Complex(double re, double im);


    Complex& setReal(double r) ;

    Complex& setImag(double i) ;
     friend Complex operator- (const Complex& c1, const Complex& c2);
    friend Complex operator* (const Complex& c1, const Complex& c2);
    friend bool operator==(const Complex& c1, const Complex& c2);
    friend bool operator!=(const Complex& c1, const Complex& c2);
    double re() const {
		return _re;
	}

	double im() const {
		return _im;
	}
 bool operator!() const {
        return _re==0 && _im==0;
    }

    Complex operator-() const {
        return Complex(-_re , -_im);
    }
 Complex operator+(const Complex& other) const;

    Complex& operator+=(const Complex& other) {
        _re+= other._re;
        _im+= other._im;
        return *this; // for call chaining
    }
        Complex& operator-=(const Complex& other) {
        _re-= other._re;
        _im-= other._im;
        return *this;
    }

    Complex& operator*=(const Complex& other) {
        double new_re = _re*other._re - _im*other._im;
        double new_im = _re*other._im + _im*other._re; 
        _re = new_re;
        _im = new_im;
		return *this;
    }
    //----------------------------------------

    // prefix increment:
    Complex& operator++() {
        _re++;
        return *this;
    }
  friend bool operator==(const Complex &a, const Complex &b){
    return (a._re == b._re && a._im == b._im);
  }

    friend std::ostream &operator<<(std::ostream &os, const Complex &c){
         os << c._re << " + " << c._im << "i";
    return os;
    }
   


    bool operator>(const Complex &other) const
    {
        return (_re > other._re) || (_re == other._re && _im > other._im);
    }

    // postfix increment:
    Complex operator++(int dummy_flag_for_postfix_increment) {
        Complex copy = *this;
        _re++;
        return copy;
    }
    

    std::string to_string() ;
};
