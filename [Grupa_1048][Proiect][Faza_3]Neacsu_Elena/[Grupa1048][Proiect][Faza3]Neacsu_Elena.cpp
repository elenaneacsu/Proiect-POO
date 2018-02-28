// Grupa1048ProiectFaza3NeacsuElena.cpp : Defines the entry point for the console application.
//

//FAZA 2
//Am adaugat clasele Raport in care generez rapoarte pentru 3 clase, FisierBinar in care generez 
//si citesc din fisiere binare, am supraincarcat operatorul >> in fiecare clasa pentru a citi din fisier text.
//Pentru fisierele CSV am lucrat in main.



#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<string> 
using namespace std;

class Cheltuieli {
public:
	virtual int* valabil() = 0;
	virtual void reducere(float p) = 0;
};

class ProdusAlimentar: public Cheltuieli {
private:
	int ziua;
	int luna;
	int an;
	char* denumire;
	float cantitate;
	char unitateMasura[10];
	int valabilitate[3];
	double pret;

public:
	const int id;
	static int nrAlimente;

	ProdusAlimentar() :id(nrAlimente++) {
		this->ziua = 1;
		this->luna = 1;
		this->an = 2000;
		this->denumire = new char[strlen("Necunoscut") + 1];
		strcpy(this->denumire, "Necunoscut");
		this->cantitate = 1;
		strcpy(this->unitateMasura, "Fara");
		for (int i = 0; i < 3; i++) {
			valabilitate[i] = 0;
		}
		this->pret = 0;
	}

	ProdusAlimentar(int v_ziua, int v_luna, int v_an, char* v_denumire, float v_cantitate,
		char v_um[10], int v_valabilitate[3], double v_pret) :id(nrAlimente++) {
		this->ziua = v_ziua;
		this->luna = v_luna;
		this->an = v_an;
		this->denumire = new char[strlen(v_denumire) + 1];
		strcpy(this->denumire, v_denumire);
		this->cantitate = v_cantitate;
		strcpy(this->unitateMasura, v_um);
		for (int i = 0; i < 3; i++) {
			this->valabilitate[i] = v_valabilitate[i];
		}
		this->pret = v_pret;
	}

	ProdusAlimentar(int v_ziua, int v_luna, char* v_denumire, float v_cantitate,
		char v_um[10], int v_valabilitate[3], double v_pret, int v_an = 2017) :id(nrAlimente++), an(v_an) {
		this->ziua = v_ziua;
		this->luna = v_luna;
		this->denumire = new char[strlen(v_denumire) + 1];
		strcpy(this->denumire, v_denumire);
		this->cantitate = v_cantitate;
		strcpy(this->unitateMasura, v_um);
		for (int i = 0; i < 3; i++) {
			this->valabilitate[i] = v_valabilitate[i];
		}
		this->pret = v_pret;
	}

	ProdusAlimentar(const ProdusAlimentar& sursa) :id(sursa.id) {
		this->ziua = sursa.ziua;
		this->luna = sursa.luna;
		this->an = sursa.an;
		this->denumire = new char[strlen(sursa.denumire) + 1];
		strcpy(this->denumire, sursa.denumire);
		this->cantitate = sursa.cantitate;
		strcpy(this->unitateMasura, sursa.unitateMasura);
		for (int i = 0; i < 3; i++) {
			this->valabilitate[i] = sursa.valabilitate[i];
		}
		this->pret = sursa.pret;
		ProdusAlimentar::nrAlimente++;
	}

	ProdusAlimentar &operator=(const ProdusAlimentar& sursa) {
		if (this->denumire != NULL) {
			delete[] denumire;
		}
		this->ziua = sursa.ziua;
		this->luna = sursa.luna;
		this->an = sursa.an;
		this->denumire = new char[strlen(sursa.denumire) + 1];
		strcpy(this->denumire, sursa.denumire);
		this->cantitate = sursa.cantitate;
		strcpy(this->unitateMasura, sursa.unitateMasura);
		for (int i = 0; i < 3; i++) {
			this->valabilitate[i] = sursa.valabilitate[i];
		}
		this->pret = sursa.pret;
		return *this;
	}

	~ProdusAlimentar() {
		if (this->denumire != NULL) {
			delete[] this->denumire;
		}
		ProdusAlimentar::nrAlimente--;
	}

	friend ostream& operator<<(ostream& out, ProdusAlimentar&ca) {
		out << "CHELTUIELI ALIMENTARE" << endl;
		out << "Ziua: " << ca.ziua << endl;
		out << "Luna: " << ca.luna << endl;
		out << "Anul: " << ca.an << endl;
		out << "Denumire produs: " << ca.denumire << endl;
		out << "Cantitate: " << ca.cantitate << endl;
		out << "Unitatea de masura: " << ca.unitateMasura << endl;
		out << "Valabilitate: " << endl;
		out << "Ziua: " << ca.valabilitate[0] << endl;;
		out << "Luna: " << ca.valabilitate[1] << endl;
		out << "An: " << ca.valabilitate[2] << endl;
		out << "Pret: " << ca.pret << endl;
		/*out << "Id: " << ca.id << endl;
		out << "Nr Alimente: " << ca.nrAlimente << endl;*/
		out << endl;
		return out;
	}

	friend istream& operator>>(istream& in, ProdusAlimentar& ca) {
		cout << "CHELTUIELI ALIMENTARE" << endl;
		cout << "Ziua: ";
		in >> ca.ziua;

		cout << "Luna: ";
		in >> ca.luna;

		cout << "Anul: ";
		in >> ca.an;

		in.ignore();
		cout << "Denumire produs: ";
		char buffer[50];
		in.getline(buffer, 50);
		ca.setDenumire(buffer);

		cout << "Cantitate: ";
		in >> ca.cantitate;

		in.ignore();
		cout << "Unitate de masura: ";
		in.getline(ca.unitateMasura, 10);

		cout << "Valabilitate: " << endl;
		cout << "\tZiua: ";
		in >> ca.valabilitate[0];
		//cout << endl;
		cout << "\tLuna: ";
		in >> ca.valabilitate[1];
		//cout << endl;
		cout << "\tAn: ";
		in >> ca.valabilitate[2];

		cout << "Pret: ";
		in >> ca.pret;

		return in;
	}

	int getZiua() {
		return this->ziua;
	}

	void setZiua(int v_ziua) {
		if (v_ziua > 31) {
			throw new exception("Imposibil");
		}
		this->ziua = v_ziua;
	}

	int getLuna() {
		return this->luna;
	}

	void setLuna(int v_luna) {
		if (v_luna > 12) {
			throw new exception("Nu exista aceasta luna");
		}
		else {
			this->luna = v_luna;
		}
	}

	int getAn() {
		return this->an;
	}

	void setAn(int v_an) {
		if (v_an < 1950) {
			throw new exception("Imposibil");
		}
		this->an = v_an;
	}

	char* getDenumire() {
		return this->denumire;
	}

	void setDenumire(char* v_denumire) {
		if (this->denumire != NULL) {
			delete[]this->denumire;
		}
		this->denumire = new char[strlen(v_denumire) + 1];
		strcpy(this->denumire, v_denumire);
	}

	float getCantitate() {
		return this->cantitate;
	}

	void setCantitate(float v_cantitate) {
		if (v_cantitate == 0) {
			throw new exception("Cantitate nula");
		}
		this->cantitate = v_cantitate;
	}

	char* getUnitateMasura() {
		return this->unitateMasura;
	}

	void setUnitateMasura(char v_um[10]) {
		strcpy(this->unitateMasura, v_um);
	}

	int* getValabilitate() {
		return this->valabilitate;
	}

	void setValabilitate(int v_valabilitate[3]) {
		if (v_valabilitate[0] > 31) {
			throw new exception("Nu exista zi");
		}
		if (v_valabilitate[1] > 12) {
			throw new exception("Nu exista luna");
		}
		if (v_valabilitate[2] < 1950) {
			throw new exception("An imposibil de adaugat");
		}
		for (int i = 0; i < 3; i++) {
			this->valabilitate[i] = v_valabilitate[i];
		}
	}

	double getPret() {
		return this->pret;
	}

	int getId() {
		return this->id;
	}

	static int getNrAlimente() {
		return ProdusAlimentar::nrAlimente;
	}

	static void setNrAlimente(int v_nrAlimente) {
		ProdusAlimentar::nrAlimente = v_nrAlimente;
	}

	void setPret(double v_pret) {
		this->pret = v_pret;
	}

	void expira() {
		if ((this->an > valabilitate[2]) || (this->an == valabilitate[2] && this->luna > valabilitate[1]) || (this->an == valabilitate[2] && this->luna == valabilitate[1] && this->ziua>valabilitate[0])) {
			cout << "Produsul a expirat!" << endl;
		}
		else if (this->ziua == valabilitate[0] && this->luna == valabilitate[1] && this->an == valabilitate[2]) {
			cout << "Produsul " << this->denumire << " expira azi." << endl;
		}
		else {
			cout << "Produsul " << this->denumire << " se afla inca in termenul de valabilitate." << endl;
		}
	}

	double pretUnitar() {
		if (this->cantitate == 0) {
			throw new exception("Imposibil!");
		}
		else {
			return this->pret / this->cantitate;
		}
	}

	bool operator>=(int an) {
		if (this->valabilitate[3] >= an)
			return true;
		else
			return false;
	}

	ProdusAlimentar& operator++() {
		if (this->ziua == 31) {
			throw new exception("Nu se poate incrementa");
		}
		else {
			++this->ziua;
		}
		return *this;
	}

	ProdusAlimentar operator++(int) {
		ProdusAlimentar copie = *this;
		if (this->ziua == 31) {
			throw new exception("Nu se poate incrementa");
		}
		else {
			this->ziua++;
		}
		return copie;
	}

	operator double()const {
		return pret;
	}

	bool operator!() const {
		if (valabilitate[2]>an) {
			return true;
		}
		else {
			return false;
		}
	}

	friend ifstream& operator>>(ifstream& in, ProdusAlimentar& ca) {
		/*char c;
		in >> c;*/
		in >> ca.ziua;
		in >> ca.luna;
		in >> ca.an;
		char buffer[50];
		in.ignore();
		in.getline(buffer, 50);
		if (ca.denumire != NULL) {
			delete[] ca.denumire;
		}
		ca.denumire = new char[strlen(buffer) + 1];
		strcpy(ca.denumire, buffer);
		in >> ca.cantitate;

		in.ignore();
		in.getline(ca.unitateMasura, 10);
		for (int i = 0; i < 3; i++) {
			in >> ca.valabilitate[i];
		}
		in >> ca.pret;
		/*	int id1=ca.getId();
		in >> id1;*/
		return in;
	}

	//overriding
	int* valabil() {
		return this->valabilitate;
	}

	void reducere(float p) {
		this->pret = this->pret - (p / 100)*this->pret;
	}

	//metode virtuale
	virtual void afisare() {
		cout << *this;
	}

