#include <QtGui/QApplication>

#include "ComplexNetsGui/inc/mainwindow.h"
#include "ComplexNetsCmd/cmdline.h"

int main(int argc, char* argv[])
{
	if (argc == 1) {
	    QApplication a(argc, argv);
	    ComplexNetsGui::MainWindow w;
	    w.show();
	    return a.exec();
	} else {
		struct gengetopt_args_info *args_info = (struct gengetopt_args_info *) malloc(sizeof(struct gengetopt_args_info));
		
		if(cmdline_parser(argc, argv, args_info) != 0) {
			return EXIT_FAILURE;
		}

		if(args_info->load_network_given) {
			printf("Load network");
		}
	}
}
