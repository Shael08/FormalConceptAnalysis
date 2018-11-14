#pragma once
#include <boost/dynamic_bitset/dynamic_bitset.hpp>

struct dimension
{
	int row;
	int cols;
};

class graph_base
{
protected:

	int m_vertices{};

	dimension m_dim = {};

	std::vector< boost::dynamic_bitset<> > m_adjacency_matrix;

public:

	std::vector< boost::dynamic_bitset<> > get_universe() const;

	dimension get_dimensions() const;

	void print_graph() const;
};

