#include <QtGui/QApplication>

#include "ComplexNetsGui/inc/mainwindow.h"
#include "ComplexNetsCmd/cmdline.h"
#include "ComplexNetsCmd/cmdmessages.h"
#include "ComplexNetsCmd/ProgramState.h"

#define ERROR_EXIT		delete state; return EXIT_FAILURE;
#define VALIDATE_POS(n)	if ((n) <= 0) { usageErrorMessage("Number of nodes cannot be negative or zero."); ERROR_EXIT; }
#define VALIDATE_P(p)	if ((p) <= 0 || (p) > 1) { usageErrorMessage("Number of nodes cannot be negative, zero or greater than one."); ERROR_EXIT; }

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
		} else {
			usageErrorMessage("A network must be specified in order to work.");
			ERROR_EXIT;
		}
	}
}
