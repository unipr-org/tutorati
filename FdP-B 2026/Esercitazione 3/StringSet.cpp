#include <iostream>
using namespace std;

#define MAX_SIZE 100

class StringSet {
	private:
		int dim;
		string* set;

	public:

		StringSet() {
			this->dim = 0;
			this->set = new string[0];

		}

		StringSet(string s[], int n) {
			this->dim = 0;
			this->set = new string[0];
			for(int i=0; i < n; i++)
				add(s[i]);
		}

		StringSet(const StringSet& s){
			this->dim = s.dim;
			this->set = new string[s.dim];
			for(int i = 0; i < s.dim; i++){
				this->set[i] = s.set[i];
			}
		}

		~StringSet(){
			delete[] set;
		}

		bool contains(const string& x) const{
			for (int i=0; i < dim; i++)
				if (x == set[i])
					return true;
			return false;
		}

		int size() const{
			return dim;
		}

		/*void add(string x) {
			if(!contains(x)){
				if (dim == MAX_SIZE)
					cout << "Errore: lunghezza massima raggiunta" << endl;
				else {
					set[dim] = x;
					dim++;
				}
			}
		}*/

		void add(string x) {
			if(!contains(x)){
				string* new_set = new string[dim+1];
				for (int i=0; i < dim; i++)
					new_set[i] = set[i];
				new_set[dim] = x;

				dim++;
				delete[] set;
				set = new_set;

			}
		}

		const StringSet& operator= (const StringSet& s){
			if(this != &s){
				delete[] this->set;
				this->dim = s.dim;
				this->set = new string[s.dim];
				for(int i = 0; i < s.dim; i++){
					this->set[i] = s.set[i];
				}
				return *this;
			} else{
				return *this;
			}
		}

		bool operator<(const StringSet& other) const {
			if (size() > other.size())
				return false;

			for (int i =0 ; i < dim; i++){
				if(!other.contains(set[i]))
					return false;
			}
			return true;
		}

		StringSet operator+(const StringSet& other) const{
			StringSet result;

			if (size() + other.size() > MAX_SIZE){
				cout << "l'unione dei due set crea un set troppo grande!" << endl;
				return result;
			}


			for (int i=0; i < dim; i++)
				result.add(set[i]);

			for (int i=0; i < other.size(); i++)
				result.add(other.set[i]);

			return result;
		}

		
		string getElem(int i) const {
			if (i < 0 || i >= dim)
				cout << "Errore"<< endl;
			return set[i];
		}

};

ostream& operator<<(ostream& dest, const StringSet& s){
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

	string a[] = {"ciao", "oggi"};

	StringSet s(a,2);

	cout << s << endl;

	StringSet b(s);

	cout << b << endl;

	StringSet c = b;

	cout << c << endl;

	return 0;
}