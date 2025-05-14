#include <iostream>
#include <regex>
#include "tlist.h"


#pragma once

struct Monom {
		double k;
		int degree;
		Monom() {
			k = 0.;
			degree = 0;
		}
		Monom(double d, int deg) {
			k = d;
			degree = deg;
		}
		Monom(std::string inp) {
			//std::cout <<"INP: " << inp << std::endl;
			k = 0.;
			degree = 0;
			if (isValid(inp)) {
				int x = 0, y = 0, z = 0;
				//std::cout << "IsValid" << std::endl;
				std::regex MonomPattern(R"(^\s*([-+]?\d+(?:\.\d+)?)?(?:\s*\*\s*[xyzXYZ]\^-?\d+|\s*[xyzXYZ]\^-?\d+)*\s*$)");
				std::smatch matches;
				std::regex_match(inp, matches, MonomPattern);
				if (matches[1].matched) {
					k = std::stod(matches[1].str());
				}
				else {
					k = 1.;
				}
				std::regex factorsPattern(R"([xyzXYZ]\^-?\d+)");
				auto begin = std::sregex_iterator(inp.begin(), inp.end(), factorsPattern);
				auto end = std::sregex_iterator();
				for (auto it = begin; it != end; ++it) {
					if (it->str()[0] == 'x' || it->str()[0] == 'X') {
						x += stoi(it->str().substr(2));
					}
					if (it->str()[0] == 'y' || it->str()[0] == 'Y') {
						y += stoi(it->str().substr(2));
					}
					if (it->str()[0] == 'z'|| it->str()[0] == 'Z') {
						z += stoi(it->str().substr(2));
					}
				}
				//std::cout << "KKK:" << k << " x:" << x << " y:" << y << " z:" << z << "\n";
				if (x > 9) {
					throw "too big degree";
				}
				if (y > 9) {
					throw "too big degree";
				}
				if (z > 9) {
					throw "too big degree";
				}
				degree = x * 100 + y * 10 + z;
				//std::cout << degree<<"\n";
			}
			else {
				//std::cout << "NotValid" << std::endl;
				throw "wrong string";
			}
		}
		Monom(double d) {
			k = d;
			degree = 0;
		}
		bool operator==(const Monom& monom) const {
			if (k == monom.k && degree == monom.degree) {
				return 1;
			}
			else {
				return 0;
			}
		}
		bool operator!=(const Monom& monom) const {
			return !(*this == monom);
		}
		Monom operator*(const Monom& monom) const {
			int lx = degree / 100;
			int ly = (degree / 10) % 10;
			int lz = degree % 10;
			int rx = monom.degree / 100;
			int ry = (monom.degree / 10) % 10;
			int rz = monom.degree % 10;
			if (rx + lx >= 10 || ry + ly >= 10 || rz + lz >= 10) {
				throw "sboi";
			}
			Monom res;
			res.k = k * monom.k;
			res.degree = degree + monom.degree;
			return res;
		}
		void print() {
			if (degree < 0 || degree> 999) {
				std::cout << "Число должно быть в диапазоне от 0 до 999.\n";
				return;
			}
			if (degree == 0) {
				std::cout << k;
			}
			else {
				// Unicode символы для степеней (от 0 до 9)
				std::string superscript[] = {"", "", "^2", "^3", "^4", "^5", "^6", "^7", "^8", "^9" };

				int hundreds = degree / 100;             // Сотни
				int tens = (degree / 10) % 10;           // Десятки
				int units = degree % 10;                 // Единицы
				//std::cout << hundreds << " " << tens << " " << units << std::endl;
				std::cout << k;
				if (hundreds > 0) {
					std::cout << "*" << "x" << superscript[hundreds];
				}
				if (tens > 0) {
					std::cout << "*" << "y" << superscript[tens];
				}
				if (units > 0) {
					std::cout << "*" << "z" << superscript[units];
				}
			}
		}
		bool isValid(std::string inp) {
			std::regex SpasesPattern(R"(^\s*$)");
			if (std::regex_match(inp, SpasesPattern)) {
				return 0;
			}
			std::regex MonomPattern(R"(^\s*([-+]?\d+(?:\.\d+)?)?(?:\s*\*\s*[xyzXYZ]\^-?\d+|\s*[xyzXYZ]\^-?\d+)*\s*$)");
			return std::regex_match(inp, MonomPattern);
		}
};

