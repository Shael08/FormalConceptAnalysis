#include "bipartite_graph.hpp"
#include <ctime>


bipartite_graph::bipartite_graph(const int t_vertices_a, const int t_vertices_b)
{
	this->m_dim.rows = t_vertices_a;
	this->m_dim.cols = t_vertices_b;
	this->m_adjacency_matrix.resize(m_dim.rows, boost::dynamic_bitset<>(m_dim.cols));

	create_random_graph();
}

void bipartite_graph::create_random_graph()
{
	srand(time(nullptr));
	for (int i = 0; i < m_dim.rows; ++i)
	{
		for (int j = 0; j < m_dim.cols; ++j)
		{
			if (rand() % 2)
			{
				m_adjacency_matrix[i][j] = true;
			}
		}
	}
}
