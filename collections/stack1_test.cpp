#include <gtest/gtest.h>
#include "stack1.h"

namespace cao1629 {

TEST(StackTest, PushAndPopTest) {
  Stack<int> stack;
  stack.Push(1);
  stack.Push(2);
  stack.Push(3);

  EXPECT_EQ(stack.Top(), 3);

  stack.Pop();
  EXPECT_EQ(stack.Top(), 2);

  stack.Pop();
  EXPECT_EQ(stack.Top(), 1);

  stack.Pop();
  EXPECT_TRUE(stack.IsEmpty());
}
}



