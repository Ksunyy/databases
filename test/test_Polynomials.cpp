#include <gtest.h>
#include "string"
#include "Polynomials.h"


// —ортируютс€ по степен€м от меньшего к большему

// --------------- POSITIVE TESTS ---------------- //

// SMOKE //

TEST(polynomials, can_create_base_string) {
	std::string str = "2x^3y^4z^5";
	ASSERT_NO_THROW(Polynomials p(str));
}
TEST(polynomials, can_create_base_positive_size) {
	ASSERT_NO_THROW(Polynomials p(8));
}
TEST(polynomials, can_create_default_pol) {
	ASSERT_NO_THROW(Polynomials p());
}

TEST(polynomials, can_compare_non_eq_pol) {
	std::string str1 = "2x^3y^4z^5-9x^4y^2z^3";
	std::string str2 = "2x^3y^4z^5+15x^9y^2z^1";
	Polynomials p1(str1);
	Polynomials p2(str2);
	bool chek = (p1 == p2);
	EXPECT_EQ(0, chek);

}
TEST(polynomials, can_compare_eq_pol) {
	std::string str1 = "2x^3y^4z^5-9x^4y^2z^3";
	std::string str2 = "2x^3y^4z^5-9x^4y^2z^3";
	Polynomials p1(str1);
	Polynomials p2(str2);
	bool chek = (p1 == p2);
	EXPECT_EQ(1, chek);

}

TEST(polynomials, chek_len) {
	std::string str = "2x^3y^3z^3-4x^8y^3z^3+3x^3y^9z^3";
	Polynomials p(str);
	EXPECT_EQ(3, p.lenPoly());
}

TEST(polynomials, sorted_store) {
	std::string str1 = "x^9y^9z^3-4x^9y^9z^9+5x^2y^1z^2";
	std::string str2 = "5x^2y^1z^2+x^9y^9z^3-4x^9y^9z^9";
	Polynomials p1(str1);
	Polynomials chek(str2);
	bool ch = p1 == chek;
	EXPECT_EQ(1, ch);

}



// FUNCTIONS //

TEST(polynomials, plus_two_pols) {
	std::string str1 = "5x^9y^2z^3-3x^2y^5z^9+4x^7y^9z^2";
	std::string str2 = "10x^9y^2z^3-6x^2y^5z^9+8x^7y^9z^2";
	Polynomials p1(str1);
	Polynomials p2(str2);
	Polynomials p3 = (p1 + p1);
	bool chek = p2 == p3;
	EXPECT_EQ(1, chek);
}
TEST(polynomials, minus_two_pols) {
	std::string str1 = "5x^9y^2z^3-3x^2y^5z^9+4x^7y^9z^2";
	std::string str2 = "10x^9y^2z^3-6x^2y^5z^9+8x^7y^9z^2";
	Polynomials p1(str1);
	Polynomials p2(str2);
	Polynomials p3 = (p2 - p1);
	bool chek = p1 == p3;
	EXPECT_EQ(1, chek);
}

TEST(polynomials, mult_on_const) {
	std::string str1 = "5x^9y^2z^3-3x^2y^5z^9+4x^7y^9z^2";
	std::string str2 = "10x^9y^2z^3-6x^2y^5z^9+8x^7y^9z^2";
	double num = 2;
	Polynomials p1(str1);
	Polynomials p2(str2);
	Polynomials p3 = p1 * num;
	bool chek = p2 == p3;
	EXPECT_EQ(1, chek);
}

TEST(polynomials, unary_minus) {
	std::string str1 = "5x^9y^2z^3-3x^2y^5z^9+4x^7y^9z^2";
	std::string str2 = "-5x^9y^2z^3+3x^2y^5z^9-4x^7y^9z^2";
	Polynomials p1(str1);
	Polynomials p2(str2);
	Polynomials p3 = -p1;
	bool chek = p2 == p3;
	EXPECT_EQ(1, chek);
}

TEST(polynomials, mult_monom_on_pol) {
	monom m(10, 111);
	std::string str1 = "5x^1y^1z^1+2x^5y^5z^5";
	std::string chekStr = "50x^2y^2z^2+20x^6y^6z^6";
	Polynomials p(str1);
	Polynomials chek(chekStr);
	bool ch = chek == (p * m);
	EXPECT_EQ(1, ch);

}

TEST(polynomials, mult_two_pols) {
	std::string str1 = "5x^1y^1z^1+2x^5y^5z^5";
	std::string str2 = "5x^2y^2z^1+3x^3y^3z^3";
	std::string chekStr = "25x^3y^3z^2+15x^4y^4z^4+10x^7y^7z^6+6x^8y^8z^8";
	Polynomials p1(str1);
	Polynomials p2(str2);
	Polynomials chek(chekStr);
	bool ch = chek == (p1 * p2);
	EXPECT_EQ(1, ch);

}

// BORDER CONDITION //

TEST(polynomials, sub_oneself) {
	std::string chek = "";
	std::string str = "5x^9y^2z^3-3x^2y^5z^9+4x^7y^9z^2";
	Polynomials p1(str);
	Polynomials p3 = (p1 - p1);
	Polynomials p2(chek);
	bool ch = p2 == p3;
	EXPECT_EQ(1, ch);

}

TEST(polynomials, mult_two_pols_example) {
	std::string str1 = "x^3y^0z^0+x^1y^0z^0+x^0y^0z^0";
	std::string str2 = "x^2y^0z^0+x^0y^0z^0";
	std::string chekStr = "x^5y^0z^0+2x^3y^0z^0+x^2y^0z^0+x^1y^0z^0+x^0y^0z^0";
	Polynomials p1(str1);
	Polynomials p2(str2);
	Polynomials chek(chekStr);
	bool ch = chek == (p1 * p2);
	EXPECT_EQ(1, ch);

}


TEST(polynomials, can_mult_max_degree) {

}

TEST(polynomials, mult_by_zero) {
	std::string str2 = "";
	std::string str = "5x^9y^2z^3-3x^2y^5z^9+4x^7y^9z^2";
	Polynomials p1(str);
	Polynomials p2(str2);
	Polynomials p3 = p1 * 0;
	bool chek = p2 == p3;
	EXPECT_EQ(1, chek);

}

TEST(polynomials, empty_polynom_zero_coef) {
	std::string zeros = "0x^2y^3z^9-0x^2y^5z^3";
	Polynomials p1(zeros);
	Polynomials p2;
	bool chek = p2 == p1;
	EXPECT_EQ(1, chek);
}

TEST(polynomials, empty_pol_empty_str) {
	std::string empty = "";
	ASSERT_NO_THROW(Polynomials p(empty));
}

// --------------- NEGATIVE TESTS ---------------- //

TEST(polynomials, cant_create_poly_negative_len) {
	ASSERT_ANY_THROW(Polynomials p(-10));
}
TEST(polynomials, mult_extra_degree_monom) {
	std::string str1 = "5x^1y^1z^1+2x^5y^5z^5";
	monom m(10, 999);
	Polynomials p1(str1);
	ASSERT_ANY_THROW(p1 * m);
}

TEST(polynomials, mult_extra_degree_poly) {
	std::string str1 = "5x^1y^1z^1+2x^5y^5z^5";
	std::string str2 = "5x^9y^9z^9+2x^5y^5z^5";
	Polynomials p1(str1);
	Polynomials p2(str2);
	ASSERT_ANY_THROW(p1 * p2);
}





