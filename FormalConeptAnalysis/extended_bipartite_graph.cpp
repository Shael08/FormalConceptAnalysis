#include "extended_bipartite_graph.hpp"
#include "bipartite_graph.hpp"


extended_bipartite_graph::extended_bipartite_graph(const bipartite_graph & t_graph)
{
	this->m_dim = t_graph.get_dimensions();
	this->m_vertices = m_dim.row + m_dim.cols;
	this->m_adjacency_matrix.resize(m_vertices, boost::dynamic_bitset<>(m_vertices));
	create_extended_graph(t_graph.get_universe());
}

void extended_bipartite_graph::create_extended_graph(const std::vector<boost::dynamic_bitset<> > &t_adjacency_matrix)
{
	for (int i = 0; i < m_dim.row; ++i)
	{
		for (int j = i + 1; j < m_dim.row; ++j)
		{
			m_adjacency_matrix[i][j] = true;
			m_adjacency_matrix[j][i] = true;
		}
	}

	for (int i = m_dim.row; i < m_dim.row + m_dim.cols; ++i)
	{
		for (int j = i + 1; j < m_dim.row + m_dim.cols; ++j)
		{
			m_adjacency_matrix[i][j] = true;
			m_adjacency_matrix[j][i] = true;
		}
	}

	for (int i = 0; i < m_dim.row; ++i)
	{
		for (int j = 0; j < m_dim.cols; ++j)
		{
			m_adjacency_matrix[m_dim.row + j][i] = t_adjacency_matrix[i][j];
			m_adjacency_matrix[i][m_dim.row + j] = t_adjacency_matrix[i][j];
		}
	}
}
