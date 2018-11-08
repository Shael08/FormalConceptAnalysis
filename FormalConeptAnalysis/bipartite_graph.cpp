#include "bipartite_graph.hpp"
#include <iostream>
#include <ctime>

bipartite_graph::bipartite_graph(const int t_vertices_a, const int t_vertices_b)
{
	this->m_vertices_a = t_vertices_a;
	this->m_vertices_b = t_vertices_b;
	this->m_adjacency_matrix.resize(t_vertices_a, boost::dynamic_bitset<>(t_vertices_b));

	create_random_graph();
}

bipartite_graph::~bipartite_graph() = default;

void bipartite_graph::print_graph() const
{
	for (int i = 0; i < m_vertices_a; ++i)
	{
		for (int j = 0; j < m_vertices_b; ++j)
		{
			std::cout << m_adjacency_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::vector<boost::dynamic_bitset<>> bipartite_graph::get_universe() const
{
	return m_adjacency_matrix;
}

int bipartite_graph::get_universe_rows() const
{
	return m_vertices_a;
}

int bipartite_graph::get_universe_cols() const
{
	return m_vertices_b;
}

void bipartite_graph::create_random_graph()
{
	srand(time(nullptr));
	for (int i = 0; i < m_vertices_a; ++i)
	{
		for (int j = 0; j < m_vertices_b; ++j)
		{
			if (rand() % 2)
			{
				m_adjacency_matrix[i][j] = true;
			}
		}
	}
}
