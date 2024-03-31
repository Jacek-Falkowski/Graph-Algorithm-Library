/**
 * @file spanning_tree.cpp
 * @author Jacek Falkowski
 * @brief File contains implementation of a maximum spanning tree algorithm
 */
#include "../include/spanning_tree.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

/**
 * Constucts maximum spanning tree's data
 * @param g: maximum spanning tree's data to be constructed.
 */
mst_data::mst_data(graph& g)
	:intree(g.max_index + 1, false),
	 distance(g.max_index + 1, std::numeric_limits<double>::min()),
	 parent(g.max_index + 1, -1)
{
}

/**
 * Calculate a maximum spanning tree for a given graph using Prim's algorithm
 * @param g: graph on which minimum spanning tree will be calculated
 * @param start: arbitrary starting index
 * @param data: data needed to run an algorithm
 * @param intree: a vector that information if a given vertex is already in a spanning tree
 * @param distance: a vector that information of a weight of a vertex in a spanning tree
 * @param parent: a vector that holds an index of a parent vertex for each of vertices
 */
void maximum_spanning_tree_impl(graph& g, int start, std::vector<bool>& intree,
	std::vector<double>& distance, std::vector<int>& parent)
{
	int x;
	int y;
	double weight;
	double dist;

	distance[start] = 0;
	x = start;

	while (intree[x] == false) {
		intree[x] = true;

		for (edge* p = g.edges[x]; p != nullptr; p = p->next) {
			y = p->y;
			weight = p->weight;
			if ((weight > distance[y]) && (intree[y] == false)) {
				distance[y] = weight;
				parent[y] = x;
			}
		}
		x = 0;
		dist = std::numeric_limits<double>::min();

		for (int i = 0; i <= g.max_index; i++) {
			if ((intree[i] == false) && (dist < distance[i])) {
				dist = distance[i];
				x = i;
			}
		}
	}
}

/**
 * Calculate a maximum spanning tree for a given graph using Prim's algorithm
 * @param g: graph on which minimum spanning tree will be calculated
 * @param start: arbitrary starting index
 * @param data: data needed to run an algorithm
 */
void maximum_spanning_tree(graph& g, int start, mst_data& data)
{
	maximum_spanning_tree_impl(g, start, data.intree, data.distance, data.parent);
}

/**
 * Prints a minimum spanning tree to an input file
 * @param data: contains a minimum spanning tree to be printed
 * @param file: output file to which maximum spanning tree will be printed
 * @return true if minimum spanning tree was output to file successfuly
 */
bool print_mst_to_file(mst_data& data, const std::string& file)
{
	std::ofstream ost(file);
	if (!ost) {
		std::cerr << "Error: cannot open output file: " << file << std::endl;
		return false;
	}

	for (size_t i = 0; i < data.intree.size(); i++) {
		if (data.parent[i] != -1) {
			ost << "(" << data.parent[i]<< ", " << i
				<< ", " << data.distance[i] << ")," << std::endl;

		}
	}

	return true;
}
