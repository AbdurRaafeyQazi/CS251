#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "canvaslist.h"
#include "include/shape.h"

using namespace std;
using namespace testing;

TEST(CanvasListCore, DefaultConstructor) {
  CanvasList list;  
  EXPECT_EQ(list.size(), 0) << "Constructor should initialize size to 0";
  EXPECT_TRUE(list.empty()) << "List should be empty after initialization";
  EXPECT_EQ(list.front(), nullptr);
}

TEST(CanvasListCore, PushFront) {
  CanvasList list;
  Shape* shape = new RightTriangle(2, 77);
  Shape* shape2 = new Circle(2, 2, 77);
  Shape* shape3 = new RightTriangle(4, 5, 2, 77);

  list.push_front(shape);
  list.push_front(shape2);
  list.push_front(shape3);

  // Check the size of the list
  EXPECT_EQ(list.size(), 3);

  // Check if the list is not empty
  EXPECT_FALSE(list.empty());

  // Check if the first element in the list is shape3 (the last one pushed)
  EXPECT_EQ(list.front()->value->as_string(), shape3->as_string());
}

TEST(CanvasListCore, EraseAll) {
  CanvasList list;

  Shape* shape = new RightTriangle(2, 77);
  Shape* shape2 = new Circle(2, 2, 77);
  Shape* shape3 = new RightTriangle(4, 5, 2, 77);

  list.push_front(shape);
  list.push_front(shape2);
  list.push_front(shape3);

  list.push_front(new Shape(2, 2));
  list.push_front(new Rect(0, 0, 3, 4));
  list.push_front(new RightTriangle(0, 0, 2, 3));
  list.push_back(new Circle(0, 0, 9));

  list.clear();
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(CanvasListIterating, CopyConstructor) {
  CanvasList list;
  list.push_front(new Shape(2, 2));
  list.push_front(new Rect(0, 0, 3, 4));
  list.push_front(new RightTriangle(0, 0, 2, 3));
  list.push_back(new Circle(0, 0, 9));

  Shape* shape = new RightTriangle(2, 77);
  Shape* shape2 = new Circle(2, 2, 77);
  Shape* shape3 = new RightTriangle(4, 5, 2, 77);

  list.push_front(shape);
  list.push_front(shape2);
  list.push_back(shape3);

  // Create a copy of the list using the copy constructor
  CanvasList copy(list);

  
  EXPECT_EQ(copy.size(), list.size());

  
  for (size_t i = 0; i < list.size(); ++i) {
    EXPECT_EQ(copy.shape_at(i)->as_string(), list.shape_at(i)->as_string());
  }
}

TEST(CanvasListIterating, Incorrect_Shape_Index) {
  CanvasList list;

  list.push_front(new Shape(2, 2));  
  list.push_front(new Rect(0, 0, 3, 4));
  list.push_front(new RightTriangle(0, 0, 2, 3));
  list.push_back(new Circle(0, 0, 9));  

  
  EXPECT_EQ(list.shape_at(0)->as_string(),
            "It's a Right Triangle at x: 0, y: 0 with base: 2 and height: 3");
  EXPECT_EQ(list.shape_at(1)->as_string(),
            "It's a Rectangle at x: 0, y: 0 with width: 3 and height: 4");
  EXPECT_EQ(list.shape_at(2)->as_string(), "It's a Shape at x: 2, y: 2");
  EXPECT_EQ(list.shape_at(3)->as_string(),
            "It's a Circle at x: 0, y: 0, radius: 9");

  // Check for out-of-bounds access
  EXPECT_EQ(list.shape_at(4), nullptr);
  EXPECT_EQ(list.shape_at(-1), nullptr);
}

TEST(CanvasListIterating, IncorrectFind) {
  CanvasList list;
  list.push_front(new Shape(2, 2));
  list.push_front(new Rect(0, 1, 3, 4));
  list.push_front(new RightTriangle(7, 99, 2, 3));
  list.push_back(new Circle(0, 0, 9));

  EXPECT_EQ(list.find(7, 99), 0);
  EXPECT_EQ(list.find(0, 1), 1);
  EXPECT_EQ(list.find(2, 2), 2);
  EXPECT_EQ(list.find(0, 0), 3);

  EXPECT_EQ(list.find(-1, -1), -1);

  
  CanvasList emptyList;
  EXPECT_EQ(emptyList.find(1, 1),
            -1);  

  
  emptyList.push_back(new Circle(1, 1, 5));
  EXPECT_EQ(emptyList.find(1, 1),
            0);  

  list.push_front(
      new Circle(0, 0, 5));  
  EXPECT_EQ(list.find(0, 0), 0);
}

TEST(CanvasListModifying, Assignment_Operator) {
  CanvasList list1;
  list1.push_back(new Circle(9, 9, 10));

  
  CanvasList listCopy;
  listCopy = list1;

  
  ASSERT_EQ(listCopy.size(), 1);
  ASSERT_EQ(listCopy.front()->value->as_string(),
            "It's a Circle at x: 9, y: 9, radius: 10");

  CanvasList emptyList;
  listCopy = emptyList;

  EXPECT_TRUE(listCopy.empty());

  listCopy.push_back(new Circle(9, 9, 10));

  CanvasList list3;
  list3 = listCopy;

  ASSERT_EQ(list3.size(), 1);
  ASSERT_EQ(list3.front()->value->as_string(),
            "It's a Circle at x: 9, y: 9, radius: 10");

  delete list1.pop_front();
  delete list3.pop_front();
}

TEST(CanvasListModifying, Pop_Front) {

  CanvasList list;
  list.push_back(new Circle(9, 9, 10));

  Shape* popFront = list.pop_front();
  EXPECT_EQ(popFront->as_string(), "It's a Circle at x: 9, y: 9, radius: 10");

  delete popFront;

  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);

  popFront = list.pop_front();
  EXPECT_EQ(popFront, nullptr);
  EXPECT_TRUE(list.empty());

  
  list.push_back(new Circle(1, 1, 5));             
  list.push_front(new RightTriangle(0, 0, 3, 4));  
  list.push_back(new Rect(5, 5, 6, 7));            

  
  EXPECT_EQ(list.size(), 3);

  
  popFront = list.pop_front();
  EXPECT_EQ(popFront->as_string(),
            "It's a Right Triangle at x: 0, y: 0 with base: 3 and height: 4");
  delete popFront;  

  
  EXPECT_EQ(list.size(), 2);
  EXPECT_FALSE(list.empty());

  
  popFront = list.pop_front();
  EXPECT_EQ(popFront->as_string(), "It's a Circle at x: 1, y: 1, radius: 5");
  delete popFront;

  
  EXPECT_EQ(list.size(), 1);

  
  popFront = list.pop_front();
  EXPECT_EQ(popFront->as_string(),
            "It's a Rectangle at x: 5, y: 5 with width: 6 and height: 7");
  delete popFront;


  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);


  popFront = list.pop_front();
  EXPECT_EQ(popFront, nullptr);
  EXPECT_TRUE(list.empty());
}

