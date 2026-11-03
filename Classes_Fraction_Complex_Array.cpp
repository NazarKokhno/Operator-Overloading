#include <iostream>
#include <windows.h>
#include <stdexcept>
#include <cstdlib>

using namespace std;

class Fraction
{
private:
	int numerator;
	int denominator;

public:
	Fraction(int numerator, int denominator) :numerator(numerator), denominator(denominator) 
	{
		if (denominator == 0)
			throw invalid_argument("Denominator cannot be zero");
	};

	Fraction operator+(const Fraction& other) const
	{
		Fraction temp(
			numerator * other.denominator + other.numerator * denominator,
			denominator * other.denominator
		);


		int divisor = gcd(abs(temp.numerator), abs(temp.denominator));

		temp.numerator /= divisor;
		temp.denominator /= divisor;

		return temp;
	}
	
	Fraction operator-(const Fraction& other) const
	{
		Fraction temp(
			numerator * other.denominator - other.numerator * denominator,
			denominator * other.denominator
		);

		int divisor = gcd(abs(temp.numerator), abs(temp.denominator));

		temp.numerator /= divisor;
		temp.denominator /= divisor;

		return temp;
	}

	Fraction operator*(const Fraction& other) const
	{
		Fraction temp(
			numerator * other.numerator,
			denominator * other.denominator
		);


		int divisor = gcd(abs(temp.numerator), abs(temp.denominator));

		temp.numerator /= divisor;
		temp.denominator /= divisor;

		return temp;
	}

	Fraction operator/(const Fraction& other) const
	{
		if (other.numerator == 0)
			throw invalid_argument("Cannot divide by zero");

		Fraction temp(
			numerator * other.denominator,
			denominator * other.numerator
		);

		int divisor = gcd(abs(temp.numerator), abs(temp.denominator));

		temp.numerator /= divisor;
		temp.denominator /= divisor;

		return temp;
	}
	

	int gcd(int a, int b) const
	{
		while (b != 0)
		{
			int temp = b;
			b = a % b;
			a = temp;
		}

		return a;
	}

	void show() const
	{
		cout << numerator << "/" << denominator;
	}
};
class Complex
{
private:
	double real;
	double imaginary;
public:
	Complex(double real, double imaginary) : real(real), imaginary(imaginary) {};

	Complex operator+(const Complex& other) const
	{
		Complex temp
		(
			real + other.real,
			imaginary + other.imaginary
		);
		return temp;
	}

	Complex operator-(const Complex& other) const
	{
		Complex temp
		(
			real - other.real,
			imaginary - other.imaginary
		);
		return temp;
	}

	Complex operator*(const Complex& other) const
	{
		Complex temp(
			real * other.real - imaginary * other.imaginary,
			real * other.imaginary + imaginary * other.real
		);

		return temp;
	}
	Complex operator/(const Complex& other) const{
		
		if (other.real == 0 && other.imaginary == 0)
			throw invalid_argument("Cannot divide by zero");
		
		double denominator = other.real * other.real +
			other.imaginary * other.imaginary;


		Complex temp(
			(real * other.real + imaginary * other.imaginary) / denominator,
			(imaginary * other.real - real * other.imaginary) / denominator
		);

		return temp;
	}


	void show()
	{
		cout << real;
		if (imaginary >= 0)
			cout << " + " << imaginary << "i";
		
		else
			cout << " - " << abs(imaginary) << "i";
	}
};
class Array
{
private:
	int* arr;
	int size;
public:
	Array()
	{
		this->size = 1;
		arr = new int[size];
	}
	
	Array(int size)
	{
		if (size <= 0)
		{
			this->size = 0;
			this->arr = nullptr;
			cout << "Cannot create array.Invalid size" << endl;
			return;
		}
		
		this->size = size;
		this->arr = new int[size];

		for (int i = 0; i < size; i++)
		{
			arr[i] = i;
		}
	}
	Array(const Array& other)
	{
		this->size = other.size;
	
		if (other.arr != nullptr)
		{
			this->arr = new int[size];

			for (int i = 0; i < other.size; i++)
			{
				this->arr[i] = other.arr[i];
			}
		}
		else 
			this->arr = nullptr;
	}

	void fill()
	{
		cout << "Enter elements:\n";

		for (int i = 0; i < size; i++)
		{
			cout << "Enter element [" << i << "]: ";
			cin >> arr[i];
		}
	}
	void show()
	{
		if (arr != nullptr)
		{
			for (int i = 0; i < size; i++)
			{
				cout << arr[i] << " ";
			}
			cout << endl;
		}
	}

