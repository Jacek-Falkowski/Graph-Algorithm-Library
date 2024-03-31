/**
 * @file spanning_tree.cpp
 * @author Jacek Falkowski
 * @brief File contains implementation of a breath-first search algorithm
 */
#pragma once

#include "../include/graph.h"

#include <algorithm>
#include <stack>
#include <functional>

//! contains data needed to run breadth-first search algorithm
struct bfs_data {
        using vertex_callback = std::function<void(int)>;
        using edge_callback = std::function<void(int, int)>;

        /**
         * Initialize context
         * @param start: index of starting vertex
         * @param process_vertex_early: callback invoked when node is initially processed
         * @param process_edge: callback invoked when edge is processed
         * @param process_vertex_late: callback invoked when node is lately processed
         */
        bfs_data(graph& g,
                vertex_callback&& process_vertex_early, edge_callback&& process_edge,
                vertex_callback&& process_vertex_late);

        vertex_callback process_vertex_early;
        edge_callback process_edge;
        vertex_callback process_vertex_late;

        std::vector<bool> discovered;  //!< a vector that information if a given vertex is discovered
        std::vector<bool> processed;  //!< a vector that information if a given vertex is processed
        std::vector<int> parent; //!< a vector that holds an index of a parent vertex for each of vertices
};

/**
 * Breadth-first search implementation based on Steven S. Skiena "The algorithm design manual".
 * @param x: starting vertex
 * @param dfs_context: context that algorithm will process
 * @param data: data needed to run an algorithm
 */
void bfs(graph& g, int start, bfs_data& data);
