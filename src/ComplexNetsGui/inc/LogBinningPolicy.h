#ifndef LOGBINNINGPOLICY_H
#define LOGBINNINGPOLICY_H

#include "ComplexNets/mili/mili.h"

namespace ComplexNetsGui
{
class LogBinningPolicy
{
public:
    static const VariantsSet transform(const VariantsSet& set, unsigned int binsAmount = 25)
    {
        return LogBin(set, binsAmount);
    }
    static const void transform(
        std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry>& vec,
        unsigned int binsAmount = 25)
    {
        return LogBin(vec, binsAmount);
    }

private:
    static const VariantsSet LogBin(const VariantsSet& set, unsigned int binsAmount)
    {
        VariantsSet toPlot;
        std::list<double> xPoints;
        std::vector<double> bins;

        // sort x data points from set
        VariantsSet::const_iterator it = set.begin();
        while (it != set.end())
        {
            xPoints.push_back(from_string<unsigned int>(it->first));
            ++it;
        }
        xPoints.sort();

        double min = xPoints.front();
        double max = xPoints.back();
        double r = pow(max - min + 1, 1 / (double)binsAmount);

        int last = 0, current;
        double cBin;
        for (unsigned int i = 0; i <= binsAmount; i++)
        {
            cBin = pow(r, i) + min - 1;
            current = i < binsAmount ? floor(cBin) : ceil(cBin);
            if (current != last)
            {
                bins.push_back(current);
                last = current;
            }
        }

        // for(int i = 0; i < bins.size(); i++) {
        //     printf("bin: %g\n", bins.at(i));
        // }

        // Go through each degree in the network and find wich bin the degree belongs to.
        // Count how many elements are contained in a bin.
        std::vector<unsigned int> pointsInBin(bins.size());
        for (unsigned int i = 0; i < bins.size(); i++)
        {
            pointsInBin[i++] = 0;
        }

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

        for (unsigned int i = 0; i < pointsInBin.size() - 1; i++)
        {
            printf("Bin[%g, %g]: %d\n", bins.at(i), bins.at(i + 1), pointsInBin.at(i));
        }

        // Probability density per bin
        // Normalization and plotting
        double sum = 0.0;
        for (unsigned int i = 0; i < bins.size(); ++i)
        {
            sum += pointsInBin[i];
        }

        double binWidth, PBin, checkIntegral = 0, binPos;
        for (unsigned int i = 0; i < bins.size(); ++i)
        {
            binWidth = fabs(bins[i + 1] - bins[i]);
            PBin = (pointsInBin[i] / sum) / binWidth;
            checkIntegral += PBin * binWidth;
            binPos = bins[i] + (binWidth / 2.0);
            toPlot.insert<double>(to_string<double>(binPos), PBin);
        }

        printf("Integral: %g\n", checkIntegral);

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

    static const void LogBin(
        std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry>& vec,
        unsigned int binsAmount)
    {
        std::vector<double> toPlot;
        std::list<double> xPoints;
        std::vector<double> bins;

        // assume it is already sorted

        double min = vec.front().degree;
        double max = vec.back().degree;
        double r = pow(max - min + 1, 1 / (double)binsAmount);

        int last = 0, current;
        double cBin;
        for (unsigned int i = 0; i <= binsAmount; i++)
        {
            cBin = pow(r, i) + min - 1;
            current = i < binsAmount ? floor(cBin) : ceil(cBin);
            if (current != last)
            {
                bins.push_back(current);
                last = current;
            }
        }

        // Go through each degree in the network and find wich bin the degree belongs to.
        // Count how many elements are contained in a bin.
        std::vector<unsigned int> pointsInBin(bins.size());
        for (unsigned int i = 0; i < bins.size(); i++)
        {
            pointsInBin[i++] = 0;
        }

        std::vector<graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry>::iterator it =
            vec.begin();
        while (it != vec.end())
        {
            unsigned int binNum = findBin(bins, it->degree);
            pointsInBin[binNum] += 1;
            it->bin = bins.at(binNum + 1);
            ++it;
        }

        for (unsigned int i = 0; i < pointsInBin.size() - 1; i++)
        {
            printf("Bin[%g, %g]: %d\n", bins.at(i), bins.at(i + 1), pointsInBin.at(i));
        }

        // Probability density per bin
        // Normalization and plotting
        double sum = 0.0;
        for (unsigned int i = 0; i < bins.size(); ++i)
        {
            sum += pointsInBin[i];
        }

        double binWidth, PBin, checkIntegral = 0, binPos;
        for (unsigned int i = 0; i < bins.size(); ++i)
        {
            binWidth = fabs(bins[i + 1] - bins[i]);
            PBin = (pointsInBin[i] / sum) / binWidth;
            checkIntegral += PBin * binWidth;
            binPos = bins[i] + (binWidth / 2.0);
        }

        return;
    }
};
}

#endif  // LOGBINNINGPOLICY_H
