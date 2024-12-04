 // Why the angle brackets? Grader reasons.
 // Don't change this or you will be sad :(
#include <prqueue.h>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;
using namespace testing;


TEST(PRQueueCore, Test) {
  prqueue<int> pq;
}


TEST(PRQueueCore, DefCons_Size)
{
    prqueue<int> pq;
    
    // Test for correct size initialization
    EXPECT_EQ(pq.size(), 0) << "Default constructor should initialize size to 0.";
}

TEST(PRQueueCore, DefCons_Root)
{
    prqueue<int> pq;

    // Test for correct root initialization
    EXPECT_EQ(pq.getRoot(), nullptr) << "Default constructor should set root to nullptr.";
}


TEST(PRQueueCore, SizeFunction)
{
    prqueue<int> pq;
    
    // Test inital size 
    EXPECT_EQ(pq.size(), 0) << "Initialize size should be 0.";

    pq.enqueue(10, 3);
    EXPECT_EQ(pq.size(), 1) << "Size should be 1 after one enqueue.";

    pq.enqueue(20, 5);
    EXPECT_EQ(pq.size(), 2) << "Size should be 2 after two enqueues.";

    pq.enqueue(30, 1);
    EXPECT_EQ(pq.size(), 3) << "Size should be 3 after three enqueues.";
}


TEST(PRQueueCore, clearFunction)
{
    prqueue<int> pq;
    pq.enqueue(10, 1);
    pq.enqueue(20, 2);
    pq.enqueue(30, 3);

    // Clear the queue
    pq.clear();

    // Check size after clear
    EXPECT_EQ(pq.size(), 0) << "Size should be 0 after clear.";

    // Check root after clear
    EXPECT_EQ(pq.getRoot(), nullptr) << "Root should be nullptr after clear.";
}


TEST(PRQueueUsing, AsStringInclusion)
{
    prqueue<int> pq;
    pq.enqueue(10, 5);
    pq.enqueue(20, 3);
    pq.enqueue(30, 1);
    
    // Updated expected string format based on actual output
    std::string expected = "1 value: 30\n3 value: 20\n5 value: 10\n";
    EXPECT_EQ(pq.as_string(), expected);
}


TEST(PRQueueUsing, AsStringFormatting)
{
    prqueue<int> pq;
    pq.enqueue(10, 5);
    pq.enqueue(20, 3);
    
    // Updated expected string format based on actual output
    EXPECT_EQ(pq.as_string(), "3 value: 20\n5 value: 10\n");
}


TEST(PRQueueUsing, Peek)
{
    prqueue<int> pq;
    pq.enqueue(10, 5);
    pq.enqueue(20, 3);
    
    // Test peek returns the correct value (front node should have priority 3)
    EXPECT_EQ(pq.peek(), 20);
}


TEST(PRQueueUsing, DequeueValue)
{
    prqueue<int> pq;
    pq.enqueue(10, 5);
    pq.enqueue(20, 3);
    
    // Test dequeue returns the correct value (front node should have priority 3)
    EXPECT_EQ(pq.dequeue(), 20);
}


TEST(PRQueueUsing, DequeueSize)
{
    prqueue<int> pq;
    pq.enqueue(10, 5);
    pq.enqueue(20, 3);
    
    pq.dequeue();
    
    // After one dequeue, the size should be 1
    EXPECT_EQ(pq.size(), 1);
}


TEST(PRQueueUsing, DequeueRemoveNode)
{
    prqueue<int> pq;
    pq.enqueue(10, 5);   // Insert with priority 5
    pq.enqueue(20, 3);   // Insert with priority 3

    pq.dequeue();  // Should remove the node with priority 3 (value 20)

    // After dequeue, the as_string output should not contain "20 value: 3"
    EXPECT_THAT(pq.as_string(), Not(HasSubstr("3 value: 20"))) << "The node with priority 3 should have been removed from the tree.";
    /*
    verifies that the output string of pq.as_string() does not contain the substring "3 value: 20". 
    This is useful to confirm that the dequeue function successfully removed the node with priority 3 and value 20 from the priority queue.
    */
}


TEST(PRQueueUsing, DequeueTree)
{
    prqueue<int> pq;
    pq.enqueue(10, 5);  // Insert with priority 5
    pq.enqueue(20, 3);  // Insert with priority 3
    pq.enqueue(15, 4);  // Insert with priority 4

    // Dequeue the node with priority 3 (value 20)
    EXPECT_EQ(pq.dequeue(), 20);

    // After removing priority 3, the size should be reduced by 1
    EXPECT_EQ(pq.size(), 2);

    // Expected tree structure after removing the priority 3 node
    string expected = "4 value: 15\n5 value: 10\n";
    EXPECT_EQ(pq.as_string(), expected) << "Tree structure incorrect after dequeue.";
}


