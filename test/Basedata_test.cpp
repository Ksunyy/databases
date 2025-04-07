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
TEST(SARR, Insert2) {
	SArray arr;
	arr.add("1", Polinom("2*x^2"));
	arr.add("100", Polinom("3*x^3"));
	arr.add("2", Polinom("3*x^3"));
	arr.add("101", Polinom("3*x^3"));
	arr.add("9", Polinom("3*x^3"));
	ASSERT_NO_THROW(arr.add("0", Polinom("3*x^3")););
}
TEST(AVL, INSERT) {
	AVLtree arr;
	ASSERT_NO_THROW(arr.add("1", Polinom("2*x^2")));
}