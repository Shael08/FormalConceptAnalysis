#include "bipartite_graph.hpp"
#include "bron_kerbosch.hpp"
#include "extended_bipartite_graph.hpp"
#include "ostergard.hpp"
#include "graph.hpp"

int main(int argc, char *argv[])
{
	const bipartite_graph bipartite_graph(5, 6);
	const extended_bipartite_graph ext_graph(bipartite_graph);

	const graph simple_graph(argv[1]);

	//bron_kerbosch bron_kerbosch_handler(ext_graph);
	//bron_kerbosch_handler.start();

	bipartite_graph.print_graph();

	ostergard ostergard_handler(bipartite_graph);
	ostergard_handler.start_bipartite();

	return 0;
}

