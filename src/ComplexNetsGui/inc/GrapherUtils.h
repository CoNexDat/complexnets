#ifndef GRAPHERUTILS_H
#define GRAPHERUTILS_H

#include <string>
#include <fstream>
#include <ostream>
#include <cstdio>
#include "../../ComplexNets/PropertyMap.h"
#include "mili/mili.h"

namespace ComplexNetsGui
{
class GrapherUtils
{
public:
    typedef std::string FilePath;
    typedef std::string Title;
    typedef std::string Label;

    static void exportPropertySet(const VariantsSet& set, const FilePath& data_path)
    {
        std::ofstream destinationFile;

        destinationFile.open(data_path.c_str(), std::ios_base::out);
        VariantsSet::const_iterator it = set.begin();

        while (it != set.end())
        {
            destinationFile << it->first << " " << it->second << std::endl;
            ++it;
        }

        destinationFile.close();
    }


    static int plotPropertySet(const VariantsSet& set, const Label& x = "x", const Label& y = "y", const Title& title = "title")
    {
        int ret = 0;
        std::string data_path, command_path, gnuplot_command;

        data_path.append("/tmp/data.txt");
        command_path.append("/tmp/command.txt");


        exportPropertySet(set, data_path);
        createCommandFile(data_path, command_path, x, y, title);

        gnuplot_command.append("gnuplot -persist ").append(command_path);
        ret = system(gnuplot_command.c_str());

        remove(data_path.c_str());
        remove(command_path.c_str());

        return ret;
    }
private:
    static void createCommandFile(const FilePath& data_path, const FilePath& command_path, const Label& x = "x", const Label& y = "y", const Title& title = "title")
    {
        std::ofstream destinationFile;

        destinationFile.open(command_path.c_str(), std::ios_base::out);

        destinationFile << "set title \"" << title << "\"" << std::endl;
        destinationFile << "set xlabel \"" << x << "\"" << std::endl;
        destinationFile << "set ylabel \"" << y << "\"" << std::endl;
        destinationFile << "plot \"" << data_path << "\"" << std::endl;

        destinationFile.close();
    }
};
}

#endif
