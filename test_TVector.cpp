#include <gtest/gtest.h>

#include "../lib_TVector/TVector.h"

TEST(TVectorTest, DefaultConstructor) {
    TVector<int> empty1, fake_empty(0);
    EXPECT_EQ(empty1 == fake_empty, true);
}

TEST(TVectorTest, DefaultConstructorParameters) {
    TVector<int> empty1;
    EXPECT_EQ(empty1.size(), 0);
    EXPECT_EQ(empty1.capacity(), CAPACITY);
}

TEST(TVectorTest, SizeConstructor) {
    TVector<int> vec1(10), vec2(10);
    EXPECT_EQ(vec1 == vec2, true);
}

TEST(TVectorTest, SizeConstructorParameters) {
    TVector<int> vec1(10);
    vec1.push_front(11);

    EXPECT_EQ(vec1.size(), 11);
    EXPECT_EQ(vec1.capacity(), 25);
    EXPECT_EQ(vec1[0], 11);
}

TEST(TVectorTest, SizeDataConstructor) {
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    TVector<int> vec1(10, arr);
    bool actual_result;
    if (vec1.size() == 10 && vec1.capacity() == 25) {
        actual_result = true;
        for (int i = 0; i < vec1.size(); i++) {
            if (vec1[i] != i + 1) actual_result = false;
        }
    }
    else {
        actual_result = false;
    }
    EXPECT_EQ(actual_result, true);
}

TEST(TVectorTest, InitConstructor) {
    int arr[2] = { 1, 2 };
    TVector<int> vec1(2, { 1, 2, 3, 4, 5 }), vec2(2, arr);
    EXPECT_EQ(vec1 == vec2, true);
}

TEST(TVectorTest, CopyConstructor) {
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    TVector<int> vec1(10, arr);
    vec1.pop_back();
    vec1.pop_front();
    TVector<int> vec2(vec1);
    EXPECT_EQ(vec1 == vec2, true);
}

TEST(TVectorTest, IsEmpty) {
    TVector<int> empty1, fake_empty(2);
    fake_empty.pop_front();
    fake_empty.pop_front();
    EXPECT_EQ(empty1.is_empty(), true);
    EXPECT_EQ(fake_empty.is_empty(), true);
}

TEST(TVectorTest, AtFirstTest) {
    TVector<int> vec1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    TVector<int> vec2({ 3, 4, 6, 7, 8 });
    vec1.pop_front();
    vec1.pop_front();
    vec1.pop_back();
    vec1.pop_back();
    vec1.erase(2);
    bool actual_result = (vec1 == vec2);
    EXPECT_EQ(vec1 == vec2, true);
}

TEST(TVectorTest, AtEmptySecondTest) {
    TVector<double> empty1;
    EXPECT_THROW(empty1.at(0), std::out_of_range);
}

TEST(TVectorTest, AtAssignThirdTest) {
    bool expected_result = true;
    TVector<int> vec1({ 1, 2, 3 });
    vec1[1] = -4;
    EXPECT_EQ(vec1[1], -4);
}

TEST(TVectorTest, PushFront) {
    TVector<int> vec1({ 1, 2, 3, 4, 5 });
    TVector<int> vec2({ -5, -4, -3, -2, -1, 1, 2, 3, 4, 5 });
    vec1.push_front(-1);
    vec1.push_front(-2);
    vec1.push_front(-3);
    vec1.push_front(-4);
    vec1.push_front(-5);
    EXPECT_EQ(vec1 == vec2, true);
}

TEST(TVectorTest, PushFrontEmpty) {
    TVector<int> empty1;
    empty1.push_front(5);
    empty1.push_front(5);
    EXPECT_EQ(empty1[0], 5);
    EXPECT_EQ(empty1[1], 5);
}

TEST(TVectorTest, PushFrontCapacityOverflow) {
    TVector<int> empty1;
    for (int i = 0; i < 15; i++) {
        empty1.push_front(5);
    }
    EXPECT_EQ(empty1.capacity(), 30);
}

TEST(TVectorTest, PushFrontToDeleted) {
    TVector<int> vec1({ 1, 2, 3, 4 }), vec2({ 5, 5, 3, 4 });
    vec1.pop_front();
    vec1.pop_front();
    vec1.push_front(5);
    vec1.push_front(5);
    EXPECT_EQ(vec1 == vec2, true);
}

TEST(TVectorTest, PushBack) {
    TVector<int> vec1({ -5, -4, -3, -2, -1 });
    TVector<int> vec2({ -5, -4, -3, -2, -1, 1, 2, 3, 4, 5 });
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    vec1.push_back(4);
    vec1.push_back(5);
    EXPECT_EQ(vec1 == vec2, true);
}

TEST(TVectorTest, PushBackEmpty) {
    TVector<int> empty1;
    empty1.push_back(5);
    empty1.push_back(5);
    EXPECT_EQ(empty1[0], 5);
    EXPECT_EQ(empty1[1], 5);
}

TEST(TVectorTest, PushBackCapacityOverflow) {
    TVector<int> empty1;
    for (int i = 0; i < 15; i++) {
        empty1.push_back(5);
    }
    EXPECT_EQ(empty1.capacity(), 30);
}

