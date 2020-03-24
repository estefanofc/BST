/**
 * Testing BST - Binary Search Tree functions
 *
 * This file has series of tests for BST
 * Each test is independent and uses assert statements
 * Test functions are of the form
 *
 *      test_netidXX()
 *
 * where netid is UW netid and XX is the test number starting from 01
 *
 * Test functions can only use the public functions from BST
 * testBSTAll() is called from main in main.cpp
 * testBSTAll calls all other functions
 * @author Multiple
 * @date ongoing
 */

#include "bst.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

/**
 * Trying to avoid global variables,
 * by creating a singleton class with our visitor functions
 * stringstream SS contains the output from visitor
 */
class TreeVisitor {
public:
    // never create an instance of TreeVisitor object
    // we'll just use the static functions
    TreeVisitor() = delete;

    // insert output to SS rather than cout, so we can test it
    static stringstream SS;

    static string getSS() {
        return SS.str();
    }

    static void resetSS() {
        SS.str(string());
    }

    // instead of cout, insert item into a string stream
    static void visitor(const string &Item) {
        SS << Item;
    }

    // instead of cout, insert item into a string stream
    static void visitor(const int &Item) {
        SS << Item;
    }
};

// initialize the static variable
//  warning: initialization of 'SS' with static storage duration
//  may throw an exception that cannot be caught [cert-err58-cpp]
//  Not sure how to do it without making code harder to read
//  NOLINTNEXTLINE
stringstream TreeVisitor::SS;

/**
 * Test functions by Yusuf Pisan
 */

// Testing ==
void testPisan01() {
    cout << "Starting testPisan01" << endl;
    cout << "* Testing == and !=" << endl;
    BST<string> B1;
    BST<string> B2;
    BST<string> B3;
    // == and != for empty trees
    assert(B1 == B2 && (!(B1 != B2)));
    B1.add("c");
    B2.add("c");
    B3.add("b");
    // == and !- for 1-Node trees B1, B2, B3
    assert(B1 == B2 && (!(B1 != B2)));
    assert(B1 != B3 && (!(B1 == B3)));
    cout << "Ending testPisan01" << endl;
}

// Testing == in detail
void testPisan02() {
    cout << "Starting testPisan02" << endl;
    cout << "* Testing == and != with more detail" << endl;
    BST<string> B1;
    BST<string> B2;
    BST<string> B3;
    for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
        B1.add(S);

    for (auto &S : vector<string>{"c", "f", "a", "g", "x"})
        B2.add(S);

    B3.add("b");

    // == for 5-Node trees B1, B2
    assert(B1 == B2 && (!(B1 != B2)));

    BST<string> B4(B3);
    // copy constructor for 1-Node trees B3, B4
    assert(B3 == B4 && (!(B3 != B4)));

    BST<string> B5(B1);
    // copy constructor for 5-Node trees B1, B5
    assert(B1 == B5 && (!(B5 != B1)));

    BST<string> B7("b");
    // 1-param constructor for 1-Node trees B3, B7
    assert(B3 == B7 && (!(B3 != B7)));

    cout << "Ending testPisan02" << endl;
}

// Testing traversal
void testPisan03() {
    cout << "Starting testPisan03" << endl;
    cout << "* Testing traversal" << endl;
    BST<string> B1;
    BST<string> B2;
    BST<string> B3;
    for (auto &S : vector<string>{"c", "a", "f", "g", "x"})
        B1.add(S);

    for (auto &S : vector<string>{"c", "f", "a", "g", "x"})
        B2.add(S);

    B3.add("b");

    TreeVisitor::resetSS();
    B1.inOrderTraverse(TreeVisitor::visitor);
    string Result = "acfgx";
    assert(TreeVisitor::getSS() == Result);

    TreeVisitor::resetSS();
    B1.preOrderTraverse(TreeVisitor::visitor);
    Result = "cafgx";
    assert(TreeVisitor::getSS() == Result);

    TreeVisitor::resetSS();
    B1.postOrderTraverse(TreeVisitor::visitor);
    Result = "axgfc";
    assert(TreeVisitor::getSS() == Result);

    cout << "Visual check B1:" << endl;
    cout << B1 << endl;
    cout << "Ending testPisan03" << endl;
}

//testing height method
void addedTest1() {
    cout << "----------TEST 1-----------" << endl;
    BST<int> B1(1);
    for (int I = 2; I < 6; ++I) {
        B1.add(I);
    }
    assert(B1.getHeight() == 5);
}

//testing remove and rebalance methods
void addedTest2() {
    cout << "----------TEST 2-----------" << endl;
    BST<int> B1(60);
    B1.add(70);
    B1.add(20);
    B1.add(10);
    B1.add(40);
    B1.add(30);
    B1.add(50);
    cout << "Original Tree" << endl;
    cout << B1 << endl;
    assert(B1.getHeight() == 4);
    //removing leaf nodes
    B1.remove(50);
    B1.remove(30);
    cout << "Tree after removing elements: 50, 30" << endl;
    cout << B1 << endl;
    B1.add(6);
    //removing node with one child
    B1.remove(10);
    cout << "Tree after removing elements: 6" << endl;
    cout << B1 << endl;
    //removing node with two children
    B1.remove(60);
    cout << "Tree after removing elements: 60" << endl;
    cout << B1 << endl;
    assert(B1.getHeight() == 3);
    assert(B1.numberOfNodes() == 4);
    //removing non existent element
    assert(!B1.remove(100));
    //rebalancing node
    B1.rebalance();
    cout << "Rebalanced Tree" << endl;
    cout << B1 << endl;
    assert(B1.getHeight() == 3);
}

//testing constructor from array
void addedTest3() {
    cout << "----------TEST 3-----------" << endl;
    int Arr[8]{11, 32, 54, 63, 73, 82, 120, 131};
    BST<int> B1(Arr, 8);
    cout << B1 << endl;
    assert(B1.contains(11));
    assert(!B1.contains(2));
    BST<double> B2;
    assert(B2.isEmpty());
}

/**
 * Test functions by Sample Sample
 */

// Testing samplefunctionality
void testSample01() {
    cout << "Starting testSample01" << endl;
    // assert(true);
    cout << "Ending testSample01" << endl;
}

// Calling all test functions
void testBSTAll() {
    testPisan01();
    testPisan02();
    testPisan03();
    testSample01();
    //
    addedTest1();
    addedTest2();
    addedTest3();
}