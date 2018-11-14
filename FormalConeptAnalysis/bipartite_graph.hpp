#pragma once
#include "graph_base.hpp"


class bipartite_graph : public graph_base
{
public:
	bipartite_graph() = default;
	explicit bipartite_graph(int t_vertices_a, int t_vertices_b);
	~bipartite_graph();

private:

	void create_random_graph();
};
