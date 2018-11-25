#pragma once
#include "bipartite_graph.hpp"
class extended_bipartite_graph;

class ostergard
{
private:

	std::vector<boost::dynamic_bitset<> > m_adjacency_matrix;
	dimension m_dim{};

	int m_vertices;
	int *m_c;
	bool m_found;
	std::vector<int> m_clique;

	void clique(boost::dynamic_bitset<> u, std::vector<int> t_clique);
	void bipartite_clique(boost::dynamic_bitset<> u, boost::dynamic_bitset<> v, std::vector<int> t_clique);

	void print_clique();

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

