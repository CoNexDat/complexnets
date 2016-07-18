// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 16th, 2015.
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
			if (args_info->erdos_given || args_info->barabasi_given || args_info->hot_given || args_info->molloy_given || args_info->hyperbolic_given) {
				usageErrorMessage("Cannot load a graph from an input file and generate a model at the same time.");
				ERROR_EXIT;
			}

			if (args_info->weighted_given) {
				state->setWeighted(true);
			} 
			
			if (args_info->digraph_given) {
				state->setDigraph(true);
                state->setDirectedInOut(args_info->out_given, args_info->in_given);
                cout << "Directed graph: positive: " << (args_info->out_given ? "true" : "false") << ", negative: " << (args_info->in_given ? "true" : "false") << endl;
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

            // Variable 't_given' no longer exists after using gengetopt on cmdline.ggo
//			if (!args_info->t_given) {
//				usageErrorMessage("Extended Hot graph generation requires the parameter user select between how many loops the core is recalculated.");
//				ERROR_EXIT;
//			}

 			int n = args_info->n_arg;
 			int m = args_info->m_arg;
 			float xi = args_info->xi_arg;
 			int q = args_info->q_arg;
 			float r = args_info->r_arg;
 			int t = 0; //args_info->t_arg;
 			VALIDATE_POS(n);
 			VALIDATE_POS(m);
 			VALIDATE_POS(q);
 			VALIDATE_POS(xi);
 			VALIDATE_POS(r);
 			VALIDATE_POS(t);

 			state->setExtendedHotGraph(m, n, xi, q, r, t);
 			cout << "Succesfully created an Extended Hot graph with " + to_string(n) + " nodes.\n";

		} else if (args_info->molloy_given) {
			if (!args_info->ks_given) {
				usageErrorMessage("A file with Ks and its nodes is needed to create a Molloy Reed graph.");
				ERROR_EXIT;
			}

			string path = args_info->ks_arg;
			state->setMolloyReedGraph(path);
		} else if (args_info->hyperbolic_given) {
			if (!args_info->n_given) {
				usageErrorMessage("Hiperbolic graph generation requires a number of nodes.");
				ERROR_EXIT;
			}
			if (!args_info->a_given) {
				usageErrorMessage("Hiperbolic graph generation requires a radial density.");
				ERROR_EXIT;
			}
			if (!args_info->deg_given) {
				usageErrorMessage("Hiperbolic graph generation requires an average node degree.");
				ERROR_EXIT;
			}
			int n = args_info->n_arg;
			float a = args_info->a_arg;
			float c  = args_info->deg_arg;
			state->setHiperbolicGraph(n, a, c);
			
		} else {
			usageErrorMessage("A network must be specified in order to work.");
			ERROR_EXIT;
		}
		
		if (args_info->betweenness_given) {
			//if (state->isWeighted()) {
			//	errorMessage("Betweenness for weighted graphs is not supported.");
			//	ERROR_EXIT;
			//}else{
			printf("Weighted Betweenness");
				int vertex_id = args_info->betweenness_arg;
				double ret = state->betweenness((unsigned int)args_info->betweenness_arg);
				if(ret != -1) {
					cout << "Betweenness for vertex " + to_string(vertex_id) + " is: " + to_string(ret) + ".\n";
				}else {
					errorMessage("Invalid vertex id");
				}
			//}
		} else if (args_info->ddist_given) {
			int degree = args_info->ddist_arg;
			if (!state->isDigraph()) {
				double ret = state->degreeDistribution(degree);
				if(ret != -1) {
					cout << "Degree distribution for degree " + to_string(degree) + " is: " + to_string(ret) + ".\n";
				}else {
					cout << "There are no vertices with degree " + to_string(degree) + ".\n";
				}
			} else {
				double ret1 = state->inDegreeDistribution(degree);
				double ret2 = state->outDegreeDistribution(degree);
				if(ret1 != -1) {
					cout << "In-Degree distribution for degree " + to_string(degree) + " is: " + to_string(ret1) + ".\n";
				}else {
					cout << "There are no vertices with degree " + to_string(degree) + ".\n";
				}
				if(ret2 != -1) {
					cout << "Out-Degree distribution for degree " + to_string(degree) + " is: " + to_string(ret2) + ".\n";
				}else {
					cout << "There are no vertices with degree " + to_string(degree) + ".\n";
				}
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
			double ret = state->knn(vertex_id);
			if(ret != -1) {
				cout << "Nearest neighbors degree for vertex " + to_string(vertex_id) + " is: " + to_string(ret) + ".\n";
			} else {
				errorMessage("Invalid vertex id");
			}
		} else if (args_info->maxCliqueExact_given) {
			int max_time = args_info->maxCliqueExact_arg;
			std::list<int> ret = state->maxCliqueExact(max_time);
			
			if(!ret.empty()) {
				cout << "Max clique size is: " + to_string(ret.size()) + ".\n";
				cout << "Max clique is: ";
				for(std::list<int>::iterator iterator = ret.begin();iterator != ret.end();iterator++){
		        	cout << to_string<int>(*iterator).c_str() << " ";
		        }
		        cout << ".\n";
			} else {
				errorMessage("Time out.");
				ERROR_EXIT;
			}
		} else if (args_info->maxCliqueAprox_given) {
			std::list<int> ret = state->maxCliqueAprox();
			if(!ret.empty()) {
				cout << "Max clique size is: " + to_string(ret.size()) + ".\n";
				cout << "Max clique is:";
				for(std::list<int>::iterator iterator = ret.begin();iterator != ret.end();iterator++){
		        	cout << " " << to_string<int>(*iterator).c_str() ;
		        }
		        cout << ".\n";
			} else {
				errorMessage("Unknown error.");
			}
		}else if (args_info->shell_given) {
			int vertex_id = args_info->shell_arg;
			double ret = state->shellIndex(vertex_id);
			if(ret != -1) {
				cout << "Shell index for vertex " + to_string(vertex_id) + " is: " + to_string(ret) + ".\n";
			} else {
				errorMessage("Invalid vertex id");
			}
		}
		
		if (args_info->print_deg_given) {
		    if (args_info->erdos_given || args_info->barabasi_given || args_info->hot_given || args_info->molloy_given || args_info->hyperbolic_given
			|| args_info->input_file_given) {
			    state->printDegrees();
			} else {
			    usageErrorMessage("You have specified the print-deg options but no graph was loaded or generated. Ignoring.");
			}
		    
		}

		if (args_info->output_file_given) {
			string path = args_info->output_file_arg;

			if (args_info->betweenness_output_given || args_info->ddist_output_given || 
					args_info->clustering_output_given || args_info->maxCliqueExact_output_given || 
					args_info->maxCliqueAprox_output_given || args_info->knn_output_given || 
					args_info->shell_output_given) {
				string functionMessage = "";

				if (args_info->betweenness_output_given) {
					//if (state->isWeighted()) {
					//	errorMessage("Betweenness for weighted graphs is not supported.");
					//	ERROR_EXIT;
					//} else {
						state->exportBetweennessVsDegree(path);
						functionMessage = "betweenness";
					//}
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
				} if (args_info->maxCliqueExact_output_given) {
					int max_time = args_info->maxCliqueExact_output_arg;
					if(!state->exportMaxCliqueExact(path, max_time)) {
						errorMessage("Time out.");
						ERROR_EXIT;
					}
					functionMessage = "max clique distribution";
				} else if (args_info->maxCliqueAprox_output_given) {
					state->exportMaxCliqueAprox(path);
					functionMessage = "max clique distribution aproximation";
				}

				cout << "Succesfully exported " + functionMessage + " in output file " + path + ".\n";
			} else {
				state->exportCurrentGraph(path);
				cout << "Succesfully saved graph in file " + path + ".\n";
			}
		}
	}

}
