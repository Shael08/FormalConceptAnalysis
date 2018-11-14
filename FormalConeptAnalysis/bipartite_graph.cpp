#include "bipartite_graph.hpp"
#include <ctime>


bipartite_graph::bipartite_graph(const int t_vertices_a, const int t_vertices_b)
{
	this->m_dim.row = t_vertices_a;
	this->m_dim.cols = t_vertices_b;
	this->m_adjacency_matrix.resize(t_vertices_a, boost::dynamic_bitset<>(t_vertices_b));

	create_random_graph();
}

bipartite_graph::~bipartite_graph() = default;

void bipartite_graph::create_random_graph()
{
	srand(time(nullptr));
	for (int i = 0; i < m_dim.row; ++i)
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
