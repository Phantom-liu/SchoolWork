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
	void add(Complex a);
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
void Complex::add(Complex a) {
	re += a.re;
	im += a.im;
	abs = re * re + im * im;
}
Complex Complex::operator+(Complex a) {
	re += a.re;
	im += a.im;
	abs = re * re + im * im;
	return *this;
}
Complex Complex::operator-(Complex a) {
	re -= a.re;
	im -= a.im;
	abs = re * re + im * im;
	return *this;
}
Complex Complex::operator*(Complex a) {
	int tmp = re;
	re = re * a.re - im * a.im;
	im = im * a.re + tmp * a.im;;
	abs = re * re + im * im;
	return *this;
}
Complex Complex::operator/(Complex a) {
	int m = a.abs;
	if (m == 0) {
		cout << "除数不可为0！" << endl;
		return *this;
	}
	Complex acon(a.re, -a.im);  //共轭
	*this = (*this)*acon;
	re /= m;
	im /= m;
	abs = re * re + im * im;
	return *this;
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
int main() {
	Complex c1(3, 5);
	Complex c2 = 4;
	c1.add(c2);
	c1.show();
	c2.show();
	Complex c3(0, 5);
	c3.show();
	c2 = "4-3i";
	c2.show(); c1.show();
	c1 = c2 * c1;
	c1.show();
	return 0;
}