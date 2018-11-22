#pragma once
#include "bipartite_graph.hpp"
class extended_bipartite_graph;

class ostergard
{
private:

	std::vector<boost::dynamic_bitset<> > m_adjacency_matrix;
	std::vector<boost::dynamic_bitset<> > m_adjacency_matrix_t;
	dimension m_dim{};
	int m_vertices;

	int m_max;
	int *m_clique;
	bool m_found;


	void clique(boost::dynamic_bitset<> u, int size);
	void bipartite_clique(boost::dynamic_bitset<> u, boost::dynamic_bitset<> v, int size, const bool &in_transposed);

public:
	explicit ostergard(const graph_base &t_graph);
	virtual ~ostergard();

	ostergard(const ostergard&) = delete; // copy constructor
	ostergard& operator=(const ostergard&) = delete; // copy assignment

	ostergard(ostergard&&) = delete;  // move constructor
	ostergard& operator=(ostergard&&) = delete; // move assignment

	void start();
	void start_bipartite();
};

