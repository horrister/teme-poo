/*Implementați în C++ o clasă Cinematograf care gestionează cinematografele dintr-un oraș.

1. Enumerare

Definiți enumerarea TipSala cu valorile CLASIC = 1, IMAX = 2 și VIP = 3.

2. Atribute

Clasa are următoarele atribute private:
- cod: un identificator unic, constant (const int);
- nume: numele cinematografului (string);
- tipSala: tipul sălii principale (TipSala);
- nrProiectii: numărul de proiecții programate astăzi (int);
- bileteVandute: un vector alocat dinamic (int*) cu numărul de bilete vândute la fiecare proiecție.

Clasa are și un atribut static public nrCinematografe, care numără cinematografele create. Îl inițializați cu 0 în afara clasei.

3. Constructori și destructor

- Constructor fără parametri: cod primește valoarea ++nrCinematografe, numele este "Necunoscut", tipul sălii este CLASIC, iar nrProiectii este 0 și vectorul este nullptr.
- Constructor cu toți parametrii: primește codul, numele, tipul sălii, numărul de proiecții și vectorul de bilete. Faceți copierea în profunzime doar dacă nrProiectii > 0 și vectorul nu este nullptr. Altfel, puneți 0 și nullptr. Contorul static se incrementează.
- Constructor de copiere: face o copie în profunzime. Obiectul nou primește un cod nou (++nrCinematografe).
- Destructor: eliberează memoria alocată.

4. Operatori

- operator=: întoarce Cinematograf&, verifică auto-atribuirea (this != &c), eliberează memoria veche și copiază în profunzime. Codul nu se modifică.
- operator>: compară două cinematografe după numărul total de bilete vândute (suma elementelor din vector) și întoarce true dacă obiectul curent a vândut mai multe.

5. Metode de acces (get/set)

- getNume() / setNume(string): noul nume trebuie să aibă cel puțin 3 caractere. Altfel aruncați excepția "Nume prea scurt".
- getNrProiectii(): întoarce numărul de proiecții.
- getBileteVandute(): întoarce o copie a vectorului, nu pointerul intern.
- setBileteVandute(int* vector, int nrP): dacă nrP <= 0 sau vectorul este nullptr, aruncați excepția "Date invalide". Altfel eliberați vectorul vechi, actualizați nrProiectii și copiați valorile.

6. Alte metode

- afisareCinematograf(): afișează codul, numele, tipul sălii ca text (CLASIC, IMAX sau VIP) și biletele vândute pe fiecare proiecție, în formatul 120, 85, 64.
- int totalBilete(): întoarce suma biletelor vândute.
- float medieBilete(): întoarce media biletelor pe proiecție, sau 0 dacă nu există proiecții.

7. Funcția int main()

1. Creați c1 cu constructorul fără parametri și afișați-l.
2. Alocați dinamic vectorul {120, 85, 64, 150} și creați prin pointer (new) cinematograful pCity cu codul 15, numele "City Cinema", tipul IMAX și 4 proiecții. Afișați-l.
3. Creați c2 ca copie a lui *pCity și afișați-l.
4. Atribuiți c1 = *pCity, apoi testați auto-atribuirea c1 = c1. Afișați c1.
5. Folosind setter-ul, dați-i lui c2 vectorul nou {200, 180} cu 2 proiecții.
6. Testați într-un bloc try...catch un setNume("AB") și afișați mesajul excepției.
7. Folosiți getBileteVandute() ca să afișați biletele lui c2, apoi eliberați copia primită.
8. Comparați c1 și c2 cu operator> și afișați care a vândut mai multe bilete.
9. Afișați media biletelor pentru c1 și numărul total de cinematografe construite.
10. Eliberați toată memoria alocată dinamic: pointerul pCity, vectorul din main și copia primită de la getter.*/

#include<iostream>
#include<string>

using namespace std;

enum tipSala { CLASIC = 1, IMAX = 2, VIP = 3 };

class Cinematograf {
private:
	const int cod;
	string nume;
	tipSala tip;
	int nrProiectii;
	int* bileteVandute;
public:
	static int nrCinematografe;

	Cinematograf():cod(++nrCinematografe) {
		this->nume = "Necunoscut";
		this->tip = CLASIC;
		this->nrProiectii = 0;
		this->bileteVandute = nullptr;
	}
	Cinematograf( int cod, string nume, tipSala tip, int nrProiectii, int* bileteVandute):cod(cod) {
		this->nume = nume;
		this->tip = tip;
		if ( nrProiectii >0 && bileteVandute != nullptr) {
			this->nrProiectii = nrProiectii;
			this->bileteVandute = new int[nrProiectii];
			for (int i = 0; i < nrProiectii; i++) {
				this->bileteVandute[i] = bileteVandute[i];
			}
		}
		else {
			this->nrProiectii = 0;
			this->bileteVandute = nullptr;
		}
		nrCinematografe++;
	}
//construct de copiere
	Cinematograf(const Cinematograf& c) : cod(++nrCinematografe) {
		this->nume = c.nume;
		this->tip = c.tip;
		this->nrProiectii = c.nrProiectii;
		if (c.bileteVandute != nullptr) {
			this->bileteVandute = new int[c.nrProiectii];
			for (int i = 0; i < c.nrProiectii; i++) {
				this->bileteVandute[i] = c.bileteVandute[i];
			}
		}
		else {
			this->bileteVandute = nullptr;
		}
	}
//destructor
	~Cinematograf() {
		if (this->bileteVandute != nullptr) {
			delete[] this->bileteVandute;
		}
	}
//get/set
	string getNume() {
		return this->nume;
	}

	void setNume(string numeNou) {
		if (numeNou.length() >= 3) {
			this->nume = numeNou;
		}
		else {
			throw "Nume prea scurt";
		}
	}
	int getnrProiectii() {
		return this->nrProiectii;
	}
};

//initializam atributul static
int Cinematograf::nrCinematografe = 0;

int main() {
	Cinematograf c1;
	cout << "c1: " << c1.getNume() << ", " << c1.getnrProiectii() << " proiectii"
		<< endl;
	int* bilete = new int[4] { 67, 21, 159, 213};
	Cinematograf c2(15, "Cinema City", IMAX, 4, bilete);
	cout << "c2: " << c2.getNume() << ", " << c2.getnrProiectii() << " proiectii" << endl;

	cout << "Am construit: " << Cinematograf::nrCinematografe << " cinematografe!" << endl;
	delete[] bilete;
	return 0;
}
