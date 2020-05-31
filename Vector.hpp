#ifndef VECTOR_H_
#define VECTOR_H_

#include<exception>

template<class T>
class Vector {
private:
	T* data;
	int capacity;
	int lenght;

	void resize();
	void copyVector(const Vector<T>&);
public:
	Vector(int = 1);
	Vector(const Vector<T>&);
	Vector<T>& operator=(const Vector<T>&);
	~Vector();

	int size() const;
	void add(const T&);
	void remove(const T&);

	bool operator==(const Vector<T>&);
	T& operator[](const int);
	const T& operator[](const int)const;

};

template<class T>
void Vector<T>::resize() {
	T* temp = new T[capacity * 2];
	for (int i = 0; i < lenght; i++)
		temp[i] = data[i];

	delete[] data;
	capacity *= 2;
	data = temp;
}

template<class T>
void Vector<T>::copyVector(const Vector<T>& other) {
	capacity = other.capacity;
	data = new T[other.capacity];
	for (int i = 0; i < other.lenght; i++) {
		data[i] = other.data[i];
	}
	lenght = other.lenght;
}

template<class T>
Vector<T>::Vector(int capacity_) {
	capacity = capacity_;
	data = new T[capacity];
	lenght = 0;
}

template<class T>
Vector<T>::Vector(const Vector<T>& other) {
	copyVector(other);
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other) {
		delete[]data;
		copyVector(other);
	}
	return *this;
}

template<class T>
Vector<T>::~Vector() {
	delete[]data;
}

template<class T>
int Vector<T>::size() const {
	return lenght;
}

template<class T>
void Vector<T>::add(const T& element) {
	if (capacity == lenght) resize();
	data[lenght] = element;
	lenght++;
}

template<class T>
bool Vector<T>::operator==(const Vector<T>& other) {
	if (lenght != other.lenght) return false;
	for (int i = 0; i < lenght; i++) {
		if (data[i] != other.data[i]) return false;
	}
	return true;
}

template<class T>
void Vector<T>::remove(const T& element) {
	int flag = 0;
	for (int i = 0; i < lenght; i++) {
		if (data[i] == element) flag = i;
	}

	T* temp = new T[lenght];
	for (int i = 0; i < flag; i++) temp[i] = data[i];
	for (int i = flag + 1; i < lenght; i++) temp[i - 1] = data[i];

	delete[]data;
	data = temp;
}


template<class T>
T& Vector<T>::operator[] (int index) {
	if (index >= 0 && index <= lenght - 1) return data[index];
	else throw std::out_of_range("Index incorrent!");
}

template<class T>
const T& Vector<T>::operator[] (int index) const {
	if (index >= 0 && index <= lenght - 1) return data[index];
	else throw std::out_of_range("Index incorrent!");
}

#endif