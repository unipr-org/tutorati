#include <iostream>
#include <string>
using namespace std;

class Prodotto {
private:
    int codice;
    string nome;
    double prezzo;
    int quantita;
    bool disponibilita;

public:
    Prodotto() : Prodotto(0, "", 0, 0) { }
    Prodotto(int codice, string nome) : Prodotto(codice, nome, 0, 0){ }
    Prodotto(int codice, string nome, double prezzo, int quantita){
        this->codice = codice;
        this->nome = nome;
        this->prezzo = prezzo;
        this->quantita = quantita;
        this->disponibilita = quantita > 0;
    }

    int getCodice() const { return this->codice; }
    string getNome() const { return this->nome; }
    double getPrezzo() const { return this->prezzo; }
    int getQuantita() const { return this->quantita; }
    bool isDisponibile() const { return this->disponibilita; }

    void setCodice(const int& codice) {
        if (codice < 0)
            throw string("Errore: il codice deve essere positivo");
        
        this->codice = codice;
    }

    void setNome(const string& nome) { this->nome = nome; }

    void setPrezzo(const double& prezzo) {
        if (prezzo < 0) 
            throw string("Errore: il prezzo deve essere positivo");
        this->prezzo = prezzo;
    }

    void setQuantita(const int& quantita) {
        if (quantita < 0)
            throw string("Errore: la quantita deve essere positiva");
        
        this->quantita = quantita;
        this->disponibilita = quantita > 0;
    }

    void aggiungiQuantita() { aggiungiQuantita(1); }

    void aggiungiQuantita(int quantita) {
        if (quantita <= 0)
            throw string("Errore: la quantita deve essere positiva");
        
        this->quantita += quantita;
        this->disponibilita = this->quantita > 0;
    }

    void rimuoviQuantita() { rimuoviQuantita(1); }

    void rimuoviQuantita(int quantita) {
        if (this->quantita == 0) 
            throw string("Errore: la quantita e' gia' zero");
        
        if (quantita > this->quantita) 
            throw string("Errore: la quantita non puo' essere negativa");
        
        this->quantita -= quantita;
        this->disponibilita = this->quantita > 0;
    }

    Prodotto operator+(const Prodotto& other) const {
        if(this->codice == other.getCodice()){
            Prodotto p(this->codice, 
                        this->nome, 
                        this->prezzo, 
                        this->quantita + other.getQuantita());
            return p;
        }
        throw string("Errore: i due oggetti hanno codice diverso, impossibile sommarli");
    }

    bool operator==(const Prodotto& other) const {
        return this->codice == other.getCodice();
    }
    bool operator!=(const Prodotto& other) const {
        return this->codice != other.getCodice();
    }

    // Operatore di incremento postfisso
    Prodotto operator++(int valore) {
        Prodotto result(this->codice, this->nome, this->prezzo, this->quantita);
        this->aggiungiQuantita();
        return result;
    }

    // Operatore di incremento infisso
    Prodotto operator++() {
        Prodotto result(this->codice, this->nome, this->prezzo, this->quantita);
        result.aggiungiQuantita();
        this->aggiungiQuantita();
        return result;
    }

    void print() const {
        cout << "Nome: " << this->nome << " [" 
            << this->codice << "], € " << this->prezzo << ", quantità: " << this->quantita << endl;
    }
};

ostream& operator<<(ostream& os, const Prodotto& p) {
    os << p.getNome() << " [id=" 
        << p.getCodice() << "], €" 
        << p.getPrezzo() << ", quantità: " 
        << p.getQuantita() << ", disponibile: "
        << (p.isDisponibile() ? "si" : "no") << endl;
    return os;
}

void testProdotto() {
    cout << endl << " ==== Test classe Prodotto ==== " << endl;

    cout << endl << " ==== Costruttori ==== " << endl;
    Prodotto p1;
    p1.print();

    Prodotto p2(1, "Tastiera");
    p2.print();

    Prodotto p3(2, "Mouse", 20, 5);
    p3.print();

    cout << endl << " ==== Test setter ==== " << endl;
    p3.setQuantita(10);
    p3.print();

    cout << endl << " ==== Test aggiungiQuantita ==== " << endl;
    p2.aggiungiQuantita(20);
    p2.print();
    p2.aggiungiQuantita();
    p2.print();

    cout << endl << " ==== Test rimuoviQuantita ==== " << endl;
    p2.rimuoviQuantita(8);
    p2.print();

    cout << endl << " ==== Test rimuoviQuantita con errore ==== " << endl;
    try {
        p2.rimuoviQuantita(100);
        p2.print();
    } catch (const string& e) {
        cerr << e << endl;
    }

    cout << endl << " ==== Test overload operatore di output (<<) ==== " << endl;
    cout << p2;

    cout << endl << " ==== Test con errore overload operatore di somma (+) ==== " << endl;
    try {
        Prodotto p4 = p1 + p3;
        cout << p4 << endl;
    } catch (const string& e) {
        cerr << e << endl;
    }

    cout << endl << " ==== Test overload operatore di somma (+) ==== " << endl;
    Prodotto p5(2, "Mouse da gaming", 20, 60);
    Prodotto p6 = p5 + p3;
    cout << p6;

    cout << endl << " ==== Test overload operatore di confronto (==) ==== " << endl;
    cout << "True: " << (p3 == p5) << endl;
    cout << "False: " << (p1 == p2) << endl;

    cout << endl << " ==== Test overload operatore di confronto (!=) ==== " << endl;
    cout << "False: " << (p3 != p5) << endl;
    cout << "True: " << (p1 != p2) << endl;
    
    cout << endl << " ==== Test overload operatore di incremento postfisso (++) ==== " << endl;
    cout << "p3 pre incremento: " << p3;
    Prodotto p4 = p3++;
    cout << "p4: " << p4;
    cout << "p3 post incremento: " << p3;

    cout << endl << " ==== Test overload operatore di incremento infisso (++) ==== " << endl;
    cout << "p3 pre incremento: " << p3;
    p4 = ++p3;
    cout << "p4: " << p4;
    cout << "p3 post incremento: " << p3;

    cout << endl << " ==== Test incremento ==== " << endl;
    cout << "p3 pre incremento: " << p3;
    p4++;
    cout << "p3 post incremento: " << p3;
    cout << "p4 post incremento: " << p4;

    cout << endl << " ==== Fine Test classe Prodotto ==== " << endl;
}

int main() {
    testProdotto();
    return 0;
}