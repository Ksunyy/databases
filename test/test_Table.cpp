#pragma once
#include <gtest.h>
#include "Polynomials.h"
#include "string"
#include "Table.h"


// --------------- POSITIVE TESTS ---------------- //

// SMOKE //

TEST(tables, can_create_default_table) {
	ASSERT_NO_THROW(Table t());
}

TEST(tables, can_insert_one_polynomial) {
	Polynomials p;
	std::string name = "name";
	Table t;
	ASSERT_NO_THROW(t.insert(name, p));
}

TEST(tables, can_erase_one_polynomial) {
	Polynomials p1, p2;
	std::string name = "name";
	std::string name2 = "name2";
	Table t;
	t.insert(name, p1);
	t.insert(name2, p2);

	ASSERT_NO_THROW(t.erase(name));
}

// FUNCTIONS //

TEST(tables, find_exist_polinomyal) {
	Polynomials p;
	std::string name = "name";
	Table t;
	t.insert(name, p);
	EXPECT_EQ(1, t.find(name));
}
TEST(tables, find_unexist_polinomyal) {
	Polynomials p;
	std::string name = "name";
	Table t;
	EXPECT_EQ(0, t.find(name));
}

TEST(tables, can_get_size_of_table) {
	Polynomials p1, p2;
	std::string name = "name";
	std::string name2 = "name2";
	Table t;
	t.insert(name, p1);
	t.insert(name2, p2);
	EXPECT_EQ(2, t.size());
}

TEST(tables, erase_exist_key) {
	Polynomials p1, p2;
	std::string name = "name";
	std::string name2 = "name2";
	Table t;
	t.insert(name, p1);
	t.insert(name2, p2);
	t.erase(name);
	EXPECT_EQ(0, t.find(name));

}

TEST(tables, erase_unexist_key) {
	Polynomials p1, p2;
	std::string name = "name";
	std::string name2 = "name2";
	Table t;
	t.insert(name2, p2);
	t.erase(name);
	EXPECT_EQ(0, t.find(name));

}

TEST(tables, insert_unexist_key) {
	Polynomials p1, p2;
	std::string name = "name";
	std::string name2 = "name2";
	Table t;
	t.insert(name, p1);
	t.insert(name2, p2);
	EXPECT_EQ(1, t.find(name));
}
TEST(tables, insert_equal_poly_dif_names) {
	Polynomials p1;
	std::string name = "name";
	std::string name2 = "name2";
	Table t;
	t.insert(name, p1);
	ASSERT_NO_THROW(t.insert(name2, p1));

}

// BORDER CONDITION //

TEST(tables, erase_elem_empty_table) {
	Table t;
	t.erase("name");
	EXPECT_EQ(0, t.size());
}

TEST(tables, find_in_empty_table) {
	Table t;
	EXPECT_EQ(0, t.find("name"));
}

// --------------- NEGATIVE TESTS ---------------- //

TEST(tables, throw_insert_existing_key) {
	Polynomials p1, p2;
	std::string name = "name";
	Table t;
	t.insert(name, p1);
	ASSERT_ANY_THROW(t.insert(name, p2));
}

 