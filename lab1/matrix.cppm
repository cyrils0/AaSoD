export module matrix;
import std;
using namespace std;


export template <typename T>
requires integral<T>
T generate_random(T lower, T upper){
	random_device rd;
	mt19937 gen(5);
	uniform_int_distribution<T> dis(lower, upper);
	return dis(gen);
}

export template <typename T>
requires floating_point<T>
T generate_random(T lower, T upper) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<T> dis(lower, upper);
    return dis(gen);
}

export template <typename T>
complex<T> generate_random(complex<T> lower, complex<T> upper) {
    random_device rd;
    mt19937 gen(rd());
	uniform_real_distribution<T> disRe(lower.real(), upper.real());
	uniform_real_distribution<T> disIm(lower.imag(), upper.imag());
    return complex<T>(disRe(gen), disIm(gen));
}

export template<typename T>
class Matrix{
private:
	size_t _rows;
	size_t _cols;
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
	Matrix(size_t r, size_t c, T value) {
		if(r <= 0 || c <= 0){
			throw invalid_argument("matrix dimensions must be > 0");
		}
		_rows = r;
		_cols = c;
		_data = new T[_rows * _cols];
		for(size_t i = 0; i < _rows * _cols; i++){
			_data[i] = value;
		}

	}
	Matrix(size_t r, size_t c, T lowerborder, T upperborder) : _rows(r), _cols(c){
		if(_rows <= 0 || _cols <= 0){
			throw invalid_argument("matrix dimensions must be > 0");
		}
		_data = new T[_rows * _cols];
		for(size_t i = 0; i < _rows * _cols; i++){
			_data[i] = generate_random(lowerborder, upperborder);
		}

	}
	~Matrix(){delete[] _data;}
	Matrix(const Matrix& other){
		_rows = other._rows;
		_cols = other._cols;
		_data = new T[_rows * _cols];
		for(size_t i = 0; i < _rows * _cols; i++){
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
	T& operator()(size_t r, size_t c){
		if(r < 0 || r >= _rows || c < 0 || c>= _cols){
			throw out_of_range("index out of range");
		}
		return _data[r * _cols + c];
		cout << "not const ()" << '\n';
	}
	const T& operator()(size_t r, size_t c) const{
		if(r < 0 || r >= _rows || c < 0 || c>= _cols){
			throw out_of_range("index out of range");
		}
		return _data[r * _cols + c];
		cout << "const ()" << '\n';
	}
	bool operator==(const Matrix& other) const {
		if(_rows != other._rows || _cols != other._cols){
			return false;
		}
		for(size_t i = 0; i < _rows * _cols; i++){
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
		for(size_t i = 0; i < _rows * _cols; i++){
			res._data[i] = _data[i] + other._data[i];
		}
		return res;
	}

	Matrix operator-(const Matrix& other) const {
		if(_rows != other._rows || _cols != other._cols){
			throw invalid_argument("matrix dimensions must be equal");
		}
		Matrix res(_rows, _cols, 0);
		for(size_t i = 0; i < _rows * _cols; i++){
			res._data[i] = _data[i] - other._data[i];
		}
		return res;
	}

	Matrix operator*(const Matrix& other) const {
		if (_cols != other._rows) {
			throw invalid_argument("matrix dimensions must be compatible");
		}

		Matrix res(_rows, other._cols, T{});

		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < other._cols; j++) {
				for (size_t k = 0; k < _cols; k++) {
					res(i, j) += (*this)(i, k) * other(k, j);
				}
			}
		}

		return res;
	}

	Matrix operator*(const T& scalar) const{
		Matrix res(_rows, _cols, 0);
		for(size_t i = 0; i < _rows * _cols; i++){
			res._data[i] = _data[i] * scalar;
		}
		return res;
	}

	Matrix operator/(const T& scalar){
		if(scalar == T{}){
			throw invalid_argument("division by zero");
		}
		Matrix res(_rows, _cols, 0);
		for(size_t i = 0; i < _rows * _cols; i++){
			res._data[i] = _data[i] / scalar;
		}
		return res;
	}

	T trace() const{
		if(_rows != _cols){
			throw invalid_argument("matrix must be square");
		}
		T sum = T{};
		for(size_t i = 0; i < _rows; i++){
			sum += _data[_cols * i + i];
		}
		return sum;
	}

	friend ostream& operator<<(ostream& out, const Matrix& matrix){
		for(size_t i = 0; i < matrix._rows; i++){
			for(size_t j = 0; j < matrix._cols; j++){
				out << matrix(i, j) << ' ';
			}
			out << '\n';
		}
		return out;
	}

	size_t get_rows() const {return _rows;}
	size_t get_cols() const {return _cols;}
};

export template<typename T>
Matrix<T> operator*(const T& scalar, const Matrix<T>& matrix){
	return matrix * scalar;
}