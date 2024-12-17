#include "DirectedGraph.h"
#include "DirectedGraphTest.h"

#include <cassert>

void TestDirectedGraph::allTests()
{
    test1();
    test2();
    //test3();
}
void TestDirectedGraph::test1()
{
    DirectedGraph<int, int> graph;
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 3);
    graph.addEdge(3, 0, 5);
    graph.addEdge(1, 4, 2);
    graph.addEdge(2, 5, 9);
    graph.addEdge(2, 3, 6);
    graph.addEdge(3, 4, 7);
    graph.addEdge(5, 1, 5);
    graph.addEdge(5, 7, 4);
    graph.addEdge(4, 7, 9);
    graph.addEdge(4, 9, 11);
    graph.addEdge(5, 6, 8);
    graph.addEdge(8, 5, 7);
    graph.addEdge(6, 4, 13);
    graph.addEdge(6, 8, 5);
    graph.addEdge(8, 9, 2);
    graph.addEdge(7, 9, 4);
    Path<int> testPath1 = graph.dijkstraPath(1, 9);
    assert(testPath1.getSize() == 3);
    assert(testPath1.get(0) == 1);
    assert(testPath1.get(1) == 4);
    assert(testPath1.get(2) == 9);
    Path<int> testPath2 = graph.dijkstraPath(4, 8);
    assert(testPath2.getSize() == 0);
    Path<int> testPath3 = graph.dijkstraPath(0, 4);
    assert(testPath3.getSize() == 3);
    assert(testPath3.get(0) == 0);
    assert(testPath3.get(1) == 1);
    assert(testPath3.get(2) == 4);
    Path<int> testPath4 = graph.dijkstraPath(1, 4);
    assert(testPath4.getSize() == 2);
    assert(testPath4.get(0) == 1);
    assert(testPath4.get(1) == 4);
    Path<int> testPath5 = graph.dijkstraPath(2, 9);
    assert(testPath5.getSize() == 4);
    assert(testPath5.get(0) == 2);
    assert(testPath5.get(1) == 5);
    assert(testPath5.get(2) == 7);
    assert(testPath5.get(3) == 9);
}
void TestDirectedGraph::test2()
{
    DirectedGraph<int, int> graph;
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 3);
    graph.addEdge(3, 0, 5);
    graph.addEdge(1, 4, 2);
    graph.addEdge(2, 5, 9);
    graph.addEdge(2, 3, 6);
    graph.addEdge(3, 4, 7);
    graph.addEdge(5, 1, 5);
    graph.addEdge(5, 7, 4);
    graph.addEdge(4, 7, 9);
    graph.addEdge(4, 9, 11);
    graph.addEdge(5, 6, 8);
    graph.addEdge(8, 5, 7);
    graph.addEdge(6, 4, 13);
    graph.addEdge(6, 8, 5);
    graph.addEdge(8, 9, 2);
    graph.addEdge(7, 9, 4);
    Path<int> testPath1 = graph.dijkstraPathWithOneVertex(0, 7, 9);
    assert(testPath1.getSize() == 0);
    Path<int> testPath2 = graph.dijkstraPathWithOneVertex(3, 9, 4);
    assert(testPath2.getSize() == 3);
    assert(testPath2.get(0) == 3);
    assert(testPath2.get(1) == 4);
    assert(testPath2.get(2) == 9);
    Path<int> testPath3 = graph.dijkstraPathWithOneVertex(0, 9, 3);
    assert(testPath3.getSize() == 5);
    assert(testPath3.get(0) == 0);
    assert(testPath3.get(1) == 2);
    assert(testPath3.get(2) == 3);
    assert(testPath3.get(3) == 4);
    assert(testPath3.get(4) == 9);
}
//void TestDirectedGraph::test3()
//{
//    DirectedGraph<int, int> graph;
//    graph.addEdge(0, 1, 1);
//    graph.addEdge(0, 2, 3);
//    graph.addEdge(3, 0, 5);
//    graph.addEdge(1, 4, 2);
//    graph.addEdge(2, 5, 9);
//    graph.addEdge(2, 3, 6);
//    graph.addEdge(3, 4, 7);
//    graph.addEdge(5, 1, 5);
//    graph.addEdge(5, 7, 4);
//    graph.addEdge(4, 7, 9);
//    graph.addEdge(4, 9, 11);
//    graph.addEdge(5, 6, 8);
//    graph.addEdge(8, 5, 7);
//    graph.addEdge(6, 4, 13);
//    graph.addEdge(6, 8, 5);
//    graph.addEdge(8, 9, 2);
//    graph.addEdge(7, 9, 4);
//    Path<int> testPath1 = graph.dijkstraPathWithTwoVertex(0, 9, 2, 4);
//    //assert(testPath1.getSize() == 0);
//    Path<int> testPath2 = graph.dijkstraPathWithTwoVertex(2, 9, 5, 7);
//
//    for (int i = 0; i < testPath1.getSize(); i++)
//    {
//        std::cout << testPath1.get(i) << " ";
//    }
//    std::cout << std::endl;
//}