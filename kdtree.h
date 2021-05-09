/**
 * @file kdtree.h
 * KDTree implementation using airports in a 2-dimensional space.
 *
 * @author CS 225 Data Structures
 */

#pragma once

#include <vector>

#include "airport.h"

/** KDTree class: implemented using airports in 2-D space. */
class KDTree {
 private:
  /** Internal structure for a node of the KDTree. Contains left, right children
   * pointers and an airport. */
  struct KDTreeNode {
    Airport airport;
    KDTreeNode *left, *right;

    KDTreeNode() : left(nullptr), right(nullptr) {}
    KDTreeNode(const Airport& airport)
        : airport(airport), left(nullptr), right(nullptr) {}
  };

 public:
  /**
   * Determines if an airport A is smaller than airport B with given coordinates
   * in a given dimension.
   * @param firstLat first airport's latitude
   * @param secondLat second airport's latitude
   * @param firstLong first airport's longitude
   * @param secondLong second airport's longitude
   * @param curDim dimension these points are being compared in
   * @return boolean value indicating whether the first airport is smaller than
   * the second airport in the given dimension
   */
  bool smallerDimVal(double firstLat, double secondLat, double firstLong,
                     double secondLong, int curDim) const;

  /**
   * Determines if an airport (currBest) is closer to the target airport than
   * another reference (potential) airport.
   * @param targetLat Target airport's latitude
   * @param currBestLat currBest airport's latitude
   * @param potentialLat Potential airport's latitude
   * @param targetLong Target airport's longitude
   * @param currBestLong currBest airport's longitude
   * @param potentialLong Potential airport's longitude
   * @return boolean value indicating whether potential is closer to target than
   * currentBest
   */
  bool shouldReplace(double targetLat, double currBestLat, double potentialLat,
                     double targetLong, double currBestLong,
                     double potentialLong) const;

  /** Default constructor */
  KDTree();

  /**
   * Constructs a KDTree from a vector of airports, each having dimension Dim.
   * @param newPoints vector of airports to build KDTree
   */
  KDTree(const std::vector<Airport>& newPoints);

  /**
   * Copy constructor for KDTree.
   * @param other KDTree to copy
   */
  KDTree(const KDTree& other);

  /**
   * Assignment operator for KDTree.
   * @param rhs ight hand side of the assignment statement
   * @return reference for performing chained assignments
   */
  KDTree const& operator=(const KDTree& rhs);

  /** Destructor for KDTree. */
  ~KDTree();

  /**
   * Finds the closest point to the parameter airport in the KDTree.
   * @param targetLat Target airport's latitude coordinate to compare against
   * @param targetLong Target airport's longitude coordinate to compare against
   * @return The closest airport to given position in the KDTree.
   */
  Airport findNearestNeighbor(double targetLat, double targetLong) const;

 private:
  /** Standardized dimension value, latitude and longitude */
  const int Dim = 2;

  /** Internal representation, root and size */
  KDTreeNode* root;
  size_t size;

  /** Stores current points for the duration of constructing the kd-tree */
  std::vector<Airport> list;

  /** Constructs the necessary kd-tree */
  KDTreeNode* buildTree(int left, int right, int dimension);

  /** Rearranges KDtree's points, for the quickselect algorithm */
  int partition(int left, int right, int pivotIndex, int dimension);

  /** Quickselect algorithm */
  Airport& select(int left, int right, int k, int dimension);

  /** Destructor helper method */
  void clear(KDTreeNode* sroot);

  /** Helper method for findNearestNeighbor */
  Airport findNearestHelper(KDTreeNode* sroot, double targetLat,
                            double targetLong, Airport currBest,
                            int dimension) const;

  /** Computes the great-circle distance between two airports using their
   * associated coordinates. */
  double ComputeDistance(double lat1, double lat2, double long1,
                         double long2) const;
};