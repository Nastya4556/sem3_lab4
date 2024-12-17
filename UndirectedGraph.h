#pragma once
#include "Dictionary.h"
#include "Path.h"
#include <limits>
#include <iostream>

const int INF1 = INT_MAX;


template <typename T, typename U>
class UndirectedGraph
{
private:
    Dictionary<T, U> edges;
public:
    void addEdge(const T& vertex1, const T& vertex2, const U& weight)
    {
        KeyValue<T, U> keyValue1{};
        KeyForUndirectedGraph<T> key1;
        key1.setVertex1(vertex1);
        key1.setVertex2(vertex2);
        keyValue1.setKey(key1);
        keyValue1.setValue(weight);
        edges.add(keyValue1);

        KeyValue<T, U> keyValue2{};
        KeyForUndirectedGraph<T> key2;
        key2.setVertex1(vertex2);
        key2.setVertex2(vertex1);
        keyValue2.setKey(key2);
        keyValue2.setValue(weight);
        edges.add(keyValue2);
    }
    size_t getSize()
    {
        return edges.getSize();
    }
    KeyValue<T, U> get(int index)
    {
        return edges.get(index);
    }
    U shortestPathLength(const T& startVertex, const T& endVertex)
    {
        DynamicArray<bool> visited(edges.getSize());
        DynamicArray<U> distance(edges.getSize());
        for (int i = 0; i < edges.getSize(); i++)
        {
            visited.set(i, false);
            distance.set(i, INF1);
        }
        int startIndex = -1;
        for (int i = 0; i < edges.getSize(); i++)
        {
            if (edges.get(i).getKeyForUndirectedGraph().getVertex1() == startVertex)
            {
                startIndex = i;
                distance[i] = 0;
                visited[i] = true;
                break;
            }
        }
        while (true)
        {
            int currentVertexIndex = -1;
            for (int i = 0; i < edges.getSize(); i++)
            {
                if (visited[i])
                {
                    currentVertexIndex = i;
                    break;
                }
            }
            if (currentVertexIndex == -1)
            {
                break;
            }
            visited[currentVertexIndex] = false;

            for (int i = 0; i < edges.getSize(); i++)
            {
                if (edges.get(i).getKeyForUndirectedGraph().getVertex1() == edges.get(currentVertexIndex).getKeyForUndirectedGraph().getVertex2())
                {
                    if (distance[i] > distance[currentVertexIndex] + 1)
                    {
                        distance[i] = distance[currentVertexIndex] + 1;
                        visited[i] = true;
                    }
                }
            }
        }
        for (int i = 0; i < edges.getSize(); i++)
        {
            if (edges.get(i).getKeyForUndirectedGraph().getVertex1() == endVertex)
            {
                return distance[i];
            }
        }
        return -1;
    }

    Path<T> dijkstraPath(T startVertex, T endVertex)
    {
        DynamicArray<U> dist(edges.getSize());
        DynamicArray<bool> visited(edges.getSize());
        DynamicArray<T> prev(edges.getSize());
        for (int i = 0; i < edges.getSize(); i++)
        {
            dist[i] = INF1;
            visited[i] = false;
            prev[i] = -1;
        }
        dist[startVertex] = 0;
        for (int i = 0; i < edges.getSize(); i++)
        {
            int u = -1;
            for (int j = 0; j < edges.getSize(); j++)
            {
                if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                {
                    u = j;
                }
            }
            if (dist[u] == INF1 || u == endVertex)
            {
                break;
            }
            visited[u] = true;
            for (int j = 0; j < edges.getSize(); j++)
            {
                int weight = edges.get(j).getValue();
                if (u == edges.get(j).getKeyForUndirectedGraph().getVertex1() && dist[u] + weight < dist[edges.get(j).getKeyForUndirectedGraph().getVertex2()])
                {
                    dist[edges.get(j).getKeyForUndirectedGraph().getVertex2()] = dist[u] + weight;
                    prev[edges.get(j).getKeyForUndirectedGraph().getVertex2()] = u;
                }
            }
        }
        if (dist[endVertex] == INF1)
        {
            return {};
        }
        Path<T> path;
        for (int u = endVertex; u != -1; u = prev[u])
        {
            path.append(u);
        }
        return path;
    }
    Path<T> dijkstraPathWithOneVertex(T startVertex, T endVertex, T intermediateVertex)
    {
        Path<T> path1 = dijkstraPath(startVertex, intermediateVertex);
        Path<T> path2 = dijkstraPath(intermediateVertex, endVertex);
        Path<T> result;
        for (int i = 0; i < path1.getSize(); i++)
        {
            result.appendWithoutInvert(path1.get(i));
        }
        for (int i = 1; i < path2.getSize(); i++)
        {
            result.appendWithoutInvert(path2.get(i));
        }
        return result;
    }
    Path<T> dijkstraPathWithTwoVertex(T startVertex, T endVertex, T intermediateVertex1, T intermediateVertex2)
    {
        T path1 = shortestPathLength(startVertex, intermediateVertex1);
        T path2 = shortestPathLength(intermediateVertex1, intermediateVertex2);
        T path3 = shortestPathLength(intermediateVertex2, endVertex);
        T result1 = path1 + path2 + path3;
        T path4 = shortestPathLength(startVertex, intermediateVertex2);
        T path5 = shortestPathLength(intermediateVertex2, intermediateVertex1);
        T path6 = shortestPathLength(intermediateVertex1, endVertex);
        T result2 = path4 + path5 + path6;
        Path<T> resultPath;
        if (result1 < result2)
        {
            Path<T> p1 = dijkstraPath(startVertex, intermediateVertex1);
            Path<T> p2 = dijkstraPath(intermediateVertex1, intermediateVertex2);
            Path<T> p3 = dijkstraPath(intermediateVertex2, endVertex);
            for (int i = 0; i < p1.getSize(); i++)
            {
                resultPath.appendWithoutInvert(p1.get(i));
            }
            for (int i = 1; i < p2.getSize(); i++)
            {
                resultPath.appendWithoutInvert(p2.get(i));
            }
            for (int i = 1; i < p3.getSize(); i++)
            {
                resultPath.appendWithoutInvert(p3.get(i));
            }
        }
        else
        {
            Path<T> p1 = dijkstraPath(startVertex, intermediateVertex2);
            Path<T> p2 = dijkstraPath(intermediateVertex2, intermediateVertex1);
            Path<T> p3 = dijkstraPath(intermediateVertex1, endVertex);
            for (int i = 0; i < p1.getSize(); i++)
            {
                resultPath.appendWithoutInvert(p1.get(i));
            }
            for (int i = 1; i < p2.getSize(); i++)
            {
                resultPath.appendWithoutInvert(p2.get(i));
            }
            for (int i = 1; i < p3.getSize(); i++)
            {
                resultPath.appendWithoutInvert(p3.get(i));
            }
        }
        return resultPath;
    }
};