TEST(TVectorTest, InsertToInvalidIndex) {
    TVector<double> empty1;
    EXPECT_THROW(empty1.insert(2, 3), std::out_of_range);
}

TEST(TVectorTest, Insert) {
    TVector<int> vec1({ 1, 2, 3, 4 }), vec2({ 1, 5, 2, 3, 5, 4 });
    vec1.insert(1, 5);
    vec1.insert(4, 5);
    EXPECT_EQ(vec1 == vec2, true);
}

TEST(TVectorTest, InsertToEmpty) {
    TVector<int> empty1;
    empty1.insert(0, 5);
    empty1.insert(0, -1);
    EXPECT_EQ(empty1[0], -1);
    EXPECT_EQ(empty1[1], 5);
}

TEST(TVectorTest, InsertCapacityOverflow) {
    TVector<int> vec1({ 1, 0 });
    for (int i = 0; i < 15; i++) {
        vec1.insert(1, 5);
    }
    EXPECT_EQ(vec1.capacity(), 32);
}

TEST(TVectorTest, PopFront) {
    TVector<int> vec1({ 1, 2, 3, 4, 5 }), vec2({ 3, 4, 5 });
    vec1.pop_front();
    vec1.pop_front();
    EXPECT_EQ(vec1 == vec2, true);
}

TEST(TVectorTest, PopFrontToEmpty) {
    TVector<int> empty1;
    EXPECT_THROW(empty1.pop_front(), std::logic_error);
}

TEST(TVectorTest, PopBack) {
    TVector<int> vec1({ 1, 2, 3, 4, 5 }), vec2({ 1, 2, 3 });
    vec1.pop_back();
    vec1.pop_back();
    EXPECT_EQ(vec1 == vec2, true);
}

TEST(TVectorTest, PopBackToEmpty) {
    TVector<int> empty1;
    EXPECT_THROW(empty1.pop_back(), std::logic_error);
}

TEST(TVectorTest, EraseToInvalidIndex) {
    TVector<int> vec1({1, 2});
    EXPECT_THROW(vec1.erase(3), std::out_of_range);
}

TEST(TVectorTest, Erase) {
    TVector<int> vec1({ 1, 2, 3, 4, 5 }), vec2({ 1, 4, 5 });
    vec1.erase(1);
    vec1.erase(1);
    EXPECT_EQ(vec1 == vec2, true);
}

TEST(TVectorTest, EraseToEmpty) {
    TVector<int> empty1;
    EXPECT_THROW(empty1.erase(0), std::logic_error);
}

TEST(TVectorTest, Clear) {
    TVector<int> vec1({ 1, 2, 3, 4, 5 }), empty1;
    vec1.clear();
    EXPECT_EQ(vec1 == empty1, true);
}

TEST(TVectorTest, ShrinkToFit) {
    TVector<int> vec1(34);
    for (int i = 0; i < 3; i++) {
        vec1.erase(1);
    }
    vec1.erase(vec1.size() - 2);
    vec1.shrink_to_fit();
    EXPECT_EQ(vec1.size(), vec1.capacity());
}

TEST(TVectorTest, Reserve) {
    TVector<int> vec1({ 1, 2, 3, 4, 5 });
    vec1.reserve(30);
    bool actual_result = (vec1.size() == 5 && vec1.capacity() == 30);
    EXPECT_EQ(vec1.size(), 5);
    EXPECT_EQ(vec1.capacity(), 30);
}

TEST(TVectorTest, ReserveLessThenSize) {
    TVector<int> vec1({ 1, 2, 3, 4, 5 });
    vec1.reserve(4);
    bool actual_result = (vec1.size() == 5 && vec1.capacity() == 20);
    EXPECT_EQ(vec1.size(), 5);
    EXPECT_EQ(vec1.capacity(), 20);
}

TEST(TVectorTest, ResizeShrink) {
    bool expected_result = true;
    TVector<int> vec1({ 1, 2, 3, 4, 5 });
    vec1.resize(2);
    EXPECT_EQ(vec1.size(), 2);
}

TEST(TVectorTest, ResizeEnlarge) {
    TVector<int> vec1({ 1, 2, 3, 4, -11 });
    vec1.resize(8);
    EXPECT_EQ(vec1.size(), 8);
    EXPECT_EQ(vec1[4], -11);
}

TEST(TVectorTest, Emplace) {
    TVector<int> vec1({ 1, 2, 3, 4, 5 }), vec2({ 2, 2, 2, 2, 2 });
    for (int i = 0; i < vec1.size(); i++) vec1.emplace(i, 2);
    EXPECT_EQ(vec1 == vec2, true);
}

TEST(TVectorTest, AssignEmpty) {
    TVector<int> vec1({ 1, 2, 3, 4 }), empty1;
    vec1 = empty1;
    EXPECT_EQ(vec1 == empty1, true);
}

TEST(TVectorTest, Assign) {
    TVector<int> vec1({ 1, 2, 3, 4 }), vec2({ 37, 55, -19, 0, 0, 12 });
    vec1 = vec2;
    EXPECT_EQ(vec1 == vec2, true);
}