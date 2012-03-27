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
        std::map<unsigned int , double> sortedMap;
        destinationFile.open(data_path.c_str(), std::ios_base::out);
        VariantsSet::const_iterator it = set.begin();

        /*
         * VariantsSet content is reinserted in a map so the data is sorted before exporting.
         */
        while (it != set.end())
        {
            sortedMap.insert(std::pair<unsigned int, double>(from_string<unsigned int>(it->first), from_string<double>(it->second)));
            ++it;
        }

        std::map<unsigned int, double>::const_iterator itSorted = sortedMap.begin();
        while (itSorted != sortedMap.end())
        {
            destinationFile << itSorted->first << " " << itSorted->second << std::endl;
            ++itSorted;
        }

        destinationFile.close();
    }
};
}

#endif
