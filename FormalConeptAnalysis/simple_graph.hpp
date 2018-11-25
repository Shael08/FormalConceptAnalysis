#pragma once
#include "graph_base.hpp"

class simple_graph : public graph_base
{
public:

	explicit simple_graph(char *file);
	~simple_graph() = default;

	simple_graph(const simple_graph&) = delete; // copy constructor
	simple_graph& operator=(const simple_graph&) = delete; // copy assignment
	simple_graph(simple_graph&&) = delete;  // move constructor
	simple_graph& operator=(simple_graph&&) = delete; // move assignment

	void read_graph(char* file);
};

