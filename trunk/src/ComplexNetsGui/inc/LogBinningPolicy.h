#ifndef LOGBINNINGPOLICY_H
#define LOGBINNINGPOLICY_H

#include "../../ComplexNets/mili/mili.h"

namespace ComplexNetsGui
{
class LogBinningPolicy
{
public:
    static const VariantsSet transform(const VariantsSet& set)
    {
        return LogBin(set, 2);
    }
private:
    static const VariantsSet LogBin(const VariantsSet& set, const double factor)
    {
        VariantsSet toPlot;
        std::list<double> xPoints;
        std::vector<double> bins;

        //sort x data points from set
        VariantsSet::const_iterator it = set.begin();
        while (it != set.end())
        {
            xPoints.push_back(from_string<unsigned int>(it->first));
            ++it;
        }
        xPoints.sort();


        //Compute bins and bins width
        double min = xPoints.front();
        double max = xPoints.back();
        bins.push_back(min * 2.0 / (double)(1.0 + factor));
        unsigned int i = 1;
        while (bins[i - 1] < max)
        {
            bins.push_back(bins[i - 1]*factor);
            ++i;
        }


        //Go through each degree in the network and find wich bin the degree belongs to.
        //Count how many elements are contained in a bin.
        std::vector<unsigned int> pointsInBin(bins.size());
        for (unsigned int i = 0; i < bins.size(); i++)
            pointsInBin[i++] = 0;
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
            double binWidth = fabs(bins[i + 1] - bins[i]);
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

        return toPlot;
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
            else
                upperLimit = halfPoint;
        }
        return lowerLimit;
    }
};
}

#endif // LOGBINNINGPOLICY_H
