#include "UndirectedGraphTest.h"
#include "UndirectedGraph.h"

#include <cassert>

void TestUndirectedGraph::allTests()
{
    test1();
    test2();
    test3();
}
void TestUndirectedGraph::test1()
{
    UndirectedGraph<int, int> graph;
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 5);
    graph.addEdge(0, 3, 7);
    graph.addEdge(1, 4, 8);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 5, 10);
    graph.addEdge(4, 5, 2);
    graph.addEdge(4, 6, 4);
    graph.addEdge(5, 6, 1);
    graph.addEdge(6, 7, 6);
    graph.addEdge(7, 9, 7);
    graph.addEdge(6, 9, 4);
    graph.addEdge(6, 8, 5);
    graph.addEdge(8, 9, 10);
    Path<int> testPath1 = graph.dijkstraPath(0, 5);
    assert(testPath1.getSize() == 4);
    assert(testPath1.get(0) == 0);
    assert(testPath1.get(1) == 2);
    assert(testPath1.get(2) == 4);
    assert(testPath1.get(3) == 5);
    Path<int> testPath2 = graph.dijkstraPath(3, 9);
    assert(testPath2.getSize() == 4);
    assert(testPath2.get(0) == 3);
    assert(testPath2.get(1) == 5);
    assert(testPath2.get(2) == 6);
    assert(testPath2.get(3) == 9);
    Path<int> testPath3 = graph.dijkstraPath(4, 9);
    assert(testPath3.getSize() == 4);
    assert(testPath3.get(0) == 4);
    assert(testPath3.get(1) == 5);
    assert(testPath3.get(2) == 6);
    assert(testPath3.get(3) == 9);
    Path<int> testPath4 = graph.dijkstraPath(1, 5);
    assert(testPath4.getSize() == 3);
    assert(testPath4.get(0) == 1);
    assert(testPath4.get(1) == 4);
    assert(testPath4.get(2) == 5);
    Path<int> testPath5 = graph.dijkstraPath(0, 6);
    assert(testPath5.getSize() == 5);
    assert(testPath5.get(0) == 0);
    assert(testPath5.get(1) == 2);
    assert(testPath5.get(2) == 4);
    assert(testPath5.get(3) == 5);
    assert(testPath5.get(4) == 6);
}
void TestUndirectedGraph::test2()
{
    UndirectedGraph<int, int> graph;
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 5);
    graph.addEdge(0, 3, 7);
    graph.addEdge(1, 4, 8);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 5, 10);
    graph.addEdge(4, 5, 2);
    graph.addEdge(4, 6, 4);
    graph.addEdge(5, 6, 1);
    graph.addEdge(6, 7, 6);
    graph.addEdge(7, 9, 7);
    graph.addEdge(6, 9, 4);
    graph.addEdge(6, 8, 5);
    graph.addEdge(8, 9, 10);
    Path<int> testPath1 = graph.dijkstraPathWithOneVertex(0, 8, 9);
    assert(testPath1.getSize() == 8);
    assert(testPath1.get(0) == 0);
    assert(testPath1.get(1) == 2);
    assert(testPath1.get(2) == 4);
    assert(testPath1.get(3) == 5);
    assert(testPath1.get(4) == 6);
    assert(testPath1.get(5) == 9);
    assert(testPath1.get(6) == 6);
    assert(testPath1.get(7) == 8);
    Path<int> testPath2 = graph.dijkstraPathWithOneVertex(2, 9, 1);
    assert(testPath2.getSize() == 7);
    assert(testPath2.get(0) == 2);
    assert(testPath2.get(1) == 0);
    assert(testPath2.get(2) == 1);
    assert(testPath2.get(3) == 4);
    assert(testPath2.get(4) == 5);
    assert(testPath2.get(5) == 6);
    assert(testPath2.get(6) == 9);
}
void TestUndirectedGraph::test3()
{
    UndirectedGraph<int, int> graph;
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 5);
    graph.addEdge(0, 3, 7);
    graph.addEdge(1, 4, 8);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 5, 10);
    graph.addEdge(4, 5, 2);
    graph.addEdge(4, 6, 4);
    graph.addEdge(5, 6, 1);
    graph.addEdge(6, 7, 6);
    graph.addEdge(7, 9, 7);
    graph.addEdge(6, 9, 4);
    graph.addEdge(6, 8, 5);
    graph.addEdge(8, 9, 10);
    Path<int> testPath1 = graph.dijkstraPathWithTwoVertex(0, 7, 3, 8);
    assert(testPath1.getSize() == 7);
    assert(testPath1.get(0) == 0);
    assert(testPath1.get(1) == 3);
    assert(testPath1.get(2) == 5);
    assert(testPath1.get(3) == 6);
    assert(testPath1.get(4) == 8);
    assert(testPath1.get(5) == 6);
    assert(testPath1.get(6) == 7);
    Path<int> testPath2 = graph.dijkstraPathWithTwoVertex(2, 3, 7, 8);
    assert(testPath2.getSize() == 10);
    assert(testPath2.get(0) == 2);
    assert(testPath2.get(1) == 4);
    assert(testPath2.get(2) == 5);
    assert(testPath2.get(3) == 6);
    assert(testPath2.get(4) == 8);
    assert(testPath2.get(5) == 6);
    assert(testPath2.get(6) == 7);
    assert(testPath2.get(7) == 6);
    assert(testPath2.get(8) == 5);
    assert(testPath2.get(9) == 3);
}
