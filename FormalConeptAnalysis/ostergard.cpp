#include "ostergard.hpp"
#include "extended_bipartite_graph.hpp"
#include <iostream>


ostergard::ostergard(const graph_base & t_graph)
{
	this->m_adjacency_matrix = t_graph.get_universe();
	this->m_dim = t_graph.get_dimensions();
	this->m_vertices = m_dim.cols + m_dim.rows;
	m_max = 0;
	m_clique = new int[m_dim.rows];
	m_found = false;
	this->m_adjacency_matrix_t.resize(m_dim.cols, boost::dynamic_bitset<>(m_dim.rows));

	for (int i = 0; i < m_dim.rows; ++i)
	{
		for (int j = 0; j < m_dim.cols; ++j)
		{
			m_adjacency_matrix_t[j][i] = m_adjacency_matrix[i][j];
		}
	}
}

ostergard::~ostergard()
{
	delete[] m_clique;
}

void ostergard::clique(boost::dynamic_bitset<> u, const int size)
{
	if(u.none())
	{
		if(size > m_max)
		{
			m_max = size;
			std::cout << m_max << std::endl;
			m_found = true;
		}
	}

	while(u.any())
	{
		if(size + int(u.count()) <= m_max)
		{
			return;
		}

		const int i = u.find_first();

		if( size + m_clique[i] <= m_max)
		{
			return;
		}

		u[i] = false;

		clique(u & m_adjacency_matrix[i], size + 1);

		if(m_found) return;
	}

}

void ostergard::bipartite_clique(boost::dynamic_bitset<> u, boost::dynamic_bitset<> v, const int size,const bool &in_transposed)
{
	if (u.none() && v.any())
	{
		if (size + int(v.count()) > m_max)
		{
			m_max = size + int(v.count());
			std::cout << m_max << std::endl;
			m_found = true;
		}
	}

	while (u.any() && v.any())
	{
		if (size + int(v.count()) + int(u.count()) <= m_max)
		{
			return;
		}

		const int i = u.find_first();

		if (size + int(v.count()) + m_clique[i] <= m_max)
		{
			return;
		}

		u[i] = false;

		v &= in_transposed ? m_adjacency_matrix_t[i] : m_adjacency_matrix[i];

		bipartite_clique(u, v, size + 1, in_transposed);

		if (m_found) return;
	}

}

void ostergard::start()
{
	for (int i = m_vertices - 1; i >= 0; --i)
	{
		m_found = false;

		boost::dynamic_bitset<> u(m_vertices);

		for(int j=i; j<m_vertices; ++j)
		{
			if (m_adjacency_matrix[i][j]) u[j] = true;
		}

		clique(u, 1);

		m_clique[i] = m_max;
	}
}

void ostergard::start_bipartite()
{
	delete[] m_clique;
	m_clique = new int[m_dim.rows];

	for (int i = m_dim.rows - 1; i >= 0; --i)
	{
		m_found = false;

		boost::dynamic_bitset<> u(m_dim.rows);

		boost::dynamic_bitset<> v(m_dim.cols);

		v = m_adjacency_matrix[i];

		for (int j = i + 1; j < m_dim.rows; ++j)
		{
			u[j] = true;
		}

		bipartite_clique(u, v, 1, false);

		m_clique[i] = m_max;
	}

	std::cout << "in transposed: " << std::endl;
	delete[] m_clique;
	m_clique = new int[m_dim.cols];
	m_max = 0;

	for (int i = m_dim.cols - 1; i >= 0; --i)
	{
		m_found = false;

		boost::dynamic_bitset<> u(m_dim.cols);

		boost::dynamic_bitset<> v(m_dim.rows);

		v = m_adjacency_matrix_t[i];

		for (int j = i + 1; j < m_dim.cols; ++j)
		{
			u[j] = true;
		}

		bipartite_clique(u, v, 1, true);

		m_clique[i] = m_max;
	}
}