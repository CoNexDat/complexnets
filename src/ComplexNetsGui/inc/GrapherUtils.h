#ifndef GRAPHERUTILS_H
#define GRAPHERUTILS_H

#include <cmath>
#include <cstdio>
#include <fstream>
#include <ostream>
#include <string>
#include "ComplexNets/PropertyMap.h"
#include "ComplexNets/mili/mili.h"

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
        std::map<double, double> sortedMap;
        destinationFile.open(data_path.c_str(), std::ios_base::out);
        VariantsSet::const_iterator it = set.begin();

        /*
         * VariantsSet content is reinserted in a map so the data is sorted before exporting.
         */
        while (it != set.end())
        {
            sortedMap.insert(std::pair<double, double>(from_string<double>(it->first),
                                                       from_string<double>(it->second)));
            ++it;
        }

        std::map<double, double>::const_iterator itSorted = sortedMap.begin();
        while (itSorted != sortedMap.end())
        {
            destinationFile << itSorted->first << " " << itSorted->second << std::endl;
            ++itSorted;
        }

        destinationFile.close();
    }

    static void exportVectors(const std::vector<double> x,
                              const std::vector<double> y,
                              const FilePath& data_path)
    {
        std::ofstream destinationFile;
        std::map<double, double> sortedMap;
        destinationFile.open(data_path.c_str(), std::ios_base::out);
        std::vector<double>::const_iterator itx = x.begin();
        std::vector<double>::const_iterator ity = y.begin();

        // if length of x != length of y, return error
        if (x.size() != y.size())
        {
            printf("Different size vectors. Cannot export. \n");
            return;
        }

        while (*itx != *x.end())
        {
            destinationFile << *ity << " " << *itx << std::endl;
            ++itx;
            ++ity;
        }

        destinationFile.close();
    }

    static void exportThreeVectors(const std::vector<double> x,
                                   const std::vector<double> y,
                                   const std::vector<unsigned int> z,
                                   const FilePath& data_path)
    {
        std::ofstream destinationFile;
        destinationFile.open(data_path.c_str(), std::ios_base::out);
        std::vector<double>::const_iterator itx = x.begin();
        std::vector<double>::const_iterator ity = y.begin();
        std::vector<unsigned int>::const_iterator itz = z.begin();

        // if length of x != length of y, return error
        while (*itx != *x.end())
        {
            destinationFile << *itx << " " << *ity << " " << *itz << std::endl;
            ++itx;
            ++ity;
            ++itz;
        }

        destinationFile.close();
    }

    static void exportFourVectors(const std::vector<double> w,
                                  const std::vector<double> x,
                                  const std::vector<double> y,
                                  const std::vector<double> z,
                                  const FilePath& data_path)
    {
        std::ofstream destinationFile;
        destinationFile.open(data_path.c_str(), std::ios_base::out);
        std::vector<double>::const_iterator itw = w.begin();
        std::vector<double>::const_iterator itx = x.begin();
        std::vector<double>::const_iterator ity = y.begin();
        std::vector<double>::const_iterator itz = z.begin();

        // if length of x != length of y, return error
        while (*itx != *x.end())
        {
            destinationFile << *itw << " " << *itx << " " << *ity << " " << *itz << std::endl;
            ++itw;
            ++itx;
            ++ity;
            ++itz;
        }

        destinationFile.close();
    }
};
}

#endif
