#include <gtest.h>
#include "Polinom.h"

TEST(PolinomTEST, CanCreatePolinom)
{
	EXPECT_NO_THROW(Polinom polinom);
}

TEST(PolinomTEST, CanCreateFromDouble)
{
	EXPECT_NO_THROW(Polinom polinom(158.4));
}

TEST(PolinomTEST, CanCreateMonomFromString1)
{
	EXPECT_NO_THROW(Monom monom = Monom("2*x^2*x^2*x^2*x^2*y^7*y^0*z^1"));
}
TEST(PolinomTEST, CanCreateMonomFromStrin2)
{
	EXPECT_NO_THROW(Monom monom = Monom("2.2*x^2*x^2*x^2*x^2*y^7*y^0*z^1"));
}
TEST(PolinomTEST, CanCreateMonomFromStrin3)
{
	EXPECT_NO_THROW(Monom monom = Monom("2.2"));
}
TEST(PolinomTEST, CanCreateMonomFromStrin4)
{
	EXPECT_NO_THROW(Monom monom = Monom("2.2*Z^2*x^2*x^2*x^2*y^7*y^0*z^1"));
}
TEST(PolinomTEST, CanCreateMonomFromStrin5)
{
	EXPECT_ANY_THROW(Monom monom = Monom(""));
}
TEST(PolinomTEST, CanPrintMonom1)
{
	Monom monom = Monom("2.2*Z^2*x^2*x^2*x^2*y^7*y^0*z^1");
	EXPECT_NO_THROW(monom.print());
}
TEST(PolinomTEST, CanPrintMonom2)
{
	Monom monom = Monom("2.2*x^2*y^7");
	EXPECT_NO_THROW(monom.print());
}
TEST(PolinomTEST, CanCreatePolinomFromSTR)
{
	EXPECT_NO_THROW(Polinom polinom = Polinom("2 + 2*x^2*y^1 + z^5"));
}
TEST(PolinomTEST, InsertTest)
{
	EXPECT_NO_THROW(
		Polinom polinom = Polinom();
		Monom mon1 = Monom("2*x^4");
		Monom mon2 = Monom("4*y^4");
		Monom mon3 = Monom("8*x^4*y^4");
		Monom mon4 = Monom("2*x^4");
		Monom mon5 = Monom("2*z^4");
		polinom.insert(mon1);
		polinom.insert(mon2);
		polinom.insert(mon3);
		polinom.insert(mon4);
		polinom.insert(mon5);
		Polinom test = Polinom("8*x^4*y^4+4*x^4+4*y^4+2*z^4");
	);
}
TEST(PolinomTEST, PlusTest1) {
	Polinom polinom1 = Polinom("2+2*x^1*y^2*z^3");
	Polinom polinom2 = Polinom("2+2*x^1*y^2*z^3");
	Polinom polinom3;
	polinom3 = polinom1 + polinom2;
	Polinom e = Polinom("4+4*x^1*y^2*z^3");
	EXPECT_EQ(polinom3, e);
}
TEST(PolinomTEST, PlusTest2) {
	Polinom polinom1 = Polinom("2");
	Polinom polinom2 = Polinom("2+2*x^1*y^2*z^3");
	Polinom polinom3;
	polinom3 = polinom1 + polinom2;
	Polinom e = Polinom("4+2*x^1*y^2*z^3");
	EXPECT_EQ(polinom3, e);
}
TEST(PolinomTEST, PlusTest3) {
	Polinom polinom1 = Polinom();
	Polinom polinom2 = Polinom("2*x^2");
	Polinom polinom3;
	polinom3 = polinom1 + polinom2;
	Polinom e = Polinom("2*x^2");
	EXPECT_EQ(polinom3, e);
}
TEST(PolinomTEST, PlusTest4) {
	Polinom polinom1 = Polinom("x^4 + y^4 + z^4");
	Polinom polinom2 = Polinom("x^5 + x^5*y^1 + x^5*z^1");
	Polinom polinom3;
	polinom3 = polinom1 + polinom2;
	Polinom e = Polinom("x^5*y^1+x^5*z^1+x^5+x^4 + y^4 + z^4");
	EXPECT_EQ(polinom3, e);
}
TEST(PolinomTEST, PlusTest5) {

	Polinom polinom1 = Polinom("2*x^2");
	Polinom polinom2 = Polinom();
	Polinom polinom3;
	polinom3 = polinom1 + polinom2;
	Polinom e = Polinom("2*x^2");
	EXPECT_EQ(polinom3, e);
}
TEST(PolinomTEST, MulMonomTest) {
	Polinom polinom1 = Polinom("2*x^2+2+24*z^1");
	Monom monom = Monom("x^1");
	Polinom res = polinom1 * monom;
	Polinom e = Polinom("2*x^3+2*x^1+24*x^1*z^1");
	EXPECT_EQ(res, e);
}
TEST(PolinomTEST, MulTest1) {
	Polinom polinom1 = Polinom("2*x^2+2+1");
	Polinom polinom2 = Polinom("2*x^2+2+1");
	Polinom res = polinom1*polinom2;
	Polinom e = Polinom("4 * x^4 + 12 * x^2 + 9");
	EXPECT_EQ(res, e);
}
TEST(PolinomTEST, MulTest2) {
	Polinom polinom1 = Polinom("2*x^2+2+1");
	Polinom res = polinom1 * polinom1*polinom1;
	Polinom e = Polinom("8*x^6+36*x^4+54*x^2+27");
	EXPECT_EQ(res, e);
}
TEST(PolinomTEST, MulTest3) {
	Polinom polinom1 = Polinom("2*x^2+2+1");
	Polinom res = polinom1 * polinom1 * polinom1*polinom1;
	Polinom e = Polinom("16*x^8+96*x^6+216*x^4+216*x^2+81");
	EXPECT_EQ(res, e);
}
TEST(PolinomTEST, MulTest4) {
	Polinom polinom1 = Polinom("2*x^2*y^1+2+1");
	Polinom res = polinom1 * polinom1 * polinom1 * polinom1;
	Polinom e = Polinom("16*x^8*y^4+96*x^6*y^3+216*x^4*y^2+216*x^2*y^1+81");
	EXPECT_EQ(res, e);
}
TEST(PolinomTEST, UnarMinus) {
	Polinom polinom1 = Polinom("2*x^2+2+24*z^1");
	Polinom res = -polinom1;
	Polinom e = Polinom("-2*x^2-2-24*z^1");
	EXPECT_EQ(res, e);
}
TEST(PolinomTEST, PolinomMinus) {
	Polinom polinom1 = Polinom("2*x^2+2+24*z^1");
	Polinom res = polinom1 - polinom1;
	Polinom e = Polinom("0*x^2+0+0*z^1");
	EXPECT_EQ(res, e);
}