// Test: Ensure that duplicates are inserted into the correct linked list
TEST(PRQueueDuplicates, EnqueueDuplicatesLinkedList)
{
    prqueue<string> pq1;
    pq1.enqueue("Apple", 6);
    pq1.enqueue("Banana", 6);
    pq1.enqueue("Pineapple",6);
    pq1.enqueue("Monkey", 5);
    pq1.enqueue("Donkey",7);
    EXPECT_THAT(pq1.getRoot()->value, StrEq("Apple"));
    ASSERT_NE(pq1.getRoot()->link, nullptr);
    EXPECT_THAT(pq1.getRoot()->link->value, StrEq("Banana"));
    EXPECT_THAT(pq1.getRoot()->link->link->value, StrEq("Pineapple"));
}



// Test: Duplicates are stored in the correct order
TEST(PRQueueDuplicates, EnqueueDuplicatesOrder)
{
    prqueue<string> pq;
    pq.enqueue("First", 2);
    pq.enqueue("Second", 2);
    pq.enqueue("Third", 2);

    string expected = "2 value: First\n2 value: Second\n2 value: Third\n";
    EXPECT_EQ(pq.as_string(), expected) << "Duplicates should maintain insertion order within the same linked list.";
}


// Test: as_string includes all duplicates
TEST(PRQueueDuplicates, AsStringIncludesDuplicates)
{
    prqueue<string> pq;
    pq.enqueue("One", 3);
    pq.enqueue("Two", 3);
    pq.enqueue("Three", 3);

    string expected = "3 value: One\n3 value: Two\n3 value: Three\n";
    EXPECT_EQ(pq.as_string(), expected) << "as_string should include all duplicates.";
}


// Test: Dequeue does not remove other duplicates
TEST(PRQueueDuplicates, DequeuePreservesDuplicates)
{
    prqueue<int> pq;
    pq.enqueue(100, 1);
    pq.enqueue(200, 1);
    pq.enqueue(300, 1);

    EXPECT_EQ(pq.dequeue(), 100) << "Dequeue should return the first inserted duplicate.";
    EXPECT_EQ(pq.as_string(), "1 value: 200\n1 value: 300\n") << "Dequeue should not remove other duplicates.";

    EXPECT_EQ(pq.dequeue(), 200) << "Dequeue should return the next duplicate.";
    EXPECT_EQ(pq.as_string(), "1 value: 300\n") << "Dequeue should preserve remaining duplicates.";

    EXPECT_EQ(pq.dequeue(), 300) << "Dequeue should return the last duplicate.";
    EXPECT_EQ(pq.as_string(), "") << "All duplicates should be removed after dequeueing.";
}


// Test: Ensuring that dequeue does not remove all duplicates
TEST(PRQueueDuplicates, DequeueDoesNotRemoveAllDuplicates)
{
    prqueue<int> pq;
    pq.enqueue(10, 1);  // Insert with priority 1
    pq.enqueue(10, 1);  // Insert duplicate with same priority 1
    pq.enqueue(20, 1);  // Insert with priority 1
    
    // Dequeue one element (should return 10, the first inserted duplicate)
    EXPECT_EQ(pq.dequeue(), 10) << "Dequeue should return the first inserted duplicate.";

    // After dequeueing one, the remaining duplicates (10, 20) should still be in the queue
    string expected_after_dequeue = "1 value: 10\n1 value: 20\n";
    EXPECT_EQ(pq.as_string(), expected_after_dequeue) << "Remaining duplicates should not be lost after dequeueing.";
}


TEST(PRQueueCopying, CopyConstructorNewQueue) {
    prqueue<int> pq;
    pq.enqueue(10, 1);
    pq.enqueue(20, 2);

    prqueue<int> copyQueue(pq);

    EXPECT_EQ(copyQueue.size(), 2);
    EXPECT_EQ(copyQueue.as_string(), pq.as_string()) << "Copy constructor should create an identical queue.";
    
    copyQueue.enqueue(30, 3); // Modify the copy
    EXPECT_NE(copyQueue.as_string(), pq.as_string()) << "Modifying the copy should not affect the original queue.";
}


