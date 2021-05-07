/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <cmath>
#include <utility>
#include <algorithm>
#include "kdtree.h"
#include "network.h"

using namespace std;

bool KDTree::smallerDimVal(double firstLat, double secondLat, double firstLong, double secondLong, int curDim) const
{ // west and south go left on tree
    if (curDim) {
      // return true if second is more west than first
      double goingeast = abs(secondLong - firstLong);
      return goingeast >= 180;
    } else {
      return (firstLat < secondLat);
    }
}

bool KDTree::shouldReplace(double targetLat, double currBestLat, double potentialLat, 
                           double targetLong, double currBestLong, double potentialLong) const
{
    double currentBestDist = ComputeDistance(targetLat, currBestLat, targetLong, currBestLong);
    double potentialDist = ComputeDistance(targetLat, potentialLat, targetLong, potentialLong);

    return (potentialDist < currentBestDist);
}

KDTree::KDTree() = default;

KDTree::KDTree(const std::vector<Airport>& newPoints)
{
  for (size_t i = 0; i < newPoints.size(); ++i) {
      list.push_back(newPoints[i]);
  }
  size = 0;
  root = buildTree(0, newPoints.size() - 1, 0);
}

KDTree::KDTreeNode* KDTree::buildTree(int left, int right, int dimension) {
  if (right < left) {
    return NULL;
  }

  int middle = (left + right) / 2;
  KDTreeNode* sroot = new KDTreeNode(select(left, right, middle, dimension));
  ++size;
  sroot->left = buildTree(left, middle - 1, (dimension + 1) % Dim);
  sroot->right = buildTree(middle + 1, right, (dimension + 1) % Dim);
  return sroot;
}

int KDTree::partition(int left, int right, int pivotIndex, int dimension) {
  Airport pivotValue = list[pivotIndex];
  std::swap(list[pivotIndex], list[right]);
  int storeIndex = left;
  for (int i = left; i < right; ++i) {
    if (smallerDimVal(list[i].getLatitude(), pivotValue.getLatitude(), list[i].getLongitude(), pivotValue.getLongitude(), dimension)) {
      std::swap(list[storeIndex], list[i]);
      ++storeIndex;
    }
  }
  std::swap(list[right], list[storeIndex]);
  return storeIndex;
}

Airport& KDTree::select(int left, int right, int k, int dimension) {
  if (left == right) {
    return list[left];
  }
  int pivotIndex = (left + right) / 2;
  int nextIndex = partition(left, right, pivotIndex, dimension);
  if (k == nextIndex) {
    return list[k];
  } else if (k < nextIndex) {
    return select(left, nextIndex - 1, k, dimension);
  } else {
    return select(nextIndex + 1, right, k, dimension);
  }
}

KDTree::KDTree(const KDTree& other) {
  list = other.list;
  size = 0;
  root = buildTree(0, list.size() - 1, 0);
}

const KDTree& KDTree::operator=(const KDTree& rhs) {
  if (this != &rhs) {
    clear(root);
    list = rhs.list;
    size = 0;
    root = buildTree(0, list.size() - 1, 0);
  }

  return *this;
}

KDTree::~KDTree() {
  clear(root);
}

void KDTree::clear(KDTreeNode* sroot) {
	if (!sroot) {
    return;
  }
  if (sroot->left) {
    clear(sroot->left);
  }
	if (sroot->right) {
    clear(sroot->right);
  }
	delete sroot;
	sroot = nullptr;
}

Airport KDTree::findNearestNeighbor(double targetLat, double targetLong) const
{
  return findNearestHelper(root, targetLat, targetLong, root->airport, 0);
}

Airport KDTree::findNearestHelper(KDTreeNode* sroot, double targetLat, double targetLong, Airport currBest, int dimension) const {
  if (!sroot->left && !sroot->right) {
    return sroot->airport;
  }

  // Find initial currBest logic
  bool searchDirection = true;
  if (smallerDimVal(targetLat, sroot->airport.getLatitude(), targetLong, sroot->airport.getLongitude(), dimension)) {
    if (sroot->left) {
      currBest = findNearestHelper(sroot->left, targetLat, targetLong, currBest, (dimension + 1) % Dim);
    }
  } else {
    if (sroot->right) {
      currBest = findNearestHelper(sroot->right, targetLat, targetLong, currBest, (dimension + 1) % Dim);
    }
    searchDirection = false;
  }

  // Backtraversal Logic based on pseudo-code
  if (shouldReplace(targetLat, currBest.getLatitude(), sroot->airport.getLatitude(), targetLong, currBest.getLongitude(), sroot->airport.getLongitude())) {
    currBest = sroot->airport;
  }

  double radius = ComputeDistance(targetLat, currBest.getLatitude(), targetLong, currBest.getLongitude());

  double splitDist = 0.0;
  if (dimension) {
    splitDist = ComputeDistance(currBest.getLatitude(), currBest.getLatitude(), targetLong, currBest.getLongitude());
  } else {
    splitDist = ComputeDistance(targetLat, currBest.getLatitude(), currBest.getLongitude(), currBest.getLongitude());
  }
  
  if (radius >= splitDist) {
    if (searchDirection) {
      if (sroot->right) {
        Airport newPoint = findNearestHelper(sroot->right, targetLat, targetLong, currBest, (dimension + 1) % Dim);
        if (shouldReplace(targetLat, currBest.getLatitude(), newPoint.getLatitude(), targetLong, currBest.getLongitude(), newPoint.getLongitude())) {
          currBest = newPoint;
        }
      }
    } else {
      if (sroot->left) {
        Airport newPoint = findNearestHelper(sroot->left, targetLat, targetLong, currBest,(dimension + 1) % Dim);
        if (shouldReplace(targetLat, currBest.getLatitude(), newPoint.getLatitude(), targetLong, currBest.getLongitude(), newPoint.getLongitude())) {
          currBest = newPoint;
        }
      }
    }
  }

  return currBest;
}

double KDTree::ComputeDistance(double lat1, double lat2, double long1, double long2) const {
  double to_radians = M_PI / 180.0;
  double haversine = 0.5 - cos((lat2 - lat1) * to_radians) / 2
      + cos(lat1 * to_radians) * cos(lat2 * to_radians) *
          (1 - cos((long2 - long1) * to_radians)) / 2;
  return 2 * Network::R * asin(sqrt(haversine));
}