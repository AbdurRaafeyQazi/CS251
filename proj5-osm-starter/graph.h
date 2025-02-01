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
    auto result = adjLst.insert({v, {}});  // List style
    if (!result.second) {
      return false;
    }

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
    set<VertexT> result;
    auto it = adjLst.find(v);

    if (it == adjLst.end()) {
        return result;  // Return empty set if vertex is not found
    }

    for (auto edge = it->second.begin(); edge != it->second.end(); ++edge) {
        result.insert(edge->first);
    }

    return result;
  }

  vector<VertexT> getVertices() const {
    vector<VertexT> vertexList;
    
    for (typename unordered_map<VertexT, unordered_map<VertexT, WeightT>>::const_iterator it = adjLst.begin(); it != adjLst.end(); ++it) {
        vertexList.push_back(it->first);
    }

    return vertexList;
  }

  size_t numVertices() const {
    return vertexCount;
  }

  size_t numEdges() const {
    return edgeCount;
  }
};
