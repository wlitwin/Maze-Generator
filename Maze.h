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
	int node;
	int edge;
	int oedge;
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
		Maze(const uint32_t sizex, const uint32_t sizey);
		~Maze();
		bool Generate();
		int Width();
		int Height();
		Node GetNode(int x, int y);

	private:
		int RandomNode();
		int GetLeftNeighbor(int node);
		int GetRightNeighbor(int node);
		int GetTopNeighbor(int node);
		int GetBottomNeighbor(int node);
		
		uint32_t size_x;
		uint32_t size_y;
		int len;
		byte* maze;

		std::vector<int> activeset;
		int index;
		int node;

		static const byte VISITED	  = 0x80;
		static const byte ACTIVE	  = 0x40;
		static const byte LEFT_EDGE   = 0x08;
		static const byte RIGHT_EDGE  = 0x04;
		static const byte TOP_EDGE    = 0x02;
		static const byte BOTTOM_EDGE = 0x01;
};

#endif
