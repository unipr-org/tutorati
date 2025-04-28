#include <iostream>
using namespace std;

template<class T>
class Multiset {
private:
	T* elements;
	int capacity;
	int count;

	void enlarge () {
		this->capacity = this->capacity * 2;
		T* new_elements = new T[this->capacity];

		for (int i = 0; i < this->count; ++i){
			new_elements[i] = elements[i];
		}

		delete [] this->elements;
		this->elements = new_elements;
	}

public:
	~Multiset() {
		delete [] elements;
	}

	Multiset() {
		this->elements = new T[5];
		this->count = 0;
		this->capacity = 5;
	}

	Multiset(const Multiset& other) {
		this->count = other.count;
		this->capacity = other.capacity;
		this->elements = new T[other.capacity];

		for (int i = 0; i < other.count; i++) {
			this->elements[i] = other.elements[i];
		}
	}

	Multiset& operator=(const Multiset& other) {
		if(this != &other) {
			delete [] elements;

			this->count = other.count;
			this->capacity = other.capacity;
			this->elements = new T[other.capacity];

			for (int i = 0; i < other.count; i++) {
				this->elements[i] = other.elements[i];
			}
		}
		return *this;
	}

	bool isEmpty() const {
		return this->count == 0;
	}

	void add(T value) {
		if(this->count == this->capacity)
			enlarge();
		elements[count++] = value;
	}

	int size() const {
		return this->count;
	}

	T get(int index) const {
		return this->elements[index];
	}

	int cardinality(T value) const {
		int count = 0;
		for (int i = 0; i < this->count; i++) 
			if(this->elements[i] == value)
				count++;
		return count;
	}

	bool contains (T value) {
		for (int i = 0; i < this->count; i++) 
			if(this->elements[i] == value)
				return true;
		return false;
	}

	Multiset<T> intersection(const Multiset<T>& other) const {
		Multiset<T> result;

		for (int i = 0; i < this->count; i++) {
			for (int ii = 0; ii < other.count; ii++) {
				if (this->elements[i] == other.elements[ii]
						&& !result.contains(this->elements[i]))
					result.add(this->elements[i]);
			}
		}
		return result;
	}
};

template<class T>
ostream& operator<<(ostream& os, const Multiset<T>& ms) {
	os << "{";
	for (int i = 0; i < ms.size(); i++) {
		os << ms.get(i);

		if (i < ms.size() - 1)
			os << ", ";
	}
	os << "}";
	return os;
}



int main() {
	Multiset<int> ms1;
	ms1.add(1);
	ms1.add(2);
	ms1.add(2);
	ms1.add(3);

	Multiset<int> ms2;
	ms2.add(2);
	ms2.add(4);

	Multiset<int> ms3 = ms1.intersection(ms2);

	cout << ms1 << endl;
	cout << ms2 << endl;
	cout << ms3 << endl;


	return 0;
}



