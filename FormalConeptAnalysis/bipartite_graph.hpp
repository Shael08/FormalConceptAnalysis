#pragma once
#include "graph_base.hpp"


class bipartite_graph : public graph_base
{
public:
	explicit bipartite_graph(int t_vertices_a, int t_vertices_b);
	~bipartite_graph() = default;

	bipartite_graph(const bipartite_graph&) = delete; // copy constructor
	bipartite_graph& operator=(const bipartite_graph&) = delete; // copy assignment
	bipartite_graph(bipartite_graph&&) = delete;  // move constructor
	bipartite_graph& operator=(bipartite_graph&&) = delete; // move assignment

private:

	bool m_matrix[5][6] = { 1, 0, 1, 0, 0, 1,
							  0, 1, 0, 1, 1, 0,
							  1, 1, 1, 0, 1, 1,
							  0, 0, 0, 0, 0, 0,
							  0, 1, 1, 1, 0, 0 };


	bool m_matrix2[5][6] = { 0, 0, 0, 0, 1, 1,
								0, 0, 1, 0, 0, 0,
								0, 1, 1, 1, 1, 0,
								0, 0, 0, 1, 0, 0,
								0, 1, 0, 0, 0, 0 };


	void create_random_graph();
};
