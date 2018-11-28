#include "iterated_greedy_with_dsatur.hpp"
#include <iostream>

iterated_greedy_with_dsatur::iterated_greedy_with_dsatur(const simple_graph & t_graph)
{
	this->m_adjacency_matrix = t_graph.get_universe();
	this->m_vertices = m_adjacency_matrix.size();
	this->m_file_name = t_graph.get_file_name();
}

#pragma region DSATUR

void iterated_greedy_with_dsatur::init_dsatur()
{
	std::cout << "\nColoring with DSATUR algorithm \n" << std::endl;

	const std::clock_t start = std::clock();

	const int result = dsatur().size();

	const double duration = double(double(std::clock()) - start) / double(CLOCKS_PER_SEC);

	std::cout << "Running time: " << duration << '\n';

	std::cout << "The graph can be colored with: " << result << " colors \n" << std::endl;
}

std::vector<color_class> iterated_greedy_with_dsatur::dsatur()
{
	std::vector<color_class> color_classes(1);
	auto*available_colors = new bool[m_vertices];
	auto* result = new int[m_vertices];

	for (int i = 0; i < m_vertices; i++)
	{
		available_colors[i] = true;
		result[i] = -1;
	}

	color_classes[0].elements.push_back(0);
	result[0] = 0;

	for (int n = 0; ; n++)
	{

		const int vertices_with_maximal_colored_neighbors = find_vertex_with_maximal_color_degree(color_classes, result);

		if (vertices_with_maximal_colored_neighbors == -1) break;

		for (int i = 0; i < m_vertices; i++)
		{
			if (m_adjacency_matrix[vertices_with_maximal_colored_neighbors][i] && result[i] != -1)
			{
				available_colors[result[i]] = false;
			}
		}

		int c;
		for (c = 0; c < m_vertices; c++)
		{
			if (available_colors[c]) break;
		}

		result[vertices_with_maximal_colored_neighbors] = c;
		if (color_classes.size() < unsigned(c + 1)) color_classes.resize(c + 1);

		color_classes[c].elements.push_back(vertices_with_maximal_colored_neighbors);

		for (int i = 0; i < m_vertices; i++)
		{
			available_colors[i] = true;
		}

	}

	delete[] result;
	delete[] available_colors;

	return color_classes;
}

int iterated_greedy_with_dsatur::find_vertex_with_maximal_color_degree(std::vector<color_class> color_classes, const int* result)
{
	int maximal_color_degree_vertex = -1;
	int maximal_color_degree = 0;

	for (int i = 0; i < m_vertices; i++)
	{
		if (result[i] == -1)
		{
			int color_degree = 0;

			for (auto& color_class : color_classes)
			{
				bool found = false;
				for (auto it = color_class.elements.begin(); it != color_class.elements.end() && !found; ++it)
				{

					if (m_adjacency_matrix[i][*it])
					{
						color_degree++;
						found = true;
					}

				}

			}

			if (color_degree > maximal_color_degree)
			{
				maximal_color_degree = color_degree;
				maximal_color_degree_vertex = i;
			}


		}
	}

	return maximal_color_degree_vertex;
}

#pragma endregion 

#pragma region iterated_greedy_coloring

std::string iterated_greedy_with_dsatur::iterated_greedy_coloring()
{
	std::cout << "\nColoring with iterated greedy algorithm \n" << std::endl;

	std::vector<color_class> color_classes = dsatur();

	m_min_color = int(color_classes.size());

	m_counter = 0;

	const std::clock_t start = std::clock();

	m_out_file.open(m_file_name + ".csv");

	m_out_file << ",colors,,inner iterations,outer iterations\n";

	std::string out_string;

	for (int j = 0; j < 15; ++j) 
	{
		std::cout << "loop: " << j << std::endl;
		m_out_file << "loop: " << j << std::endl;
		for (int i = 0; i < 10; ++i)
		{
			m_min_color = int(color_classes.size());
			iterate(color_classes, iteration_type(i));

			//out_string += std::to_string(m_min_color) + "," + std::to_string(m_counter) + "," + std::to_string(duration) + ",";

			//m_out_file << iteration_type_name(iteration_type(i)) << "," << m_min_color << "\n";
		}
	}
	const double duration = double(double(std::clock()) - start) / double(CLOCKS_PER_SEC);

	m_out_file << "\nNumber of iterations:," << m_counter << "\n";

	m_out_file << "Running time:," << duration << '\n';
	std::cout << "Running time: " << duration << '\n';

	std::cout << "The graph can be colored with: " << m_min_color << " colors \n" << std::endl;
	m_out_file << "The graph can be colored with:," << m_min_color << "\n";

	m_out_file.close();

	return out_string;
}

