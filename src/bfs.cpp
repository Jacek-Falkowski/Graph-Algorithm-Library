/**
 * @file spanning_tree.cpp
 * @author Jacek Falkowski
 * @brief File contains implementation of a breadth-first search algorithm
 */
#include "../include/bfs.h"

#include <algorithm>
#include <queue>
#include <functional>

/**
  * Initialize context
  * @param start: index of starting vertex
  * @param process_vertex_early: callback invoked when node is initially processed
  * @param process_edge: callback invoked when edge is processed
  * @param process_vertex_late: callback invoked when node is lately processed
  */
bfs_data::bfs_data(graph& g,
                vertex_callback&& process_vertex_early, edge_callback&& process_edge,
                vertex_callback&& process_vertex_late)
        :process_vertex_early(process_vertex_early),
         process_edge(process_edge),
         process_vertex_late(process_vertex_late),
         discovered(g.max_index + 1, false),
         processed(g.max_index + 1, false),
         parent(g.max_index + 1, -1) { }

/**
 * Breadth-first search implementation based on Steven S. Skiena "The algorithm design manual".
 * @param x: starting vertex
 * @param dfs_context: context that algorithm will process
 * @param data: data needed to run an algorithm
 */
void bfs_impl(graph& g, int start, bfs_data& data)
{
    std::queue<int> q;
    int x;

    q.push(start);
    data.discovered[start] = true;

    while (!q.empty()) {
        x = q.front();
        q.pop();

        data.process_vertex_early(x);
        data.processed[x] = true;

        for (edge* p = g.edges[x]; p != nullptr; p = p->next) {
            int y = p->y;

            if (!data.processed[y])
                data.process_edge(x, y);

            if (!data.discovered[y]) {
                data.discovered[y] = true;
                q.push(y);
                data.parent[y] = x;
            }
        }
        data.process_vertex_late(x);
    }
}

/**
 * Breadth-first search implementation based on Steven S. Skiena "The algorithm design manual".
 * @param x: starting vertex
 * @param dfs_context: context that algorithm will process
 * @param data: data needed to run an algorithm
 */
void bfs(graph& g, int start, bfs_data& data)
{
    bfs_impl(g, start, data);
}
