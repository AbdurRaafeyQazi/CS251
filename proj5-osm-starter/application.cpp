#include "application.h"

#include <iostream>
#include <limits>
#include <map>
#include <queue>  // priority_queue
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "dist.h"
#include "graph.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

double INF = numeric_limits<double>::max();

void buildGraph(istream& input, graph<long long, double>& g,
                vector<BuildingInfo>& buildings) {
  json j;
  input >> j;

  unordered_map<long long, Coordinates> waypCoords;

  if (j.contains("waypoints") && j["waypoints"].is_array()) {
    for (const auto& wayp : j["waypoints"]) {
      long long id = wayp["id"];
      double lat = wayp["lat"];
      double lon = wayp["lon"];
      Coordinates coords(lat, lon);
      waypCoords[id] = coords;

      g.addVertex(id);
    }
  }

  if (j.contains("footways") && j["footways"].is_array()) {
    for (const auto& footway : j["footways"]) {
      if (footway.is_array()) {
        for (size_t i = 0; i < footway.size() - 1; ++i) {
          long long id1 = footway[i];
          long long id2 = footway[i + 1];

          Coordinates coord1 = waypCoords[id1];
          Coordinates coord2 = waypCoords[id2];

          double dist = distBetween2Points(coord1, coord2);
          g.addEdge(id1, id2, dist);
          g.addEdge(id2, id1, dist);
        }
      }
    }
  }

  if (j.contains("buildings") && j["buildings"].is_array()) {
    for (const auto& building : j["buildings"]) {
      long long id = building["id"];
      double lat = building["lat"];
      double lon = building["lon"];
      string name = building["name"];
      string abbr = building["abbr"];
      Coordinates coords(lat, lon);
      buildings.emplace_back(id, coords, name, abbr);

      g.addVertex(id);
    }
  }

  for (const auto& building : buildings) {
    for (const auto& wayp : j["waypoints"]) {
      double distance = distBetween2Points(
          Coordinates(building.location.lat, building.location.lon),
          Coordinates(wayp["lat"], wayp["lon"]));
      if (distance <= 0.036) {
        g.addEdge(building.id, wayp["id"], distance);
        g.addEdge(wayp["id"], building.id, distance);
      }
    }
  }
}

BuildingInfo getBuildingInfo(const vector<BuildingInfo>& buildings,
                             const string& query) {
  for (const BuildingInfo& building : buildings) {
    if (building.abbr == query) {
      return building;
    } else if (building.name.find(query) != string::npos) {
      return building;
    }
  }
  BuildingInfo fail;
  fail.id = -1;
  return fail;
}

BuildingInfo getClosestBuilding(const vector<BuildingInfo>& buildings,
                                Coordinates c) {
  double minDestDist = INF;
  BuildingInfo ret = buildings.at(0);
  for (const BuildingInfo& building : buildings) {
    double dist = distBetween2Points(building.location, c);
    if (dist < minDestDist) {
      minDestDist = dist;
      ret = building;
    }
  }
  return ret;
}

vector<long long> dijkstra(const graph<long long, double>& G, long long start,
                           long long target,
                           const set<long long>& ignoreNodes) {
  // Comparator for priority queue to order pairs based on the second element
  // (usually distance or weight).
  // The lambda function compares the second element of two pairs (lhs and rhs),
  // which represent a long long (usually a vertex or node) and a double
  // (typically a weight or distance). The comparator ensures that pairs with
  // smaller second elements (distances/weights) are given higher priority,
  // meaning they will be processed first in the priority queue.
  auto comparator = [](const pair<long long, double>& lhs,
                       const pair<long long, double>& rhs) {
    return lhs.second > rhs.second;
  };

  priority_queue<pair<long long, double>, vector<pair<long long, double>>,
                 decltype(comparator)>
      pq(comparator);

  unordered_map<long long, double> distances;
  unordered_map<long long, long long> predecessors;

  // Set initial distances to infinity
  for (const long long& vertex : G.getVertices()) {
    distances[vertex] = INF;
  }

  distances[start] = 0;
  pq.push({start, 0});

  while (!pq.empty()) {
    auto [node, nodeDist] = pq.top();
    pq.pop();

    // Skip nodes that should be ignored
    if (ignoreNodes.count(node) && node != start && node != target) {
      continue;
    }

    // Path reconstruction if target reached
    if (node == target) {
      vector<long long> path;
      while (node != start) {
        path.push_back(node);
        node = predecessors[node];
      }
      path.push_back(start);
      reverse(path.begin(), path.end());
      return path;
    }

    // Process neighbors
    for (const long long& neighbor : G.neighbors(node)) {
      double edgeWeight;
      if (G.getWeight(node, neighbor, edgeWeight)) {
        double alternativeDist = nodeDist + edgeWeight;
        if (alternativeDist < distances[neighbor]) {
          distances[neighbor] = alternativeDist;
          predecessors[neighbor] = node;
          pq.push({neighbor, alternativeDist});
        }
      }
    }
  }

  return {};  // Return empty if no path exists
}