void iterated_greedy_with_dsatur::iterate(std::vector<color_class> &color_classes, const iteration_type type)
{

	if (type == random)
	{
		sort_random_order(color_classes);
		const int min_color = recolor_color_class(color_classes);

		if (min_color < m_min_color)
		{
			m_min_color = min_color;
			std::cout << iteration_type_name(type) << m_min_color << "\treached at:\t" << 0 << " / " << m_counter << std::endl;
			m_out_file << iteration_type_name(type) << "," << m_min_color << ",reached at:," << 0 << "," << m_counter << "\n";
		}
	}
	else 
	{
		int iterations_index = 0;

		std::pair<bool, int> periodic = std::make_pair(false, 0);

		int local_counter = 0;

		while (!periodic.first && iterations_index < fib_max)
		{
			const int iterations = m_fib[iterations_index];

			std::vector<int> array_of_sums;

			for (int k = 0; k < iterations; ++k)
			{
				switch (type)
				{
				case reverse: std::reverse(color_classes.begin(), color_classes.end());
					break;
				case increasing: std::sort(color_classes.begin(), color_classes.end(), sort_increasing_size);
					break;
				case decreasing: std::sort(color_classes.begin(), color_classes.end(), sort_decreasing_size);
					break;
				case increasing_degree:
					calculate_color_classes_degree(color_classes);
					std::sort(color_classes.begin(), color_classes.end(), sort_increasing_degree);
					break;
				case decreasing_degree:
					calculate_color_classes_degree(color_classes);
					std::sort(color_classes.begin(), color_classes.end(), sort_decreasing_degree);
					break;
				case increasing_color_degree_v1:
					calculate_color_degree(color_classes);
					std::sort(color_classes.begin(), color_classes.end(), sort_increasing_color_degree_v1);
					break;
				case decreasing_color_degree_v1:
					calculate_color_degree(color_classes);
					std::sort(color_classes.begin(), color_classes.end(), sort_decreasing_color_degree_v1);
					break;
				case increasing_color_degree_v2:
					calculate_color_degree(color_classes);
					std::sort(color_classes.begin(), color_classes.end(), sort_increasing_color_degree_v2);
					break;
				case decreasing_color_degree_v2:
					calculate_color_degree(color_classes);
					std::sort(color_classes.begin(), color_classes.end(), sort_decreasing_color_degree_v2);
					break;
				default: return;
				}

				const int min_color = recolor_color_class(color_classes);

				if (min_color < m_min_color)
				{
					m_min_color = min_color;
					std::cout << iteration_type_name(type) << m_min_color << "\treached at:\t" << local_counter << " / " << m_counter << std::endl;
					m_out_file << iteration_type_name(type) << "," << m_min_color << ",reached at:," << local_counter << "," << m_counter << "\n";
				}

				int sum = 0;

				for (unsigned j = 0; j < color_classes.size(); ++j)
				{
					sum += (j + 1) * color_classes[j].elements.size();
				}

				array_of_sums.push_back(sum);

			}

			periodic = is_periodic(array_of_sums);

			if (periodic.first)
			{
				std::cout << iteration_type_name(type) << "\tperiodic at:\t" << periodic.second << " / " << m_counter << std::endl;
				m_out_file << iteration_type_name(type) << ",,periodic at:," << periodic.second << "," << m_counter << "\n";
				array_of_sums.clear();
			}
			else
			{
				++iterations_index;
			}
			local_counter++;
		}
	}
}

std::pair<bool, int> iterated_greedy_with_dsatur::is_periodic(const std::vector<int> &array_of_sums)
{
	bool loop_found = false;
	int loop_at_index = -2;
	const unsigned iterations = array_of_sums.size();
	for (unsigned i = 0; i < iterations; ++i)
	{
		for (unsigned j = i + 1; j < iterations; ++j)
		{
			if (array_of_sums[i] == array_of_sums[j])
			{
				const unsigned d = j - i;
				if (iterations - 2 * d > i)
				{
					loop_found = true;
					for (unsigned k = i; k < iterations - d; ++k)
					{
						if (array_of_sums[k] != array_of_sums[k + d])
						{
							loop_found = false;
							break;
						}

					}
				}

				if (loop_found)
					break;
			}
		}
		if (loop_found)
		{
			loop_at_index = i;
			break;
		}
	}


	return std::make_pair(loop_found, loop_at_index);
}