	virtual void deTip() {
		cout << "Produsul " << this->denumire << " are un tip nedefinit" << endl;
	}

};
ProdusAlimentar operator+(ProdusAlimentar& ca, int numar) {
	ProdusAlimentar copie = ca;
	double f = ca.getPret() / ca.getCantitate();
	copie.setCantitate(ca.getCantitate() + numar);
	copie.setPret(f*copie.getCantitate());
	return copie;
}
bool operator==(ProdusAlimentar& ca1, ProdusAlimentar& ca2) {
	string s1 = ca1.getUnitateMasura();
	string s2 = ca2.getUnitateMasura();
	if (s1.compare(s2) == 0) {
		if (ca1.getCantitate() == ca2.getCantitate()) {
			return true;
		}
		else {
			return false;
		}
	}
}

class Lactate: public ProdusAlimentar {
private:
	char tip[15]; //daca sunt vegane sau de origine animala
	char producator[30];

public:
	Lactate(): ProdusAlimentar() {
		strcpy(this->tip, "necunoscut");
		strcpy(this->producator, "anonim");
	}

	Lactate(int v_ziua, int v_luna, int v_an, char* v_denumire, float v_cantitate,
		char v_um[10], int v_valabilitate[3], double v_pret, char v_tip[15], char v_producator[30]):ProdusAlimentar(v_ziua, v_luna, v_an, v_denumire, v_cantitate,
			v_um, v_valabilitate, v_pret) {
		strcpy(this->tip, v_tip);
		strcpy(this->producator, v_producator);
	}

	int* valabil() {
		return this->getValabilitate();
	}

	void reducere(float p) {
		this->setPret(this->getPret() - (p / 100)*this->getPret());
	}

	void afisare() {
		cout << *this << endl;
	}

	void deTip() {
		cout << "Produsul " << this->getDenumire() << " este de tipul "<<this->tip << endl;
	}

	char* getTip() {
		return this->tip;
	}

	char* getProducator() {
		return this->producator;
	}

	friend ostream& operator<<(ostream& out, Lactate& l) {
		out << "CHELTUIELI ALIMENTARE CU LACTATELE" << endl;
		out << "Ziua: " << l.getZiua() << endl;
		out << "Luna: " << l.getLuna() << endl;
		out << "Anul: " << l.getAn() << endl;
		out << "Denumire produs: " << l.getDenumire() << endl;
		out << "Cantitate: " << l.getCantitate() << endl;
		out << "Unitatea de masura: " << l.getUnitateMasura() << endl;
		out << "Valabilitate: " << endl;
		out << "Ziua: " << l.getValabilitate()[0] << endl;;
		out << "Luna: " << l.getValabilitate()[1] << endl;
		out << "An: " << l.getValabilitate()[2] << endl;
		out << "Pret: " << l.getPret() << endl;
		out << "Tip: " << l.tip << endl;
		out << "Producator: " << l.producator << endl;
		out << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Lactate& l) {
		/*char c;
		in >> c;*/
		int ziua = l.getZiua();
		in >> ziua;
		int luna = l.getLuna();
		in >> luna;
		int an = l.getAn();
		in >> an;
		char buffer[50];
		in.ignore();
		in.getline(buffer, 50);
		l.setDenumire(buffer);

		float cantitate = l.getCantitate();
		in >> cantitate;

		in.ignore();
		in.getline(l.getUnitateMasura(), 10);
		for (int i = 0; i < 3; i++) {
			in >> l.getValabilitate()[i];
		}
		double pret = l.getPret();
		in >> pret;

		in.ignore();
		in.getline(l.tip, 15);
		in.getline(l.producator, 30);
		
		return in;
	}

};

class ProdusNealimentar {
private:
	int ziua;
	int luna;
	int an;
	char denumire[50];
	double pret;
	char* adresare;
	int id;
	static int nrNealimente;

public:
	ProdusNealimentar() :id(nrNealimente++) {
		this->ziua = 1;
		this->luna = 1;
		this->an = 2000;
		strcpy(this->denumire, "Necunoscuta");
		this->pret = 0;
		this->adresare = new char[strlen("Necunoscuta") + 1];
		strcpy(this->adresare, "Necunoscuta");
	}

	ProdusNealimentar(int v_ziua, int v_luna, int v_an, char v_denumire[50], double v_pret,
		char* v_adresare) :id(nrNealimente++) {
		this->ziua = v_ziua;
		this->luna = v_luna;
		this->an = v_an;
		strcpy(this->denumire, v_denumire);
		this->pret = v_pret;
		this->adresare = new char[strlen(v_adresare) + 1];
		strcpy(this->adresare, v_adresare);
	}

	ProdusNealimentar(int v_ziua, int v_luna, int v_an, double v_pret, char v_denumire[50],
		char* v_adresare = "Uz personal") :id(nrNealimente++) {
		this->ziua = v_ziua;
		this->luna = v_luna;
		this->an = v_an;
		strcpy(this->denumire, v_denumire);
		this->pret = v_pret;
		this->adresare = new char[strlen(v_adresare) + 1];
		strcpy(this->adresare, v_adresare);
	}

	ProdusNealimentar(const ProdusNealimentar& sursa) :id(sursa.id) {
		this->ziua = sursa.ziua;
		this->luna = sursa.luna;
		this->an = sursa.an;
		strcpy(this->denumire, sursa.denumire);
		this->pret = sursa.pret;
		this->adresare = new char[strlen(sursa.adresare) + 1];
		strcpy(this->adresare, sursa.adresare);
	}

	ProdusNealimentar& operator=(ProdusNealimentar& sursa) {
		if (this->adresare != NULL) {
			delete[]this->adresare;
		}
		this->ziua = sursa.ziua;
		this->luna = sursa.luna;
		this->an = sursa.an;
		strcpy(this->denumire, sursa.denumire);
		this->pret = sursa.pret;
		this->adresare = new char[strlen(sursa.adresare) + 1];
		strcpy(this->adresare, sursa.adresare);
		return *this;
	}

	~ProdusNealimentar() {
		if (this->adresare != NULL) {
			delete[]this->adresare;
		}
		nrNealimente--;
	}

	friend ostream& operator<<(ostream& out, ProdusNealimentar &cn) {
		out << "CHELTUIELI NEALIMENTARE" << endl;
		out << "Id: " << cn.id << endl;
		out << "Ziua: " << cn.ziua << endl;
		out << "Luna: " << cn.luna << endl;
		out << "Anul: " << cn.an << endl;
		out << "Denumire produs: " << cn.denumire << endl;
		out << "Pret: " << cn.pret << endl;
		out << "Scopul achizitiei: " << cn.adresare << endl;
		out << endl;
		return out;
	}

	friend istream& operator>>(istream& in, ProdusNealimentar &cn) {
		cout << "CHELTUIELI NEALIMENTARE" << endl;
		cout << "Ziua: ";
		in >> cn.ziua;

		cout << "Luna: ";
		in >> cn.luna;

		cout << "Anul: ";
		in >> cn.an;

		in.ignore();
		cout << "Denumire produs: ";
		in.getline(cn.denumire, 50);

		cout << "Pret: ";
		in >> cn.pret;

		in.ignore();
		cout << "Scopul achizitiei: ";
		char buffer[50];
		in.getline(buffer, 50);
		cn.setAdresare(buffer);

		return in;
	}

	int getZiua() {
		return this->ziua;
	}

	void setZiua(int v_ziua) {
		if (v_ziua > 31) {
			throw new exception("Imposibil");
		}
		this->ziua = v_ziua;
	}

	int getLuna() {
		return this->luna;
	}

	void setLuna(int v_luna) {
		if (v_luna > 12) {
			throw new exception("Luna imposibila");
		}
		this->luna = v_luna;
	}

	int getAn() {
		return this->an;
	}

	void setAn(int v_an) {
		if (v_an < 1950) {
			throw new exception("Imposibil");
		}
		this->an = v_an;
	}

	char* getDenumire() {
		return this->denumire;
	}

	void setDenumire(char v_denumire[50]) {
		strcpy(this->denumire, v_denumire);
	}

	double getPret() {
		return this->pret;
	}

	void setPret(double v_pret) {
		this->pret = v_pret;
	}

	char* getAdresare() {
		return this->adresare;
	}

	void setAdresare(char* v_adresare) {
		if (strlen(v_adresare) < 3) {
			throw new exception("Motiv prea scurt");
		}
		else {
			if (this->adresare != NULL) {
				delete[]this->adresare;
			}
			this->adresare = new char[strlen(v_adresare) + 1];
			strcpy(this->adresare, v_adresare);
		}
	}

	int getId() {
		return this->id;
	}

	static int getNrNealimente() {
		return ProdusNealimentar::nrNealimente;
	}

	static void setNrNealimente(int v_nrNealimente) {
		ProdusNealimentar::nrNealimente = v_nrNealimente;
	}

	void anBisect() {
		if ((this->an % 4 == 0 && this->an % 100 != 0) || (this->an % 400 == 0)) {
			cout << "Produsul " << this->denumire << " a fost achizitionat intr-un an bisect." << endl;
		}
		else {
			cout << "Produsul " << this->denumire << " nu a fost achizitionat intr-un an bisect." << endl;
		}
	}

	ProdusNealimentar operator/(double nr) {
		ProdusNealimentar copie = *this;
		copie.pret = this->pret / nr;
		return copie;
	}

	bool operator<=(double nr) {
		if (this->pret <= nr)
			return true;
		else
			return false;
	}

	ProdusNealimentar& operator--() {
		--this->luna;
		return *this;
	}

	ProdusNealimentar operator--(int) {
		ProdusNealimentar copie = *this;
		this->luna--;
		return copie;
	}

	operator double()const {
		return pret;
	}

	bool operator!() const {
		if (luna == 12)
			return true;
		else
			return false;
	}

	friend ifstream& operator>>(ifstream& in, ProdusNealimentar& cn) {
		in >> cn.ziua;
		in >> cn.luna;
		in >> cn.an;
		in.ignore();
		in.getline(cn.denumire, 50);
		in >> cn.pret;
		char buffer[50];
		in.ignore();
		in.getline(buffer, 50);
		if (cn.adresare != NULL) {
			delete[] cn.adresare;
		}
		cn.adresare = new char[strlen(buffer) + 1];
		strcpy(cn.adresare, buffer);
		//in >> cn.id;
		//in >> cn.nrNealimente;
		return in;
	}
};
bool operator==(ProdusNealimentar& cn, double v_pret) {
	if (cn.getPret() == v_pret) {
		return true;
	}
	else {
		return false;
	}
}

class Factura {
private:
	int ziua;
	int luna;
	int an;
	char* denumire;
	char cod[10];
	double cost;
	bool restanta;

public:

	Factura() {
		this->ziua = 1;
		this->luna = 1;
		this->an = 2000;
		this->denumire = new char[strlen("Necunoscut") + 1];
		strcpy(this->denumire, "Necunoscut");
		strcpy(this->cod, "Inexistent");
		this->cost = 0;
		this->restanta = 0;
	}

	Factura(int v_ziua, int v_luna, int v_an, char* v_denumire, char v_cod[10], double v_cost, bool v_restanta) {
		this->ziua = v_ziua;
		this->luna = v_luna;
		this->an = v_an;
		this->denumire = new char[strlen(v_denumire) + 1];
		strcpy(this->denumire, v_denumire);
		strcpy(this->cod, v_cod);
		this->cost = v_cost;
		this->restanta = v_restanta;
	}

