#ifndef GRAPHERUTILS_H
#define GRAPHERUTILS_H

#include <string>
#include <fstream>
#include <ostream>
#include <cstdio>
#include <cmath>
#include "../../ComplexNets/PropertyMap.h"
#include "../../ComplexNets/mili/mili.h"

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

    static void plotLogBinDegree(const VariantsSet& set, const double factor)
    {
        VariantsSet toPlot;
        std::list<double> xPoints;
        std::vector<double> bins(set.size());
        unsigned int j = 2;

        //sort x data points
        VariantsSet::const_iterator it = set.begin();
        while (it != set.end())
        {
            xPoints.push_back(from_string<unsigned int>(it->first));
            ++it;
        }
        xPoints.sort();

        //Compute bins and bins width
        std::list<double>::const_iterator pointsIt = xPoints.begin();
        std::list<double>::const_iterator previous;
        bins[0] = *pointsIt;
        ++pointsIt;
        bins[1] = *pointsIt;
        previous = pointsIt;
        ++pointsIt;
        while (pointsIt != xPoints.end())
        {
            bins[j] = (*previous) * factor;
            previous = pointsIt;
            ++j;
            ++pointsIt;
        }

        //Go through each degree in the network and find wich bin the degree belongs to.
        //Count how many elements are contained in a bin.
        std::vector<unsigned int> pointsInBin(set.size());
        it = set.begin();
        while (it != set.end())
        {
            unsigned int amount = from_string<unsigned int>(it->second);
            for (unsigned int i = 0; i < amount; ++i)
            {
                unsigned int binNum = findBin(bins, from_string<unsigned int>(it->first));
                pointsInBin[binNum] += 1;
            }
            ++it;
        }

        //Probability density per bin
        std::vector<double> PBin(set.size());
        std::vector<double> binCenter(set.size());
        for (unsigned int i = 0; i < bins.size(); ++i)
        {
            double binWidth = bins[i + 1] - bins[i];
            PBin[i] = pointsInBin[i] / (double)binWidth;
            binCenter[i] = binWidth / 2.0;
        }

        //Normalization and plotting
        double sum = 0.0;
        for (unsigned int i = 0; i < bins.size(); ++i)
            sum += PBin[i];

        for (unsigned int i = 0; i < bins.size(); ++i)
        {
            PBin[i] /= sum;
            toPlot.insert<double>(to_string<double>(binCenter[i]), PBin[i]);
        }

        plotPropertySet(toPlot, "d", "P(d)", "Degree distribucion");
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

    static unsigned int findBin(const std::vector<double>& bins, const unsigned int value)
    {
        unsigned int lowerLimit = 0;
        unsigned int upperLimit = bins.size() - 1;
        unsigned int halfPoint;
        while (upperLimit - lowerLimit > 1)
        {
            halfPoint = ceil(0.5 * (upperLimit + lowerLimit));
            if (value >= bins[halfPoint])
                lowerLimit = halfPoint;
            else upperLimit = halfPoint;
        }
        return lowerLimit;
    }
};
}

#endif
