#include "extended_bipartite_graph.hpp"
#include "bipartite_graph.hpp"


extended_bipartite_graph::extended_bipartite_graph(const bipartite_graph & t_graph)
{
	this->m_base_dimension = t_graph.get_dimensions();
	this->m_vertices = m_base_dimension.rows + m_base_dimension.cols;
	m_dim.cols = m_vertices;
	m_dim.rows = m_vertices;
	this->m_adjacency_matrix.resize(m_vertices, boost::dynamic_bitset<>(m_vertices));
	create_extended_graph(t_graph.get_universe());
}

dimension extended_bipartite_graph::get_bipartite_graph_dimension() const
{
	return m_base_dimension;
}

void extended_bipartite_graph::create_extended_graph(const std::vector<boost::dynamic_bitset<> > &t_adjacency_matrix)
{
	for (int i = 0; i < m_base_dimension.rows; ++i)
	{
		for (int j = i + 1; j < m_base_dimension.rows; ++j)
		{
			m_adjacency_matrix[i][j] = true;
			m_adjacency_matrix[j][i] = true;
		}
	}

	for (int i = m_base_dimension.rows; i < m_base_dimension.rows + m_base_dimension.cols; ++i)
	{
		for (int j = i + 1; j < m_base_dimension.rows + m_base_dimension.cols; ++j)
		{
			m_adjacency_matrix[i][j] = true;
			m_adjacency_matrix[j][i] = true;
		}
	}

	for (int i = 0; i < m_base_dimension.rows; ++i)
	{
		for (int j = 0; j < m_base_dimension.cols; ++j)
		{
			m_adjacency_matrix[m_base_dimension.rows + j][i] = t_adjacency_matrix[i][j];
			m_adjacency_matrix[i][m_base_dimension.rows + j] = t_adjacency_matrix[i][j];
		}
	}
}
