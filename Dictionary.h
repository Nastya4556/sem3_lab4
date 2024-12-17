#pragma once
#include "DynamicArray.h"

template<typename U>
class KeyForUndirectedGraph
{
private:
	U Vertex1;
	U Vertex2;
public:
	KeyForUndirectedGraph() {}
	KeyForUndirectedGraph(const U& v1, const U& v2)
	{
		Vertex1 = v1;
		Vertex2 = v2;
	}
	const U getVertex1() const
	{
		return Vertex1;
	}
	const U getVertex2() const
	{
		return Vertex2;
	}
	void setVertex1(const U& otherVertex1)
	{
		Vertex1 = otherVertex1;
	}
	void setVertex2(const U& otherVertex2)
	{
		Vertex2 = otherVertex2;
	}
	bool operator == (const KeyForUndirectedGraph<U>& other) const
	{
		return (Vertex1 == other.Vertex1 && Vertex2 == other.Vertex2) || (Vertex1 == other.Vertex2 && Vertex2 == other.Vertex1);
	}
};

template <typename U>
class KeyForDirectedGraph
{
private:
	U From;
	U To;
public:
	KeyForDirectedGraph() {}
	KeyForDirectedGraph(const U& from, const U& to)
	{
		From = from;
		To = to;
	}
	const U getFrom() const
	{
		return From;
	}
	const U getTo() const
	{
		return To;
	}
	void setFrom(const U& otherFrom)
	{
		From = otherFrom;
	}
	void setTo(const U& otherTo)
	{
		To = otherTo;
	}
	bool operator == (const KeyForDirectedGraph<U>& other) const
	{
		return From == other.From && To == other.To;
	}
};
template<typename T, typename U>
class KeyValue
{
public:
	enum class KeyType { Undirected, Directed };
private:
	KeyType keyType;
	union {
		KeyForUndirectedGraph<U> undirectedKey;
		KeyForDirectedGraph<U> directedKey;
	};
	T value;
public:
	KeyValue() {}
	KeyValue(const KeyForUndirectedGraph<U>& key, const T& value)
	{
		keyType = KeyType::Undirected;
		undirectedKey = key;
		value = value;
	}
	KeyValue(const KeyForDirectedGraph<U>& key, const T& value)
	{
		keyType = KeyType::Directed;
		directedKey = key;
		value = value;
	}
	KeyForUndirectedGraph<U> getKeyForUndirectedGraph()
	{
		return undirectedKey;
	}
	KeyForDirectedGraph<U> getKeyForDirectedGraph()
	{
		return directedKey;
	}
	const T& getValue() const {
		return value;
	}
	void setKey(const KeyForUndirectedGraph<U>& newKey) {
		undirectedKey = newKey;
	}
	void setKey(const KeyForDirectedGraph<U>& newKey) {
		directedKey = newKey;
	}
	void setValue(const T& newValue) {
		value = newValue;
	}
};

template<typename T, typename U>
class Dictionary
{
private:
	DynamicArray<KeyValue<T, U>> dict;
public:
	Dictionary() {}
	void add(const KeyValue<T, U>& keyValue)
	{
		dict.append(keyValue);
	}
	KeyValue<T, U> get(int index)
	{
		return dict.get(index);
	}
	size_t getSize() const
	{
		return dict.getSize();
	}
	T getFrom(size_t index) const {
		return dict.get(index).getKey().getFrom();
	}

	T getTo(size_t index) const {
		return dict.get(index).getKey().getTo();
	}

	U getWeight(size_t index) const {
		return dict.get(index).getValue();
	}

	void setTo(size_t index, const T& newTo) {
		KeyValue<T, U>& kv = dict.get(index);
		KeyForDirectedGraph<U> key = kv.getKey();
		key.setTo(newTo);
	}

	void setFrom(size_t index, const T& newFrom) {
		KeyValue<T, U>& kv = dict.get(index);
		KeyForDirectedGraph<U> key = kv.getKey();
		key.setFrom(newFrom);
	}

	void setWeight(size_t index, const U& newWeight) {
		KeyValue<T, U>& kv = dict.get(index);
		kv.setValue(newWeight);
	}
};