TEST(CanvasListModifying, Pop_back_empty) {
  CanvasList list;

  
  list.push_back(new Shape(99, 99));               
  list.push_back(new Rect(0, 0, 5, 54));           
  list.push_back(new RightTriangle(0, 0, 91, 7));  

  
  EXPECT_EQ(list.size(), 3);

  
  Shape* popBack = list.pop_back();
  EXPECT_EQ(popBack->as_string(),
            "It's a Right Triangle at x: 0, y: 0 with base: 91 and height: 7");
  EXPECT_EQ(list.size(), 2);
  delete popBack;  

  
  popBack = list.pop_back();
  EXPECT_EQ(popBack->as_string(),
            "It's a Rectangle at x: 0, y: 0 with width: 5 and height: 54");
  EXPECT_EQ(list.size(), 1);
  delete popBack;

  popBack = list.pop_back();
  EXPECT_EQ(popBack->as_string(), "It's a Shape at x: 99, y: 99");
  EXPECT_EQ(list.size(), 0);
  delete popBack;

  EXPECT_TRUE(list.empty());

  popBack = list.pop_back();
  EXPECT_EQ(popBack, nullptr);  
  EXPECT_TRUE(list.empty());
}

TEST(CanvasListModifying, PopBack) {
  CanvasList list;

  list.push_back(new Circle(9, 9, 10));
  Shape* popBack = list.pop_back();
  EXPECT_EQ(popBack->as_string(), "It's a Circle at x: 9, y: 9, radius: 10");
  delete popBack;
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);  

  
  popBack = list.pop_back();
  EXPECT_EQ(popBack, nullptr);  
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);  

  
  list.push_back(new Circle(0, 3, 7));
  popBack = list.pop_back();
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);  
  delete popBack;
}

