/**
 * @file main.cpp
 * @author Jacek Falkowski
 * @brief File contains implementation of a main function, command-line arguments and files handling
 */
#include <iostream>
#include <fstream>
#include <getopt.h>
#include <string>
#include <iomanip>
#include "../include/graph.h"
#include "../include/bfs.h"

std::string help =
R"(Traverse input graph using breadth-first search algorithm.
Usage: bfs [OPTION]...
Program options:
--input -i=<val>:            input file containg the graph description.
--start -s=<val>:            starting index of the provided input graph.
--help -h:                   show help
)";

/**
 * Main program's function
 * @param argc: number of command line arguments
 * @param argv: an array of command line arguments
 * @return return zero on program's exit
 */
int main(int argc, char** argv)
{
    if (argc == 1) {
        std::cerr << help;
		return 0;
    }

    const char* const short_opts = "i:s:";

    const option long_opts[] = {
        {"input", required_argument, nullptr, 'i'},
        {"start", required_argument, nullptr, 's'},
        {nullptr, no_argument, nullptr, 0}
    };

	bool has_ifile = false;
	bool has_start = false;
	std::string input_file_name;
	int start = 0;

    while (true) {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (opt == -1)
            break;

        switch (opt) {
        case 'i':
			input_file_name = optarg;
			has_ifile = true;
        break;
		case 's':
			start = std::atoi(optarg);
			has_start = true;
        break;
        case 'h':
        case '?':
        default:
			std::cout << help << std::endl;
			return 0;
        break;
        }
    }

	if (!has_ifile) {
        std::cerr << "Error: input file not provided" << std::endl;
		return 0;
    }

	if (!has_start) {
        std::cerr << "Error: start index not provided" << std::endl;
		return 0;
    }

	graph g;

	if (graph_from_file(input_file_name, g) == false)
		return 0;

	auto process_vertex_early = [&] (int v) {
		std::cout << "visiting vertex: " << v << std::endl;
	};
	auto process_edge = [&] (int x, int y) {
		std::cout << "visiting edge: (" << x << ", " << y << ")" << std::endl;
	};
	auto process_vertex_late = [&] (int v) {
		std::cout << "exiting vertex: " << v << std::endl;
	};

	bfs_data data(g, process_vertex_early, process_edge, process_vertex_late);

    bfs(g, start, data);

	free_graph(g);
	return 0;
}
