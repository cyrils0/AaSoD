import std;
import matrix;
using namespace std;

template <typename T>
bool AreCoplanar(const Matrix<T>& matrix) {
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

		Matrix<complex<double>> vectors(3, 3, complex<double>{});

		vectors(0, 0) = {1.0, 0.0};
		vectors(0, 1) = {0.0, 0.0};
		vectors(0, 2) = {0.0, 0.0};

		vectors(1, 0) = {0.0, 0.0};
		vectors(1, 1) = {1.0, 0.0};
		vectors(1, 2) = {0.0, 0.0};

		vectors(2, 0) = {0.0, 0.0};
		vectors(2, 1) = {0.0, 0.0};
		vectors(2, 2) = {0.0, 1.0};

		cout << AreCoplanar(vectors) << '\n';
	} catch(const exception& e){
		cerr << e.what() << '\n';
	}


    return 0;
}