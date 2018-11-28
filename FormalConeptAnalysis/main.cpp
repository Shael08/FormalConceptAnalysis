#include "bipartite_graph.hpp"
#include "bron_kerbosch.hpp"
#include "extended_bipartite_graph.hpp"
#include "ostergard.hpp"
#include "simple_graph.hpp"
#include "iterated_greedy_with_dsatur.hpp"
#include <iostream>

int main(int argc, char *argv[])
{

	std::string files[12] = { "brock200_1.clq",
						"brock800_2.clq",
						"brock800_4.clq",
						"C250.9.clq",
						"C500.9.clq",
						"hamming10-4.clq",
						"keller5.clq",
						"keller6.clq",
						"monoton-8.clq",
						"monoton-9.clq",
						"p_hat1500-3.clq",
						"p_hat700-3.clq" };


	//std::string out_string;

	//std::ofstream m_out_file;

	//m_out_file.open("test.csv");

	for (int i = 0; i < 12; ++i)
	{
		std::cout << files[i] << std::endl;

		simple_graph graph(files[i]);
		iterated_greedy_with_dsatur coloring_handler(graph);
		coloring_handler.iterated_greedy_coloring();
		//out_string += files[i] + "," + coloring_handler.iterated_greedy_coloring() + "\n";
	}

	//m_out_file << out_string;
	//m_out_file.close();

	return 0;
}
