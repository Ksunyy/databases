#include <iostream>
template<typename T>
class Polinom {
private:
	struct stepeni
	{
		int koefficient
		std::int8_t x;
		std::int8_t y;
		std::int8_t z;
	};
	std::string name;
	std::vector<stepeni> polinom;
public:
	Polinom();
	~Polinom();
	operator+ () {};
	opertator* () {};
	operator-() {};
	operator-() {};
	operator/(){};

//6 разных баз данных на разных структурах данных, провести исследвания скорости
//массив: sorted table and unsorted table
//две хеш таблицы
// поисковое дерево
//арифметические операции над полиномами
//парсер для полиномов
//интерфейс
};
class base {
	struct e {
		std::string name;
		Polinom polinom;
	};
private:
	std::stack<e*> data;
public:
	void add();
	void remove();
	auto find();
}