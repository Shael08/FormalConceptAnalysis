#pragma once
#include "graph_base.hpp"

class simple_graph : public graph_base
{
private:
	std::string m_file_name;
	void read_graph(const char* file);

public:

	explicit simple_graph(char *file);
	explicit simple_graph(const std::string &file);
	~simple_graph() = default;

	simple_graph(const simple_graph&) = delete; // copy constructor
	simple_graph& operator=(const simple_graph&) = delete; // copy assignment
	simple_graph(simple_graph&&) = delete;  // move constructor
	simple_graph& operator=(simple_graph&&) = delete; // move assignment

	std::string get_file_name() const;
};

