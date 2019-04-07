#include <iostream>
#include <cstring>
using namespace std;

class Nod {
	char info;
	Nod* next;
public:
	Nod() {
		next = NULL;
		info = '\0';
	}
	Nod(char info) {
		Nod* tmp = new Nod();
		tmp->info = info;
		tmp->next = NULL;
		this->info = tmp->info;
		this->next = tmp->next;
	}
	char get_info();
	Nod*& get_next();
};

class Coada {
protected:
	Nod* prim, * ultim;
	int dim_max;
	int nr_elemente;
public:
	Coada(int dimensiune) {
		prim = ultim = NULL;
		dim_max = dimensiune;	
		nr_elemente = 0;
	}
	void inserare_sfarsit(char val);
	void stergere_inceput();
	void afisare();
	virtual bool is_deque() {
		return 0;
	}
};

Nod*& Nod::get_next(){
	return next;
}

char Nod::get_info(){
	return info;
}

void Coada::inserare_sfarsit(char val) {
	if (nr_elemente + 1 > dim_max) { cout << "Queue overflow!\n"; return; }
	else nr_elemente++;

	Nod *tmp = new Nod(val);
	if (ultim == NULL) {
		prim = ultim = tmp;
	}
	else {
		ultim->get_next() = tmp;
		ultim = tmp;
	}
}

void Coada::stergere_inceput() {
	if (prim == NULL)
		cout << "Coada nula!\n";
	else {
		Nod* tmp = prim;
		prim = prim->get_next();
		if (prim == NULL) ultim = NULL;
	}
	nr_elemente--;
}

void Coada::afisare() {
	if (prim == NULL) cout << "Coada nula!\n";
	Nod* tmp = this->prim;
	while (tmp != NULL) {
		cout << tmp->get_info() << ' ';
		tmp = tmp->get_next();
	}
	cout << this->nr_elemente;
	cout << '\n';
}

class Deque :public Coada {

public:
	Deque(int dimensiune) :Coada(dimensiune) {};
	void inserare_inceput(char val);
	void stergere_sfarsit();
	bool is_deque() {
		return 1;
	}

};

void Deque::stergere_sfarsit() {
	if (prim == NULL) cout << "Deque nul!\n";
	else {
		Nod* tmp = prim;
		while (((tmp->get_next())->get_next()) != NULL) {
			tmp = tmp->get_next();
		}
		Nod* aux = tmp;
		aux->get_next() = NULL;
		tmp = tmp->get_next();
		delete tmp;
	}
	nr_elemente--;
}

void Deque::inserare_inceput(char val)
{
	if (nr_elemente + 1 > dim_max) { cout << "Deque overflow!\n"; return; }
	else nr_elemente++;

	Nod* tmp = new Nod(val);
	if (prim == NULL && ultim == NULL) {
		prim = ultim = tmp;
	}
	else {
		tmp->get_next() = prim;
		prim = tmp;
	}
}


int main()
{
	Coada q(5);
	q.inserare_sfarsit('a');
	q.inserare_sfarsit('b');
	q.inserare_sfarsit('C');
	q.inserare_sfarsit('D');
	q.inserare_sfarsit('E');
	q.inserare_sfarsit('l');
	q.afisare();

	Deque d(7);
	d.inserare_inceput('d');
	d.inserare_inceput('2');
	d.inserare_inceput('A');
	d.inserare_sfarsit('c');
	d.inserare_inceput('b');
	d.inserare_sfarsit('l');
	d.stergere_inceput();
	d.stergere_sfarsit();
	d.afisare();

	if (d.is_deque() == 1) cout << "Este deque!\n";
	else cout << "Nu este deque!\n";

	if (q.is_deque() == 1) cout << "Este deque!\n";
	else cout << "Nu este deque!\n";
	return 0;
}

