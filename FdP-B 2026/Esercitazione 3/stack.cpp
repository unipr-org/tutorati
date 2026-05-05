#include <iostream>
#include <exception>
using namespace std;

class Stack{
	private:
		int* A;
		int dim;
		int top;

		void enlarge() {
			int* new_elem = new int[dim+10];
			for (int i=0; i < dim; i++)
				new_elem[i] = A[i];
			dim+=10;
			delete[] A;
			A = new_elem;
		}

	public:
		Stack() {
			dim = 10;
			top = 0;
			A = new int[10];
		}

		Stack(const Stack& s) {

				A = new int[s.dim];
				for (int i=0; i < s.top; i++)
					A[i] = s.A[i];

				dim = s.dim;
				top = s.top;

		}

		~Stack(){
			if (A != nullptr)
				delete[] A;
		}

		void push(int x) {
			if (top == dim)
				enlarge();
			A[top] = x;
			top++;
		}

		int pop() {
			if (isEmpty())
				throw out_of_range("Stack vuoto");
			top--;
			return A[top];
		}

		const Stack& operator=(const Stack& s){
			if (this != &s){
				delete[] A;

				A = new int[s.dim];
				for (int i=0; i < s.top; i++)
					A[i] = s.A[i];

				dim = s.dim;
				top = s.top;

			}

			return *this;
		}

		bool operator==(const Stack& s){
			if(this->top != s.top){
				return false;
			}
			for(int i = 0; i < this->top; i++){
				// if(this->A[i] != s.A[i])
				if(this->getElem(i) != s.getElem(i)){
					return false;
				}
			}
			return true;
		}

		bool operator!=(const Stack& s){
			if(this->top != s.top){
				return true;
			}
			for(int i = 0; i < this->top; i++){
				if(this->getElem(i) != s.getElem(i)){
					return true;
				}
			}
			return false;
			
			// return !(*this == s);
			// return !(this->operator==(s));
		} 

		bool operator< (const Stack& s){
			//if( this->operator==(s)){
			//	return false;
			//}
			
			if(this->top >= s.top){
				return false;
			}
			for(int i = 0; i < this->top; i++){
				if(this->getElem(i) != s.getElem(i)){
					return false;
				}
			}
			return true;
		}

		bool isEmpty() {
			return top == 0;
		}

		int getElem(int x) const{
			return A[x];
		}

		int size() const{
			return top;
		}

};	

ostream& operator<<(ostream& dest, const Stack& s){
	if (s.size() == 0){
		dest << "{}";
		return dest;
	}

	dest<< "{";
	for (int i=0; i < s.size(); i++){
		dest << s.getElem(i);
		if (i < s.size() -1)
			dest << ", ";
	}

	dest << "}";
	return dest;
}	

int main(){
	Stack p1;
	cout << p1 << endl;
	p1.push(3);
	p1.push(4);
	p1.push(5);
	cout << p1 << endl;

	Stack p2;
	//p2.pop();
	cout << p2 << endl;

	Stack p3(p1);

	cout << (p3 == p1) << endl;
	cout << (p3 != p2) << endl;

	p3.pop();

	cout << p3 << endl;

	cout << (p3 < p1) << endl;

	return 0;
}