	Array operator+(const Array& other) const
	{
		Array temp(size + other.size);

		for (int i = 0; i < size; i++)
		{
			temp.arr[i] = arr[i];
		}

		for (int i = 0; i < other.size; i++)
		{
			temp.arr[size + i] = other.arr[i];
		}

		return temp;
	}
	Array operator-(int count) const
	{
		if (count < 0 || count > size)
		{
			cout << "Invalid size" << endl;
			return Array();
		}

		Array temp(size - count);

		for (int i = 0; i < size - count; i++)
		{
			temp.arr[i] = arr[i];
		}

		return temp;
	}
	Array& operator=(const Array& other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete[] this->arr;

		this->size = other.size;

		if (other.arr != nullptr)
		{
			this->arr = new int[size];

			for (int i = 0; i < size; i++)
			{
				this->arr[i] = other.arr[i];
			}
		}
		else
		{
			this->arr = nullptr;
		}

		return *this;
	}
	int operator[](int index)
	{
		if (index >= 0 && index < size)
		{
			return arr[index];
		}
		else
			cout << "Invalid index" << endl;
	}
	int operator()() const
	{
		int maxIndex = 0;
		
		for (int i = 0; i < size; i++)
		{
			if (arr[maxIndex] < arr[i]) maxIndex = i;
		}

		return maxIndex;
	}
	operator int() const
	{
		int sum = 0;
		for (int i = 0; i < size; i++)
		{
			if (arr[i] > 0)
				sum += arr[i];
		}
		
		return sum;
	}

	operator double() const
	{
		double value = -0.1;
		for (int i = 0; i < size; i++)
		{
			if (arr[i] < 0)
			{
				if (value > arr[i]) 
					value = arr[i];
			}
		}
		return value;
	}

	~Array()
	{
		delete[] arr;
	}

	friend ostream& operator<<(ostream& os, const Array& a);
	friend istream& operator>>(istream& is, Array& a);
};

ostream& operator<<(ostream& os, const Array& a)
{
	os << "[";
	for (int i = 0; i < a.size; i++)
	{
		os << a.arr[i];
		if (i + 1 < a.size) os << ", ";
	}
	os << "]";
	return os;
}

istream& operator>>(istream& is, Array& a)
{
	for (int i = 0; i < a.size; i++)
	{
		is >> a.arr[i];
	}
	return is;
}


int main()
{
	// class Fraction
	/*try
	{
		Fraction num1(2, 3);
		Fraction num2(3, 4);

		cout << "Fraction 1: ";
		num1.show();
		cout << endl;
		
		cout << "Fraction 2: ";
		num2.show();
		cout << endl;
		cout << endl;

		cout << "Addition: ";
		(num1 + num2).show();
		cout << endl;

		cout << "Subtraction: ";
		(num1 - num2).show();
		cout << endl;

		cout << "Multiplication: ";
		(num1 * num2).show();
		cout << endl;

		cout << "Division: ";
		(num1 / num2).show();

	}
	catch (const invalid_argument& e)
	{
		cout << e.what();
	}*/

	//class Complex
	/*try
	{
		Complex num1(3, 2);
		Complex num2(1, 1);

		cout << "Complex 1: ";
		num1.show();
		cout << endl;

		cout << "Complex 2: ";
		num2.show();
		cout << endl;
		cout << endl;


		cout << "Addition: ";
		(num1 + num2).show();
		cout << endl;

		cout << "Subtraction: ";
		(num1 - num2).show();
		cout << endl;

		cout << "Multiplication: ";
		(num1 * num2).show();		
		cout << endl;

		cout << "Division: ";
		(num1 / num2).show();
		cout << endl;
	
	}
	catch (const invalid_argument& e)
	{
		cout << e.what();
	}*/

	//class Array
	Array a(5);
	Array b(3);

	cout << "Array A:\n";
	a.show();

	cout << "\nArray B:\n";
	b.show();

	cout << "\nFill array A:\n";
	a.fill();

	cout << "\nFill array B:\n";
	b.fill();

	cout << "\nArray A: " << a;
	cout << "Array B: " << b;

	Array c(a);
	cout << "\nCopy constructor (C): ";
	c.show();

	Array d;
	d = b;
	cout << "\nAssignment operator (D): ";
	d.show();

	Array sum = a + b;
	cout << "\nA + B: ";
	sum.show();

	Array sub = a - 2;
	cout << "\nA - 2: ";
	sub.show();

	cout << "\nA[2] = " << a[2] << endl;

	cout << "\nMax element index in A: " << a() << endl;

	int positiveSum = a;
	cout << "\nSum of positive elements: " << positiveSum << endl;

	double minNegative = a;
	cout << "\nMinimum negative element: " << minNegative << endl;

	Array e(3);
	cout << "\nEnter array E:\n";
	cin >> e;

	cout << "Array E: " << e;

	return 0;
	

}