class Polinom : protected Tlist<Monom> {

private:
	
	Tlist& operator= (const Tlist& list) {}
	Tlist& replace(Tlist& list) {}
	Monom operator[](int index) {};
	void set_element(Monom value, int index) {}
	iterator insert_front(Monom value) {};
	iterator errase_front() {};
	iterator find(Monom value) {};//O(n)
	iterator find_ptr(int index) {};
	size_t size() {};
	Tlist& merge_sorted_lists(Tlist& list) {};
public:
	
	Polinom() : Tlist() {
		//std::cout << "Polinom Constructor\n";
	};

	Polinom(double d) : Tlist() {
		Tlist::insert_front(Monom(d));
		//std::cout << "Polinom Constructor\n";
	};
	Polinom(Monom monom) : Tlist() {
		Tlist::insert_front(monom);
	}
	Polinom(std::string inp) : Tlist() {
		bool isNegative = false; 
		std::string sub; 

		for (char c : inp) {
			if (c == '+' || c == '-') {
				if (!sub.empty()) { 
					if (isNegative) {
						sub = "-" + sub; 
					}
					Monom monom = Monom(sub); 
					this->insert(monom); 
					sub.clear(); 
				}
				isNegative = (c == '-'); 
			}
			else {
				sub += c; 
			}
		}
		if (!sub.empty()) {
			if (isNegative) {
				sub = "-" + sub;
			}
			Monom monom = Monom(sub);
			this->insert(monom);
		}
	}

	~Polinom(){
		//std::cout << "Polinom Destructor\n";
	};

	void insert(Monom value) {
		if (first == nullptr) {
			Node* temp = new Node();
			first = temp;
			first->data.degree = value.degree;
			first->data.k = value.k;
		}
		else {
			if (value.degree > first->data.degree) {
				Node* temp = new Node();
				temp->next = first;
				temp->data.degree = value.degree;
				temp->data.k = value.k;
				first = temp;
			}
			else {
				Node* prev = first;
				Node* cur = first->next;
				if (cur != nullptr){
					while (cur != nullptr) {
						if (prev->data.degree > value.degree && value.degree > cur->data.degree) {
							Node* temp = new Node();
							temp->data = value;
							temp->next = cur;
							prev->next = temp;
							break;
						}
						if (cur->data.degree == value.degree) {
							cur->data.k += value.k;
							break;
						}
						if (prev->data.degree == value.degree) {
							prev->data.k += value.k;
							break;
						}
						prev = cur;
						cur = cur->next;
					}
					if (cur == nullptr) {
						Node* temp = new Node();
						temp->data = value;
						temp->next = nullptr;
						prev->next = temp;
					}
				}
				else {
					if (prev->data.degree > value.degree) {
						Node* temp = new Node();
						temp->data = value;
						temp->next = nullptr;
						prev->next = temp;
					}
					if (prev->data.degree == value.degree) {
						prev->data.k += value.k;
					}
				}
			}
		}
	};

