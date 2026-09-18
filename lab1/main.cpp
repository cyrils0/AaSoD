import std;
using namespace std;

template<typename T>
class Matrix{
private:
	int _rows;
	int cols;
	T* _data;
public:
	Matrix(int r, int c, T value) {
		if(_rows <= 0 || _cols <= 0){
			throw invalid_argument("размеры не могут быть = 0 или < 0");
		}
		_rows = r;
		_cols = c;
		_data = new T[_rows * _cols];
		for(int i = 0; i < _rows * _cols; i++){
			_data[i] = value;
		}

	}
	Matrix(int r, int c, T lowerborder, T upperboarder) : _rows(r), _cols(c){
		if(_rows <= 0 || _cols <= 0){
			throw invalid_argument("размеры не могут быть = 0 или < 0");
		}
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<T> dis(lowerborder, upperborder);


	}
	~Matrix(){delete[] _data;}
	Matrtix(cosnt Matrix& other){
		_rows = other._rows;
		_cols = other._cols;
		_data = new T[_rows * _cols];
		for(int i = 0; i < _rows * _cols; i++){
			_data[i] = other._data[i];
		}
	}
	void swap(const Matrix& other){
		swap(_rows, other._rows);
		swap(_cols, other._cols);
		swap(_data. other._data);
	}
	Matrix& operator=(const Matrix& other){
		Matrix tmp(other);
		this->swap(tmp);
		return *this;
	}




	int get_rows() const {return _rows;}
	int get_cols() const {return _cols;}


};