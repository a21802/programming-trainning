#include <iostream>

using namespace std;

class Point2D 
{
public:
	Point2D();
	Point2D(int, int);
	int x() { return _x; }
	int y() { return _y; }
	Point2D operator+(const Point2D&);	 // 重載+運算子 
	Point2D operator-(const Point2D&);	 // 重載-運算子 
	Point2D& operator++();				 // 重載++前置，例如 ++p 
	Point2D operator++();			 // 重載++後置，例如 p++
	Point2D& operator--();				 // 重載--前置，例如 --p 
	Point2D operator--();			 // 重載--後置，例如 p--
	
	bool operator==(const Point2D&);

    void print() {
        cout << "(" << x() << "," << y() << ")" << endl;
    }
 
private:
	int _x;
	int _y;
};

Point2D::Point2D()
		:_x(0), 
		 _y(0)
{
}
Point2D::Point2D(int x, int y)
		: _x(x), _y(y)
{
}
Point2D Point2D::operator+(const Point2D &p) {
	Point2D tmp(_x + p._x, _y + p._y);
	return tmp;
}

Point2D Point2D::operator-(const Point2D &p) {
	Point2D tmp(_x - p._x, _y - p._y);
	return tmp;
}

Point2D& Point2D::operator++() { // ++p
	_x++;
	_y++;

	return *this;
}

Point2D Point2D::operator++(int) { // p++
	Point2D tmp(_x, _y);
	_x++;
	_y++;

	return tmp;
}

Point2D& Point2D::operator--() { // --p
	_x--;
	_y--;

	return *this;
}

Point2D Point2D::operator--(int) { // p--
	Point2D tmp(_x, _y);
	_x--;
	_y--;

	return tmp;
}

bool Point2D::operator==(const Point2D &p)
{
	if (_x == p._x && _y == p._y)
		return true;
	return false;

}


int main()
{
	Point2D p1(5, 5);
	Point2D p2(10, 10);
	Point2D p3;
	
	cout << "p1(x, y) = ";
	p1.print();             // (5, 5)
	cout << "p2(x, y) = ";
	p2.print();             // (10, 10)

	p3 = p1 + p2;
	cout << "p1 + p2  = ";
	p3.print();             // (15, 15)

	p3 = p2 - p1;
	cout << "p2 - p1  = ";
	p3.print();             // (5, 5)

	p3 = ++p1;
	cout << "++p1     = ";
	p3.print();             // (6, 6)
	
	p3 = p1++;
	cout << "p1++     = ";
	p3.print();             // (6, 6)

    cout << "p1(x, y) = ";
	p1.print();             // (7, 7)

	bool bEqual = (p1 == p2);
	cout << "p1 == p2 ?  " << endl << "> ";
	bEqual == true ?
		cout << "Equal" << endl : cout << "Not Equal" << endl; // Not Equal
	return 0;
}