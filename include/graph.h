/**
 * @file graph.h
 * @author Jacek Falkowski
 * @brief File contains declaration of graph data structure
 */
#pragma once

#include <vector>
#include <iostream>

//! Singly-linked list of graph's edges
struct edge {
	/**
	 * Constucts a new edge
	 * @param y: index of a vertex
	 * @param weight: weight of an edge
	 * @param next: a pointer to a next edge in a linked list
	 */
	edge(int y, double weight, edge* next);

	int y; //!< index of a vertex to which an edge is pointing
	double weight; //!< weight of an edge
	struct edge* next; //!< a pointer to next element in the linked list
};

/**
 * Insert new edge at the beggining of the list
 * @param head: head of the linked list
 * @param y: index of a vertex
 * @param weight: weight of an edge
 */
void insert_front(edge*& head, int y, double weight);

/*
 * Print a linked list.
 * @param head: head of a linked list to be printed
 */
void print_edges(edge* head);

/*
 * Free a linked list.
 * @param head: head of a linked list to be freed
 */
void free_edges(edge* head);

//! Graph data structure implemented using adjacency list
struct graph {
	/**
	 * Creates a new instance of a graph data structure
	 */
	graph();

	std::vector<edge*> edges; //!< list of neighbours of each vertex
	int max_index; //!< maximal index of a vertex in a graph
};

/**
 * Insert undirected edge x <--> y edge into adjacency list
 * @param x: index of a first vertex
 * @param y: index of a second vertex
 * @param weight: weight of an edge
 */
void add_edge(graph& g, int x, int y, double weight);

/*
 * Print a graph.
 * @param g: graph to be printed
 */
void print_graph(graph& g);

/*
 * Free a graph.
 * @param g: graph to be freed
 */
void free_graph(graph& g);

/**
 * Initializes a graph with a data from an input file
 * @param path: path to an input file
 * @param g: graph that will be constructed with a data from a file
 * @return true if a graph was read from an input file successfuly
 */
bool graph_from_file(const std::string& path, graph& g);
