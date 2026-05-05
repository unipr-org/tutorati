#include <iostream>
#include <string>

using namespace std;

class Veicolo{

    protected:

    int velocita_massima;
    int n_ruote;
    string modello;

    public:

    Veicolo(int velocita_massima, int ruote, string modello){
        if(velocita_massima <= 0){
            throw invalid_argument("Velocita non valida");
        } else {
            this->velocita_massima = velocita_massima;
        }
        if( ruote < 0){
            throw invalid_argument("Ruote non valide");
        } else {
            this->n_ruote = ruote;   
        }
        
        this->modello = modello;
    }

    void stampa(ostream& dest) const {
        dest << "Modello: " << modello << "\nVelocita Massima: " << velocita_massima << "\nNumero ruote: " << n_ruote;
    }

};

class VeicoloMotorizzato : public Veicolo{

    protected:

    string targa;
    string carburante;

    public:

    VeicoloMotorizzato(int velocita_massima, int ruote, string modello, string targa, string carburante) : Veicolo(velocita_massima, ruote, modello) {
        this->targa = targa;
        this->carburante = carburante;
    }

    void stampa(ostream& dest) const{
        Veicolo::stampa(dest);
        dest << "Targa: " << targa << "\nCarburante: " << carburante;
    }

};

class Automobile : public VeicoloMotorizzato{

    protected:

    bool supercar;
    string bagaliaio;

    public:

    Automobile(int velocita_massima, string modello, string targa, string carburante, bool supercar, string bagagliaio) : VeicoloMotorizzato(velocita_massima, 4, modello, targa, carburante){
        this->supercar = supercar;
        this->bagaliaio = bagagliaio;
    }

    void stampa(ostream& dest) const{
        VeicoloMotorizzato::stampa(dest);
        dest << "Supercar: " << (supercar ? "Si" : "No") << "\nBagagliaio: " << bagaliaio;
    }

};

class Camion : public VeicoloMotorizzato{

    protected:

    string rimorchio;

    public:

    Camion(int velocita_massima,int ruote, string modello, string targa, string carburante, string rimorchio) : VeicoloMotorizzato(velocita_massima, ruote, modello, targa, carburante){
        this->rimorchio = rimorchio;
    }

    void stampa(ostream& dest) const{
        VeicoloMotorizzato::stampa(dest);
        dest << "Rimorchio: " << rimorchio << endl;
    }

};

int main(){

}