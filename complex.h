#pragma once

class Complex {
public:
	float real, imag;

	Complex(float r = 0, float i = 0)
	{
		real = r;
		imag = i;
	}

	// This is automatically called when '+' is used with
	// between two Complex objects
	Complex operator+(Complex const& obj)
	{
		Complex res;
		res.real = real + obj.real;
		res.imag = imag + obj.imag;
		return res;
	}

	template <typename NUMERIC>
	Complex operator+(NUMERIC n) {
		return Complex(real + n, imag);
	}

	template <typename NUMERIC>
	Complex operator-(NUMERIC n) {
		return Complex(real - n, imag);
	}

	Complex operator*(Complex const& obj) {
		// (a+bi)*(c+di)
		// ac + adi + bci - bd
		// ac - bd + (ad+bc)i
		Complex res;
		res.real += real * obj.real - imag * obj.imag;
		res.imag += real * obj.imag + imag * obj.real;
		return res;
	}

	template <typename NUMERIC>
	Complex operator*(NUMERIC n) {
		return Complex(real * n, imag * n);
	}


	Complex conjugate() const {
		return Complex(real, -imag);
	}

	Complex operator/(Complex const& divisor) {
		Complex res = (*this) * divisor.conjugate();
		float size = divisor.real * divisor.real + divisor.imag * divisor.imag;
		res.real /= size;
		res.imag /= size;
		return res;
	}

	std::string str() {
		return std::to_string(real) + " + " + std::to_string(imag) + "i";
	}

};