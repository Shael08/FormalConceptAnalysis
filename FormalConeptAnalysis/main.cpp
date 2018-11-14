#include "bipartite_graph.hpp"
#include "bron_kerbosch.hpp"
#include "extended_bipartite_graph.hpp"
#include "ostergard.hpp"
#include "graph.hpp"

int main(int argc, char *argv[])
{
	const bipartite_graph bipartite_graph(10, 10);
	const extended_bipartite_graph ext_graph(bipartite_graph);

	const graph simple_graph(argv[1]);


	bron_kerbosch bron_kerbosch_handler(ext_graph);

	//bron_kerbosch_handler.start();

	ostergard ostergard_handler(simple_graph);
	ostergard_handler.start();
	

	return 0;
}

