/**
 * @file spanning_tree.h
 * @author Jacek Falkowski
 * @brief File contains declaration of a maximum spanning tree algorithm' functions
 */
#pragma once

#include "../include/graph.h"

//! contains minimum spanning tree after running the Prim's algorithm
struct mst_data {
	/**
	 * Constucts maximum spanning tree's data
	 * @param g: maximum spanning tree's data to be constructed.
	 */
	mst_data(graph& g);

	std::vector<bool> intree; //!< a vector that information if a given vertex is already in a spanning tree
	std::vector<double> distance; //!< a vector that information of a weight of a vertex in a spanning tree
	std::vector<int> parent; //!< a vector that holds an index of a parent vertex for each of vertices
};

/**
 * Calculate a maximum spanning tree for a given graph using Prim's algorithm
 * @param g: graph on which minimum spanning tree will be calculated
 * @param start: arbitrary starting index
 * @param data: data needed to run an algorithm
 */
void maximum_spanning_tree(graph& g, int start, mst_data& data);

/**
 * Prints a minimum spanning tree to an input file
 * @param data: contains a minimum spanning tree to be printed
 * @param file: output file to which maximum spanning tree will be printed
 * @return true if minimum spanning tree was output to file successfuly
 */
bool print_mst_to_file(mst_data& data, const std::string& file);
