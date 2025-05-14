#pragma once
#include <gtest.h>
#include <vector>
#include <cmath>
#include "Polynomials.h"
#include "RBtree.h"


class RBtreeTest : public::testing::Test {
protected:
	RBtree tree;
	std::string str1 = "x^2y^0z^0+x^0y^0z^0";
	Polynomials poly = Polynomials(str1);

	virtual void SetUp() {
		for (int i = 0; i < 100000; ++i) {
			tree.RB_insert(i, poly);
		}
	}

	virtual void TearDown() {


	}

};



// --------------- POSITIVE TESTS ---------------- //

// SMOKE //

TEST(RBtrees, can_create_RBtree) {
	ASSERT_NO_THROW(RBtree tree);
}	

TEST(RBtrees, can_copy_RBtree) {
	RBtree tree1;
	ASSERT_NO_THROW(RBtree(tree1));
}

TEST(RBtrees, can_asing_another_RBtree) {
	RBtree tree1;
	RBtree tree2;
	ASSERT_NO_THROW(tree2 = tree1);

}

TEST(RBtrees, can_print_RBtree) {
	Polynomials p;
	int key = 1;
	RBtree tree1;
	tree1.RB_insert(key, p);

	ASSERT_NO_THROW(tree1.RB_print());
}

// FUNCTIONS //

TEST_F(RBtreeTest, chek_size) {
	EXPECT_EQ(100000, tree.getSize());
}

TEST_F(RBtreeTest, is_root_black_after_insert) {
	EXPECT_EQ(1, tree.getRoot()->col);
}

TEST_F(RBtreeTest, count_rotates_after_insert) {
	bool chek = 1;
	for (int i = 0; i < tree.getInsertRotates().size(); i++) {
		if (tree.getInsertRotates()[i] > 2) chek = 0;

	}
	EXPECT_EQ(1, chek);
}

TEST(RBtree, count_two_rotates_after_insert) {
	RBtree tree1;
	Polynomials p;
	int mx = 0;
	std::vector<int> v = { 10, 30, 20, 40, 15 };
	for (int i = 0; i < 5; i++) {
		tree1.RB_insert(v[i], p);
		if (mx <= tree1.getInsertRotates()[i]) mx = tree1.getInsertRotates()[i];
	}
	EXPECT_EQ(2, mx);

}

TEST_F(RBtreeTest, erase_on_exist_key) {
	tree.RB_erase(2);
	EXPECT_EQ(nullptr, tree.RB_find(2));
}

TEST_F(RBtreeTest, erase_on_unexist_key) {
	tree.RB_erase(-200);
	EXPECT_EQ(nullptr, tree.RB_find(-200));
}

TEST_F(RBtreeTest, is_root_black_after_erase) {
	tree.RB_erase(3);
	EXPECT_EQ(1, tree.getRoot()->col);
}

TEST_F(RBtreeTest, count_rotates_after_erase) {
	bool chek = 1;
	for (int i = 0; i < tree.getSize(); i++) {
		tree.RB_erase(i);
		if (tree.getEraseRotates()[i] > 3) chek = 0;
	}
	EXPECT_EQ(1, chek);
}

TEST_F(RBtreeTest, find_on_exist_key) {
	EXPECT_NE(nullptr, tree.RB_find(10));
}

TEST_F(RBtreeTest, find_on_unexist_key) {
	EXPECT_EQ(nullptr, tree.RB_find(-200));
}






