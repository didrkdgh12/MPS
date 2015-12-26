#ifndef DSETS_H
#define DSETS_H

#include <vector>

class DisjointSets {
	public:


		/**
		 * Creates N unconnected root nodes at the end of the vector
		 * @param num The number of nodes to create
		 */
		void addelements(int num);

		/**
		 * Follows parent nodes until it reaches root
		 * @param  elem The element to start at
		 * @return int  The index of the parent node
		 */
		int find(int elem);

		/**
		 * Unions two disjoint sets. The smaller set points at the larger
		 * @param a Index of the first element to union
		 * @param b Index of the second element to union
		 */
		void setunion(int a, int b);

	private:
		std::vector<int> vSet;

		/**
		 * Returns true if the index a is bigger than the index b
		 * @param  a index a in the set
		 * @param  b index b in the set
		 * @return boolean true if a is bigger than b
		 */
		bool isBigger(int a, int b);
};

#endif // DSETS_H