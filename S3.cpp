/*Să se creeze o clasă numită Biblioteca care să gestioneze mai multe filiale ale unui sistem județean.
Atribute:

    idBiblioteca (întreg, constant) — id-ul unic al filialei.

    nume (șir de caractere / string) — numele filialei (ex: "Sectia Copii").

    nrSali (întreg) — numărul de săli de lectură din filială.

    nrCartiPerSala (pointer la int) — un vector alocat dinamic care reține numărul de cărți existente în fiecare sală.

    totalBiblioteci (întreg, static) — contorizează câte biblioteci au fost create în total. */

#include<iostream>
#include<string>

using namespace std;

class Biblioteca {
private:
	const int idBiblioteca;
	string nume;
	int nrSali;
	int* nrCartiSala;
public:
	static int totalBiblioteci;

	//constructor fara param
	Biblioteca() : idBiblioteca(++totalBiblioteci) {
		this->nume = "Default";
		this->nrSali = 0;
		this->nrCartiSala = nullptr;
	};
	//constructor cu toti param
	Biblioteca(int idBiblioteca, string nume, int nrSali, int* nrCartiSala)
		: idBiblioteca(idBiblioteca) {
		this->nume = nume;
		if (nrSali > 0 && nrCartiSala != nullptr) {
			this->nrSali = nrSali;
			this->nrCartiSala = new int[nrSali];
			for (int i = 0; i < this->nrSali; i++) {
				this->nrCartiSala[i] = nrCartiSala[i];
			}
		}
		else {
			this->nrSali = 0;
			this->nrCartiSala = nullptr;
		}
		totalBiblioteci++;
	}
	//afisare
	void afisareBiblioteca() {
		cout << endl << "Id: " << this->idBiblioteca;
		cout << endl << "Nume: " << this->nume;
		cout << endl << "Nr sali: " << this->nrSali;
		if (this->nrSali > 0) {
			cout << endl << "Carti per sala: ";
			for (int i = 0; i < this->nrSali - 1; i++) {
				cout << this->nrCartiSala[i] << ". ";
			}
			cout << this->nrCartiSala[this->nrSali - 1] << ".";
		}
		cout << endl;
	}
	//destructor
	~Biblioteca() {
		if (this->nrCartiSala != nullptr) {
			delete[] this->nrCartiSala;
		}
	}
};




int Biblioteca::totalBiblioteci = 0;

int main() {
	Biblioteca b1;
	b1.afisareBiblioteca();
	int* carti = new int[3] {1200, 850, 430};
	Biblioteca* pCopii = new Biblioteca(10, "Sectia Copii", 3, carti);
	pCopii->afisareBiblioteca();
	delete pCopii;
	delete[] carti;
	cout << endl << " Am construit " << Biblioteca::totalBiblioteci
		<< " biblioteci!";

	return 0;
}
