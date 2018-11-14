#pragma once
#include "graph_base.hpp"

class graph : public graph_base
{
public:
	explicit graph(char *file);
	~graph();
	void read_graph(char* file);
};