	Factura(int v_ziua, char* v_denumire, char v_cod[10], double v_cost, bool v_restanta,
		int v_luna = 1, int v_an = 2018) :luna(v_luna), an(v_an) {
		this->ziua = v_ziua;
		this->denumire = new char[strlen(v_denumire) + 1];
		strcpy(this->denumire, v_denumire);
		strcpy(this->cod, v_cod);
		this->cost = v_cost;
		this->restanta = v_restanta;
	}

	Factura(const Factura& sursa) {
		this->ziua = sursa.ziua;
		this->luna = sursa.luna;
		this->an = sursa.an;
		this->denumire = new char[strlen(sursa.denumire) + 1];
		strcpy(this->denumire, sursa.denumire);
		strcpy(this->cod, sursa.cod);
		this->cost = sursa.cost;
		this->restanta = sursa.restanta;
	}

	Factura& operator=(const Factura& sursa) {
		if (this->denumire != NULL) {
			delete[] this->denumire;
		}
		this->ziua = sursa.ziua;
		this->luna = sursa.luna;
		this->an = sursa.an;
		this->denumire = new char[strlen(sursa.denumire) + 1];
		strcpy(this->denumire, sursa.denumire);
		strcpy(this->cod, sursa.cod);
		this->cost = sursa.cost;
		this->restanta = sursa.restanta;

		return *this;
	}

	~Factura() {
		if (this->denumire != NULL) {
			delete[]this->denumire;
		}
	}

	friend ostream& operator<<(ostream& out, Factura& f) {
		out << "FACTURA" << endl;
		out << "Ziua: " << f.ziua << endl;
		out << "Luna: " << f.luna << endl;
		out << "Anul: " << f.an << endl;
		out << "Denumire: " << f.denumire << endl;
		out << "Cod factura: " << f.cod << endl;
		out << "Costul Facturai: " << f.cost << endl;
		out << "A fost restanta din lunile precedente (1 DA / 0 NU): " << f.restanta << endl;
		out << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Factura& f) {
		cout << "FACTURA" << endl;
		cout << "Ziua: ";
		in >> f.ziua;

		cout << "Luna: ";
		in >> f.luna;

		cout << "Anul: ";
		in >> f.an;

		in.ignore();
		cout << "Denumire: ";
		char buffer[50];
		in.getline(buffer, 50);
		f.setDenumire(buffer);

		cout << "Codul Facturai: ";
		in.ignore();
		in.getline(f.cod, 10);

		cout << "Cost factura: ";
		in >> f.cost;

		cout << "A fost restanta din lunile precedente (1 DA / 0 NU): ";
		in >> f.restanta;

		return in;
	}

	int getZiua() {
		return this->ziua;
	}

	void setZiua(int v_ziua) {
		if (v_ziua > 31) {
			throw new exception("Imposibil");
		}
		else {
			this->ziua = v_ziua;
		}
	}

	int getLuna() {
		return this->luna;
	}

	void setLuna(int v_luna) {
		if (v_luna > 12) {
			throw new exception("Nu exista aceasta luna");
		}
		else {
			this->luna = v_luna;
		}
	}

	int getAn() {
		return this->an;
	}

	void setAn(int v_an) {
		this->an = v_an;
	}

	char* getDenumire() {
		return this->denumire;
	}

	void setDenumire(char* v_denumire) {
		if (this->denumire != NULL) {
			delete[] this->denumire;
		}
		this->denumire = new char[strlen(v_denumire) + 1];
		strcpy(this->denumire, v_denumire);
	}

	char* getCod() {
		return this->cod;
	}

	void setCod(char v_cod[10]) {
		strcpy(this->cod, v_cod);
	}

	double getCost() {
		return this->cost;
	}

	void setCost(double v_cost) {
		this->cost = v_cost;
	}

	bool getRestanta() {
		return this->restanta;
	}

	void setRestanta(bool v_restanta) {
		this->restanta = v_restanta;
	}

	void afisare() {
		cout << "Factura la " << this->denumire << ", avand codul " << this->cod << ", in valoare de " << this->cost << " lei, a fost achitata pe data de " << this->ziua << "." << this->luna << "." << this->an << endl;
		if (this->restanta == 0) {
			cout << "Nu a fost restanta din lunile precedente." << endl;
		}
		else {
			cout << "A fost restanta." << endl;
		}
	}

	Factura operator*(int nr) {
		Factura copie = *this;
		copie.cost = this->cost*nr;
		return copie;
	}

	bool operator>(const Factura& f) {
		if (this->restanta>f.restanta)
			return true;
		else
			return false;
	}

	Factura& operator--() {
		if (this->cost == 1) {
			throw new exception("Imposibil de decrementat");
		}
		else {
			--this->cost;
		}
		return *this;
	}

	Factura operator--(int) {
		Factura copie = *this;
		if (this->cost == 1) {
			throw new exception("Imposibil de decrementat");
		}
		else {
			this->cost--;
		}
		return copie;
	}

	operator bool() const {
		return restanta;
	}

	bool operator!() const {
		return restanta;
	}

	friend ifstream& operator>>(ifstream& in, Factura& f) {
		in >> f.ziua;
		in >> f.luna;
		in >> f.an;

		in.ignore();
		char buffer[50];
		in.getline(buffer, 50);
		if (f.denumire != NULL) {
			delete[] f.denumire;
		}
		f.denumire = new char[strlen(buffer) + 1];
		strcpy(f.denumire, buffer);

		in.getline(f.cod, 10);

		in >> f.cost;
		in >> f.restanta;
		return in;
	}
};
bool operator==(Factura& f1, Factura& f2) {
	string s1 = f1.getDenumire();
	string s2 = f2.getDenumire();
	if (s1.compare(s2) == 0)
		if ((f1.getLuna() == f2.getLuna() + 1 && f1.getAn() == f2.getAn()) || (f2.getLuna() == f1.getLuna() + 1 && f1.getAn() == f2.getAn()))
			if (f1.getCost() == f2.getCost())
				return true;
			else {
				return false;
			}
}

class Rata {
private:
	int ziua;
	int luna;
	int an;
	char* denumire;
	double cost;
	int perioada;
	char moneda[20];

public:

	Rata() {
		this->ziua = 1;
		this->luna = 1;
		this->an = 2000;
		this->denumire = new char[strlen("Necunoscut") + 1];
		strcpy(this->denumire, "Necunoscut");
		this->cost = 0;
		this->perioada = 0;
		strcpy(this->moneda, "RON");
	}

	Rata(int v_ziua, int v_luna, int v_an, char* v_denumire, double v_cost, int v_perioada, char v_moneda[20]) {
		this->ziua = v_ziua;
		this->luna = v_luna;
		this->an = v_an;
		this->denumire = new char[strlen(v_denumire) + 1];
		strcpy(this->denumire, v_denumire);
		this->cost = v_cost;
		this->perioada = v_perioada;
		strcpy(this->moneda, v_moneda);
	}

	Rata(int v_ziua, int v_luna, int v_an, double v_cost, char* v_denumire,
		int v_perioada, char v_moneda[20] = "RON") {
		this->ziua = v_ziua;
		this->luna = v_luna;
		this->an = v_an;
		this->denumire = new char[strlen(v_denumire) + 1];
		strcpy(this->denumire, v_denumire);
		this->cost = v_cost;
		this->perioada = v_perioada;
		strcpy(this->moneda, v_moneda);
	}

	Rata(const Rata&sursa) {
		this->ziua = sursa.ziua;
		this->luna = sursa.luna;
		this->an = sursa.an;
		this->denumire = new char[strlen(sursa.denumire) + 1];
		strcpy(this->denumire, sursa.denumire);
		this->cost = sursa.cost;
		this->perioada = sursa.perioada;
		strcpy(this->moneda, sursa.moneda);
	}

	Rata& operator=(const Rata& sursa) {
		if (this->denumire != NULL) {
			delete[] this->denumire;
		}
		this->ziua = sursa.ziua;
		this->luna = sursa.luna;
		this->an = sursa.an;
		this->denumire = new char[strlen(sursa.denumire) + 1];
		strcpy(this->denumire, sursa.denumire);
		this->cost = sursa.cost;
		this->perioada = sursa.perioada;
		strcpy(this->moneda, sursa.moneda);

		return *this;
	}

	~Rata() {
		if (this->denumire != NULL) {
			delete[]this->denumire;
		}
	}

	friend ostream& operator<<(ostream& out, Rata& r) {
		out << "RATA" << endl;
		out << "Ziua: " << r.ziua << endl;
		out << "Luna: " << r.luna << endl;
		out << "Anul: " << r.an << endl;
		out << "Denumire: " << r.denumire << endl;
		out << "Cost: " << r.cost << endl;
		out << "Perioada in ani: " << r.perioada << endl;
		out << "Moneda: " << r.moneda << endl;
		out << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Rata& r) {
		cout << "RATA" << endl;
		cout << "Ziua: ";
		in >> r.ziua;

		cout << "Luna: ";
		in >> r.luna;

		cout << "Anul: ";
		in >> r.an;

		cout << "Denumire: ";
		char buffer[50];
		in >> buffer;
		r.setDenumire(buffer);

		in.ignore();
		cout << "Cost: ";
		in >> r.cost;

		cout << "Perioada in ani: ";
		in >> r.perioada;

		cout << "Moneda: ";
		in.ignore();
		in.getline(r.moneda, 20);

		return in;
	}

	int getZiua() {
		return this->ziua;
	}

	void setZiua(int v_ziua) {
		if (v_ziua > 31) {
			throw new exception("Imposibil");
		}
		this->ziua = v_ziua;
	}

	int getLuna() {
		return this->luna;
	}

	void setLuna(int v_luna) {
		if (v_luna > 12) {
			throw new exception("Luna imposibila");
		}
		this->luna = v_luna;
	}

	int getAn() {
		return this->an;
	}

	void setAn(int v_an) {
		if (v_an < 1950) {
			throw new exception("Imposibil");
		}
		this->an = v_an;
	}

	char* getDenumire() {
		return this->denumire;
	}

	void setDenumire(char* v_denumire) {
		if (this->denumire != NULL) {
			delete[] this->denumire;
		}
		this->denumire = new char[strlen(v_denumire) + 1];
		strcpy(this->denumire, v_denumire);
	}

	double getCost() {
		return this->cost;
	}

	void setCost(double v_cost) {
		this->cost = v_cost;
	}

	int getPerioada() {
		return this->perioada;
	}

	void setPerioada(int v_perioada) {
		if (v_perioada < 1) {
			throw new exception("Termen prea scurt");
		}
		this->perioada = v_perioada;
	}

	char* getMoneda() {
		return this->moneda;
	}

	void setMoneda(char v_moneda[20]) {
		strcpy(this->moneda, v_moneda);
	}

	double costTotal() {
		return cost*perioada * 12;
	}

	void afisare() {
		cout << "In data de " << this->ziua << "." << this->luna << "." << this->an << " a fost achitata rata la " << this->denumire << " in valoare de " << this->cost << " " << this->moneda << endl;
		cout << "Contractul s-a semnat pe o perioada de " << this->perioada * 12 << " luni." << endl;
	}

	Rata operator-(int nr) {
		Rata copie = *this;
		if (nr < this->cost) {
			copie.cost = this->cost - nr;
			return copie;
		}
		else {
			throw new exception("Imposibil!");
		}
	}

