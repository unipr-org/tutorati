#include <string>
#include <iostream>

using namespace std;

class Studente{

    protected:

    string nome;
    int eta;

    public:

    Studente(string nome, int eta){
        this->nome = nome;
        this->eta = eta;
    }

    void stampa(ostream& dest) const{
        dest << "Nome: " << nome << "\nEta': " << eta << endl;
    }

};


class StudenteTriennale : public Studente{

    protected:

    int matricola;
    string corso;
    double media;

    public: 

    StudenteTriennale(string nome, int eta, int matricola, string corso, double media) : Studente(nome, eta){
        this->matricola = matricola;
        this->corso = corso;
        this->media = media;
    }

    void stampa(ostream& dest) const{
        Studente::stampa(dest);
        dest << "Matricola: " << matricola << "\nCorso: " << corso << "\nMedia: " << media << endl;
    }

    bool operator<(const StudenteTriennale& other) const{
       return this->media < other.media;
    }

};

class StudenteMagistrale : public StudenteTriennale{

    private:
     
    string specialistica;

    public:

    StudenteMagistrale(string nome, int eta, int matricola, string corso, double media, string specialistica) : StudenteTriennale(nome, eta, matricola, corso, media){
        this->specialistica = specialistica;
    }

    void stampa(ostream& dest)const{
        StudenteTriennale::stampa(dest);
        dest << "Specialistica: " << specialistica << endl;
    }

};

void test(Studente s){
    s.stampa(cout);
}

int main(){
    Studente s1("Mario Rossi", 21);

    s1.stampa(cout);

    StudenteTriennale s2("Mario NonRossi", 22, 123, "informatica", 28);
    StudenteTriennale s3("Giovanni", 24, 456, "informatica", 25.7);

    s2.stampa(cout);
    s3.stampa(cout);

    if(s2 < s3){
        cout << "Vero" << endl;
    } else {
        cout << "Falso" << endl;
    }

    StudenteMagistrale s4("Marco", 26, 30, "informatica", 28.5, "scienze informatiche");

    s4.stampa(cout);

    cout << (s3 < s4) << " " << (s4 < s3) << endl;

    test(s1); // Studente
    test(s2); // StudenteTriennale
    test(s4); // StudenteMagistrale

}