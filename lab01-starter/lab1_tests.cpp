#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "lab1.h"
#include "test_utils.h"

using ::testing::HasSubstr;

namespace {

TEST(NumWordsIn, OneWord) {
  ASSERT_EQ(numWordsIn("word"), 1);
}

TEST(NumWordsIn, MultipleWords) {
  ASSERT_EQ(numWordsIn("This is two words!"), 4);
}

TEST(NumWordsIn, EmptyString) {
  ASSERT_EQ(numWordsIn(""), 0);
}

class Lab1Main : public CaptureCinCout {};

TEST_F(Lab1Main, OneWord) {
  input << "word" << endl;

  original_main();

  string actual_output = output.str();
  ASSERT_THAT(actual_output, HasSubstr("1"));
}

TEST_F(Lab1Main, MultipleWords) {
  input << "This is an input to main!" << endl;

  original_main();

  string actual_output = output.str();
  ASSERT_THAT(actual_output, HasSubstr("6"));
}

TEST_F(Lab1Main, EmptyString) {
  input << "" << endl;

  original_main();

  string actual_output = output.str();
  ASSERT_THAT(actual_output, HasSubstr("0"));
}

// If you're done early, uncomment these tests to try to work on them! You
// don't need to pass the below tests to receive full credit for the lab.
// There is a similar problem in the project, though, so it's good to start
// thinking about it.

// TEST(NumWordsIn, MultipleSpaces) {
//   ASSERT_EQ(numWordsIn("This   has   three   spaces   between   every   word"), 7);
// }

// TEST(NumWordsIn, LeadingAndTrailingSpaces) {
//   ASSERT_EQ(numWordsIn("    Spaces in front and at the end   "), 7);
// }

// TEST(NumWordsIn, EmptyStringWithOnlySpaces) {
//   ASSERT_EQ(numWordsIn("    "), 0);
// }

}  // namespace
