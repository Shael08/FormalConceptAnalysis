#include "bipartite_graph.hpp"
#include "bron_kerbosch.hpp"
#include "extended_bipartite_graph.hpp"
#include "ostergard.hpp"
#include "simple_graph.hpp"

int main(int argc, char *argv[])
{

	//const simple_graph graph(argv[1]);
	//ostergard ostergard_handler(graph);
	//ostergard_handler.start();

	const bipartite_graph bipartite_graph(15, 15);
	bipartite_graph.print_graph();
	ostergard ostergard_bipartite_handler(bipartite_graph);
	ostergard_bipartite_handler.start_bipartite();

	return 0;
}