	bool operator<(double c_cost) {
		double aux = this->perioada*this->cost * 12;
		if (aux<c_cost)
			return true;
		else
			return false;

	}

	Rata& operator--() {
		if (this->perioada == 1) {
			throw new exception("Nu se poate decrementa!");
		}
		else {
			--this->perioada;
		}
		return *this;
	}

	Rata operator--(int) {
		Rata copie = *this;
		if (this->perioada == 1) {
			throw new exception("Nu se poate decrementa!");
		}
		else {
			this->perioada--;
		}
		return copie;
	}

	operator char*() const {
		char* aux;
		aux = new char[strlen(this->denumire) + 1];
		strcpy(aux, denumire);
		return aux;
		delete[] aux;
	}

	bool operator!() const {
		if (perioada > 1)
			return true;
		else
			return false;
	}

	friend ifstream& operator>>(ifstream& in, Rata& r) {
		in >> r.ziua;
		in >> r.luna;
		in >> r.an;

		char buffer[50];
		in.ignore();
		in.getline(buffer, 50);
		if (r.denumire != NULL) {
			delete[] r.denumire;
		}
		r.denumire = new char[strlen(buffer) + 1];
		strcpy(r.denumire, buffer);

		in >> r.cost;
		in >> r.perioada;

		in.ignore();
		in.getline(r.moneda, 20);
		return in;
	}

};
bool operator==(Rata& r1, Rata& r2) {
	string s1 = r1.getMoneda();
	string s2 = r2.getMoneda();
	if (s1.compare(s2) == 0)
		return true;
	else
		return false;
}

class Serviciu: public Cheltuieli {
private:
	int ziua;
	int luna;
	int an;
	char* denumire;
	double cost;
	char distribuitor[25];

public:

	Serviciu() {
		this->ziua = 1;
		this->luna = 1;
		this->an = 2000;
		this->denumire = new char[strlen("Necunoscut") + 1];
		strcpy(this->denumire, "Necunoscut");
		this->cost = 0;
		strcpy(this->distribuitor, "Necunoscut");
	}

	Serviciu(int v_ziua, int v_luna, int v_an, char* v_denumire, double v_cost, char v_distribuitor[25]) {
		this->ziua = v_ziua;
		this->luna = v_luna;
		this->an = v_an;
		this->denumire = new char[strlen(v_denumire) + 1];
		strcpy(this->denumire, v_denumire);
		this->cost = v_cost;
		strcpy(this->distribuitor, v_distribuitor);
	}

	Serviciu(int v_ziua, int v_luna, int v_an, double v_cost, char* v_denumire, char v_distribuitor[25] = "METROREX") {
		this->ziua = v_ziua;
		this->luna = v_luna;
		this->an = v_an;
		this->denumire = new char[strlen(v_denumire) + 1];
		strcpy(this->denumire, v_denumire);
		this->cost = v_cost;
		strcpy(this->distribuitor, v_distribuitor);
	}

	Serviciu(const Serviciu& sursa) {
		this->ziua = sursa.ziua;
		this->luna = sursa.luna;
		this->an = sursa.an;
		this->denumire = new char[strlen(sursa.denumire) + 1];
		strcpy(this->denumire, sursa.denumire);
		this->cost = sursa.cost;
		strcpy(this->distribuitor, sursa.distribuitor);
	}

	Serviciu& operator=(const Serviciu& sursa) {
		if (this->denumire != NULL) {
			delete[]this->denumire;
		}
		this->ziua = sursa.ziua;
		this->luna = sursa.luna;
		this->an = sursa.an;
		this->denumire = new char[strlen(sursa.denumire) + 1];
		strcpy(this->denumire, sursa.denumire);
		this->cost = sursa.cost;
		strcpy(this->distribuitor, sursa.distribuitor);

		return *this;
	}

	~Serviciu() {
		if (this->denumire != NULL) {
			delete[] this->denumire;
		}
	}

	friend ostream& operator<<(ostream& out, Serviciu& s) {
		out << "SERVICIU" << endl;
		out << "Ziua: " << s.ziua << endl;
		out << "Luna: " << s.luna << endl;
		out << "Anul: " << s.an << endl;
		out << "Denumire: " << s.denumire << endl;
		out << "Cost: " << s.cost << endl;
		out << "Distribuitor: " << s.distribuitor << endl;
		out << endl;
		return out;
	}

	friend istream& operator>>(istream& in, Serviciu& s) {
		cout << "SERVICIU" << endl;
		cout << "Ziua: ";
		in >> s.ziua;

		cout << "Luna: ";
		in >> s.luna;

		cout << "Anul: ";
		in >> s.an;

		in.ignore();
		cout << "Denumire: ";
		char buffer[50];
		in.getline(buffer, 50);
		s.setDenumire(buffer);

		cout << "Cost: ";
		in >> s.cost;

		cout << "Distribuitor: ";
		in.ignore();
		in.getline(s.distribuitor, 25);
		cout << endl;

		return in;
	}

	int getZiua() {
		return this->ziua;
	}

	void setZiua(int v_ziua) {
		if (v_ziua > 31) {
			throw new exception("Imposibil");
		}
		this->ziua = v_ziua;
	}

	int getLuna() {
		return this->luna;
	}

	void setLuna(int v_luna) {
		if (v_luna > 12) {
			throw new exception("Luna imposibila");
		}
		this->luna = v_luna;
	}

	int getAn() {
		return this->an;
	}

	void setAn(int v_an) {
		if (v_an < 1950) {
			throw new exception("Imposibil");
		}
		this->an = v_an;
	}

	char* getDenumire() {
		return this->denumire;
	}

	void setDenumire(char* v_denumire) {
		if (strlen(v_denumire) > 100) {
			throw new exception("Nume prea lung!");
		}
		if (this->denumire != NULL) {
			delete[] this->denumire;
		}
		this->denumire = new char[strlen(v_denumire) + 1];
		strcpy(this->denumire, v_denumire);
	}

	double getCost() {
		return this->cost;
	}

	void setCost(double v_cost) {
		if (v_cost < 0) {
			throw new exception("Cost imposibil!");
		}
		this->cost = v_cost;
	}

	char* getDistribuitor() {
		return this->distribuitor;
	}

	void setDistribuitor(char v_distribuiutor[25]) {
		if (strlen(v_distribuiutor) < 3) {
			throw new exception("Imposibil");
		}
		strcpy(this->distribuitor, v_distribuiutor);
	}

	void costMinim(Serviciu&s) {
		if (this->cost < s.cost) {
			cout << "Serviciul " << this->denumire << " a avut costul mai mic.";
		}
		else {
			cout << "Serviciul " << s.denumire << " a avut costul mai mic.";
		}
	}

	Serviciu operator+(const Serviciu& s) {
		Serviciu copie = *this;
		copie.cost = this->cost + s.cost;
		strcat(strcat(copie.distribuitor, ","), s.distribuitor);
		char* aux = new char(strlen(copie.denumire) + strlen(s.denumire) + 1);
		strcpy(aux, copie.denumire);
		strcat(aux, ", ");
		strcat(aux, s.denumire);
		delete[] copie.denumire;
		copie.denumire = new char[strlen(aux) + 1];
		strcpy(copie.denumire, aux);
		return copie;
	}

	bool operator<(const Serviciu& s) {
		if ((this->ziua <= s.ziua) && (this->luna <= s.luna) && (this->an <= s.an)) {
			return true;
		}
		else {
			return false;
		}
	}

	Serviciu& operator++() {
		++this->cost;
		return *this;
	}

	Serviciu operator++(int) {
		Serviciu copie = *this;
		this->cost++;
		return copie;
	}

	operator double() const {
		return cost;
	}

	bool operator!() const {
		return ziua % 2 == 0;
	}


	friend ifstream& operator>>(ifstream& in, Serviciu& s) {
		in >> s.ziua;
		in >> s.luna;
		in >> s.an;
		char buffer[50];
		in.ignore();
		in.getline(buffer, 50);
		if (s.denumire != NULL) {
			delete[] s.denumire;
		}
		s.denumire = new char[strlen(buffer) + 1];
		strcpy(s.denumire, buffer);

		in >> s.cost;
		in.ignore();
		in.getline(s.distribuitor, 25);
		return in;
	}

	//overriding 
	//se presupune ca serviciul e valabil o luna
	int* valabil() {
		int ziua = this->ziua;
		int luna = this->luna;
		int anul = this->an;
		int valabil[3] = { ziua, luna, anul };
		if (luna == 12) {
			luna = 1;
			anul++;
		}
		else {
			luna++;
		}
		return valabil;
	}

	//se aplica reducerea daca serviciul e facut in prima saptamana a lunii
	void reducere(float p) {
		if (this->ziua >= 1 || this->ziua <= 7) {
			this->cost = (this->cost) - (p / 100)*this->cost;
		}
	}

	//metoda virtuala
	virtual void afisare() {
		cout<< *this;
	}

};
bool operator==(Serviciu& s1, Serviciu& s2) {
	if (s1.getZiua() == s2.getZiua() && s1.getLuna() == s2.getLuna() && s1.getAn() == s2.getAn())
		return true;
	else
		return false;
}

class ServiciuOnline : public Serviciu {
private:
	char* website;

public:
	ServiciuOnline() :Serviciu() {
		this->website = new char[strlen("neidentificat")+1];
		strcpy(this->website, "neidentificat");
	}

	ServiciuOnline(int v_ziua, int v_luna, int v_an, char* v_denumire, double v_cost, char v_distribuitor[25], char* v_website): Serviciu(v_ziua, 
		v_luna, v_an, v_denumire, v_cost, v_distribuitor) {
		this->website = new char[strlen(v_website)+1];
		strcpy(this->website, v_website);
	}

	~ServiciuOnline() {
		if (this->website != NULL) {
			delete[] this->website;
		}
	}

	ServiciuOnline(const ServiciuOnline& sursa):Serviciu(sursa) {
		this->website = new char[strlen(sursa.website) + 1];
		strcpy(this->website, sursa.website);
	}

	ServiciuOnline& operator=(const ServiciuOnline& sursa) {
		Serviciu::operator=(sursa);
		if (this->website != NULL) {
			delete[] this->website;
		}
		this->website = new char[strlen(sursa.website) + 1];
		strcpy(this->website, sursa.website);

		return*this;
	}

	char* getWebsite() {
		return this->website;
	}

	void setWebsite(char* v_website) {
		if (this->website != NULL) {
			delete[] this->website;
		}
		this->website = new char[strlen(v_website)+1];
		strcpy(this->website, v_website);
	}

	friend ostream& operator<<(ostream& out, ServiciuOnline& so) {
		out << "SERVICIU ONLINE" << endl;
		out << "Ziua: " << so.getZiua() << endl;
		out << "Luna: " << so.getLuna() << endl;
		out << "Anul: " << so.getAn() << endl;
		out << "Denumire: " << so.getDenumire() << endl;
		out << "Cost: " << so.getCost() << endl;
		out << "Distribuitor: " << so.getDistribuitor() << endl;
		out << "Website: " << so.website << endl;
		out << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, ServiciuOnline& so) {
		int ziua = so.getZiua();
		in >> ziua;
		int luna = so.getLuna();
		in >> luna;
		int an = so.getAn();
		in >> an;
		char buffer[50];
		in.ignore();
		in.getline(buffer, 50);
		so.setDenumire(buffer);
		double cost = so.getCost();
		in >> cost;
		in.ignore();
		in.getline(so.getDistribuitor(), 25);
		char buff[50];
		in.getline(buff, 50);
		so.setWebsite(buff);
		return in;
	}