	void print() {
		Node* cur = first;
		while (cur != nullptr) {
			cur->data.print();
			if (cur->next != nullptr) {
				std::cout << '+';
			}
			cur = cur->next;
		}
		std::cout << "\n";
	};
	Polinom operator+(Polinom& right) {
		Node* fr = right.first;
		Node* fl = this->first;
		Polinom res;
		if (fr == nullptr) {

			if (fl == nullptr) {
				return res;
			}
			if (fl != nullptr) {
				res.insert(fl->data);
				fl = fl->next;
				Node* res_ptr = res.first;
				while (fl != nullptr) {
					Node* temp = new Node();
					temp->data.k = fl->data.k;
					temp->data.degree = fl->data.degree;
					temp->next = nullptr;

					res_ptr->next = temp;

					res_ptr = res_ptr->next;
					fl = fl->next;
				}
				return res;
			}
		}
		if (fl == nullptr) {
			if (fr == nullptr) {
				return res;
			}
			if (fr != nullptr) {
				res.insert(fr->data);
				fr = fr->next;
				Node* res_ptr = res.first;
				while (fr != nullptr) {
					Node* temp = new Node();
					temp->data.k = fr->data.k;
					temp->data.degree = fr->data.degree;
					temp->next = nullptr;

					res_ptr->next = temp;
					res_ptr = res_ptr->next;
					fr = fr->next;
				}
				return res;
			}
		}
		//копируем left O(n)
		res.insert(fl->data);
		fl = fl->next;
		Node* res_ptr = res.first;
		while (fl != nullptr) {
			Node* temp = new Node();
			temp->data.k = fl->data.k;
			temp->data.degree = fl->data.degree;
			temp->next = nullptr;

			res_ptr->next = temp;

			res_ptr = res_ptr->next;
			fl = fl->next;
		}
		//последовательно вставляем элементы из right O(n1 + n2) 
		Node* cur = res.first;
		res.insert(fr->data);
		fr = fr->next;
		if (fr == nullptr) {
			return res;
		}
		res.insert(fr->data);
		fr = fr->next;
		Node* prev = res.first;
		cur = res.first->next;
		bool isEq = 0;
		while (fr != nullptr) {
			while (cur != nullptr) {
				if (prev->data.degree > fr->data.degree && fr->data.degree > cur->data.degree) {
					break;
				}
				if (cur->data.degree == fr->data.degree) {
					isEq = 1;
					break;
				}
				cur = cur->next;
				prev = prev->next;
			}
			if (isEq) {
				cur->data.k += fr->data.k;
				fr = fr->next;
				isEq = 0;
			}
			else {
				Node* temp = new Node();
				temp->data = fr->data;
				temp->next = cur;
				prev->next = temp;
				fr = fr->next;
			}
		}
		return res;
	};
	Polinom operator+(Monom& left) {
		Polinom res;
		res.insert(left);
		res = res + *this;
		return res;
	};
	Polinom operator*(Monom& left) {
		Polinom res;
		Node* cur = first;
		if (cur == nullptr) {
			return res;
		}
		res.insert(left * cur->data);
		Node* pes = res.first;
		cur = cur->next;
		while (cur != nullptr) {
			Node* temp = new Node();
			temp->data = left * cur->data;
			temp->next = nullptr;
			pes->next = temp;
			pes = pes->next;
			cur = cur->next;
		}
		return res;
	};
	Polinom operator*(Polinom& left) {
		Node* lp = left.first;
		Polinom res;
		//Перебираем O(n)
		while (lp != nullptr) {
			Polinom temp;
			//Умножение на моном O(n)
			temp = *this * lp->data;
			lp = lp->next;
			//Сложение O(n)
			res = res + temp;
		}
		//Итого O(n^2)
		return res;
	};
	Polinom operator-(Polinom& left) {
		Polinom res = *this + (-left);
		return res;
	};
	Polinom operator-(Monom& left) {
		Polinom res = *this + (-Polinom(left));
		return res;
	};
	Polinom operator-() {
		if (first == nullptr) {
			return Polinom();
		}
		Polinom res;
		Node* rp = first;
		res.insert(Monom(-rp->data.k,rp->data.degree));
		rp = rp->next;
		Node* pes = res.first;
		while (rp!=nullptr){
			Node* temp = new Node();
			temp->data.k = -rp->data.k;
			temp->data.degree = rp->data.degree;
			pes->next = temp;
			pes = pes->next;
			rp = rp->next;
		}
		return res;
	};

	bool operator==(const Polinom& right) const {
		bool res = true;
		Node* current2 = right.first;
		Node* current1 = first;
		while (current1 != nullptr || current2 != nullptr) {
			if ((current1 == nullptr && current2 != nullptr) || (current2 == nullptr && current1 != nullptr)) {
				res = false;
				return res;
			}
			if (current1->data != current2->data) {
				res = false;
				return res;
			}
			current1 = current1->next;
			current2 = current2->next;
		}
		return res;
	}
//6 разных баз данных на разных структурах данных, провести исследвания скорости
//массив: sorted table and unsorted table
//две хеш таблицы
// поисковое дерево
//арифметические операции над полиномами
//парсер для полиномов
//интерфейс
};