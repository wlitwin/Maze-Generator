#ifndef __MAZE_H__
#define __MAZE_H__

#include <vector>
#include <cstdlib>

#include <unistd.h>

#include <iostream>

typedef unsigned char byte;
typedef unsigned int uint32_t;

using std::cout;
using std::endl;

typedef struct
{
	int node; // Node index
	int edge; // first edge
	int oedge;// opposite edge
} PossibleNode;

typedef struct
{
	bool visited;
	bool active;
	bool left_edge; 	
	bool right_edge;
	bool top_edge;
	bool bottom_edge;
	bool invalid;

	void print()
	{
		if (invalid) { cout << "Invalid!"; return; }
		cout << "Visited: " << visited << endl;
		cout << "Left   : " << left_edge << endl;
		cout << "Right  : " << right_edge << endl;
		cout << "Top    : " << top_edge << endl;
		cout << "Bottom : " << bottom_edge << endl;
	}
} Node;

class Maze 
{
	public:
		/* Create a new maze of size sizex by sizey
		 *
		 * \param[in] sizex The width of the maze
		 * \param[in] sizey The height of the maze
		 */
		Maze(const uint32_t sizex, const uint32_t sizey);

		/* Clean up the maze
		 */
		~Maze();

		/* Generate the maze. This is meant to be called iteratively.
		 * It only generates one piece of the maze at a time and returns
		 * True when it's finished generating.
		 *
		 * \return True when the maze has been fully generated
		 */
		bool Generate();

		/* Get the width of the maze
		 *
		 * \return The width of the maze
		 */
		int Width();

		/* Get the height of the maze
		 *
		 * \return The height of the maze
		 */
		int Height();

		/* Get the node at the specified position in the maze. Creates
		 * a new Node every time. Check the invalid flag to see if The
		 * node returned is part of the maze
		 *
		 * \param[in] x The x coordinate of the Node
		 * \param[in] y The y coordinate of the Node
		 *
		 * \return A node object, the invalid flag will be false if the 
		 *         node is part of the maze.
		 */
		Node GetNode(int x, int y);

	private:
		/* Get a random node from the maze.
		 *
		 * \return The linear index of a valid node in 
		 *         the maze
		 */
		int RandomNode();

		/* Get the left neighbot of a node
		 *
		 * \param[in] node The node to get the left neighbor of
		 *
		 * \return The linear index of the neighbor node or -1 if 
		 *         there is no left neighbor
		 */
		int GetLeftNeighbor(int node);

		/* Get the right neighbot of a node
		 *
		 * \param[in] node The node to get the right neighbor of
		 *
		 * \return The linear index of the neighbor node or -1 if 
		 *         there is no right neighbor
		 */
		int GetRightNeighbor(int node);

		/* Get the top neighbot of a node
		 *
		 * \param[in] node The node to get the top neighbor of
		 *
		 * \return The linear index of the neighbor node or -1 if 
		 *         there is no top neighbor
		 */
		int GetTopNeighbor(int node);

		/* Get the bottom neighbot of a node
		 *
		 * \param[in] node The node to get the bottom neighbor of
		 *
		 * \return The linear index of the neighbor node or -1 if 
		 *         there is no bottom neighbor
		 */
		int GetBottomNeighbor(int node);

	private: /* Variables */
		uint32_t size_x; // Maze width
		uint32_t size_y; // Maze height
		int len;         // Length of the maze (size_x * size_y)
		byte* maze;      // An array of all the nodes in the maze

		std::vector<int> activeset; // Used for generating the maze
		int index; // Used for storing state between 'Generate()' calls
		int node;  // Used for storing state between 'Generate()' calls

		// Constants for the node flags
		static const byte VISITED	  = 0x80;
		static const byte ACTIVE	  = 0x40;
		static const byte LEFT_EDGE   = 0x08;
		static const byte RIGHT_EDGE  = 0x04;
		static const byte TOP_EDGE    = 0x02;
		static const byte BOTTOM_EDGE = 0x01;
};

#endif