	//overriding
	//se presupune ca serviciul e valabil 1 an
	int* valabil() {
		int ziua = this->getZiua();
		int luna = this->getLuna();
		int anul = this->getAn();
		anul++;
		int valabil[3] = { ziua, luna, anul };
		return valabil;
	}
	
	//se aplica reducerea daca costul depaseste 500
	void reducere(float p) {
		if (this->getCost() > 500) {
			this->setCost(this->getCost() - (p / 100 * this->getCost()));
		}
	}

	void afisare() {
		cout << *this;
	}

};

class FisierBinar {
public:
	FisierBinar() {}
	//scriere in fisier binar pt toate clasele
	void generareFisierBinarProdusAlimentar(ProdusAlimentar* cha, int nr, char* numeFisier) {
		ofstream fisier;
		fisier.open(numeFisier, ofstream::out | ofstream::binary);
		if (fisier.is_open()) {
			fisier.write((char*)&nr, sizeof(int));
			for (int i = 0; i < nr; i++) {
				int zi = cha[i].getZiua();
				fisier.write((char*)&zi, sizeof(int));
				int luna = cha[i].getLuna();
				fisier.write((char*)&luna, sizeof(int));
				int an = cha[i].getAn();
				fisier.write((char*)&an, sizeof(int));
				int lungime = strlen(cha[i].getDenumire()) + 1;
				fisier.write((char*)&lungime, sizeof(int));
				fisier.write(cha[i].getDenumire(), sizeof(char)*lungime);
				float cantitate = cha[i].getCantitate();
				fisier.write((char*)&cantitate, sizeof(float));
				fisier.write(cha[i].getUnitateMasura(), 10 * sizeof(char));
				int valabilitate[3];
				for (int j = 0; j<3; j++) {
					valabilitate[j] = cha[i].getValabilitate()[j];
					fisier.write((char*)&valabilitate[j], sizeof(int));
				}
				double pret = cha[i].getPret();
				fisier.write((char*)&pret, sizeof(double));
				/*int id = cha[i].getId();
				fisier.write((char*)&id, sizeof(int));
				int nrAlimente = cha[i].getNrAlimente();
				fisier.write((char*)&nrAlimente, sizeof(int));*/
			}
			fisier.close();
		}
		else {
			cout << "Eroare la scrierea fisierului CHELTUIELI ALIMENTARE..." << endl;

		}
	}

	
	void generareFisierBinarLactate(Lactate* l, int nr, char* numeFisier) {
		ofstream fisier;
		fisier.open(numeFisier, ofstream::out | ofstream::binary);
		if (fisier.is_open()) {
			fisier.write((char*)&nr, sizeof(int));
			for (int i = 0; i < nr; i++) {
				int zi = l[i].getZiua();
				fisier.write((char*)&zi, sizeof(int));
				int luna = l[i].getLuna();
				fisier.write((char*)&luna, sizeof(int));
				int an = l[i].getAn();
				fisier.write((char*)&an, sizeof(int));
				int lungime = strlen(l[i].getDenumire()) + 1;
				fisier.write((char*)&lungime, sizeof(int));
				fisier.write(l[i].getDenumire(), sizeof(char)*lungime);
				float cantitate = l[i].getCantitate();
				fisier.write((char*)&cantitate, sizeof(float));
				fisier.write(l[i].getUnitateMasura(), 10 * sizeof(char));
				int valabilitate[3];
				for (int j = 0; j < 3; j++) {
					valabilitate[j] = l[i].getValabilitate()[j];
					fisier.write((char*)&valabilitate[j], sizeof(int));
				}
				double pret = l[i].getPret();
				fisier.write((char*)&pret, sizeof(double));
				fisier.write(l[i].getTip(), 15 * sizeof(char));
				fisier.write(l[i].getProducator(), 30 * sizeof(char));
			}
			fisier.close();
		}
		else {
			cout << "Eroare la LACTATE" << endl;
		}
	}

	void generareFisierBinarProdusNealimentar(ProdusNealimentar* cn, int nr, char* numeFisier) {
		ofstream fisier;
		fisier.open(numeFisier, ofstream::out | ofstream::binary);
		if (fisier.is_open()) {
			fisier.write((char*)&nr, sizeof(int));
			for (int i = 0; i < nr; i++) {
				int zi = cn[i].getZiua();
				fisier.write((char*)&zi, sizeof(int));
				int luna = cn[i].getLuna();
				fisier.write((char*)&luna, sizeof(int));
				int an = cn[i].getAn();
				fisier.write((char*)&an, sizeof(int));
				fisier.write(cn[i].getDenumire(), 50 * sizeof(char));
				double pret = cn[i].getPret();
				fisier.write((char*)&pret, sizeof(double));
				int lungime = strlen(cn[i].getAdresare()) + 1;
				fisier.write((char*)&lungime, sizeof(int));
				fisier.write(cn[i].getAdresare(), sizeof(char)*lungime);
				/*int id = cn[i].getId();
				fisier.write((char*)&id, sizeof(int));
				int nrNealimente = cn[i].getNrNealimente();
				fisier.write((char*)&nrNealimente, sizeof(int));*/
			}
			fisier.close();
		}
		else {
			cout << "Eroare la scrierea fisierului CHELTUIELI NEALIMENTARE..." << endl;
		}
	}

	void generareFisierBinarFactura(Factura *f, int nr, char* numeFisier) {
		ofstream fisier;
		fisier.open(numeFisier, ofstream::out | ofstream::binary);
		if (fisier.is_open()) {
			fisier.write((char*)&nr, sizeof(int));
			for (int i = 0; i < nr; i++) {
				int zi = f[i].getZiua();
				fisier.write((char*)&zi, sizeof(int));
				int luna = f[i].getLuna();
				fisier.write((char*)&luna, sizeof(int));
				int an = f[i].getAn();
				fisier.write((char*)&an, sizeof(int));
				int lungime = strlen(f[i].getDenumire()) + 1;
				fisier.write((char*)&lungime, sizeof(int));
				fisier.write(f[i].getDenumire(), sizeof(char)*lungime);
				fisier.write(f[i].getCod(), 10 * sizeof(char));
				double cost = f[i].getCost();
				fisier.write((char*)&cost, sizeof(double));
				bool restanta = f[i].getRestanta();
				fisier.write((char*)&restanta, sizeof(bool));
			}
			fisier.close();
		}
		else {
			cout << "Eroare la scrierea fisierului Factura..." << endl;
		}
	}

	void generareFisierBinarRata(Rata *r, int nr, char* numeFisier) {
		ofstream fisier;
		fisier.open(numeFisier, ofstream::out | ofstream::binary);
		if (fisier.is_open()) {
			fisier.write((char*)&nr, sizeof(int));
			for (int i = 0; i < nr; i++) {
				int zi = r[i].getZiua();
				fisier.write((char*)&zi, sizeof(int));
				int luna = r[i].getLuna();
				fisier.write((char*)&luna, sizeof(int));
				int an = r[i].getAn();
				fisier.write((char*)&an, sizeof(int));
				int lungime = strlen(r[i].getDenumire()) + 1;
				fisier.write((char*)&lungime, sizeof(int));
				fisier.write(r[i].getDenumire(), sizeof(char)*lungime);
				double cost = r[i].getCost();
				fisier.write((char*)&cost, sizeof(double));
				int perioada = r[i].getPerioada();
				fisier.write((char*)&perioada, sizeof(int));
				fisier.write(r[i].getMoneda(), 20 * sizeof(char));
			}
			fisier.close();
		}
		else {
			cout << "Eroare la scrierea fisierului Rata..." << endl;
		}
	}

	void generareFisierBinarServiciu(Serviciu *s, int nr, char* numeFisier) {
		ofstream fisier;
		fisier.open(numeFisier, ofstream::out | ofstream::binary);
		if (fisier.is_open()) {
			fisier.write((char*)&nr, sizeof(int));
			for (int i = 0; i < nr; i++) {
				int zi = s[i].getZiua();
				fisier.write((char*)&zi, sizeof(int));
				int luna = s[i].getLuna();
				fisier.write((char*)&luna, sizeof(int));
				int an = s[i].getAn();
				fisier.write((char*)&an, sizeof(int));
				int lungime = strlen(s[i].getDenumire()) + 1;
				fisier.write((char*)&lungime, sizeof(int));
				fisier.write(s[i].getDenumire(), sizeof(char)*lungime);
				double cost = s[i].getCost();
				fisier.write((char*)&cost, sizeof(double));
				fisier.write(s[i].getDistribuitor(), 25 * sizeof(char));
			}
			fisier.close();
		}
		else {
			cout << "Eroare la scrierea fisierului Serviciu..." << endl;
		}
	}

	//citire din fisier binar pentru Cheltuieli Alimentare
	void incarcaFisierBinarProdusAlimentar(ProdusAlimentar*& cheltuieli_alimentare, int& nr, char* numeFisier) {
		ifstream fisier;
		fisier.open(numeFisier, ifstream::in | ifstream::binary);
		if (fisier.is_open()) {
			fisier.read((char*)&nr, sizeof(int));
			cheltuieli_alimentare = new ProdusAlimentar[nr];
			for (int i = 0; i < nr; i++) {
				int ziua;
				fisier.read((char*)&ziua, sizeof(int));
				int luna;
				fisier.read((char*)&luna, sizeof(int));
				int an;
				fisier.read((char*)&an, sizeof(int));
				int lungime;
				fisier.read((char*)&lungime, sizeof(int));
				char denumire[100];
				fisier.read(denumire, sizeof(char)*lungime);
				float cantitate;
				fisier.read((char*)&cantitate, sizeof(float));
				char unitateMasura[10];
				fisier.read(unitateMasura, sizeof(char) * 10);
				int valabilitate[3];
				for (int j = 0; j<3; j++) {
					fisier.read((char*)&valabilitate[j], sizeof(int));
				}
				double pret;
				fisier.read((char*)&pret, sizeof(double));
				/*int id;
				fisier.read((char*)&id, sizeof(int));
				int nrAlimente;
				fisier.read((char*)&nrAlimente, sizeof(int));*/

				cheltuieli_alimentare[i] = ProdusAlimentar(ziua, luna, an, denumire, cantitate, unitateMasura, valabilitate, pret);
			}
			fisier.close();
		}
		else {
			cout << "Eroare la citirea fisierului CHELTUIELI ALIMENTARE..." << endl;
		}

	}

