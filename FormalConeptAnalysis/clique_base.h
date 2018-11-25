#pragma once
#include "graph_base.hpp"

class clique_base : public graph_base
{
protected:

	std::vector<int> m_clique;

	void print_clique();

	std::vector<int> get_clique();

	int get_clique_size();

	virtual void find_clique() = 0;

public:
	virtual ~clique_base() = default;

	clique_base(const clique_base&) = delete; // copy constructor
	clique_base& operator=(const clique_base&) = delete; // copy assignment

	clique_base(clique_base&&) = delete;  // move constructor
	clique_base& operator=(clique_base&&) = delete; // move assignment
};

