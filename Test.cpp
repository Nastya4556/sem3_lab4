#include "Test.h"
#include "UndirectedGraphTest.h"
#include "DirectedGraphTest.h"

void Test::allTests()
{
    testUndirectedGraph();
    testDirectedGraph();
}
void Test::testUndirectedGraph()
{
    TestUndirectedGraph testUndirectedGraph;
    testUndirectedGraph.allTests();
}
void Test::testDirectedGraph()
{
    TestDirectedGraph testDirectedGraph;
    testDirectedGraph.allTests();
}