TEST(PRQueueCopying, CopyConstructorDuplicates) {
    prqueue<int> pq;
    pq.enqueue(10, 1);
    pq.enqueue(20, 1); // Duplicate priority

    prqueue<int> copyQueue(pq);

    string expected = "1 value: 10\n1 value: 20\n";
    EXPECT_EQ(copyQueue.as_string(), expected) << "Copy constructor should copy duplicates correctly.";
}


TEST(PRQueueCopying, assign_duplicates) {
  prqueue<int> pq1;
  pq1.enqueue(99, 9);
  pq1.enqueue(99, 9);

  prqueue<int> pq2;
  pq2 = pq1;

  ASSERT_EQ(pq2.size(), pq1.size());
  pq2.begin();
  int value, priority;

  EXPECT_EQ(pq2.next(value, priority), true);
  EXPECT_EQ(value, 99);
  EXPECT_EQ(priority, 9);

  EXPECT_EQ(pq2.next(value, priority), true);
  EXPECT_EQ(value, 99);
  EXPECT_EQ(priority, 9);

  EXPECT_EQ(pq2.next(value, priority), false);
}


TEST(PRQueueEquality, EqualQueues) {
    prqueue<int> pq1;
    prqueue<int> pq2;

    // Enqueue identical elements into both priority queues
    pq1.enqueue(10, 1);
    pq1.enqueue(20, 2);
    pq1.enqueue(30, 3);

    pq2.enqueue(10, 1);
    pq2.enqueue(20, 2);
    pq2.enqueue(30, 3);

    // Check if operator== returns true for identical queues
    EXPECT_TRUE(pq1 == pq2) << "Equal queues should be considered equal.";
}


TEST(PRQueueEquality, EqualSizesAndPrioritiesDifferentOrder) {
    prqueue<int> pq1;
    prqueue<int> pq2;

    // Enqueue elements with the same values and priorities but in different orders
    pq1.enqueue(10, 1);
    pq1.enqueue(20, 2);
    pq2.enqueue(20, 2);
    pq2.enqueue(10, 1);

    // Check if operator== correctly identifies that they are not equal
    EXPECT_FALSE(pq1 == pq2) << "Queues with the same values and priorities in different orders should not be considered equal.";
}


TEST(PRQueueIterator, BeginOnEmptyQueue) {
    prqueue<char> pq;
    pq.begin();
    char value;
    int priority;
    EXPECT_FALSE(pq.next(value, priority)) << "Expected next() to return false for an empty queue.";
}


TEST(PRQueueIterator, BeginOnSingleItemQueue) {
    prqueue<string> pq;
    pq.enqueue("apple", 2);
    pq.begin();
    string value;
    int priority;
    EXPECT_TRUE(pq.next(value, priority)) << "Expected next() to return true when the queue is not empty.";
    EXPECT_EQ(value, "apple");
    EXPECT_EQ(priority, 2);
}



TEST(PRQueueIterator, NextValue) {
  prqueue<int> pq;
  pq.enqueue(10, 5);
  pq.enqueue(20, 10);
  pq.begin();
  int value, priority;
  pq.next(value, priority);
  EXPECT_EQ(value, 10);
  pq.next(value, priority);
  EXPECT_EQ(value, 20);
}




TEST(PRQueueIterator, according) {
    prqueue<string> pq;

    // Adding entries, including duplicates with the same priority
    pq.enqueue("Alpha", 8);
    pq.enqueue("Bravo", 6);
    pq.enqueue("Charlie", 3);
    pq.enqueue("Delta", 4);
    pq.enqueue("Echo", 7);
    pq.enqueue("Foxtrot", 10);
    pq.enqueue("Golf", 9);
    pq.enqueue("Hotel", 5);
    pq.enqueue("Delta1", 4); // Duplicate with the same priority as Delta
    pq.enqueue("Charlie1", 3); // Duplicate with the same priority as Charlie

    string item;
    int prio;

    // Expected order of items with duplicates included
    vector<string> items = {"Charlie", "Charlie1", "Delta", "Delta1", "Hotel", "Bravo", "Echo", "Alpha", "Golf", "Foxtrot"};
    vector<int> prios = {3, 3, 4, 4, 5, 6, 7, 8, 9, 10};

    pq.begin();
    for (int i = 0; i < items.size(); i++) {
        EXPECT_THAT(pq.next(item, prio), Eq(true));
        EXPECT_THAT(item, Eq(items[i]));
        EXPECT_THAT(prio, Eq(prios[i]));
    }
}







