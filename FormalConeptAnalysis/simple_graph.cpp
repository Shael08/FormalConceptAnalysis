#include "simple_graph.hpp"
#include <fstream>

simple_graph::simple_graph(char *file)
{
	read_graph(file);
	m_dim.rows = m_vertices;
	m_dim.cols = m_vertices;
	m_file_name = std::string(file);
}

simple_graph::simple_graph(const std::string &file)
{
	const char* filename = file.c_str();
	read_graph(filename);
	m_dim.rows = m_vertices;
	m_dim.cols = m_vertices;
	m_file_name = file;
}

std::string simple_graph::get_file_name() const
{
	return m_file_name;
}


void simple_graph::read_graph(const char *file) {
	std::ifstream file_;
	file_.open(file);

	if (file_.is_open()) 
	{
		std::string mark;


		while (file_ >> mark) 
		{

			if (mark == "p") 
			{
				std::string tmp;
				int tmp_vertex;
				file_ >> tmp >> tmp_vertex;

				m_vertices = tmp_vertex;
				if (m_vertices == 0) exit(2);
			}

			m_adjacency_matrix.resize(m_vertices, boost::dynamic_bitset<>(m_vertices));
			if (mark == "e") 
			{

				int fv, sv;

				file_ >> fv >> sv;

				m_adjacency_matrix[fv - 1][sv - 1] = true;
				m_adjacency_matrix[sv - 1][fv - 1] = true;
			}

		}

	}
	else 
	{
		exit(1);
	}
}
