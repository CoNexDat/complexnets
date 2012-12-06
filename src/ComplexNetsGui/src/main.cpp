#include <QtGui/QApplication>

#include "ComplexNetsGui/inc/mainwindow.h"
#include "ComplexNetsCmd/cmdline.h"
#include "ComplexNetsCmd/cmdmessages.h"
#include "ComplexNetsCmd/ProgramState.h"

#define ERROR_EXIT delete state; return EXIT_FAILURE;

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

		} else if (args_info->model_given) {
			if (args_info->erdos_given) {
				
			}
		}
		else {
			usageErrorMessage("A network must be specified in order to work.");
			ERROR_EXIT;
		}
	}
}
