#pragma once
#include "bipartite_graph.hpp"
class extended_bipartite_graph;

class ostergard
{
private:

	std::vector<boost::dynamic_bitset<> > m_extended_adjacency_matrix;
	int m_vertices;
	int m_max;
	int *m_clique;
	bool m_found;

	void clique(boost::dynamic_bitset<> u, int size);

public:
	explicit ostergard(const graph_base &t_graph);
	~ostergard();

	void start();
};