TEST(CanvasListModifying, remove_at_) {
  CanvasList list;

  list.push_back(new Rect(0, 0, 5, 54));
  list.push_back(new RightTriangle(0, 0, 91, 7));

  list.remove_at(0);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.front()->value->as_string(),
            "It's a Right Triangle at x: 0, y: 0 with base: 91 and height: 7");

  size_t original_size = list.size();
  list.remove_at(2);                      
  EXPECT_EQ(list.size(), original_size);  

  list.remove_at(0);          
  EXPECT_TRUE(list.empty());  
  delete list.pop_front();
}

TEST(CanvasListModifying, remove_at_cutoff) {
  CanvasList list;

  list.push_back(new Shape(76, 42));               
  list.push_back(new Rect(0, 0, 5, 54));           
  list.push_back(new RightTriangle(0, 0, 32, 4));  

  list.remove_at(1);
  EXPECT_EQ(list.size(), 2);  
  EXPECT_EQ(list.front()->value->as_string(),
            "It's a Shape at x: 76, y: 42");  

  delete list.pop_front();    
  EXPECT_EQ(list.size(), 1);  

  EXPECT_EQ(list.front()->value->as_string(),
            "It's a Right Triangle at x: 0, y: 0 with base: 32 and height: 4");

  delete list.pop_front();  
  EXPECT_TRUE(list.empty());
}

TEST(CanvasListExtras, After_every_other) {
  CanvasList list;
  list.push_back(new Shape(76, 42));
  list.push_back(new Rect(0, 0, 5, 54));
  list.push_back(new RightTriangle(0, 0, 32, 4));
  list.remove_every_other();
  EXPECT_EQ(list.size(), 2);
  list.clear();
  EXPECT_TRUE(list.empty());
}
TEST(CanvasListExtras, After_Empty) {
  CanvasList list;
  EXPECT_TRUE(list.empty());
  list.remove_every_other();
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0);
}

TEST(CanvasListExtras, InsertAfterIndex0) {
  CanvasList list;
  Shape* shape1 = new Shape(10, 20);
  Shape* shape2 = new Shape(30, 40);
  list.push_back(shape1);

  list.insert_after(0, shape2);

  EXPECT_EQ(list.size(), 2);            
  EXPECT_EQ(list.shape_at(1), shape2);  

  list.clear();
  EXPECT_TRUE(list.empty());  
}

TEST(CanvasListExtras, InsertAfterSizeUpdate) {
  CanvasList list;
  Shape* shape1 = new Shape(10, 20);
  Shape* shape2 = new Shape(30, 40);
  Shape* shape3 = new Shape(50, 60);
  list.push_back(shape1);
  list.push_back(shape2);

  list.insert_after(1, shape3);

  EXPECT_EQ(list.size(), 3);  
  EXPECT_EQ(list.shape_at(2), shape3);

  list.clear();
  EXPECT_TRUE(list.empty());
}

TEST(CanvasListExtras, RemoveEveryOther_Empty) {
  CanvasList list;
  EXPECT_TRUE(list.empty());

  list.remove_every_other();

  EXPECT_TRUE(list.empty());  
  EXPECT_EQ(list.size(), 0);  
}

TEST(CanvasListExtras, RemoveEveryOther_SingleElement) {
  CanvasList list;
  Shape* shape = new Shape(10, 20);
  list.push_back(shape);

  list.remove_every_other();

  EXPECT_EQ(list.size(), 1);  
  EXPECT_EQ(list.shape_at(0),
            shape);  

  list.clear();
  EXPECT_TRUE(list.empty());
}

TEST(CanvasListExtras, RemoveEveryOther_SizeUpdate) {
  CanvasList list;
  Shape* shape1 = new Shape(10, 20);
  Shape* shape2 = new Shape(30, 40);
  Shape* shape3 = new Shape(50, 60);
  list.push_back(shape1);
  list.push_back(shape2);
  list.push_back(shape3);

  list.remove_every_other();

  EXPECT_EQ(list.size(), 2);  
  EXPECT_EQ(list.shape_at(0), shape1);  
  EXPECT_EQ(list.shape_at(1),
            shape3);  

  list.clear();
  EXPECT_TRUE(list.empty());
}