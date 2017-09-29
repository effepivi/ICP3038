#include <iostream>

int main(int argc, char** argv) {
	if (argc == 3) {
		float f1, f2;
		f1 = atof(argv[1]);
		f2 = atof(argv[2]);
		std::cout << "sum = " << f1 + f2 << std::endl;
		return 0;
	}
	else {
		std::cout << "Usage:\t" << argv[0] << " f1 f2" << std::endl;
		return 1;
	}
}
