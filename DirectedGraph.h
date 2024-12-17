#pragma once
#include "Dictionary.h"
#include "Path.h"
#include <limits>
#include <iostream>

const int INF = INT_MAX;

template <typename T, typename U>
class DirectedGraph
{
private:
    Dictionary<T, U> edges;
public:
    void addEdge(const T& from, const T& to, const U& weight)
    {
        KeyValue<T, U> keyValue{};
        KeyForDirectedGraph<T> key;
        key.setFrom(from);
        key.setTo(to);
        keyValue.setKey(key);
        keyValue.setValue(weight);
        edges.add(keyValue);
    }
    size_t getSize() const {
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
            distance.set(i, INF);
        }
        int startIndex = -1;
        for (int i = 0; i < edges.getSize(); i++)
        {
            if (edges.get(i).getKeyForDirectedGraph().getFrom() == startVertex)
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
                if (edges.get(i).getKeyForDirectedGraph().getFrom() == edges.get(currentVertexIndex).getKeyForDirectedGraph().getTo())
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
            if (edges.get(i).getKeyForDirectedGraph().getFrom() == endVertex)
            {
                return distance[i];
            }
        }
        return -1;
    }
    Path<T> dijkstraPath(int startVertex, int endVertex)
    {
        DynamicArray<U> dist(edges.getSize());
        DynamicArray<bool> visited(edges.getSize());
        DynamicArray<T> prev(edges.getSize());
        for (int i = 0; i < edges.getSize(); i++)
        {
            dist[i] = INF;
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
            if (dist[u] == INF || u == endVertex)
            {
                break;
            }
            visited[u] = true;
            for (int j = 0; j < edges.getSize(); j++)
            {
                int weight = edges.get(j).getValue();
                if (u == edges.get(j).getKeyForDirectedGraph().getFrom() && dist[u] + weight < dist[edges.get(j).getKeyForDirectedGraph().getTo()])
                {
                    dist[edges.get(j).getKeyForDirectedGraph().getTo()] = dist[u] + weight;
                    prev[edges.get(j).getKeyForDirectedGraph().getTo()] = u; // Store the previous vertex
                }
            }
        }
        if (dist[endVertex] == INF)
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
        if (path1.getSize() == 0 || path2.getSize() == 0)
        {
            return {};
        }
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
};



