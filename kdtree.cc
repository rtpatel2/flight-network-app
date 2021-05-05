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

bool KDTree::smallerDimVal(const Airport& first,
                                const Airport& second, int curDim) const
{
    if (curDim) {
      return (first.getLongitude() < second.getLongitude());
    } else {
      return (first.getLatitude() < second.getLatitude());
    }
}

bool KDTree::shouldReplace(const Airport& target,
                                const Airport& currentBest,
                                const Airport& potential) const
{
    double currentBestDist = ComputeDistance(target.getLatitude(), currentBest.getLatitude(), target.getLongitude(), currentBest.getLongitude());
    double potentialDist = ComputeDistance(target.getLatitude(), potential.getLatitude(), target.getLongitude(), currentBest.getLongitude());

    return (potentialDist < currentBestDist);
}

KDTree::KDTree(const vector<Airport>& newPoints)
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

void KDTree::swap(int one, int two) {
  Airport tmp = list[one];
  list[one] = list[two];
  list[two] = tmp;
}

int KDTree::partition(int left, int right, int pivotIndex, int dimension) {
  Airport pivotValue = list[pivotIndex];
  swap(pivotIndex, right);
  int storeIndex = left;
  for (int i = left; i < right; ++i) {
    if (smallerDimVal(list[i], pivotValue, dimension)) {
      swap(storeIndex, i);
      ++storeIndex;
    }
  }
  swap(right, storeIndex);
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
    delete this;
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

Airport KDTree::findNearestNeighbor(const Airport& query) const
{
  return findNearestHelper(root, query, root->airport, 0);
}

Airport KDTree::findNearestHelper(KDTreeNode* sroot, const Airport& target, Airport currBest, int dimension) const {
  if (!sroot->left && !sroot->right) {
    return sroot->airport;
  }

  // Find initial currBest logic
  bool searchDirection = true;
  if (smallerDimVal(target, sroot->airport, dimension)) {
    if (sroot->left) {
      currBest = findNearestHelper(sroot->left, target, currBest, (dimension + 1) % Dim);
    }
  } else {
    if (sroot->right) {
      currBest = findNearestHelper(sroot->right, target, currBest, (dimension + 1) % Dim);
    }
    searchDirection = false;
  }

  // Backtraversal Logic based on pseudo-code
  if (shouldReplace(target, currBest, sroot->airport)) {
    currBest = sroot->airport;
  }

  double radius = ComputeDistance(target.getLatitude(), currBest.getLatitude(), target.getLongitude(), currBest.getLongitude());

  double splitDist = 0.0;
  if (dimension) {
    splitDist = ComputeDistance(0, 0, target.getLongitude(), currBest.getLongitude());
  } else {
    splitDist = ComputeDistance(target.getLatitude(), currBest.getLatitude(), 0, 0);
  }
  
  if (radius >= splitDist) {
    if (searchDirection) {
      if (sroot->right) {
        Airport newPoint = findNearestHelper(sroot->right, target, currBest, (dimension + 1) % Dim);
        if (shouldReplace(target, currBest, newPoint)) {
          currBest = newPoint;
        }
      }
    } else {
      if (sroot->left) {
        Airport newPoint = findNearestHelper(sroot->left, target, currBest, (dimension + 1) % Dim);
        if (shouldReplace(target, currBest, newPoint)) {
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