	void incarcaFisierBinarLactate(Lactate*& lactate, int& nr, char* numeFisier) {
		ifstream fisier;
		fisier.open(numeFisier, ifstream::in | ifstream::binary);
		if (fisier.is_open()) {
			fisier.read((char*)&nr, sizeof(int));
			lactate = new Lactate[nr];
			for (int i = 0; i < nr; i++) {
				int ziua;
				fisier.read((char*)&ziua, sizeof(int));
				int luna;
				fisier.read((char*)&luna, sizeof(int));
				int an;
				fisier.read((char*)&an, sizeof(int));
				int lungime;
				fisier.read((char*)&lungime, sizeof(int));
				char denumire[100];
				fisier.read(denumire, sizeof(char)*lungime);
				float cantitate;
				fisier.read((char*)&cantitate, sizeof(float));
				char unitateMasura[10];
				fisier.read(unitateMasura, sizeof(char) * 10);
				int valabilitate[3];
				for (int j = 0; j<3; j++) {
					fisier.read((char*)&valabilitate[j], sizeof(int));
				}
				double pret;
				fisier.read((char*)&pret, sizeof(double));
				char tip[15];
				fisier.read(tip, sizeof(char) * 15);
				char producator[30];
				fisier.read(producator, sizeof(char) * 30);
				/*int id;
				fisier.read((char*)&id, sizeof(int));
				int nrAlimente;
				fisier.read((char*)&nrAlimente, sizeof(int));*/

				lactate[i] = Lactate(ziua, luna, an, denumire, cantitate, unitateMasura, valabilitate, pret, tip, producator);
			}
			fisier.close();
		}
		else {
			cout << "Eroare la citirea fisierului CHELTUIELI ALIMENTARE..." << endl;
		}

	}

	//citire din fisier binar pentru Cheltuieli Nealimentare
	void incarcaFisierBinarProdusNealimentar(ProdusNealimentar*& cheltuieli_nealimentare, int& nr, char* numeFisier) {
		ifstream fisier;
		fisier.open(numeFisier, ifstream::in | ifstream::binary);
		if (fisier.is_open()) {
			fisier.read((char*)&nr, sizeof(int));
			cheltuieli_nealimentare = new ProdusNealimentar[nr];
			for (int i = 0; i < nr; i++) {
				int ziua;
				fisier.read((char*)&ziua, sizeof(int));
				int luna;
				fisier.read((char*)&luna, sizeof(int));
				int an;
				fisier.read((char*)&an, sizeof(int));
				char denumire[50];
				fisier.read(denumire, sizeof(char) * 50);
				double pret;
				fisier.read((char*)&pret, sizeof(double));
				int lungime;
				fisier.read((char*)&lungime, sizeof(int));
				char adresare[100];
				fisier.read(adresare, sizeof(char)*lungime);
				/*int id;
				fisier.read((char*)&id, sizeof(int));
				int nrNealimente;
				fisier.read((char*)&nrNealimente, sizeof(int));*/

				cheltuieli_nealimentare[i] = ProdusNealimentar(ziua, luna, an, denumire, pret, adresare);
			}
			fisier.close();
		}
		else {
			cout << "Eroare la citirea fisierului CHELTUIELI NEALIMENTARE..." << endl;
		}

	}

	//citire din fisier binar pentru Factura
	void incarcaFisierBinarFactura(Factura*& facturi, int& nr, char* numeFisier) {
		ifstream fisier;
		fisier.open(numeFisier, ifstream::in | ifstream::binary);
		if (fisier.is_open()) {
			fisier.read((char*)&nr, sizeof(int));
			facturi = new Factura[nr];
			for (int i = 0; i < nr; i++) {
				int ziua;
				fisier.read((char*)&ziua, sizeof(int));
				int luna;
				fisier.read((char*)&luna, sizeof(int));
				int an;
				fisier.read((char*)&an, sizeof(int));
				int lungime;
				fisier.read((char*)&lungime, sizeof(int));
				char denumire[100];
				fisier.read(denumire, sizeof(char)*lungime);
				char cod[10];
				fisier.read(cod, sizeof(char) * 10);
				double cost;
				fisier.read((char*)&cost, sizeof(double));
				bool restanta;
				fisier.read((char*)&restanta, sizeof(bool));

				facturi[i] = Factura(ziua, luna, an, denumire, cod, cost, restanta);
			}
			fisier.close();
		}
		else {
			cout << "Eroare la citirea fisierului Factura..." << endl;
		}
	}

	void incarcaFisierBinarRata(Rata*& rate, int& nr, char* numeFisier) {
		ifstream fisier;
		fisier.open(numeFisier, ifstream::in | ifstream::binary);
		if (fisier.is_open()) {
			fisier.read((char*)&nr, sizeof(int));
			rate = new Rata[nr];
			for (int i = 0; i<nr; i++) {
				int ziua;
				fisier.read((char*)&ziua, sizeof(int));
				int luna;
				fisier.read((char*)&luna, sizeof(int));
				int an;
				fisier.read((char*)&an, sizeof(int));
				int lungime;
				fisier.read((char*)&lungime, sizeof(int));
				char denumire[100];
				fisier.read(denumire, sizeof(char)*lungime);
				double cost;
				fisier.read((char*)&cost, sizeof(double));
				int perioada;
				fisier.read((char*)&perioada, sizeof(int));
				char moneda[20];
				fisier.read(moneda, sizeof(char) * 20);

				rate[i] = Rata(ziua, luna, an, denumire, cost, perioada, moneda);
			}
			fisier.close();
		}
		else {
			cout << "Eroare la citirea fisierului Rata. . ." << endl;
		}
	}

	void incarcaFisierBinarServiciu(Serviciu*& servicii, int& nr, char* numeFisier) {
		ifstream fisier;
		fisier.open(numeFisier, ifstream::in | ifstream::binary);
		if (fisier.is_open()) {
			fisier.read((char*)&nr, sizeof(int));
			servicii = new Serviciu[nr];
			for (int i = 0; i<nr; i++) {
				int ziua;
				fisier.read((char*)&ziua, sizeof(int));
				int luna;
				fisier.read((char*)&luna, sizeof(int));
				int an;
				fisier.read((char*)&an, sizeof(int));
				int lungime;
				fisier.read((char*)&lungime, sizeof(int));
				char denumire[100];
				fisier.read(denumire, sizeof(char)*lungime);
				double cost;
				fisier.read((char*)&cost, sizeof(double));
				char distribuitor[25];
				fisier.read(distribuitor, sizeof(char) * 25);

				servicii[i] = Serviciu(ziua, luna, an, denumire, cost, distribuitor);
			}
			fisier.close();
		}
		else {
			cout << "Eroare la citirea fisierului Serviciu. . ." << endl;
		}
	}

};

class Raport {
public:
	FisierBinar fb;
	Raport() {}

	void RaportProdusAlimentar(char*numeFisier, int zi, int luna, int an) {
		ProdusAlimentar* cheltuieli_alimentare = NULL;
		int nr_ca = 0;
		double suma = 0;
		fb.incarcaFisierBinarProdusAlimentar(cheltuieli_alimentare, nr_ca, numeFisier);
		if (nr_ca > 0) {
			for (int i = 0; i < nr_ca; i++) {
				if (cheltuieli_alimentare[i].getZiua() == zi&&cheltuieli_alimentare[i].getLuna() == luna&&cheltuieli_alimentare[i].getAn() == an) {
					suma += cheltuieli_alimentare[i].getPret();
				}
			}
		}
		cout << "Suma cheltuita pe alimente la data de " << zi << " " << luna << " " << an << " a fost de " << suma << "." << endl;

		ofstream fisierOutTxt;
		fisierOutTxt.open("raport_cheltuieli_alimentare.txt", ofstream::out);
		fisierOutTxt << "Total cheltuieli alimentare pe data de " << zi << " " << luna << " " << an << ": " << suma << endl;
		fisierOutTxt.close();
	}

	void RaportProdusNealimentar(char* numeFisier, int luna, int an) {
		ProdusNealimentar* cheltuieli_nealimentare = NULL;
		int nr_cn = 0;
		double suma = 0;
		fb.incarcaFisierBinarProdusNealimentar(cheltuieli_nealimentare, nr_cn, numeFisier);
		if (nr_cn > 0) {
			for (int i = 0; i < nr_cn; i++) {
				if (cheltuieli_nealimentare[i].getLuna() == luna&&cheltuieli_nealimentare[i].getAn() == an) {
					suma += cheltuieli_nealimentare[i].getPret();
				}
			}
		}
		cout << "Suma cheltuita pe nealimente in luna " << luna << " a anului " << an << " a fost de " << suma << endl;
		ofstream fisierOutTxt;
		fisierOutTxt.open("raport_cheltuieli_nealimentare.txt", ofstream::out);
		fisierOutTxt << "Total cheltuieli nealimentare in luna " << luna << ", anul " << an << ": " << suma << endl;
		fisierOutTxt.close();
	}


	void RaportFactura(char* numeFisier, char* denumire, int an) {
		Factura* Factura = NULL;
		int nr_f = 0;
		double suma = 0;
		fb.incarcaFisierBinarFactura(Factura, nr_f, numeFisier);
		if (nr_f > 0) {
			for (int i = 0; i < nr_f; i++) {
				if (strcmp(Factura[i].getDenumire(), denumire) == 0 && Factura[i].getAn() == an) {
					suma += Factura[i].getCost();
				}
			}
		}
		cout << "Suma totala a Facturalor la " << denumire << " in anul " << an << " a fost de " << suma << endl;

		ofstream fisierOutTxt;
		fisierOutTxt.open("raport_Factura.txt", ofstream::out);
		fisierOutTxt << "Suma totala a Facturalor la " << denumire << " in anul " << an << " a fost de " << suma << endl;
		fisierOutTxt.close();
	}
};

class Utilitate {
private:
	int nrFacturi;
	Factura** facturi;

public:
	Utilitate() {
		this->nrFacturi = 0;
		this->facturi = NULL;
	}

	Utilitate(int v_nrFactura, Factura** v_Factura) {
		this->nrFacturi = v_nrFactura;
		this->facturi = new Factura*[this->nrFacturi];
		for (int i = 0; i<this->nrFacturi; i++) {
			this->facturi[i] = v_Factura[i];
		}
	}

	~Utilitate() {
		if (this->facturi != NULL) {
			delete[] this->facturi;
		}
	}

	Utilitate(const Utilitate& sursa) {
		this->nrFacturi = sursa.nrFacturi;
		this->facturi = new Factura*[this->nrFacturi];
		for (int i = 0; i<this->nrFacturi; i++) {
			this->facturi[i] = sursa.facturi[i];
		}
	}

	friend ostream& operator<<(ostream& out, Utilitate& u) {
		out << "Total Facturi: " << u.nrFacturi << endl;
		for (int i = 0; i<u.nrFacturi; i++)
			out << u.facturi[i] << endl;
	}
};


int ProdusAlimentar::nrAlimente = 0;
int ProdusNealimentar::nrNealimente = 0;

