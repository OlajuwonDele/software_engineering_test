#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <random>
#include <cmath>
#include <limits>
#include <cassert>

// Simple point representation
using TPoint = std::array<double, 2>;

// Function to read a comma-separated list of 2D points
bool ReadInputFile(const std::string& Filename, std::vector<TPoint>& o_rData){
    o_rData.clear();

    std::ifstream File;
    File.open(Filename);
    if (!File.is_open())
    {
        return false;
    }

    double x, y;
    char sep;
    while (File >> x >> sep >> y)
    {
        o_rData.push_back({ x, y });
    }

    return true;
}

// Define a structure to represent a line with two points (slope and intercept).
struct Line {
    TPoint point1;
    TPoint point2;
};


// Function to calculate the distance between a point and a line (using the formula for a perpendicular distance).
double CalculateDistance(const TPoint& point, const Line& line) {
    double x1 = line.point1[0];
    double y1 = line.point1[1];
    double x2 = line.point2[0];
    double y2 = line.point2[1];
    double numerator = std::abs((y2 - y1) * point[0] - (x2 - x1) * point[1] + x2 * y1 - y2 * x1);
    double denominator = std::sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
    return numerator / denominator;
}


int main(int argc, char** argv)
{
    // Setup the input parameters
    std::string InputFilename;
    std::string OutputFilename("output1.txt");
    double Confidence = 0.99;
    double Threshold = 0.1;
    double ApproximateInlierFraction = 0.5;

    std::cout << "Enter the file name: \n";
    std::cin >> InputFilename;

    std::vector<TPoint> Data;
    if (!ReadInputFile(InputFilename, Data))
    {
        std::cerr << "Unable to read point data from file '" << InputFilename << "'" << std::endl;
        return 1;
    }

    // Output variables ...
    std::vector<bool> Inliers;
    TPoint Point0;
    TPoint Point1;
    bool bSuccess(false);

    // ------------------------------------------



    // Initialize variables for the best line and inliers
    Line bestLine;
    std::vector<bool> bestInliers;
    int bestInlierCount = 0;

    // Create a random number generator more reliable than std::rand() to create a random number
    std::random_device rd;
    std::mt19937 generator(rd());


    // RANSAC parameters
    int maxIterations = 1000;       // Maximum number of RANSAC iterations
    double inlierThreshold = 0.1;  // Inlier threshold distance

    // RANSAC algorithm to estimate a line
    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        // Randomly select two points to form a candidate line
        std::vector<TPoint> randomPoints;
        std::uniform_int_distribution<int> distribution(0, Data.size() - 1);
        for (int i = 0; i < 2; ++i) {
            int randomIndex = distribution(generator);
            randomPoints.push_back(Data[randomIndex]);
        }

        // Fit a line to the two random points
        Line candidateLine;
        candidateLine.point1 = randomPoints[0];
        candidateLine.point2 = randomPoints[1];

        // Count inliers (points that are close to the candidate line)
        std::vector<bool> inliers(Data.size(), false);
        int inlierCount = 0;
        for (size_t i = 0; i < Data.size(); ++i) {
            double distance = CalculateDistance(Data[i], candidateLine);
            if (distance < inlierThreshold) {
                inliers[i] = true;
                inlierCount++;
            }
        }

        // If this candidate line has more inliers than the best line so far, update the best line
        if (inlierCount > bestInlierCount) {
            bestInlierCount = inlierCount;
            bestLine = candidateLine;
            bestInliers = inliers;
        }
    }

    // Output variables ...
    Point0 = bestLine.point1;
    Point1 = bestLine.point2;
    Inliers = bestInliers;
    bSuccess = true;

    // ...

    // -------------------------------------------

    // if successful, write the line parameterized as two points, and each input point along with its inlier status
    if (bSuccess)
    {
        std::ofstream Out(OutputFilename);
        Out << Point0[0] << " " << Point0[1] << "\n";
        Out << Point1[0] << " " << Point1[1] << "\n";
        assert(Inliers.size() == Data.size());
        for (size_t Index = 0; Index != Data.size(); ++Index)
        {
            Out << Data[Index][0] << " " << Data[Index][1] << " " << Inliers[Index] << "\n";
        }
        Out.close();
        std::cout << "Success!" << std::endl;
    }
    

    return 0;
}
