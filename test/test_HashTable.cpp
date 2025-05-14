#include <gtest.h>
#include "string"
#include "Polynomials.h"
#include "HashTable.h"

class HashTableTest : public:: testing:: Test {
protected:
	HashTableOpenAdress tab;
	std::string str1 = "x^2y^0z^0+x^0y^0z^0";
	Polynomials poly = Polynomials(str1);
	virtual void SetUp() {
		tab = HashTableOpenAdress(100000);
		for (int i = 0; i < 100000; i++) {
			std::string name = std:: to_string(i);
			tab.insert(name, poly);
		}

	}
	virtual void TearDown() {

	}

};

// --------------- POSITIVE TESTS ---------------- //

// SMOKE //

TEST(HashTable, can_create_table) {
	ASSERT_NO_THROW(HashTableOpenAdress tab);
}

TEST(HashTable, can_create_table_fix_len) {
	ASSERT_NO_THROW(HashTableOpenAdress tab(10));
}

TEST(HashTable, can_copy_table) {
	HashTableOpenAdress tab1;
	ASSERT_NO_THROW(HashTableOpenAdress(tab1));
}

TEST(HashTable, can_asign_table) {
	HashTableOpenAdress tab1;
	HashTableOpenAdress tab2;
	ASSERT_NO_THROW(tab1 = tab2);
}

// FUNCTIONS //

TEST_F(HashTableTest, can_find_on_exist_key) {
	EXPECT_EQ(1, tab.find("0"));
}
TEST_F(HashTableTest, can_find_on_unexist_key) {
	EXPECT_EQ(0, tab.find("111111n"));
}

TEST_F(HashTableTest, can_erase_on_exist_key) {
	tab.erase("90");
	EXPECT_EQ(0, tab.find("90"));
}

TEST_F(HashTableTest, size_down_after_erase) {
	int size1 = tab.GetCountItems();
	tab.erase("94");
	int size2 = tab.GetCountItems();
	EXPECT_EQ(size1-1, size2);
}

TEST_F(HashTableTest, can_erase_on_unexist_key) {
	tab.erase("3333333g");
	EXPECT_EQ(0, tab.find("3333333g"));
}

TEST_F(HashTableTest, can_insert_on_unexist_key) {
	std::string name = "nnnnnname";
	std::string str1 = "x^2y^0z^0+x^0y^0z^0";
	Polynomials poly = Polynomials(str1);
	tab.insert(name, poly);
	EXPECT_EQ(1, tab.find(name));
}
TEST_F(HashTableTest, size_up_after_insert) {
	std::string name = "n110101";
	std::string str1 = "x^2y^0z^0+x^0y^0z^0";
	Polynomials poly = Polynomials(str1);
	int size1 = tab.GetCountItems();
	tab.insert(name, poly);
	int size2 = tab.GetCountItems();
	EXPECT_EQ(size1+1, size2);
}


TEST_F(HashTableTest, can_insert_on_unexist_key_repacking) {
	std::string name = std:: to_string(900099);
	std::string str1 = "x^2y^0z^0+x^0y^0z^0";
	Polynomials poly = Polynomials(str1);
	tab.insert(name, poly);
	EXPECT_EQ(1, tab.find(name));
}
TEST(HashTable, size_up_after_repacking) {
	HashTableOpenAdress tab1;
	std::string name1 = std::to_string(900099999);
	std::string name2 = std::to_string(99999);
	std::string str1 = "x^2y^0z^0+x^0y^0z^0";
	Polynomials poly = Polynomials(str1);
	tab1.insert(name1, poly);
	int size1 = tab1.GetSize();
	tab1.insert(name2, poly);
	EXPECT_EQ(size1*2, tab1.GetSize());
}

TEST(HashTable, can_get_size) {
	HashTableOpenAdress tab(10);
	EXPECT_EQ(10, tab.GetSize());
}
// --------------- NEGATIVE TESTS ---------------- //


TEST(HashTable, cant_create_tab_negative_len) {
	ASSERT_ANY_THROW(HashTableOpenAdress tab1(-1));
}




