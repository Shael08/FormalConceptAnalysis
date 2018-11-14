#include "ostergard.hpp"
#include "extended_bipartite_graph.hpp"
#include <iostream>


ostergard::ostergard(const graph_base & t_graph)
{
	this->m_extended_adjacency_matrix = t_graph.get_universe();
	this->m_vertices = m_extended_adjacency_matrix.size();
	m_max = 0;
	m_clique = new int[m_vertices];
	m_found = false;
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

		clique(u & m_extended_adjacency_matrix[i], size + 1);

		if(m_found) return;
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
			if (m_extended_adjacency_matrix[i][j]) u[j] = true;
		}

		clique(u, 1);

		m_clique[i] = m_max;
	}
}
