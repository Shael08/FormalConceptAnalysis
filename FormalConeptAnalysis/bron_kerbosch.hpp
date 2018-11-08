#pragma once
#include "bipartite_graph.hpp"

class bron_kerbosch
{
private:
	std::vector<boost::dynamic_bitset<> > m_extended_adjacency_matrix;

	int m_rows;

	int m_cols;

	int m_vertices;

	void create_extended_graph(const std::vector<boost::dynamic_bitset<>> &m_adjacency_matrix);

	static std::vector<int> set_union(std::vector<int> r, const int v);

	std::vector<int> set_intersection(std::vector<int> r, const int v);

	void print_clique(std::vector<int> clique) const;

	void bron_kerbosch_algorithm(const std::vector<int> &r, std::vector<int> p, std::vector<int> x);

public:
	explicit bron_kerbosch(const bipartite_graph &t_graph);

	~bron_kerbosch() = default;

	void print_extended_graph() const;

	void start();
};

