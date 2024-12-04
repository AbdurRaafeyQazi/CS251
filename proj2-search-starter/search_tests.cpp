#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "include/search.h"

using namespace std;
using namespace testing;

TEST(CleanToken, TokenWithPunctuationAtBothEnds) {
  ASSERT_THAT(cleanToken("!!a!!"), StrEq("a"));
  ASSERT_THAT(cleanToken("...z..."), StrEq("z"));
  ASSERT_THAT(cleanToken("~~~b~~~"), StrEq("b"));
}

TEST(CleanToken, TokenWithPunctuationAtNoEnds) {
  ASSERT_THAT(cleanToken("a!a"), StrEq("a!a"));
  ASSERT_THAT(cleanToken("z#z$z"), StrEq("z#z$z"));
  ASSERT_THAT(cleanToken("bana&&&nna"), StrEq("bana&&&nna"));
}

TEST(CleanToken, TokenWithPunctuationInFront) {
  ASSERT_THAT(cleanToken("&a!a"), StrEq("a!a"));
  ASSERT_THAT(cleanToken("&&&&&&&&z#z$z"), StrEq("z#z$z"));
  ASSERT_THAT(cleanToken("&&&bana&&&nna"), StrEq("bana&&&nna"));
}
// Test one with multiple punctuations even after ""  ""
TEST(CleanToken, TokenWithPunctuationInBack) {
  ASSERT_THAT(cleanToken("a!a!"), StrEq("a!a"));
  ASSERT_THAT(cleanToken("z#z$z~~~~~~"), StrEq("z#z$z"));
  ASSERT_THAT(cleanToken("bana&&&nna^^^"), StrEq("bana&&&nna"));
}
//---------------------------------------------------------------


TEST(GatherTokens, TxtWithLeadingSpaces) {
  string text = "     ^^Umm~what";
  set<string> expected = {"umm~what"};

  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherTokens, TxtWithTrailingSpaces) {
  string text = "Z#z$z~~~~~~     ";
  set<string> expected = {"z#z$z"};

  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

TEST(GatherTokens, TxtWithMultipleSpacesInBetween) {
  string text = "  BA na&& &nna^ ^^  ";
  set<string> expected = {"ba", "na", "nna"};

  EXPECT_THAT(gatherTokens(text), ContainerEq(expected))
      << "text=\"" << text << "\"";
}

//-------------------------------------------------------------------------

TEST(BuildIndex, tTinyTxt) {
  string filename = "data/tiny.txt";
  map<string, set<string>> expectedIndex = {
      {"eggs", {"www.shoppinglist.com"}},
      {"milk", {"www.shoppinglist.com"}},
      {"fish", {"www.shoppinglist.com", "www.dr.seuss.net"}},
      {"bread", {"www.shoppinglist.com"}},
      {"cheese", {"www.shoppinglist.com"}},
      {"red", {"www.rainbow.org", "www.dr.seuss.net"}},
      {"gre-en", {"www.rainbow.org"}},
      {"orange", {"www.rainbow.org"}},
      {"yellow", {"www.rainbow.org"}},
      {"blue", {"www.rainbow.org", "www.dr.seuss.net"}},
      {"indigo", {"www.rainbow.org"}},
      {"violet", {"www.rainbow.org"}},
      {"one", {"www.dr.seuss.net"}},
      {"two", {"www.dr.seuss.net"}},
      {"i'm", {"www.bigbadwolf.com"}},
      {"not", {"www.bigbadwolf.com"}},
      {"trying", {"www.bigbadwolf.com"}},
      {"to", {"www.bigbadwolf.com"}},
      {"eat", {"www.bigbadwolf.com"}},
      {"you", {"www.bigbadwolf.com"}},
  };
  map<string, set<string>> tstIndex;
  int tstNum = buildIndex(filename, tstIndex);

  string indexTestFeedback =
      "buildIndex(\"" + filename + "\", ...) index incorrect\n";
  EXPECT_THAT(tstIndex, ContainerEq(expectedIndex)) << indexTestFeedback;

  string cntTestFeedback =
      "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
  EXPECT_THAT(tstNum, Eq(4)) << cntTestFeedback;
}


TEST(BuildIndex, noFile) {
  string filename = "data/hehe.txt";
  map<string, set<string>> tstIndex;
  int tstNum = buildIndex(filename, tstIndex);

  string cntTestFeedback =
      "buildIndex(\"" + filename + "\", ...) return value incorrect\n";
  EXPECT_THAT(tstNum, Eq(0)) << cntTestFeedback;
}


//--------------------------------------------------------------------------------------

TEST(FindQueryMatches, FirstTermNotInIndex) {
    map<string, set<string>> INDEX = {
        {"hello", {"example.com", "uic.edu"}},
        {"all", {"example.com", "uic.edu", "random.org"}}
    };

    set<string> expected = {}; // No matches because the first term isn't in the index
    EXPECT_THAT(findQueryMatches(INDEX, "nonexistent"), ContainerEq(expected));

    
    expected = {"example.com", "uic.edu", "random.org"};
    EXPECT_THAT(findQueryMatches(INDEX, "nonexistent all"), ContainerEq(expected)); // no term union all // DNE
}

TEST(FindQueryMatches, LaterTermNotInIndex) {
    map<string, set<string>> INDEX = {
        {"hello", {"example.com", "uic.edu"}},
        {"all", {"example.com", "uic.edu", "random.org"}},
        {"known", {"uic.edu"}}
    };

    // Intersection test, later term does not exist in index
    set<string> expected = {};
    EXPECT_THAT(findQueryMatches(INDEX, "hello +nonexistent"), ContainerEq(expected)); // Hello intersects wrong term == empty

    // Union with nonexistent term (should ignore missing term)
    expected = {"example.com", "uic.edu", "random.org"};
    EXPECT_THAT(findQueryMatches(INDEX, "all nonexistent"), ContainerEq(expected)); // all union wrong term ==  all 

    // Difference with nonexistent term (should not remove anything)
    expected = {"uic.edu"};
    EXPECT_THAT(findQueryMatches(INDEX, "known -nonexistent"), ContainerEq(expected)); // nothing to remove, so just return at known
}

