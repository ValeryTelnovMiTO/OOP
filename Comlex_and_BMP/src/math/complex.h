#pragma once // запрещает повторное использование инклюдом
#include<iostream>
#include<vector>

class bmp;

class Complex {
public:
  Complex();
  Complex(float re, float im);
  ~Complex();

  float Re() const;
  float Im() const;

  float denominator() const;

  Complex operator+(const Complex &other) const;
  Complex operator-(const Complex &other) const;
  Complex operator*(const Complex &other) const;
  Complex operator/(const Complex &other) const;

  Complex operator*(float) const;
  
  Complex operator-() const; //const запрещает менять this->s

  double norm() const;

  Complex& operator=(float);
  void set(float r, float i){ this -> re = r; this -> im = i;}

  static Complex Mapping(bmp& img, double x, double y, double re_min, double im_min, double re_max, double im_max);
  
  static int iterate(const Complex &z, int n_max);


private:
  float re;
  float im;
};

Complex operator*(float k, const Complex& c);
std::ostream& operator<<(std::ostream& o, const Complex& other);
std::istream& operator>>(std::istream& i, Complex& other);
