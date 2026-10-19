#include "complex.h" 
#include "..\bmp\bmp.h"

Complex::Complex() {}

Complex::Complex(float re, float im) {
  this-> re = re;
  this-> im = im;
}

Complex::~Complex() = default;

float Complex::Re() const { return re; }

float Complex::Im() const { return im; }

float Complex::denominator() const{
  return(Re() * Re() + Im() * Im());
}

Complex Complex::operator+(const Complex &other) const {
  return Complex(re + other.re, im + other.Im());
}

Complex Complex::operator-(const Complex &other) const{
  return Complex(re - other.Re(), im - other.Im());
}

Complex Complex::operator*(const Complex &other) const{
  return Complex(re * other.re - im * other.Im(), im * other.Re() + re * other.Im());
}

Complex Complex::operator/(const Complex &other) const{
  Complex R;
  float den = other.denominator();
  R.re = (re * other.Re() + im * other.Im()) / den;
  R.im = (im * other.Re() - re * other.Im()) / den;
  return R;
}

Complex Complex::operator*(float k) const{
  return Complex(re * k, im * k);
}

Complex Complex::operator-() const{
  return Complex(-re, -im);
}

Complex& Complex::operator=(float k){
  re = k;
  im = 0;
  return *this;
}

Complex operator*(float k, const Complex& c){
  return c * k;
}

double Complex::norm() const{
  return sqrt(re * re + im * im);
}

Complex Complex::Mapping(bmp& img, double x, double y, double re_min, double im_min, double re_max, double im_max){
  uint32_t w = img.GetWidth();
  uint32_t h = img.GetHeight();
  double re = re_min + (re_max - re_min) * x / (w - 1);
  double im = im_min + (im_max - im_min) * y / (h - 1);
  return Complex(re, im);
}

int Complex::iterate(const Complex &z, int n_max){
  Complex zk = z;
  double zNorm = zk.norm();
  int nIter = 0;
  while (zNorm < 2 && nIter <= n_max)
  {
    zk = zk * zk + z;
    zNorm = zk.norm();
    nIter++;
  }
    
  return nIter;
}

std::ostream& operator<<(std:: ostream& o, const Complex& other){
  if (other.Im() < 0)
  {
    return o << other.Re() << " - " << -other.Im() << "i"; 
  }else
  {
    return o << other.Re() << " + " << other.Im() << "i"; 
  }
}

std::istream& operator>>(std::istream& i, Complex& other){
  double re;
  double im;
  char sign;
  i >> re >> sign >> im;
  if (sign == '-')
  {
    im = -im;
  }
  other.set(re, im);
  return i;
}
