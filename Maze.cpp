#include <ctime>
#include "Maze.h"

// Bit layout
// 0 - Visited or not
// 1 - 
// 2 -
// 3 -
// 4 - Left edge
// 5 - Right edge
// 6 - Up 
// 7 - Down 

using std::cout;
using std::endl;
using std::vector;

Maze::Maze(const uint32_t size_x_, const uint32_t size_y_) : 
	size_x(size_x_), size_y(size_y_)
{
	len = (size_x * size_y);
	maze = new byte[len];
	// Zero the array
	for (int i = 0; i < len; ++i)
	{
		maze[i] = 0;
	}

	srand(time(NULL));
	
	int node = RandomNode();
	activeset.push_back(node);
}

Maze::~Maze()
{
	delete [] maze;
}

int Maze::Width()
{
	return size_x;
}

int Maze::Height()
{
	return size_y;
}

Node Maze::GetNode(int x, int y)
{
	Node node;
	int index = (y * size_y) + x;
	if (index >= len || index < 0)
	{
		//cout << "Index: " << index << endl;
		node.invalid = true;	
		return node;
	}

	node.visited 	 = (maze[index] & VISITED) > 0;
	node.active		 = (maze[index] & ACTIVE) > 0;
	node.left_edge   = (maze[index] & LEFT_EDGE) > 0;
	node.right_edge  = (maze[index] & RIGHT_EDGE) > 0;
	node.top_edge 	 = (maze[index] & TOP_EDGE) > 0;
	node.bottom_edge = (maze[index] & BOTTOM_EDGE) > 0;
	node.invalid	 = false;

	return node;
}

int Maze::RandomNode()
{
	int i = rand() % len;
	while ((maze[i] & VISITED) > 0) 
	{
		i = rand() % len;
	}

	maze[i] |= VISITED;
	return i;
}

// Returns -1 if there is no neighbor there
int Maze::GetLeftNeighbor(int node)
{
	// [  0  1  2  3  4  5  6 ]
	// [  7  8  9 10 11 12 13 ]
	// [ 14 15 16 17 18 19 20 ]
	// [ 21 22 23 24 25 26 27 ]

	// Need to know if we we've moved up a row
	// or not
	int py = (node-1) / size_x;
	int y  = (node) / size_x;

	if (y != py) 
	{
		// They are on different rows
		return -1;
	}

	return node-1;	
}

int Maze::GetRightNeighbor(int node)
{
	int ny = (node+1) / size_x;
	int y  = (node) / size_x;

	if (y != ny)
	{
		// They are on different rows
		return -1;
	}

	return node+1;
}

int Maze::GetTopNeighbor(int node)
{
	// [  0  1  2  3  4  5  6 ]
	// [  7  8  9 10 11 12 13 ]
	// [ 14 15 16 17 18 19 20 ]
	// [ 21 22 23 24 25 26 27 ]

	int tx = (node - size_x);
	if (tx < 0) 
	{
		// Outside the array
		return -1;
	}

	return tx;
}

int Maze::GetBottomNeighbor(int node)
{
	// [  0  1  2  3  4  5  6 ]
	// [  7  8  9 10 11 12 13 ]
	// [ 14 15 16 17 18 19 20 ]
	// [ 21 22 23 24 25 26 27 ]

	int bx = (node + size_x);
	if (bx >= len)
	{	
		// Off the end of the array
		return -1;	
	}

	return bx;
}

bool Maze::Generate()
{
	// Algorithm 
	// Choose a node at random and add it to the active set
	// 
	if (activeset.empty())
	{
		return true;
	}

	// Choose a node at random from the active set
	// We'll choose the newest
	//node = activeset.back();

	// Choose a random node from the set
	if (rand() % 2 == 0)
	{
		index = rand() % activeset.size();
	} else {
		index = activeset.size()-1;
	}
	//index = activeset.size()-1;
	node  = activeset.at(index);

	// Add one of the unvisited neighbors to the set
	// check left

	int left 	= GetLeftNeighbor(node);
	int right   = GetRightNeighbor(node);
	int top 	= GetTopNeighbor(node);
	int bottom  = GetBottomNeighbor(node);

	bool try_again = false;

	vector<PossibleNode> possibilities;

	// Is the left unvisited?
	if (left != -1 && (maze[left] & VISITED) == 0) 
	{
		PossibleNode pn = { left, RIGHT_EDGE, LEFT_EDGE };
		possibilities.push_back(pn);
	}

	if (right != -1 && (maze[right] & VISITED) == 0)
	{
		PossibleNode pn = { right, LEFT_EDGE, RIGHT_EDGE };
		possibilities.push_back(pn);
	}

	if (top != -1 && (maze[top] & VISITED) == 0)
	{
		PossibleNode pn = { top, BOTTOM_EDGE, TOP_EDGE };
		possibilities.push_back(pn);
	}

	if (bottom != -1 && (maze[bottom] & VISITED) == 0)
	{
		PossibleNode pn = { bottom, TOP_EDGE, BOTTOM_EDGE };
		possibilities.push_back(pn);
	}
	
	if (possibilities.empty())
	{
		maze[node] &= ~ACTIVE;
		activeset.erase(activeset.begin()+index);
	} else {
		int pick = rand() % possibilities.size();
		PossibleNode other = possibilities.at(pick);

		maze[other.node] |= ACTIVE | VISITED | other.edge;
		maze[node] 		 |= other.oedge;
		activeset.push_back(other.node);
	}
	
	return false;
}
