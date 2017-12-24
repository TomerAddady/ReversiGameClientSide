//
// Created by tomer on 28/11/17.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/Cell.h"
using namespace std;

TEST(Cell_test, from_cell_to_string) {
    Cell c1 (3,7);
    Cell c2 (3,7);
    Cell c3 (7,3);
    EXPECT_TRUE(strcmp(c1.getStringCell(), c2.getStringCell()));
    EXPECT_FALSE(strcmp(c1.getStringCell(), c3.getStringCell()));
}

TEST(Cell_test, equals_operator_overLoading_test) {
    Cell c1 (3,7);
    Cell c2 (3,7);
    Cell c3 (7,3);
    EXPECT_TRUE(c1 == c2);
    EXPECT_FALSE(c2 == c3);
}

TEST(Cell_test, getRow_and_getCol_test) {
    Cell c2 (3,7);
    EXPECT_EQ(c2.getCol(), 7);
    EXPECT_EQ(c2.getRow(), 3);
    EXPECT_FALSE(c2.getCol() == 3);
    EXPECT_FALSE(c2.getRow() == 7);

}
