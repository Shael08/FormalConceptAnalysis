#include "bipartite_graph.hpp"
#include "bron_kerbosch.hpp"

int main()
{
	const bipartite_graph graph(10, 10);

	//graph.print_graph();

	bron_kerbosch bron_kerbosch_handler(graph);

	//bron_kerbosch_handler.print_extended_graph();

	bron_kerbosch_handler.start();

	return 0;
}

