/**
 * @file main.cpp
 * @author Jacek Falkowski
 * @brief File contains implementation of a main function, command-line arguments and files handling
 */
#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <iomanip>
#include "../include/graph.h"
#include "../include/spanning_tree.h"

std::string help =
R"(Calculate maximum spanning tree of the provided input graph
Usage: maxspanningtree [OPTION]...
Program options:
--input -i=<val>:            input file containg the graph description.
--output -o=<val>:           output file containg the maximum spanning tree of the provided input graph.
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
		{"output", required_argument, nullptr, 'o'},
        {nullptr, no_argument, nullptr, 0}
    };

	bool has_ifile = false;
	bool has_ofile = false;
	std::string input_file_name;
	std::string output_file_name;

    while (true) {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (opt == -1)
            break;

        switch (opt) {
        case 'i':
			input_file_name = optarg;
			has_ifile = true;
        break;
		case 'o':
			output_file_name = optarg;
			has_ofile = true;
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

	if (!has_ofile) {
        std::cerr << "Error: output file not provided" << std::endl;
		return 0;
    }

	graph g;

	if (graph_from_file(input_file_name, g) == false)
		return 0;

	int start = -1;
	for (size_t i = 0; i < g.edges.size(); i++) {
		if (g.edges[i] != nullptr) {
			start = i;
			break;
		}
	}

	if (start == -1) {
		std::cerr << "Error: input graph is empty" << std::endl;
	}

	mst_data data(g);

	if (start == -1) {
		std::cerr << "Error: input graph is empty" << std::endl;
	}

	maximum_spanning_tree(g, start, data);

	if (print_mst_to_file(data, output_file_name) == false)
		return 0;

	free_graph(g);
	return 0;
}

