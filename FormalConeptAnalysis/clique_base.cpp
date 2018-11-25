#include "clique_base.h"
#include <iostream>

void clique_base::print_clique()
{
	if (m_clique.empty())
	{
		find_clique();
	}

	std::cout << "Members of the clique: " << std::endl;
	for (std::_Vector_iterator<std::_Vector_val<std::_Simple_types<int>>>::value_type& it : m_clique)
	{
		std::cout << it << " " << std::endl;
	}

}

std::vector<int> clique_base::get_clique()
{
	if (m_clique.empty())
	{
		find_clique();
	}

	return std::vector<int>();
}

int clique_base::get_clique_size()
{
	if (m_clique.empty())
	{
		find_clique();
	}

	return m_clique.size();
}
