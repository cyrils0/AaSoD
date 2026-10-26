import std;
import matrix;
using namespace std;

template <typename T>
bool are_coplanar(const Matrix<T>& matrix) {
    if (matrix.get_rows() != 3 || matrix.get_cols() != 3) {
        throw invalid_argument("matrix must be 3x3");
    }

    T det =
        matrix(0, 0) * (matrix(1, 1) * matrix(2, 2) - matrix(1, 2) * matrix(2, 1))
        - matrix(0, 1) * (matrix(1, 0) * matrix(2, 2) - matrix(1, 2) * matrix(2, 0))
        + matrix(0, 2) * (matrix(1, 0) * matrix(2, 1) - matrix(1, 1) * matrix(2, 0));

    if constexpr (is_integral_v<T>) {
        return det == T{};
    } else {
        return abs(det) < 1e-6;
    }
}

int main() {
	try{	

		Matrix<complex<double>> complex_vectors(3, 3, complex<double>{});
		Matrix<double> double_vectors(3, 3, 0.0);
		Matrix<int> int_vector(3, 3, 0);
		Matrix<int> int_vectors(3, 3, 1, 10);

		complex_vectors(0, 0) = {1.0, 0.0};
		complex_vectors(0, 1) = {0.0, 0.0};
		complex_vectors(0, 2) = {0.0, 0.0};
		complex_vectors(1, 0) = {0.0, 0.0};
		complex_vectors(1, 1) = {1.0, 0.0};
		complex_vectors(1, 2) = {0.0, 0.0};
		complex_vectors(2, 0) = {0.0, 0.0};
		complex_vectors(2, 1) = {0.0, 0.0};
		complex_vectors(2, 2) = {0.0, 1.0};

		double_vectors(0, 0) = 1.0;
		double_vectors(0, 1) = 1.0;
		double_vectors(0, 2) = 0.0;
		double_vectors(1, 0) = 0.0;
		double_vectors(1, 1) = 1.0;
		double_vectors(1, 2) = 0.0;
		double_vectors(2, 0) = 1.0;
		double_vectors(2, 1) = 0.0;
		double_vectors(2, 2) = 1.0;


		int_vector(0, 0) = 1;
		int_vector(0, 1) = 2;
		int_vector(0, 2) = 3;
		int_vector(1, 0) = 4;
		int_vector(1, 1) = 5;
		int_vector(1, 2) = 6;
		int_vector(2, 0) = 7;
		int_vector(2, 1) = 8;
		int_vector(2, 2) = 9;
		
		cout << boolalpha<< are_coplanar(int_vector) << '\n';
		cout << are_coplanar(complex_vectors) << '\n';
		cout << are_coplanar(double_vectors) << '\n';
		cout << int_vectors << '\n';
	} catch(const exception& e){
		cerr << "exception: "<< e.what() << '\n';
	}

    return 0;
}