#pragma once
#include "bipartite_graph.hpp"

class extended_bipartite_graph;

class bron_kerbosch
{
private:
	std::vector<boost::dynamic_bitset<> > m_extended_adjacency_matrix;

	int m_vertices;

	dimension m_dim{};

	static std::vector<int> set_union(std::vector<int> r, const int v);

	std::vector<int> set_intersection(std::vector<int> r, const int v);

	void print_clique(std::vector<int> clique) const;

	void bron_kerbosch_algorithm(const std::vector<int> &r, std::vector<int> p, std::vector<int> x);

public:
	explicit bron_kerbosch(const extended_bipartite_graph &t_graph);

	~bron_kerbosch() = default;

	bron_kerbosch(const bron_kerbosch&) = delete; // copy constructor
	bron_kerbosch& operator=(const bron_kerbosch&) = delete; // copy assignment

	bron_kerbosch(bron_kerbosch&&) = delete;  // move constructor
	bron_kerbosch& operator=(bron_kerbosch&&) = delete; // move assignment

	void start();
};

