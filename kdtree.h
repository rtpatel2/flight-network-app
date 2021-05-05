/**
 * @file kdtree.h
 * KDTree implementation using Airports in a k-dimensional space.
 *
 * @author CS 225 Data Structures
 */

#pragma once

#include <vector>
#include "airport.h"

using std::vector;

/**
 * KDTree class: implemented using Airports in a 2-D Space (Latitude, Longitude).
 */
class KDTree
{
  private:
    /**
     * Internal structure for a node of the KDTree.
     * Contains left, right children pointers and an Aiport
     */
    struct KDTreeNode
    {
      Airport airport;
      KDTreeNode *left, *right;

      KDTreeNode() : airport(), left(NULL), right(NULL) {}
      KDTreeNode(const Airport &airport) : airport(airport), left(NULL), right(NULL) {}
    };

  public:
    /**
     * Determines if an Airport A is smaller than Airport B in a given dimension, curDim.
     * @param first First Airport to compare.
     * @param second Second Airport to compare.
     * @param curDim The dimension these points are being compared in.
     * @return A boolean value indicating whether the first Airport is smaller
     *  than the second Airport in the curDim dimension.
     */
    bool smallerDimVal(const Airport& first, const Airport& second,
                       int curDim) const;

    /**
     * Determines if an Airport (currentBest) is closer to the target Airport than another
     * reference (potential) Airport.
     * @param target The target Airport we want to be close to.
     * @param currentBest The closest Airport to target.
     * @param potential The candidate airport to replace currentBest.
     * @return A boolean value indicating whether potential is closer
     *  to target than currentBest.
     */
    bool shouldReplace(const Airport& target, const Airport& currentBest,
                       const Airport& potential) const;

    /**
     * Constructs a KDTree from a vector of Airports, each having dimension Dim.
     * @param newPoints The vector of points to build your KDTree off of.
     */
    KDTree(const vector<Airport>& newPoints);


    /**
     * Copy constructor for KDTree.
     *
     * @param other The KDTree to copy.
     */
    KDTree(const KDTree& other);

    /**
     * Assignment operator for KDTree.
     *
     * @param rhs The right hand side of the assignment statement.
     * @return A reference for performing chained assignments.
     */
    KDTree const &operator=(const KDTree& rhs);

    /**
     * Destructor for KDTree.
     */
    ~KDTree();

    /**
     * Finds the closest point to the parameter Airport in the KDTree.
     * @param query The point we wish to find the closest neighbor to in the
     *  tree.
     * @return The closest point to a in the KDTree.
     */
    Airport findNearestNeighbor(const Airport& query) const;

  private:
    /** Standardized dimension value, latitude and longitude */
    const int Dim = 2;

    /** Internal representation, root and size */
    KDTreeNode *root;
    size_t size;

    /** Stores current points for the duration of constructing the kd-tree. */
    vector<Airport> list;

    /**
     * Constructs the necessary kd-tree.
     */
    KDTreeNode* buildTree(int left, int right, int dimension);

    /**
     * Swaps the elements for the partition method of the kd-tree.
    */
    void swap(int one, int two);

    /**
     * Rearranges our kd-tree's points, for the quickselect algorithm.
    */
    int partition(int left, int right, int pivotIndex, int dimension);

    /**
     * Official quickselect function.
    */
    Airport& select(int left, int right, int k, int dimension);

    /**
     * Destructor helper method
     */
    void clear(KDTreeNode* sroot);

    /**
     * Official helper method for findNearestNeighbor.
     */
    Airport findNearestHelper(KDTreeNode* sroot, const Airport& target, Airport currBest, int dimension) const;

    /**
     * Computes the great-circle distance between two airports using their 
     * associated coordinates.
     */
    double ComputeDistance(double lat1, double lat2, double long1, double long2) const;
};
