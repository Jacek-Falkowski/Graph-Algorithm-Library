/**
 * @file graph.cpp
 * @author Jacek Falkowski
 * @brief File contains implementation of a graph data structure
 */
#include "../include/graph.h"

#include <fstream>

/**
 * Constucts a new edge
 * @param y: index of a vertex
 * @param weight: weight of an edge
 * @param next: a pointer to a next edge in a linked list
 */
edge::edge(int y, double weight, edge* next)
	:y(y), weight(weight), next(next)
{
}

/**
 * Insert new edge at the beggining of the list
 * @param head: head of the linked list
 * @param y: index of a vertex
 * @param weight: weight of an edge
 */
void insert_front(edge*& head, int y, double weight)
{
	head = new edge(y, weight, head);
}

/*
 * Print a linked list.
 * @param head: head of a linked list to be printed
 */
void print_edges(edge* head)
{
	for (; head != nullptr; head = head->next) {
		std::cout << "(" << head->y << ", " << head->weight << ") -> ";
	}

	std::cout << "null" << std::endl;
}

/*
 * Free a linked list.
 * @param head: head of a linked list to be freed
 */
void free_edges(edge* head)
{
	edge* tmp;
	while (head != nullptr) {
		tmp = head;
		head = head->next;
		delete tmp;
	}
}

/**
 * Creates a new instance of a graph data structure
 */
graph::graph()
	:edges(8, nullptr), max_index(-1)
{
}

/**
 * Insert undirected edge x <--> y edge into adjacency list
 * @param x: index of a first vertex
 * @param y: index of a second vertex
 * @param weight: weight of an edge
 */
void add_edge(graph& g, int x, int y, double weight)
{
	int max = std::max(x, y);
	if (max >= (int)g.edges.size()) {
		g.edges.resize(max * 2, nullptr);
	}

	g.max_index = std::max(g.max_index, max);

	insert_front(g.edges[x], y, weight);
	insert_front(g.edges[y], x, weight);
}

/*
 * Print a graph.
 * @param g: graph to be printed
 */
void print_graph(graph& g)
{
	for (size_t i = 0; i < g.edges.size(); i++) {
		if (g.edges[i] == nullptr)
			continue;

		std::cout << i << ": ";
		print_edges(g.edges[i]);
	}
}

/*
 * Free a graph.
 * @param g: graph to be freed
 */
void free_graph(graph& g)
{
	for (size_t i = 0; i < g.edges.size(); i++) {
		free_edges(g.edges[i]);
	}
}

/**
 * Initializes a graph with a data from an input file
 * @param path: path to an input file
 * @param g: graph that will be constructed with a data from a file
 * @return true if a graph was read from an input file successfuly
 */
bool graph_from_file(const std::string& path, graph& g)
{
	std::ifstream ist(path);

	if (!ist) {
		std::cerr << "Error: cannot open input file: " << path << std::endl;
		return false;
	}

	int x;
	int y;
	double weight;
	char ch1, ch2, ch3, ch4;

	while (true) {
		ist >> ch1 >> x >> ch2 >> y >> ch3 >> weight >> ch4;

		if (ist) {
			if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') {
				std::cerr << "Error: error while reading input file: " << path << std::endl;
				return false;
			}
			add_edge(g, x, y, weight);
		}
		if (ist.peek() == ',')
			ist.get();

		if (ist.eof())
			break;

		if (ist.fail()) {
			std::cerr << "Error: error while reading input file: " << path << std::endl;
			return false;
		}
	}

	return true;
}