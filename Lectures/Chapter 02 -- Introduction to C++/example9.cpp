#include <iostream>

class Point
{
public:
	inline Point(float aXValue = 0.0, float aYValue = 0.0, float aZValue = 0.0) :
		m_x(aXValue),
		m_y(aYValue),
		m_z(aZValue)
	{}

	inline void display()
	{
		std::cout << m_x << "\t" << m_y << "\t" << m_z << std::endl;
	}

private:
	float m_x;
	float m_y;
	float m_z;
};

int main(int argc, char** argv)
{
	Point point1(1.0, 2.0, 3.0);
	std::cout << "Display point1" << std::endl;
	point1.display();

	Point* p_point1(&point1); // C++ equivalent of C code: Point* p_point1 = &point1;
	Point* p_point2(0); // C++ equivalent of C code: Point* p_point2 = NULL;

	std::cout << "Display p_point1" << std::endl;
	std::cout << p_point1 << std::endl;
	p_point1->display();

	{
		Point* p_point3 = new Point(4.0, 5.0, 6.0);
		p_point3->display();

		p_point2 = p_point3; 

		// The pointers are stored in different memory cells
		std::cout << &p_point2 << std::endl;
		std::cout << &p_point3 << std::endl;

		// But they store the same memory address
		std::cout << p_point2 << std::endl;
		std::cout << p_point3 << std::endl;

		p_point2->display();
		p_point3->display();
	}

	// p_point3 no longer exisits
	// But the memory pointed by p_point3 has not been released
	std::cout << "Display p_point2" << std::endl;
	p_point2->display();

	// Can only free memory that has been dynamically allocated
	// delete p_point1; // Segmentation fault

	// Release the memory pointed by p_point2
	delete p_point2;
	p_point2 = 0;

	//p_point2->display(); // Segmentation fault
	
	Point* p_point4;

	// p_point4 has not been initliased, it stores a random address.
	// In fact it contains what ever was in the memory cell before the creation of the variable
	std::cout << p_point4 << std::endl;
	// p_point4->display(); // Segmentation fault
	
	return 0;
}
