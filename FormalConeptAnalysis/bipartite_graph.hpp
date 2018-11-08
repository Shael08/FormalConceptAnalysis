#pragma once
#include <vector>
#include <boost/dynamic_bitset.hpp>

class bipartite_graph
{
public:
	bipartite_graph() = default;
	explicit bipartite_graph(int t_vertices_a, int t_vertices_b);
	~bipartite_graph();

	void print_graph() const;

	std::vector<boost::dynamic_bitset<> > get_universe() const;

	int get_universe_rows() const;
	int get_universe_cols() const;

private:

	std::vector<boost::dynamic_bitset<> > m_adjacency_matrix;
	int m_vertices_a;
	int m_vertices_b;

	void create_random_graph();
};