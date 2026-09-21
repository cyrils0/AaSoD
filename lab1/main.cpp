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
T GenerateRandom(complex<T> lower, complex<T> upper) {
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
		swap(_rows, other._rows);
		swap(_cols, other._cols);
		swap(_data, other._data);
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








	int get_rows() const {return _rows;}
	int get_cols() const {return _cols;}


};

int main() {
    Matrix<int> matrix(3, 3, 5);

    cout << matrix(0, 0) << '\n';

    return 0;
}