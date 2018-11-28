#pragma once
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include "simple_graph.hpp"
#include <fstream>

struct color_class
{
	std::vector<int> elements;
	int degree{};
	int color_degree{};
};


class iterated_greedy_with_dsatur
{
private:
	static const int fib_max = 9;

	int m_min_color{};
	int m_counter{};
	int m_vertices;
	const int m_fib[fib_max] = { 8, 13, 21, 34, 55, 89, 144, 233, 377 /*, 610, 987, 1597, 2584, 4181, 6765*/ }; //28644
	std::string m_file_name;
	std::ofstream m_out_file;
	std::vector<boost::dynamic_bitset<> > m_adjacency_matrix;

	enum iteration_type
	{
		reverse = 0,
		increasing = 1,
		decreasing = 2,
		increasing_degree = 3,
		decreasing_degree = 4,
		increasing_color_degree_v1 = 5,
		decreasing_color_degree_v1 = 6,
		increasing_color_degree_v2 = 7,
		decreasing_color_degree_v2 = 8,
		random = 9
	};

	static std::string iteration_type_name(const iteration_type type)
	{
		switch (type)
		{
		case reverse: return "reverse: ";
		case increasing: return "increase: ";
		case decreasing: return "decrease: ";
		case increasing_degree: return "inc_deg: ";
		case decreasing_degree: return "dec_deg: ";
		case increasing_color_degree_v1: return "inc_col_deg_v1: ";
		case decreasing_color_degree_v1: return "dec_col_deg_v1: ";
		case increasing_color_degree_v2: return "inc_col_deg_v2: ";
		case decreasing_color_degree_v2: return "dec_col_deg_v2: ";
		case  random: return "random: ";
		default: return "";
		}
	}

	std::vector<color_class> dsatur();

	int find_vertex_with_maximal_color_degree(std::vector<color_class> color_classes, const int * result);

	void iterate(std::vector<color_class>& color_classes, const iteration_type type);

	void calculate_color_classes_degree(std::vector<color_class>& color_classes);

	void calculate_color_degree(std::vector<color_class>& color_classes);

	int recolor_color_class(std::vector<color_class>& color_classes);

	static std::pair<bool, int> is_periodic(const std::vector<int>& array_of_sums);

	static bool sort_increasing_size(const color_class &class_1, const color_class &class_2);

	static bool sort_decreasing_size(const color_class &class_1, const color_class &class_2);

	static bool sort_increasing_degree(const color_class &class_1, const color_class &class_2);

	static bool sort_decreasing_degree(const color_class &class_1, const color_class &class_2);

	static bool sort_decreasing_color_degree_v1(const color_class & class_1, const color_class & class_2);

	static bool sort_increasing_color_degree_v1(const color_class & class_1, const color_class & class_2);

	static bool sort_decreasing_color_degree_v2(const color_class & class_1, const color_class & class_2);

	static bool sort_increasing_color_degree_v2(const color_class & class_1, const color_class & class_2);

	static void sort_random_order(std::vector<color_class>& color_classes);

public:
	explicit iterated_greedy_with_dsatur(const simple_graph &t_graph);

	~iterated_greedy_with_dsatur() = default;

	iterated_greedy_with_dsatur(const iterated_greedy_with_dsatur&) = delete; // copy constructor
	iterated_greedy_with_dsatur& operator=(const iterated_greedy_with_dsatur&) = delete; // copy assignment

	iterated_greedy_with_dsatur(iterated_greedy_with_dsatur&&) = delete;  // move constructor
	iterated_greedy_with_dsatur& operator=(iterated_greedy_with_dsatur&&) = delete; // move assignment


	void init_dsatur();
	std::string iterated_greedy_coloring();
};

