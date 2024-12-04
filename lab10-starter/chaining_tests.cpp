#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <vector>

#include "chaining.h"

using namespace std;
using namespace testing;

vector<pair<int, int>> collectEntries(ChainingHashMap::Entry* head) {
  vector<pair<int, int>> entries;
  while (head != nullptr) {
    entries.push_back({head->k, head->v});
    head = head->next;
  }
  return entries;
}

vector<vector<pair<int, int>>> collectMapEntries(ChainingHashMap& m) {
  vector<vector<pair<int, int>>> buckets;
  for (int i = 0; i < m.capacity; i++) {
    buckets.push_back(collectEntries(m.buckets[i]));
  }
  return buckets;
}

namespace {

TEST(ChainingNoRehash, Sequential) {
  ChainingHashMap student_map(5);
  for (int i = -2; i < 3; i++) {
    student_map.insert(i, i);
  }

  ASSERT_THAT(student_map.capacity, Eq(5))
      << "Map does not have capacity 5 -- resized too early?`";

  vector<vector<pair<int, int>>> expected_entries = {
      {{0, 0}}, {{1, 1}}, {{2, 2}}, {{-2, -2}}, {{-1, -1}},
  };
  auto student_entries = collectMapEntries(student_map);
  for (int i = 0; i < student_entries.size(); i++) {
    auto student_bucket = student_entries.at(i);
    auto expected_bucket = expected_entries.at(i);
    EXPECT_THAT(student_bucket, UnorderedElementsAreArray(expected_bucket))
        << "Contents of bucket " << i << " incorrect";
  }
}

TEST(ChainingNoRehash, SingleBucket) {
  vector<pair<int, int>> entries;
  ChainingHashMap student_map(160);
  for (int i = -10; i < 100; i++) {
    // Multiples of 160 should all go in bucket 0 for all capacities:
    // 5, 10, 20, 40, 80, 160
    student_map.insert(160 * i, i);
    entries.push_back({160 * i, i});
  }

  ASSERT_THAT(student_map.capacity, Eq(160))
      << "Map has incorrect capacity after sequence of insertions";

  auto student_entries = collectMapEntries(student_map);
  ASSERT_THAT(student_entries.at(0), UnorderedElementsAreArray(entries))
      << "Contents of bucket index" << 0 << " incorrect after rehash";
  for (int i = 1; i < student_entries.size(); i++) {
    auto student_bucket = student_entries.at(i);
    EXPECT_THAT(student_bucket, IsEmpty())
        << "Contents of bucket index" << i << " incorrect after rehash";
  }
}

TEST(ChainingRehash, Sequential) {
  ChainingHashMap student_map(5);
  for (int i = -2; i < 4; i++) {
    student_map.insert(i, i);
  }

  ASSERT_THAT(student_map.capacity, Eq(10))
      << "Map does not have capacity 5*2 = 10 -- didn't resize?`";

  auto student_entries = collectMapEntries(student_map);
  vector<vector<pair<int, int>>> expected_entries = {
      {{0, 0}}, {{1, 1}}, {{2, 2}}, {{3, 3}},   {},
      {},       {},       {},       {{-2, -2}}, {{-1, -1}}};
  for (int i = 0; i < student_entries.size(); i++) {
    auto student_bucket = student_entries.at(i);
    auto expected_bucket = expected_entries.at(i);
    EXPECT_THAT(student_bucket, UnorderedElementsAreArray(expected_bucket))
        << "Contents of bucket " << i << " incorrect after rehash";
  }
}

TEST(ChainingRehash, SingleBucket) {
  vector<pair<int, int>> entries;
  ChainingHashMap student_map(5);
  for (int i = 0; i < 100; i++) {
    // Multiples of 160 should all go in bucket 0 for all capacities:
    // 5, 10, 20, 40, 80, 160
    student_map.insert(160 * i, i);
    entries.push_back({160 * i, i});
  }

  ASSERT_THAT(student_map.capacity, Eq(160))
      << "Map has incorrect capacity after sequence of insertions";

  auto student_entries = collectMapEntries(student_map);
  ASSERT_THAT(student_entries.at(0), UnorderedElementsAreArray(entries))
      << "Contents of bucket index" << 0 << " incorrect after rehash";
  for (int i = 1; i < student_entries.size(); i++) {
    auto student_bucket = student_entries.at(i);
    EXPECT_THAT(student_bucket, IsEmpty())
        << "Contents of bucket index" << i << " incorrect after rehash";
  }
}

};  // namespace
