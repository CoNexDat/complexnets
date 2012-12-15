#include <QtGui/QApplication>

#include "ComplexNetsGui/inc/mainwindow.h"
#include "ComplexNetsCmd/cmdline.h"
#include "ComplexNetsCmd/cmdmessages.h"
#include "ComplexNetsCmd/ProgramState.h"

#define ERROR_EXIT		delete state; return EXIT_FAILURE;
#define VALIDATE_POS(n)	if ((n) <= 0) { usageErrorMessage("The specified parameter cannot be negative or zero."); ERROR_EXIT; }
#define VALIDATE_P(p)	if ((p) <= 0 || (p) > 1) { usageErrorMessage("The specified parameter cannot be negative, zero or greater than one."); ERROR_EXIT; }

int main(int argc, char* argv[])
{
	if (argc == 1) {
		// We don't have arguments, we start the graphical interface.

	    QApplication a(argc, argv);
	    ComplexNetsGui::MainWindow w;
	    w.show();
	    return a.exec();

	} else {
		// We read the arguments sent at the command line.
		ProgramState *state = new ProgramState();

		struct gengetopt_args_info *args_info = (struct gengetopt_args_info *) malloc(sizeof(struct gengetopt_args_info));
		
		if (cmdline_parser(argc, argv, args_info) != 0) {
			usageErrorMessage("There was an error reading from the command line.");
			ERROR_EXIT;
		}

		if (args_info->input_file_given) {
			if (args_info->erdos_given || args_info->barabasi_given || args_info->hot_given || args_info->molloy_given) {
				usageErrorMessage("Cannot load a graph from an input file and generate a model at the same time.");
				ERROR_EXIT;
			}

			if (args_info->weighted_given) {
				state->setWeighted(true);
			}

			string path = args_info->input_file_arg;

			try {
				state->readGraphFromFile(path.c_str());
				cout << "Succesfully read graph from file " + path + "\n";
			} catch (const FileNotFoundException& e) {
				errorMessage("The specified input was not found in the filesystem.");
				ERROR_EXIT;
			} catch (const DuplicatedEdgeLoading& ex) {
				errorMessage("The specified input file has duplicated edges.");
				ERROR_EXIT;
			} catch (...) {
				errorMessage("There were problems reading the input file.");
				ERROR_EXIT;
			}

		} else if (args_info->erdos_given) {
			if (!args_info->n_given) {
				usageErrorMessage("Erdos-Renyi graph generation requires a number of nodes.");
				ERROR_EXIT;
			}

			if (!args_info->p_given) {
				usageErrorMessage("Erdos-Renyi graph generation requires a probability.");
				ERROR_EXIT;
			}

			int n = args_info->n_arg;
			float p = args_info->p_arg;
			VALIDATE_POS(n);
			VALIDATE_P(p);

			state->setErdosRenyiGraph(n, p);
			cout << "Succesfully created an Erdos-Renyi graph with " + to_string(n) + " nodes.\n";

		} else if (args_info->barabasi_given) {
			if (!args_info->m0_given) {
				usageErrorMessage("Barabasi-Albert graph generation requires an initial number of nodes.");
				ERROR_EXIT;
			}

			if (!args_info->m_given) {
				usageErrorMessage("Barabasi-Albert graph generation requires a number of nodes to attach with new nodes.");
				ERROR_EXIT;
			}

			if (!args_info->n_given) {
				usageErrorMessage("Barabasi-Albert graph generation requires a number of nodes.");
				ERROR_EXIT;
			}

			int n = args_info->n_arg;
			int m0 = args_info->m0_arg;
			int m = args_info->m_arg;
			VALIDATE_POS(n);
			VALIDATE_POS(m0);
			VALIDATE_POS(m);

			if (m > m0) {
				usageErrorMessage("The number of nodes to attach cannot be greater than the initial number of nodes.");
				ERROR_EXIT;
			}

			state->setBarabasiAlbertGraph(m0, m, n);
			cout << "Succesfully created a Barabasi-Albert graph with " + to_string(n) + " nodes.\n";
		} else if (args_info->hot_given) {
			if (!args_info->n_given) {
				usageErrorMessage("Extended Hot graph generation requires a number of nodes.");
				ERROR_EXIT;
			}

			if (!args_info->m_given) {
				usageErrorMessage("Extended Hot graph generation requires the number of edges in each new vertex.");
				ERROR_EXIT;
			}

			if (!args_info->xi_given) {
				usageErrorMessage("Extended Hot graph generation requires the parameter used to select the neighbors for a new vertex.");
				ERROR_EXIT;
			}

			if (!args_info->q_given) {
				usageErrorMessage("Extended Hot graph generation requires the number of edges added in the graph after of connect a vertex.");
				ERROR_EXIT;
			}

			if (!args_info->r_given) {
				usageErrorMessage("Extended Hot graph generation requires the parameter user to selected the edges in the graph after connecting a vertex.");
				ERROR_EXIT;
			}

 			int n = args_info->n_arg;
 			int m = args_info->m_arg;
 			float xi = args_info->xi_arg;
 			int q = args_info->q_arg;
 			float r = args_info->r_arg;
 			VALIDATE_POS(n);
 			VALIDATE_POS(m);
 			VALIDATE_POS(q);
 			VALIDATE_POS(xi);
 			VALIDATE_POS(r);

 			state->setExtendedHotGraph(m, n, xi, q, r);
 			cout << "Succesfully created an Extended Hot graph with " + to_string(n) + " nodes.\n";

		} else if (args_info->molloy_given) {
			cout << "Molloy option selected.\n";
		} else {
			usageErrorMessage("A network must be specified in order to work.");
			ERROR_EXIT;
		}
		
		if (args_info->betweenness_given) {
			if (state->isWeighted()) {
				errorMessage("Betweenness for weighted graphs is not supported.");
				ERROR_EXIT;
			}else{
				int vertex_id = args_info->betweenness_arg;
				double ret = state->betweenness((unsigned int)args_info->betweenness_arg);
				if(ret != -1) {
					cout << "Betweenness for vertex " + to_string(vertex_id) + " is: " + to_string(ret) + ".\n";
				}else {
					errorMessage("Invalid vertex id");
				}
			}
		} else if (args_info->ddist_given) {
			int degree = args_info->ddist_arg;
			double ret = state->degreeDistribution(degree);
			if(ret != -1) {
				cout << "Degree distribution for degree " + to_string(degree) + " is: " + to_string(ret) + ".\n";
			}else {
				cout << "There are no vertices with degree " + to_string(degree) + ".\n";
			}
		} else if (args_info->clustering_given) {
			int vertex_id = args_info->clustering_arg;
			double ret = state->clustering(vertex_id);
			if(ret != -1) {
				cout << "Clustering coefficient for vertex " + to_string(vertex_id) + " is: " + to_string(ret) + ".\n";
			} else {
				errorMessage("Invalid vertex id");
			}
		} else if (args_info->knn_given) {
			int vertex_id = args_info->knn_arg;
			double ret = state->clustering(vertex_id);
			if(ret != -1) {
				cout << "Nearest neighbors degree for vertex " + to_string(vertex_id) + " is: " + to_string(ret) + ".\n";
			} else {
				errorMessage("Invalid vertex id");
			}
		} else if (args_info->shell_given) {
			int vertex_id = args_info->shell_arg;
			double ret = state->shellIndex(vertex_id);
			if(ret != -1) {
				cout << "Shell index for vertex " + to_string(vertex_id) + " is: " + to_string(ret) + ".\n";
			} else {
				errorMessage("Invalid vertex id");
			}
		}

		if (args_info->output_file_given) {
			string path = args_info->output_file_arg;
			string functionMessage = "";

			if (args_info->betweenness_output_given) {
				if (state->isWeighted()) {
					errorMessage("Betweenness for weighted graphs is not supported.");
					ERROR_EXIT;
				} else {
					state->exportBetweennessVsDegree(path);
					functionMessage = "betweenness";
				}
			} else if (args_info->ddist_output_given) {
				state->exportDegreeDistribution(path, args_info->log_bin_given, args_info->log_bin_arg);
				functionMessage = "degreeDistribution";
			} else if (args_info->clustering_output_given) {
				state->exportClusteringVsDegree(path);
				functionMessage = "clustering coefficient";
			} else if (args_info->knn_output_given) {
				state->exportNearestNeighborsDegreeVsDegree(path);
				functionMessage = "nearest neighbors degree";
			} else if (args_info->shell_output_given) {
				if (state->isWeighted()) {
					errorMessage("Shell index for weighted graphs is not supported.");
					ERROR_EXIT;
				} else {
					state->exportShellIndexVsDegree(path);
					functionMessage = "shellIndex";
				}
			}

			cout << "Succesfully exported " + functionMessage + " in output file " + path + ".\n";
		}

		if (args_info->save_given) {
			string path = args_info->save_arg;
			state->exportCurrentGraph(path);

			cout << "Succesfully saved graph in file " + path + ".\n";
		}
	}

}
