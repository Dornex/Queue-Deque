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
	Coada(Nod* p, Nod* u, int dimensiune);
	void inserare_sfarsit(char val);
	void stergere_inceput();
	void afisare();
	virtual bool is_deque() {
		return 0;
	}
	friend ifstream& operator>>(ifstream& in, Coada& queue);
	friend ostream& operator<<(ostream& os, Coada& queue);
};

Coada::Coada(Nod* p, Nod* u, int dimensiune) {
	if (p != NULL && u != NULL) { prim = p; ultim = u; }
	else prim = ultim = NULL;
	dim_max = dimensiune;
	nr_elemente = 0;
}

istream& operator>>(istream& in, Coada& queue) {
	char x[5];
	cout << "Citim pana la intalnirea stringului \"STOP\": ";
	while (in >> x)
	{
		if (strcmp(x, "STOP") != 0)
			queue.inserare_sfarsit(x[0]);
		else break;
	}
	in.clear();
	return in;
}

ostream& operator<<(ostream& os, Coada& queue) {
	if (queue.prim == NULL) os << "Coada nula!\n";
	Nod* tmp = queue.prim;
	while (tmp != NULL) {
		os << tmp->get_info() << ' ';
		tmp = tmp->get_next();
	}
	os << '\n';
	return os;
}

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
	if (prim == NULL) cout << "Coada nula!\n";
	else {
		Nod* tmp = prim;
		prim = prim->get_next();
		if (prim == NULL) ultim = NULL;
	}
	nr_elemente--;
}

class Deque :public Coada {

public:
	Deque(Nod* p, Nod* u, int dimensiune) :Coada(prim, ultim, dimensiune) {};
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
	Coada q(NULL, NULL, 5);
	cin >> q;
	cout << q;

	Deque d(NULL, NULL, 7);
	cin >> d;
	cout << d;

	if (d.is_deque() == 1) cout << "Este deque!\n";
	else cout << "Nu este deque!\n";

	if (q.is_deque() == 1) cout << "Este deque!\n";
	else cout << "Nu este deque!\n";
	return 0;
}
