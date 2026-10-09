import std;
using namespace std;


template <typename T>
requires integral<T>
T GenerateRandom(T lower, T upper){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<T> dis(lower, upper);
	return dis(gen);
}

template <typename T>
requires floating_point<T>
T GenerateRandom(T lower, T upper) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<T> dis(lower, upper);
    return dis(gen);
}

template <typename T>
complex<T> GenerateRandom(complex<T> lower, complex<T> upper) {
    random_device rd;
    mt19937 gen(rd());
	uniform_real_distribution<T> disRe(lower.real(), upper.real());
	uniform_real_distribution<T> disIm(lower.imag(), upper.imag());
    return complex<T>(disRe(gen), disIm(gen));
}

template<typename T>
class Matrix{
private:
	int _rows;
	int _cols;
	T* _data;
    static constexpr double EPS = 1e-6;

	template<typename U>
	requires integral<U>
	bool equal(const U& a, const U& b) const {
    	return a == b;
	}

	template<typename U>
	requires floating_point<U>
	bool equal(const U& a, const U& b) const {
		return abs(a - b) < EPS;
	}
	template<typename U>
	bool equal(complex<U> a, complex<U> b) const{
		return abs(a.real() - b.real()) < EPS && abs(a.imag() - b.imag()) < EPS;
	}
public:
	Matrix(int r, int c, T value) {
		if(r <= 0 || c <= 0){
			throw invalid_argument("matrix dimensions must be > 0");
		}
		_rows = r;
		_cols = c;
		_data = new T[_rows * _cols];
		for(int i = 0; i < _rows * _cols; i++){
			_data[i] = value;
		}

	}
	Matrix(int r, int c, T lowerborder, T upperborder) : _rows(r), _cols(c){
		if(_rows <= 0 || _cols <= 0){
			throw invalid_argument("matrix dimensions must be > 0");
		}
		_data = new T[_rows * _cols];
		for(int i = 0; i < _rows * _cols; i++){
			_data[i] = GenerateRandom(lowerborder, upperborder);
		}

	}
	~Matrix(){delete[] _data;}
	Matrix(const Matrix& other){
		_rows = other._rows;
		_cols = other._cols;
		_data = new T[_rows * _cols];
		for(int i = 0; i < _rows * _cols; i++){
			_data[i] = other._data[i];
		}
	}
	void swap(Matrix& other){
		std::swap(_rows, other._rows);
		std::swap(_cols, other._cols);
		std::swap(_data, other._data);
	}
	Matrix& operator=(const Matrix& other){
		Matrix tmp(other);
		this->swap(tmp);
		return *this;
	}
	T& operator()(int r, int c){
		if(r < 0 || r >= _rows || c < 0 || c>= _cols){
			throw out_of_range("index out of range");
		}
		return _data[r * _cols + c];
	}
	const T& operator()(int r, int c) const{
		if(r < 0 || r >= _rows || c < 0 || c>= _cols){
			throw out_of_range("index out of range");
		}
		return _data[r * _cols + c];
	}
	bool operator==(const Matrix& other) const {
		if(_rows != other._rows || _cols != other._cols){
			return false;
		}
		for(int i = 0; i < _rows * _cols; i++){
			if(!equal(_data[i], other._data[i])){
				return false;
			}
		}
		return true;
	}
	bool operator!=(const Matrix& other) const {
		return !(*this == other);
	}

	Matrix operator+(const Matrix& other) const {
		if(_rows != other._rows || _cols != other._cols){
			throw invalid_argument("matrix dimensions must be equal");
		}
		Matrix res(_rows, _cols, 0);
		for(int i = 0; i < _rows * _cols; i++){
			res._data[i] = _data[i] + other._data[i];
		}
		return res;
	}

	Matrix operator-(const Matrix& other) const {
		if(_rows != other._rows || _cols != other._cols){
			throw invalid_argument("matrix dimensions must be equal");
		}
		Matrix res(_rows, _cols, 0);
		for(int i = 0; i < _rows * _cols; i++){
			res._data[i] = _data[i] - other._data[i];
		}
		return res;
	}

	Matrix operator*(const Matrix& other) const {
		if (_cols != other._rows) {
			throw invalid_argument("matrix dimensions must be compatible");
		}

		Matrix res(_rows, other._cols, 0);

		for (int i = 0; i < _rows; i++) {
			for (int j = 0; j < other._cols; j++) {
				for (int k = 0; k < _cols; k++) {
					res(i, j) += (*this)(i, k) * other(k, j);
				}
			}
		}

		return res;
	}

	Matrix operator*(const T& scalar) const{
		Matrix res(_rows, _cols, 0);
		for(int i = 0; i < _rows * _cols; i++){
			res._data[i] = _data[i] * scalar;
		}
		return res;
	}

	Matrix operator/(const T& scalar){
		if(scalar == T{}){
			throw invalid_argument("division by zero");
		}
		Matrix res(_rows, _cols, 0);
		for(int i = 0; i < _rows * _cols; i++){
			res._data[i] = _data[i] / scalar;
		}
		return res;
	}

	T trace() const{
		if(_rows != _cols){
			throw invalid_argument("matrix must be square");
		}
		T sum = T{};
		for(int i = 0; i < _rows; i++){
			sum += _data[_cols * i + i];
		}
		return sum;
	}

	friend ostream& operator<<(ostream& out, const Matrix& matrix){
		for(int i = 0; i < matrix._rows; i++){
			for(int j = 0; j < matrix._cols; j++){
				out << matrix(i, j) << ' ';
			}
			out << '\n';
		}
		return out;
	}







	int get_rows() const {return _rows;}
	int get_cols() const {return _cols;}


};

template<typename T>
Matrix<T> operator*(const T& scalar, const Matrix<T>& matrix){
	return matrix * scalar;
}

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