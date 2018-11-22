#pragma once
#include <vector>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include "bipartite_graph.hpp"
#include "graph_base.hpp"

class bipartite_graph;

class extended_bipartite_graph : public graph_base
{
private:
	void create_extended_graph(const std::vector<boost::dynamic_bitset<>> & t_adjacency_matrix);
	dimension m_base_dimension;

public:
	explicit extended_bipartite_graph(const bipartite_graph &t_graph);
	~extended_bipartite_graph() = default;
	dimension get_bipartite_graph_dimension() const;

	extended_bipartite_graph(const extended_bipartite_graph&) = delete; // copy constructor
	extended_bipartite_graph& operator=(const extended_bipartite_graph&) = delete; // copy assignment
	extended_bipartite_graph(extended_bipartite_graph&&) = delete;  // move constructor
	extended_bipartite_graph& operator=(extended_bipartite_graph&&) = delete; // move assignment
};

