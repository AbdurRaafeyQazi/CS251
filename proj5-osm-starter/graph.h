#pragma once

#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename VertexT, typename WeightT>
class graph {
 private:
  unordered_map<VertexT, unordered_map<VertexT, WeightT>> adjLst;

  size_t vertexCount = 0;
  size_t edgeCount = 0;

 public:
  graph() = default;

  bool addVertex(VertexT v) {
    if (adjLst.find(v) != adjLst.end()) return false;

    adjLst[v] = {};
    ++vertexCount;

    return true;
  }

  bool addEdge(VertexT from, VertexT to, WeightT weight) {
    if (adjLst.find(from) == adjLst.end() || adjLst.find(to) == adjLst.end()) {
      return false;
    }
    if (adjLst[from].find(to) == adjLst[from].end()) {
      ++edgeCount;
    }

    adjLst[from][to] = weight;
    return true;
  }

  bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
    auto it = adjLst.find(from);

    if (it == adjLst.end() || it->second.find(to) == it->second.end()) {
      return false;
    }

    weight = it->second.at(to);
    return true;
  }

  set<VertexT> neighbors(VertexT v) const {
    set<VertexT> S;
    auto it = adjLst.find(v);

    if (it == adjLst.end()) {
      return S;
    }

    for (const auto& [neighbor, _] : it->second) {
      S.insert(neighbor);
    }

    return S;
  }

  vector<VertexT> getVertices() const {
    vector<VertexT> vertices;

    for (const auto& [vertex, _] : adjLst) {
      vertices.push_back(vertex);
    }

    return vertices;
  }

  size_t numVertices() const {
    return vertexCount;
  }

  size_t numEdges() const {
    return edgeCount;
  }
};
