#pragma once
#include <boost/dynamic_bitset/dynamic_bitset.hpp>

struct dimension
{
	int rows;
	int cols;
};

class graph_base
{
protected:

	int m_vertices{};

	dimension m_dim = {};

	std::vector< boost::dynamic_bitset<> > m_adjacency_matrix;

public:

	graph_base() = default;

	virtual ~graph_base() = default;

	graph_base(const graph_base&) = delete; // copy constructor
	graph_base& operator=(const graph_base&) = delete; // copy assignment

	graph_base(graph_base&&) = delete;  // move constructor
	graph_base& operator=(graph_base&&) = delete; // move assignment

	std::vector< boost::dynamic_bitset<> > get_universe() const;

	dimension get_dimensions() const;

	void print_graph() const;
};

