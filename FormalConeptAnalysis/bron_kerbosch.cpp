#include "bron_kerbosch.hpp"
#include <iostream>
#include "extended_bipartite_graph.hpp"

bron_kerbosch::bron_kerbosch(const extended_bipartite_graph &t_graph)
{
	this->m_extended_adjacency_matrix = t_graph.get_universe();
	this->m_dim = t_graph.get_bipartite_graph_dimension();
	this->m_vertices = m_dim.rows + m_dim.cols;

}

std::vector<int> bron_kerbosch::set_union(std::vector<int> r, const int v)
{
	r.emplace_back(v);

	return r;
}

std::vector<int> bron_kerbosch::set_intersection(std::vector<int> r, const int v)
{
	for (auto it = r.begin(); it != r.end();)
	{
		if (m_extended_adjacency_matrix[v][(*it)] == 0 || (*it) == v)
		{
			it = r.erase(it);
		}
		else
		{
			++it;
		}
	}

	return r;
}

void bron_kerbosch::print_clique(std::vector<int> clique) const
{
	std::vector<int> part_a;
	std::vector<int> part_b;

	for (auto it = clique.begin(); it != clique.end(); ++it)
	{
		if ((*it) < m_dim.rows)
		{
			part_a.emplace_back(*it);
		}
		else
		{
			part_b.emplace_back((*it) - m_dim.rows);
		}
	}

	if (!part_a.empty() && !part_b.empty())
	{
		std::cout << "Clique found: ";

		std::cout << "\n\tA: {";
		for (auto it = part_a.begin(); it != part_a.end(); ++it)
		{
			std::cout << " " << (*it) + 1 << " ";
		}
		std::cout << "}";

		std::cout << "\n\tB: {";
		for (auto it = part_b.begin(); it != part_b.end(); ++it)
		{
			std::cout << " " << (*it) + 1 << " ";
		}
		std::cout << "}" << std::endl;
	}
}

void bron_kerbosch::bron_kerbosch_algorithm(const std::vector<int>& r, std::vector<int> p, std::vector<int> x)
{
	if (p.empty() && x.empty())
	{
		print_clique(r);
	}
	auto v = p.begin();
	while (!p.empty() && v != p.end())
	{
		bron_kerbosch_algorithm(set_union(r, (*v)), set_intersection(p, (*v)), set_intersection(x, (*v)));
		x = set_union(x, (*v));
		v = p.erase(v);
	}
}

void bron_kerbosch::start()
{
	const std::vector<int> r, x;
	std::vector<int> p(m_vertices);

	for (int i = 0; i < m_vertices; i++)
	{
		p.emplace_back(i);
	}

	bron_kerbosch_algorithm(r, p, x);
}
