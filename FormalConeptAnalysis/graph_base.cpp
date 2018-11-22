#include "graph_base.hpp"
#include <iostream>


std::vector<boost::dynamic_bitset<>> graph_base::get_universe() const
{
	return m_adjacency_matrix;
}

dimension graph_base::get_dimensions() const
{
	return m_dim;
}

void graph_base::print_graph() const
{
	for (int i = 0; i < m_dim.rows; ++i)
	{
		for (int j = 0; j < m_dim.cols; ++j)
		{
			std::cout << m_adjacency_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
