import std;
import matrix;
using namespace std;



int main() {
	try{	
	Matrix<complex<double>> a(1, 2, complex<double>(0.0, 0.0));
	Matrix<complex<double>> b(1, 2, complex<double>(0.0, 0.0));

	a(0, 0) = complex<double>(1.0, 2.0);
	a(0, 1) = complex<double>(3.0, 4.0);

	b(0, 0) = complex<double>(1.0 + 1e-8, 2.0);
	b(0, 1) = complex<double>(3.0, 4.0 + 1e-8);

	cout << (a == b) << '\n';
	cout << (a != b) << '\n';
	} catch(const exception& e){
		cerr << e.what() << '\n';
	}


    return 0;
}