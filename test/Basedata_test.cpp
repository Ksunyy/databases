#include <gtest.h>
#include "Basedata.h"

TEST(SARR, Creation) {
	ASSERT_NO_THROW(SArray());
}
TEST(SARR, Insert1) {
	SArray arr;
	ASSERT_NO_THROW(arr.add("2", Polinom("3*x^3")));
}
TEST(SARR, InsertSameName) {
	SArray arr;
	arr.add("1", Polinom("2*x^2"));
	ASSERT_ANY_THROW(arr.add("1", Polinom("3*x^3")));
}
TEST(SARR, Insert2) {
	SArray arr;
	arr.add("1", Polinom("2*x^2"));
	arr.add("100", Polinom("3*x^3"));
	arr.add("2", Polinom("3*x^3"));
	arr.add("101", Polinom("3*x^3"));
	arr.add("9", Polinom("3*x^3"));
	ASSERT_NO_THROW(arr.add("0", Polinom("3*x^3")););
}
TEST(AVL, INSERT1) {
	AVLtree arr;
	arr.printTreeByLevels();
	arr.add("1", Polinom("2*x^2"));
	arr.printTreeByLevels();
	ASSERT_NO_THROW();
}
TEST(AVL, INSERT2) {
	AVLtree arr;
	arr.add("1", Polinom("2*x^2"));
	arr.add("2", Polinom("2*x^2"));
	arr.add("3", Polinom("2*x^2"));
	arr.printTreeByLevels();
	arr.add("4", Polinom("2*x^2"));
	arr.add("5", Polinom("2*x^2"));
	arr.printTreeByLevels();
	arr.add("6", Polinom("2*x^2"));
	arr.add("7", Polinom("2*x^2"));
	arr.printTreeByLevels();
	ASSERT_NO_THROW();
}
TEST(AVL, INSERT3) {
	AVLtree arr;
	arr.add("7", Polinom("2*x^2"));
	arr.add("6", Polinom("2*x^2"));
	arr.add("5", Polinom("2*x^2"));
	arr.printTreeByLevels();
	arr.add("4", Polinom("2*x^2"));
	arr.add("3", Polinom("2*x^2"));
	arr.printTreeByLevels();
	arr.add("2", Polinom("2*x^2"));
	arr.add("1", Polinom("2*x^2"));
	arr.printTreeByLevels();
	ASSERT_NO_THROW();
}
TEST(AVL, INSERT4) {
	AVLtree arr;
	arr.add("7", Polinom("2*x^2"));
	arr.add("5", Polinom("2*x^2"));
	arr.add("6", Polinom("2*x^2"));
	arr.printTreeByLevels();
	arr.add("3", Polinom("2*x^2"));
	arr.add("4", Polinom("2*x^2"));
	arr.printTreeByLevels();
	arr.add("8", Polinom("2*x^2"));
	arr.add("1", Polinom("2*x^2"));
	arr.add("2", Polinom("2*x^2"));
	arr.printTreeByLevels();
	ASSERT_NO_THROW();
}
TEST(AVL, DEL1) {
	AVLtree arr;
	arr.add("7", Polinom("2*x^2"));
	arr.printTreeByLevels();
	arr.remove("7");
	arr.printTreeByLevels();
	ASSERT_NO_THROW();
}
TEST(AVL, DEL2) {
	AVLtree arr;
	arr.add("7", Polinom("2*x^2"));
	arr.add("8", Polinom("2*x^2"));
	arr.add("9", Polinom("2*x^2"));
	arr.printTreeByLevels();
	arr.remove("7");
	arr.printTreeByLevels();
	ASSERT_NO_THROW();
}
TEST(AVL, DEL3) {
	AVLtree arr;
	arr.add("7", Polinom("2*x^2"));
	arr.add("8", Polinom("2*x^2"));
	arr.add("9", Polinom("2*x^2"));
	arr.add("1", Polinom("2*x^2"));
	arr.add("2", Polinom("2*x^2"));
	arr.add("3", Polinom("2*x^2"));
	arr.printTreeByLevels();
	arr.remove("7");
	arr.printTreeByLevels();
	ASSERT_NO_THROW();
}
TEST(AVL, DEL4) {
	AVLtree arr;
	arr.add("7", Polinom("2*x^2"));
	arr.add("8", Polinom("2*x^2"));
	arr.add("9", Polinom("2*x^2"));
	arr.add("1", Polinom("2*x^2"));
	arr.add("2", Polinom("2*x^2"));
	arr.add("3", Polinom("2*x^2"));
	arr.printTreeByLevels();
	arr.remove("8");
	arr.printTreeByLevels();
	ASSERT_NO_THROW();
}
TEST(AVL, FIND1) {
	AVLtree arr;
	arr.add("7", Polinom("2*x^2"));
	arr.add("8", Polinom("2*x^2*y^1"));
	arr.add("9", Polinom("2*x^2"));
	arr.add("1", Polinom("2*x^2"));
	arr.add("2", Polinom("2*x^2"));
	arr.add("3", Polinom("2*x^2"));
	Polinom res = arr.find("8");
	EXPECT_EQ(Polinom("2*x^2*y^1"), res);
}