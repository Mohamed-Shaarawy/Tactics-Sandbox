#include <gtest/gtest.h>

#include "tactics/core.h"

TEST(CoreTest, AnswerIs42)
{
    EXPECT_EQ(tactics::Answer(), 42);
}