void main(int argc, char* argv[]) {
	//AICI AM INCERCAT SA FAC VECTORUL DE Factura ALOCAT DINAMIC, DAR NU MERGE :)
	//int dimensiune;
	//Factura f1;
	//FILE *f = fopen("Factura.txt", "r");
	//fseek(f, 0, SEEK_END);
	//dimensiune = ftell(f) / sizeof(f1);
	//cout << dimensiune;
	//fclose(f);
	Factura* vector_Factura = new Factura[50];
	Factura* vector_Factura1 = new Factura[50]; //acest vector_nume1 e folosit pt a testa daca functioneaza citirea din fisier binar
	Factura f;
	ProdusAlimentar* vector_ca = new ProdusAlimentar[50];
	ProdusAlimentar* vector_ca1 = new ProdusAlimentar[50];
	ProdusAlimentar ca;
	Lactate* vector_lactate = new Lactate[50];
	Rata* vector_Rata = new Rata[50];
	Rata* vector_Rata1 = new Rata[50];
	Serviciu* vector_Serviciu = new Serviciu[50];
	Serviciu* vector_Serviciu1 = new Serviciu[50];
	ServiciuOnline* vector_Serviciu_online = new ServiciuOnline[50];
	ProdusNealimentar* vector_cn = new ProdusNealimentar[50];
	ProdusNealimentar* vector_cn1 = new ProdusNealimentar[50];
	int aux;
	int vector_auxiliar[50];
	int vector_auxiliar_serv[50];
	FisierBinar fb;
	Raport r;
	cout << "Numar argumente: " << argc << endl;
	for (int i = 0; i < argc; i++) {
		cout << "Argumentul " << i + 1 << ": " << argv[i] << endl;
	}
	cout << "MENIU" << endl;
	cout << "**************************************************" << endl;
	cout << "1: Importare date din fisier text " << endl;
	cout << "2: Salvare date in binar " << endl;
	cout << "3: Afisare la consola informatii din fisier binar " << endl;
	cout << "4: Generare raport " << endl;
	cout << "5: Importare date din fisier CSV pentru Cheltuieli Alimentare sau Factura" << endl;
	cout << "6: Introducere date produse alimentare de la tastatura " << endl;
	cout << "7: Testare getteri/setteri/constructori/metode " << endl;
	cout << "8: Inchidere aplicatie " << endl;


	int optiune;
	cout << "Selectati o optiune: ";
	cin >> optiune;

	while (optiune != 8) {
		switch (optiune) {
		case 1:
			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "Factura.txt") == 0) {
					ifstream fisierInTxt;
					aux = 0;
					fisierInTxt.open("Factura.txt", ifstream::in);
					if (fisierInTxt.is_open()) {
						while (!fisierInTxt.eof()) {
							Factura temp;
							fisierInTxt >> temp;
							cout << temp;
							vector_Factura[aux++] = temp;
						}
					}
					fisierInTxt.close();
				}
				if (strcmp(argv[i], "cheltuieli_alimentare.txt") == 0) {
					ifstream fisierInTxt;
					fisierInTxt.open("cheltuieli_alimentare.txt", ifstream::in);
					aux = 0;
					if (fisierInTxt.is_open()) {
						while (!fisierInTxt.eof()) {
							char c;
							fisierInTxt >> c;
							if (c == 'x') {
								ProdusAlimentar temp;
								fisierInTxt >> temp;
								temp.afisare();
								vector_ca[aux++] = temp;
							}
							else if (c == 'y') {
								Lactate temp;
								fisierInTxt >> temp;
								temp.afisare();
								vector_lactate[aux++] = temp;
							}
						}
					}
					fisierInTxt.close();
				}
				if (strcmp(argv[i], "Rata.txt") == 0) {
					ifstream fisierInTxt;
					fisierInTxt.open("Rata.txt", ifstream::in);
					aux = 0;
					if (fisierInTxt.is_open()) {
						while (!fisierInTxt.eof()) {
							Rata temp;
							fisierInTxt >> temp;
							cout << temp;
							vector_Rata[aux++] = temp;
						}
					}
					fisierInTxt.close();
				}

				if (strcmp(argv[i], "Serviciu.txt") == 0) {
					ifstream fisierInTxt;
					fisierInTxt.open("Serviciu.txt", ifstream::in);
					aux = 0;
					if (fisierInTxt.is_open()) {
						while (!fisierInTxt.eof()) {
							char c;
							fisierInTxt >> c;
							if (c == 'x') {
								Serviciu temp;
								fisierInTxt >> temp;
								temp.afisare();
								vector_Serviciu[aux++] = temp;
								
							}
							else if (c == 'y') {
								ServiciuOnline temp;
								fisierInTxt >> temp;
								temp.afisare();
								vector_Serviciu_online[aux++] = temp;
							}
						}
					}
					fisierInTxt.close();
				}

				if (strcmp(argv[i], "cheltuieli_nealimentare.txt") == 0) {
					ifstream fisierInTxt;
					fisierInTxt.open("cheltuieli_nealimentare.txt", ifstream::in);
					aux = 0;
					if (fisierInTxt.is_open()) {
						while (!fisierInTxt.eof()) {
							ProdusNealimentar temp;
							fisierInTxt >> temp;
							cout << temp;
							vector_cn[aux++] = temp;
						}
					}
					fisierInTxt.close();
				}

			}
			break;

		case 2:
			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "cheltuieli_alimentare.txt") == 0 || strcmp(argv[i], "cheltuieli_alimentare.dat") == 0) {
							fb.generareFisierBinarProdusAlimentar(vector_ca, aux, "cheltuieli_alimentare.dat");
					}

			}
			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "Factura.txt") == 0 || strcmp(argv[i], "Factura.dat") == 0) {
					fb.generareFisierBinarFactura(vector_Factura, aux, "Factura.dat");
				}
			}

			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "Rata.txt") == 0 || strcmp(argv[i], "Rata.dat") == 0) {
					fb.generareFisierBinarRata(vector_Rata, aux, "Rata.dat");
				}
			}

			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "Serviciu.txt") == 0 || strcmp(argv[i], "Serviciu.dat") == 0) {
					fb.generareFisierBinarServiciu(vector_Serviciu, aux, "Serviciu.dat");
				}
			}

			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "cheltuieli_nealimentare.txt") == 0 || strcmp(argv[i], "cheltuieli_nealimentare.dat") == 0) {
					fb.generareFisierBinarProdusNealimentar(vector_cn, aux, "cheltuieli_nealimentare.dat");
				}
			}

			cout << "Succes la scriere in binar" << endl;
			break;

		case 3:
			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "Factura.txt") == 0 || strcmp(argv[i], "Factura.dat") == 0) {
					fb.incarcaFisierBinarFactura(vector_Factura1, aux, "Factura.dat");
					for (int i = 0; i < aux; i++) {
						cout << vector_Factura1[i];
					}
				}
			}
			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "cheltuieli_alimentare.txt") == 0 || strcmp(argv[i], "cheltuieli_alimentare.dat") == 0) {
					fb.incarcaFisierBinarProdusAlimentar(vector_ca1, aux, "cheltuieli_alimentare.dat");
					for (int i = 0; i < aux; i++) {
						cout << vector_ca1[i];
					}
				}
			}
			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "Rata.txt") == 0 || strcmp(argv[i], "Rata.dat") == 0) {
					fb.incarcaFisierBinarRata(vector_Rata1, aux, "Rata.dat");
					for (int i = 0; i < aux; i++) {
						cout << vector_Rata1[i];
					}
				}
			}

			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "Serviciu.txt") == 0 || strcmp(argv[i], "Serviciu.dat") == 0) {
					fb.incarcaFisierBinarServiciu(vector_Serviciu1, aux, "Serviciu.dat");
					for (int i = 0; i < aux; i++) {
						cout << vector_Serviciu1[i];
					}
				}
			}

			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "cheltuieli_nealimentare.txt") == 0 || strcmp(argv[i], "cheltuieli_nealimentare.dat") == 0) {
					fb.incarcaFisierBinarProdusNealimentar(vector_cn1, aux, "cheltuieli_nealimentare.dat");
					for (int i = 0; i < aux; i++) {
						cout << vector_cn1[i];
					}
				}
			}

			break;

		case 4:
			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "cheltuieli_alimentare.txt") == 0 || strcmp(argv[i], "cheltuieli_alimentare.dat") == 0) {
					cout << "Ziua pentru generarea raportului: ";
					int ziua;
					cin >> ziua;
					cout << "Luna pentru generarea raportului: ";
					int luna;
					cin >> luna;
					cout << "Anul pentru generarea raportului: ";
					int anul;
					cin >> anul;
					r.RaportProdusAlimentar("cheltuieli_alimentare.dat", ziua, luna, anul);
				}

				if (strcmp(argv[i], "cheltuieli_nealimentare.txt") == 0 || strcmp(argv[i], "cheltuieli_nealimentare.dat") == 0) {
					cout << "Luna pentru generarea raportului: ";
					int luna;
					cin >> luna;
					cout << "Anul pentru generarea raportului: ";
					int anul;
					cin >> anul;
					r.RaportProdusNealimentar("cheltuieli_nealimentare.dat", luna, anul);
				}

				if (strcmp(argv[i], "Factura.txt") == 0 || strcmp(argv[i], "Factura.dat") == 0) {
					cout << "Anul pentru generarea raportului: ";
					int an;
					cin >> an;
					cout << "Denumirea Facturai: ";
					char denumire[50];
					cin.ignore();
					cin.getline(denumire, 50);
					r.RaportFactura("Factura.dat", denumire, an);
				}

			}

		case 5:
			for (int i = 1; i < argc; i++) {
				if (strcmp(argv[i], "cheltuieli_alimentare.csv") == 0) {
					ifstream file;
					file.open("cheltuieli_alimentare.csv", ifstream::in);
					if (file.is_open()) {
						while (file.good()) {
							string zi = to_string(ca.getZiua());
							getline(file, zi, ',');
							cout << "Zi: " << zi << endl;
							string luna = to_string(ca.getLuna());
							getline(file, luna, ',');
							cout << "Luna: " << luna << endl;
							string an = to_string(ca.getAn());
							getline(file, an, ',');
							cout << "An: " << an << endl;
							string denumire = ca.getDenumire();
							getline(file, denumire, ',');
							cout << "Denumire: " << denumire << endl;
							string cantitate = to_string(ca.getCantitate());
							getline(file, cantitate, ',');
							cout << "Cantitate: " << cantitate << endl;
							string um = ca.getUnitateMasura();
							getline(file, um, ',');
							cout << "Unitate de masura: " << um << endl;
							cout << "Valabilitate: ";
							for (int i = 0; i < 3; i++) {
								string valabilitate = to_string(ca.getValabilitate()[i]);
								getline(file, valabilitate, ',');
								cout << valabilitate << " ";
							}
							cout << endl;
							string pret = to_string(ca.getPret());
							getline(file, pret);
							cout << "Pret " << pret << endl;
							cout << endl;
						}
					}
				}
				if (strcmp(argv[i], "Factura.csv") == 0) {
					ifstream file;
					file.open("Factura.csv", ifstream::in);
					if (file.is_open()) {
						while (file.good()) {
							string zi = to_string(f.getZiua());
							getline(file, zi, ',');
							cout << "Zi: " << zi << endl;
							string luna = to_string(f.getLuna());
							getline(file, luna, ',');
							cout << "Luna: " << luna << endl;
							string an = to_string(f.getAn());
							getline(file, an, ',');
							cout << "An: " << an << endl;
							string denumire = f.getDenumire();
							getline(file, denumire, ',');
							cout << "Denumire: " << denumire << endl;
							string cod = f.getCod();
							getline(file, cod, ',');
							cout << "Cod: " << cod << endl;
							string cost = to_string(f.getCost());
							getline(file, cost, ',');
							cout << "Cost: " << cost << endl;
							string restanta = to_string(f.getRestanta());
							getline(file, restanta);
							cout << "Restanta: " << restanta << endl;
							cout << endl;
						}
					}
				}
			}
		case 6:
			

		case 7:
			////CHELTUIELI ALIMENTARE
			////testare constructor fara parametri
			//ProdusAlimentar ca1;
			//cout << ca1;
			////verificare supraincarcare >> si <<
			////cin >> ca1;
			//cout << ca1;

			////testare operator +
			//ProdusAlimentar ca2;
			//ca2 = ca1 + 2;
			//cout << ca2;

			////testare operator >=
			//if (ca1 >= 2018) {
			//	cout << "Produsul "<<ca1.getDenumire()<<" va expira in 2018 sau mai tarziu"<<endl;
			//}
			//else {
			//	cout << "Produsul " << ca1.getDenumire() << " este aproape de finalul termenului de valabilitate sau a expirat deja."<<endl;
			//}

			////initializare vector pentru termenul de valabilitate
			//int v[3] = { 30, 3, 2018 };

			////testare constructor cu toti parametri
			//ProdusAlimentar ca3(25, 10, 2017, "avocado", 3, "bucata", v, 21);

			////testare constructor cu valoare implicita pentru an=2017
			//ProdusAlimentar ca6(12, 8, "banane", 3, "kg", v, 15);
			//cout << ca6;

			////testare cast
			//double pretProdus = ca3;
			//cout << pretProdus<<endl;

			////testare functii expira si pret unitar
			//ca3.expira();
			//cout << "Produsul " << ca3.getDenumire() << " a costat " << ca3.pretUnitar() << " lei per " << ca3.getUnitateMasura()<<endl;
			//
			////testare operator ++ forta postfixata
			//ProdusAlimentar ca4;
			//ca4 = ca3++;
			//cout << ca3;
			//cout << ca4;

			////testare operator -- forma prefixata
			//ProdusAlimentar ca5;
			//ca5 = ++ca3;
			//cout << ca3;
			//cout << ca5;

			////testare operator ==
			//if (ca1 == ca3) {
			//	cout << "Produsele "<<ca1.getDenumire()<<" si "<<ca3.getDenumire()<<" au fost cumpaRata in aceeasi cantitate";
			//}
			//else { 
			//	cout << "Produsele " << ca1.getDenumire() << " si " << ca3.getDenumire() << " nu au fost cumpaRata in aceeasi cantitate";
			//}
			////testare operator !
			//if (!ca3) {
			//	cout << "Produsul expira cel putin in anul urmator." << endl;
			//}
			//else {
			//	cout << "Produsul expira anul acesta."<<endl;
			//}
			//
			//cout << "S-au cumparat " << ProdusAlimentar::getNrAlimente() << " produse alimentare." << endl;
			//

			////CHELTUIELI NEALIMENTARE
			////testare constructor fara parametri
			//ProdusNealimentar cn1;
			//cout << cn1;

			////testare supraincarcare >> si <<
			////cin >> cn1;
			//cout << cn1;

			////testare operator /
			//ProdusNealimentar cn2;
			//cn2 = cn1 / 2.2;
			//cout << cn2;

			////testare operator <=
			//ProdusNealimentar cn3;
			////cin >> cn3;
			//cout << cn3;
			//double s;
			//cout << "Dati o suma admisibila: ";
			////cin >> s;
			//if (cn3 <= s) {
			//	cout << "Achizitia s-a incadrat in suma de bani admisa.";
			//}
			//else {
			//	cout << "Achizitia nu s-a incadrat in suma de bani admisa.";
			//}

			////testare operator ==
			//if (cn1 == 250.0) {
			//	cout << "Produsul " << cn1.getDenumire() << " a costat 250 ron" << endl;
			//}
			//else {
			//	cout << "Produsul " << cn1.getDenumire() << " nu a costat 250 ron" << endl;
			//}
			//
			////testare constructor cu toti parametri
			//ProdusNealimentar cn4(2, 3, 2017, "rochie", 150, "cadou mama");
			//cout << cn4;

			////testare constructor cu valoare implicita pentru adresare
			//ProdusNealimentar cn6(10, 10, 2017, 10, "sapun lichid");
			//cout << cn6;

			////testare -- prefixat
			//--cn4;
			//cout << cn4;

			////testare --postfixat
			//ProdusNealimentar cn5;
			//cn5 = cn4--;
			//cout << cn4;
			//cout << cn5;

			////testare functie de an bisect
			//cn4.anBisect();

			////testare cast
			//double pretCast = cn4;
			//cout << pretCast << endl;

			////testare operator !
			//if (!cn4) {
			//	cout << "Produsul " << cn4.getDenumire() << " a fost achizionat in luna cadourilor." << endl;
			//}
			//else {
			//	cout << "Produsul " << cn4.getDenumire() << " nu a fost achizionat in luan cadourilor." << endl;
			//}
			//cout << "S-au cumparat " << ProdusNealimentar::getNrNealimente() << " produse nealimentare." << endl;
			//cout << endl;


			////Factura
			////testare constructor fara parametri
			//Factura f1;
			//cout << f1;

			////testare supraincarcare << si >>
			////cin >> f1;
			//cout << f1;

			////testare supraincarcare operator *
			//Factura f2;
			//f2 = f1 * 3;
			//cout << f2;

			////testare operator >
			//Factura f3;
			////cin >> f3;
			//cout << f3;
			//if (f1 > f3) {
			//	cout << "Factura " << f1.getDenumire() << " are prioritate la plata.";
			//}
			//else {
			//	cout << "Factura " << f3.getDenumire() << " are prioritate la plata.";
			//}
			//
			////testare constructor cu toti parametri
			//Factura f4(1, 12, 2017, "enel", "2234", 200, 0);
			//cout << f4;

			////testare constructor cu valori implicite pentru luna si an
			//Factura f5(1, "enel", "2202", 80, 0);
			//
			////testare functie de afisare
			//f5.afisare();

			////testare cast
			//bool restantaCast = f5;
			//cout << "Variabila are valoarea " << restantaCast<<endl;

			////testare -- forma postfixata
			//Factura f6;
			//f6 = f4--;
			//cout << f4;
			//cout << f6;

			////testare -- forma prefixata
			//Factura f7;
			//f7 = --f4;
			//cout << f4;
			//cout << f7;

			////testare operator ==
			//if (f4 == f5) {
			//	cout << "Factura la " << f4.getDenumire() << " a costat " << f4.getCost() << " ron doua luni consecutive."<<endl;
			//}
			//else {
			//	cout << "Nu se poate realiza comparatia"<<endl;
			//}

			////testare operator!
			//if (!f4) {
			//	cout << "Factura " << f4.getDenumire() << " este restanta." << endl;
			//}
			//else {
			//	cout << "Factura " << f4.getDenumire() << " nu este restanta." << endl;
			//}

			////Rata
			////testare constructor fara parametri
			//Rata r1;
			//cout << r1;

			////testare supraincarcare >> si <<
			////cin >> r1;
			//cout << r1;

			////testare operator <
			//if (r1 < 25000) {
			//	cout << "Rata poate fi achitata in 12 luni"<<endl;
			//}
			//else {
			//	cout << "Este indicat ca rata sa fie achitata intr-o perioada de peste 12 luni." << endl;
			//}
			//
			////testare operator -
			//Rata r2;
			//r2 = r1 - 5;
			//cout << r2;

			////testare constructor cu toti parametri
			//Rata r3(1, 1, 2010, "masina", 100, 3, "ron");
			//cout << r3;

			////testare constructor cu valoare implicita pentru moneda
			//Rata r6(7, 11, 2016, 50, "frigider", 1);
			//cout << r6;

			////testare cast
			//char* testCast=r3;
			//cout << testCast<<endl;

			////testare operator !
			//if (!r3) {
			//	cout << "Perioada de plata este mai mare de 1 an"<<endl;
			//}
			//else {
			//	cout << "Perioada de plata este mai mica de 1 an"<<endl;
			//}

			////testare functii de afisare si de cost total al Ratai
			//r3.afisare();
			//cout << "Rata la " << r3.getDenumire() << " are un cost total, pe intreaga perioada de " << r3.getPerioada() * 12 << " luni, de " << r3.costTotal() << " " << r3.getMoneda()<<endl;
			//
			////testare operator -- forma postfixata
			//Rata r4;
			//r4 = r3--;
			//cout << r3;
			//cout << r4;

			////testare operator -- forma prefixata
			//Rata r5;
			//r5 = r3--;
			//cout << r3;
			//cout << r5;

			////testare operator ==
			//if (r1 == r3) {
			//	cout << "Ratale la " << r1.getDenumire() << " si la " << r3.getDenumire() << " se platesc in aceeasi moneda."<<endl;
			//}
			//else {
			//	cout<< "Ratale la " << r1.getDenumire() << " si la " << r3.getDenumire() << " nu se platesc in aceeasi moneda."<<endl;
			//}


			////Serviciu
			////testare constructor fara parametri
			//Serviciu s1, s2;
			//cout << s1 << s2;

			////testare supraincarcare << si >>
			////cin >> s1;
			//cout << s1;
			////cin >> s2;
			//cout << s2;
			//
			////testare operator +
			//Serviciu s3;
			//s3 = s1 + s2;
			//cout << s3;

			////testare functie de cost minim dintre doua Serviciu
			//s1.costMinim(s2);

			////testare operator <
			//if (s1 < s2) {
			//	cout << "Serviciul " << s1.getDenumire() << " s-a efectuat inaintea serviciului " << s2.getDenumire()<<endl;
			//}
			//else {
			//	cout << "Serviciul " << s1.getDenumire() << " s-a efectuat dupa serviciul " << s2.getDenumire() << endl;
			//}

			////testare operator ==
			//if (s1 == s2) {
			//	cout << "Serviciule " << s1.getDenumire() << " si " << s2.getDenumire() << " s-au achitat in aceeasi zi."<<endl;
			//}
			//else {
			//	cout<< "Serviciule " << s1.getDenumire() << " si " << s2.getDenumire() << " nu s-au achitat in aceeasi zi."<<endl;
			//}

			////testare constructor cu toti parametri
			//Serviciu s4(3, 6, 2017, "abonament metrou", 70, "metrorex");
			//cout << s4;

			////testare constructor cu valori implicite pentru distribuitor si operator ++ valoare postfixata
			//Serviciu s5(26, 9, 2017, 35, "abonament mentrou");
			//s5 = s4++;
			//cout << s4;
			//cout << s5;

			////testare operator ++ valoare prefixata
			//Serviciu s6;
			//s6 = s4++;
			//cout << s4;
			//cout << s6;

			////testare cast
			//double costCast = s4;
			//cout << "Variabila are valoarea "<<costCast << endl;

			////testare operator !
			//if (!s4) {
			//	cout << "Serviciul s-a efectuat intr-o zi para";
			//}
			//else {
			//	cout << "Serviciul s-a efectuat intr-o zi impara";
			//}
			cout << ". . .Cod comentat. . ." << endl;
		default:
			cout << "Optiunea aleasa nu exista. Consultati manualul aplicatiei." << endl;
			break;
		}

		cout << "Dati optiunea dorita: ";
		cin >> optiune;
	}
	cout << "Aplicatia se inchide . . . " << endl;
}
