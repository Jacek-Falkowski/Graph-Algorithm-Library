/**
 * @file spanning_tree.cpp
 * @author Jacek Falkowski
 * @brief File contains implementation of a depth-first search algorithm
 */
#include "../include/dfs.h"

#include <algorithm>
#include <stack>
#include <functional>

/**
  * Initialize context
  * @param start: index of starting vertex
  * @param process_vertex_early: callback invoked when node is initially processed
  * @param process_edge: callback invoked when edge is processed
  * @param process_vertex_late: callback invoked when node is lately processed
  */
dfs_data::dfs_data(graph& g,
                vertex_callback&& process_vertex_early, edge_callback&& process_edge,
                vertex_callback&& process_vertex_late)
        :process_vertex_early(process_vertex_early),
         process_edge(process_edge),
         process_vertex_late(process_vertex_late),
         discovered(g.max_index + 1, false),
         processed(g.max_index + 1, false),
         parent(g.max_index + 1, -1) { }

/**
 * Depth-first search implementation based on Steven S. Skiena "The algorithm design manual".
 * @param x: starting vertex
 * @param dfs_context: context that algorithm will process
 * @param data: data needed to run an algorithm
 */
void dfs_impl(graph& g, int x, dfs_data& data)
{
    data.discovered[x] = true;
    data.process_vertex_early(x);

    for (edge* p = g.edges[x]; p != nullptr; p = p->next) {
        int y = p->y;

        if (!data.discovered[y]) {
            data.parent[y] = x;
            data.process_edge(x, y);
            dfs_impl(g, y, data);
        }
    }

    data.processed[x] = true;
    data.process_vertex_late(x);
}

/**
 * Depth-first search implementation based on Steven S. Skiena "The algorithm design manual".
 * @param x: starting vertex
 * @param dfs_context: context that algorithm will process
 * @param data: data needed to run an algorithm
 */
void dfs(graph& g, int start, dfs_data& data)
{
    dfs_impl(g, start, data);
}
