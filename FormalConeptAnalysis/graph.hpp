#pragma once
#include "graph_base.hpp"

class graph : public graph_base
{
public:
	explicit graph(char *file);
	~graph() = default;
	void read_graph(char* file);

	graph(const graph&) = delete; // copy constructor
	graph& operator=(const graph&) = delete; // copy assignment
	graph(graph&&) = delete;  // move constructor
	graph& operator=(graph&&) = delete; // move assignment
};