double pathLength(const graph<long long, double>& G,
                  const vector<long long>& path) {
  double length = 0.0;
  double weight;
  for (size_t i = 0; i + 1 < path.size(); i++) {
    bool res = G.getWeight(path.at(i), path.at(i + 1), weight);
    if (!res) {
      return -1;
    }
    length += weight;
  }
  return length;
}

void outputPath(const vector<long long>& path) {
  for (size_t i = 0; i < path.size(); i++) {
    cout << path.at(i);
    if (i != path.size() - 1) {
      cout << "->";
    }
  }
  cout << endl;
}

void application(const vector<BuildingInfo>& buildings,
                 const graph<long long, double>& G) {
  string p1building, p2building;

  set<long long> buildingNodes;
  for (const auto& building : buildings) {
    buildingNodes.insert(building.id);
  }

  cout << endl;
  cout << "Enter person 1's building (partial name or abbreviation), or #> ";
  getline(cin, p1building);

  while (p1building != "#") {
    cout << "Enter person 2's building (partial name or abbreviation)> ";
    getline(cin, p2building);

    // Look up buildings by query
    BuildingInfo p1 = getBuildingInfo(buildings, p1building);
    BuildingInfo p2 = getBuildingInfo(buildings, p2building);
    Coordinates P1Coords, P2Coords;
    string P1Name, P2Name;

    if (p1.id == -1) {
      cout << "Person 1's building not found" << endl;
    } else if (p2.id == -1) {
      cout << "Person 2's building not found" << endl;
    } else {
      cout << endl;
      cout << "Person 1's point:" << endl;
      cout << " " << p1.name << endl;
      cout << " " << p1.id << endl;
      cout << " (" << p1.location.lat << ", " << p1.location.lon << ")" << endl;
      cout << "Person 2's point:" << endl;
      cout << " " << p2.name << endl;
      cout << " " << p2.id << endl;
      cout << " (" << p2.location.lon << ", " << p2.location.lon << ")" << endl;

      Coordinates centerCoords = centerBetween2Points(p1.location, p2.location);
      BuildingInfo dest = getClosestBuilding(buildings, centerCoords);

      cout << "Destination Building:" << endl;
      cout << " " << dest.name << endl;
      cout << " " << dest.id << endl;
      cout << " (" << dest.location.lat << ", " << dest.location.lon << ")"
           << endl;

      vector<long long> P1Path = dijkstra(G, p1.id, dest.id, buildingNodes);
      vector<long long> P2Path = dijkstra(G, p2.id, dest.id, buildingNodes);

      // This should NEVER happen with how the graph is built
      if (P1Path.empty() || P2Path.empty()) {
        cout << endl;
        cout << "At least one person was unable to reach the destination "
                "building. Is an edge missing?"
             << endl;
        cout << endl;
      } else {
        cout << endl;
        cout << "Person 1's distance to dest: " << pathLength(G, P1Path);
        cout << " miles" << endl;
        cout << "Path: ";
        outputPath(P1Path);
        cout << endl;
        cout << "Person 2's distance to dest: " << pathLength(G, P2Path);
        cout << " miles" << endl;
        cout << "Path: ";
        outputPath(P2Path);
      }
    }

    //
    // another navigation?
    //
    cout << endl;
    cout << "Enter person 1's building (partial name or abbreviation), or #> ";
    getline(cin, p1building);
  }
}
