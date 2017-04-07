#include "ComplexNetsGui/inc/GnuplotConsole.h"
#include "ComplexNetsGui/inc/GrapherUtils.h"

#include "ComplexNetsGui/inc/LogBinningPolicy.h"

using namespace ComplexNetsGui;

GnuplotConsole::GnuplotConsole(QWidget* parent) : QDialog(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("Dialog"));

    this->resize(706, 326);
    this->setModal(false);
    groupBox = new QGroupBox(this);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(10, 10, 681, 241));
    textBrowser = new QTextBrowser(groupBox);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    textBrowser->setGeometry(QRect(10, 20, 661, 211));
    groupBox_2 = new QGroupBox(this);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    groupBox_2->setGeometry(QRect(10, 260, 681, 61));
    lineEdit = new QLineEdit(groupBox_2);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setGeometry(QRect(10, 20, 661, 27));

    this->setWindowTitle(QApplication::translate("Dialog", "Gnuplot console", 0));
    groupBox->setTitle(QApplication::translate("Dialog", "Console", 0));
    groupBox_2->setTitle(QApplication::translate("Dialog", "Command", 0));

    QObject::connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(commandEntered()));
    QMetaObject::connectSlotsByName(this);
}

GnuplotConsole::~GnuplotConsole()
{
    std::string exitCommand = "quit\n";
    if (pipe != nullptr)
    {
        writeCommand(exitCommand);
        pclose(pipe);
    }
    if (outputFile.is_open())
    {
        outputFile.clear();
        outputFile.close();
    }
    delete textBrowser;
    delete lineEdit;
    delete groupBox;
    delete groupBox_2;
}

// TODO should be const
bool GnuplotConsole::plotPropertySet(
    const VariantsSet& set, const std::string& propertyName, const bool logBin, unsigned int bins)
{
    GrapherUtils utils;
    if (pipe == nullptr)
    {
        pipe = popen("gnuplot -persist > /tmp/complexnets_gnuplot_output.txt 2>&1", "w");
    }
    if (pipe == nullptr)
        return false;

    writeCommand("set logscale x");
    writeCommand("set logscale y");
    writeCommand("set style data linespoints");
    std::string command =
        std::string("plot ").append("\"/tmp/").append(propertyName).append("\"\n");
    std::string file = "/tmp/";
    file.append(propertyName);
    /*
     * TODO this should be implemented as a policy. Using default template is only allowed in C++0x.
     * Another option would be to pass a preprocesing object as a parameter.
     */
    if (logBin)
    {
        LogBinningPolicy policy;
        utils.exportPropertySet(policy.transform(set, bins), file);
    }
    else
        utils.exportPropertySet(set, file);

    writeCommand(command);
    return true;
}

void GnuplotConsole::commandEntered()
{
    std::string command = lineEdit->text().toStdString();
    // TODO do nothing when the command is either exit or quit.
    if (!command.empty())
    {
        writeCommand(command);
        lineEdit->clear();
    }
}

void GnuplotConsole::writeCommand(const std::string& command)
{
    std::string _command = command;
    _command.append("\n");

    QString text("gnuplot> ");
    text.append(_command.c_str());
    this->textBrowser->append(text);

    fputs(_command.c_str(), pipe);
    _command = "replot";
    _command.append("\n");
    fputs(_command.c_str(), pipe);
    fflush(pipe);

    /*if(!outputFile.is_open())
    {
        outputFile.open("/tmp/complexnets_gnuplot_output.txt", std::ios_base::in);
        outputFile.clear();
    }
    if(!outputFile.is_open())
        return ;

    QString console;
    std::string line;
    while(std::getline(outputFile,line))
    {
        console.append(line.c_str());
        //console.append("\n");
    }
    this->textBrowser->clear();
    this->textBrowser->append(console);*/
}

bool GnuplotConsole::boxplotCC(
    std::vector<graphpp::Boxplotentry> bpentries, const bool logBin, unsigned int bins)
{
    std::vector<double> Q1, Q2, Q3, d, m;
    std::vector<unsigned int> bin;
    if (logBin)
    {
        LogBinningPolicy policy;
        policy.transform(bpentries, bins);
    }

    for (auto& entry : bpentries)
    {
        printf("[Degree %d] Size: %lu, Mean: %f\n", entry.degree, entry.values.size(), entry.mean);
        printf("   Min: %f - Max: %f\n", entry.min, entry.max);
        printf("   Q1: %f \t Q2: %f \t Q3: %f\n", entry.Q1, entry.Q2, entry.Q3);

        if (logBin)
        {
            for (auto& value : entry.values)
            {
                d.push_back(entry.degree);
                m.push_back(value);
                bin.push_back(entry.bin);
            }
        }
        else
        {
            d.push_back(entry.degree);
            m.push_back(entry.mean);
            Q1.push_back(entry.Q1);
            Q2.push_back(entry.Q2);
            Q3.push_back(entry.Q3);
        }
    }

    GrapherUtils utils;
    if (pipe == nullptr)
    {
        pipe = popen("gnuplot -persist > /tmp/complexnets_gnuplot_output.txt 2>&1", "w");
    }
    if (pipe == nullptr)
        return false;

    if (logBin)
    {
        std::string file = "/tmp/boxplotlog";
        utils.exportThreeVectors(d, m, bin, file);

        writeCommand("set style data boxplot");
        writeCommand("set logscale y");
        writeCommand("unset logscale x");
        std::string command = std::string("plot \"/tmp/boxplotlog\" using  (1):2:(0.5):3");
        writeCommand(command);
    }
    else
    {
        writeCommand("set logscale y");
        writeCommand("set logscale x");

        std::string command = std::string("plot \"/tmp/Q1\" title 'Q1' with lines, ");
        utils.exportVectors(Q1, d, "/tmp/Q1");

        command.append("\"/tmp/Q2\" title 'Q2' with lines, ");
        utils.exportVectors(Q2, d, "/tmp/Q2");

        command.append("\"/tmp/Q3\" title 'Q3' with lines\n");
        utils.exportVectors(Q3, d, "/tmp/Q3");

        writeCommand(command);
    }

    return true;
}

unsigned int GnuplotConsole::findBin(const std::vector<double>& bins, const unsigned int value)
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

bool GnuplotConsole::addLogBins(std::vector<graphpp::Boxplotentry>& vec, unsigned int binsAmount)
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

    auto it = vec.begin();
    while (it != vec.end())
    {
        unsigned int binNum = findBin(bins, it->degree);
        pointsInBin[binNum] += 1;
        it->bin = bins.at(binNum + 1);
        // printf("Degree: %d --> bin %d\n", it->degree, binNum+1);
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

    return true;
}
