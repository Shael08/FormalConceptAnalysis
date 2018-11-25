#include "ostergard.hpp"
#include "extended_bipartite_graph.hpp"
#include <iostream>


ostergard::ostergard(const graph_base & t_graph)
{
	this->m_adjacency_matrix = t_graph.get_universe();
	this->m_dim = t_graph.get_dimensions();
	this->m_vertices = m_adjacency_matrix.size();
	m_c = new int[m_vertices];
	m_found = false;
}

ostergard::~ostergard()
{
	delete[] m_c;
}

void ostergard::clique(boost::dynamic_bitset<> u, std::vector<int> t_clique)
{
	if(u.none())
	{
		if(t_clique.size() > m_clique.size())
		{
			m_clique = t_clique;
			m_found = true;

			print_clique();
		}
	}

	while(u.any())
	{
		if(t_clique.size() + int(u.count()) <= m_clique.size())
		{
			return;
		}

		const int i = u.find_first();

		if(t_clique.size() + m_c[i] <= m_clique.size())
		{
			return;
		}

		u[i] = false;

		t_clique.push_back(i);

		clique(u & m_adjacency_matrix[i], t_clique);

		t_clique.pop_back();

		if(m_found) return;
	}

}

void ostergard::bipartite_clique(boost::dynamic_bitset<> u, boost::dynamic_bitset<> v, std::vector<int> t_clique)
{
	if (v.none()) return;

	if (t_clique.size() + int(v.count()) > m_clique.size())
	{
		m_clique = t_clique;

		for (int i = 0; i < v.size(); ++i)
		{
			if (v[i]) m_clique.push_back(i);
		}

		m_found = true;

		print_clique();
	}
	
	while (u.any())
	{
		if (t_clique.size() + int(v.count()) + int(u.count()) <= m_clique.size())
		{
			return;
		}

		const int i = u.find_first();

		if (t_clique.size() + int(v.count()) + m_c[i] <= m_clique.size())
		{
			return;
		}

		u[i] = false;

		auto t_v = v;

		t_v &= m_adjacency_matrix[i];

		t_clique.push_back(i);

		bipartite_clique(u, t_v, t_clique);

		t_clique.pop_back();

		if (m_found) return;
	}

}

void ostergard::print_clique()
{
	std::cout << "\nClique size: " << m_clique.size() << std::endl;

	std::cout << "Clique Elements are: ";

	for (std::_Vector_iterator<std::_Vector_val<std::_Simple_types<int>>>::value_type& it : m_clique)
	{
		std::cout << it << " ";
	}

	std::cout << std::endl;
}

void ostergard::start()
{

	std::vector<int> t_clique;

	for (int i = m_vertices - 1; i >= 0; --i)
	{
		m_found = false;

		boost::dynamic_bitset<> u(m_vertices);

		for(int j=i; j<m_vertices; ++j)
		{
			if (m_adjacency_matrix[i][j]) u[j] = true;
		}

		t_clique.push_back(i);

		clique(u, t_clique);

		t_clique.pop_back();

		m_c[i] = m_clique.size();
	}
}

void ostergard::start_bipartite()
{
	delete[] m_c;
	m_c = new int[m_dim.rows];

	std::vector<int> t_clique;

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

		t_clique.push_back(i);

		bipartite_clique(u, v, t_clique);

		t_clique.pop_back();

		m_c[i] = m_clique.size();
	}
}