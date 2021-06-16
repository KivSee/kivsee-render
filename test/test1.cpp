#include <gtest/gtest.h>

template <typename T>
T f_add (T a, T b)
{
    return a + b;
}

template <typename T>
T f_mul (T a, T b)
{
    return a * b;
}


TEST (SillyNumbersTest, Addition) { 
    EXPECT_EQ (6, f_add(3, 3));
    EXPECT_EQ (10, f_add(9, 1));
}

TEST (SillyNumbersTest, Multiplication) { 
    ASSERT_EQ (0.0, f_mul(0.0, 3.1));
    ASSERT_EQ (1.0, f_mul(3.1, 1.0/3.1));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