int iterated_greedy_with_dsatur::recolor_color_class(std::vector<color_class> &color_classes)
{
	auto* result = new int[m_vertices];
	auto* available_colors = new bool[m_vertices];

	for (int i = 0; i < m_vertices; i++)
	{
		result[i] = -1;
		available_colors[i] = false;
	}


	for (unsigned i = 0; i < color_classes.size(); i++)
	{
		for (auto it = color_classes[i].elements.begin(); it != color_classes[i].elements.end(); ++it)
		{
			if (i == 0 && it == color_classes[0].elements.begin()) result[color_classes[0].elements[0]] = 0;
			for (int j = 0; j < m_vertices; j++)
			{
				if (m_adjacency_matrix[(*it)][j] == 1 && result[j] != -1)
				{
					available_colors[result[j]] = true;
				}

			}

			int cr;
			for (cr = 0; cr < m_vertices; cr++)
				if (!available_colors[cr])
					break;

			result[*it] = cr;


			for (int j = 0; j < m_vertices; j++)
			{
				available_colors[j] = false;
			}

		}

	}

	int max = 0;
	for (int u = 0; u < m_vertices; u++)
	{
		if (result[u] > max) max = result[u];
	}

	max += 1;

	for (unsigned i = 0; i < max; i++)
	{
		color_classes[i].elements.clear();
	}

	color_classes.resize(max);

	for (int i = 0; i < m_vertices; i++)
	{
		color_classes[result[i]].elements.push_back(i);
	}

	//for (int i = 0; i < max; i++)
	//{
	//	std::cout << i << ": ";
	//	for (auto it = color_classes[i].begin(); it != color_classes[i].end(); ++it)
	//	{
	//		std::cout << *it << " ";
	//	}
	//	std::cout << std::endl;
	//}

	delete[] result;
	delete[] available_colors;

	m_counter++;

	return max;
}

void iterated_greedy_with_dsatur::calculate_color_classes_degree(std::vector<color_class> &color_classes)
{
	for (auto& color_class : color_classes)
	{
		int sum = 0;
		for (auto it_2 = color_class.elements.begin(); it_2 != color_class.elements.end(); ++it_2)
		{
			sum += m_adjacency_matrix[(*it_2)].count();
		}
		color_class.degree = sum;
	}
}

void iterated_greedy_with_dsatur::calculate_color_degree(std::vector<color_class> &color_classes)
{
	std::vector<boost::dynamic_bitset<> > color_degrees;
	color_degrees.resize(color_classes.size(), boost::dynamic_bitset<>(color_classes.size()));

	for (unsigned i = 0; i < color_classes.size(); ++i)
	{
		bool neighbors = false;

		for (unsigned k = i + 1; k < color_classes.size(); ++k)
		{
			if (!color_degrees[i][k])
			{
				for (unsigned j = 0; j < color_classes[i].elements.size(); ++j)
				{
					for (unsigned l = 0; l < color_classes[k].elements.size(); ++l)
					{
						//std::cout << color_classes[i].elements[j] << " " << color_classes[k].elements[l] << std::endl;
						if (m_adjacency_matrix[color_classes[i].elements[j]][color_classes[k].elements[l]])
						{
							color_degrees[i][k] = color_degrees[k][i] = true;
							neighbors = true;
							break;
						}
					}
					if (neighbors) break;
				}
			}
		}
	}

	for (unsigned i = 0; i < color_classes.size(); ++i)
	{
		color_classes[i].color_degree = color_degrees[i].count();
		//std::cout << i << " color_degree: " << color_degrees[i].count() << " " << color_classes[i].elements.size() << std::endl;
	}
}

bool iterated_greedy_with_dsatur::sort_increasing_size(const color_class &class_1, const color_class &class_2) {
	return class_1.elements.size() < class_2.elements.size();
}

bool iterated_greedy_with_dsatur::sort_decreasing_size(const color_class &class_1, const color_class &class_2) {
	return class_1.elements.size() > class_2.elements.size();
}

bool iterated_greedy_with_dsatur::sort_increasing_degree(const color_class &class_1, const color_class &class_2)
{
	return class_1.degree < class_2.degree;
}

bool iterated_greedy_with_dsatur::sort_decreasing_degree(const color_class &class_1, const color_class &class_2)
{
	return class_1.degree > class_2.degree;
}

bool iterated_greedy_with_dsatur::sort_increasing_color_degree_v1(const color_class &class_1, const color_class &class_2)
{
	return class_1.color_degree < class_2.color_degree;
}

bool iterated_greedy_with_dsatur::sort_decreasing_color_degree_v1(const color_class &class_1, const color_class &class_2)
{
	return class_1.color_degree > class_2.color_degree;
}

bool iterated_greedy_with_dsatur::sort_increasing_color_degree_v2(const color_class &class_1, const color_class &class_2)
{
	return class_1.color_degree + class_1.elements.size() < class_2.color_degree + class_2.elements.size();
}

bool iterated_greedy_with_dsatur::sort_decreasing_color_degree_v2(const color_class &class_1, const color_class &class_2)
{
	return class_1.color_degree + class_1.elements.size() > class_2.color_degree + class_2.elements.size();
}


void iterated_greedy_with_dsatur::sort_random_order(std::vector<color_class>& color_classes)
{
	for (unsigned i = 0; i < color_classes.size(); i++)
	{
		const int new_pos = ((i + 1) * 401) % color_classes.size();

		const auto temp = color_classes[new_pos];
		color_classes[new_pos] = color_classes[i];
		color_classes[i] = temp;
	}
}


#pragma endregion 