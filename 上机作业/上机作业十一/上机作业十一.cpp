#include<iostream>
#include<string>
using namespace std;
class Complex {
public:
	Complex(double a = 0, double b = 0) {
		re = a;
		im = b;
		abs = re * re + im * im;
	}
	Complex operator =(string s);
	Complex operator+(Complex a);
	Complex operator-(Complex a);
	Complex operator*(Complex a);
	Complex operator/(Complex a);
	void show();
private:
	double re, im;
	double abs;  //模长
};
Complex Complex::operator = (string s) {
	int pos = s.find('+');
	if (pos == -1)pos = s.find('-');
	if (pos == -1) {
		if (s[s.length() - 1] == 'i') {
			im = atoi(s.substr(0, s.length() - 1).c_str());
			re = 0;
		}
		else {
			re = atoi(s.substr(0, s.length()).c_str());
		}
		abs = re * re + im * im;
		return *this;
	}
	re = atoi(s.substr(0, pos).c_str());  //atoi函数会处理正负号
	im = atoi(s.substr(pos).c_str());
	abs = re * re + im * im;
	return *this;
}
Complex Complex::operator+(Complex a) {
	Complex c(*this);
	c.re += a.re;
	c.im += a.im;
	c.abs = re * re + im * im;
	return c;
}
Complex Complex::operator-(Complex a) {
	Complex c(*this);
	c.re -= a.re;
	c.im -= a.im;
	c.abs = re * re + im * im;
	return c;
}
Complex Complex::operator*(Complex a) {
	Complex c(*this);
	int tmp = re;
	c.re = re * a.re - im * a.im;
	c.im = im * a.re + tmp * a.im;;
	c.abs = re * re + im * im;
	return c;
}
Complex Complex::operator/(Complex a) {
	Complex c(*this);
	int m = a.abs;
	if (m == 0) {
		cout << "除数不可为0！" << endl;
		return *this;
	}
	Complex acon(a.re, -a.im);  //共轭
	c = (c)*acon;
	c.re /= m;
	c.im /= m;
	c.abs = re * re + im * im;
	return c;
}
void Complex::show() {
	if (re&&im) {
		if (im > 0)cout << re << "+" << im << "i" << endl;
		else cout << re << im << "i" << endl;
	}
	else if (re)cout << re << endl;
	else if (im)cout << im << "i" << endl;
	else cout << 0 << endl;
}
// fraction类
class Fraction {
public:
	Fraction(int den, int num) :den(den), num(num) {}
	void print() { cout << num << endl; };
	Fraction& operator++() {
		num += den;
		return *this;
	}
	Fraction operator++(int) {
		Fraction tmp(*this);
		num += den;
		return tmp;
	}
private:
	int den;
	int num;
};
int main() {
	Complex c1(3, 5);
	Complex c2 = 4;
	c1 = c1 + c2;
	c2 = c1 * c2;
	c1.show();
	c2.show();
	Fraction b(1, 10), a(4, -8);
	(a++).print();
	a.print();
	a = b++;
	a.print();
	a = ++b;
	a.print();
	return 0;
}