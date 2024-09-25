/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

// Function to convert a string from a given base to base 10 (decimal)
long long baseToDecimal(const string& value, int base) {
    long long result = 0;
    for (char digit : value) {
        result = result * base + (isdigit(digit) ? digit - '0' : toupper(digit) - 'A' + 10);
    }
    return result;
}

// Lagrange interpolation to find the polynomial's constant term (secret 'c')
long long lagrangeInterpolation(const vector<pair<int, long long>>& points, int k) {
    long long secret = 0;
    int n = points.size();
    
    for (int i = 0; i < k; ++i) {
        long long xi = points[i].first;
        long long yi = points[i].second;

        long long li = 1; // Lagrange basis polynomial
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                long long xj = points[j].first;
                li *= (0 - xj) / (xi - xj); // li(0) for constant term
            }
        }
        secret += yi * li;
    }
    
    return secret;
}

int main() {
    // Open and parse the input JSON file
    ifstream file("input.json");
    if (!file) {
        cerr << "Error: Cannot open input file." << endl;
        return 1;
    }
    
    // Variables to store JSON data
    int n, k;
    map<int, pair<int, string>> roots;
    
    string line;
    while (getline(file, line)) {
        // Parsing the keys
        if (line.find("\"n\"") != string::npos) {
            sscanf(line.c_str(), "\"n\": %d", &n);
        } else if (line.find("\"k\"") != string::npos) {
            sscanf(line.c_str(), "\"k\": %d", &k);
        } 
        // Parsing the roots (x, y) with base
        else if (line.find("\"base\"") != string::npos) {
            int index, base;
            string value;
            sscanf(line.c_str(), "\"%d\": {\"base\": \"%d\", \"value\": \"%[^\"]\"}", &index, &base, &value[0]);
            roots[index] = make_pair(base, value);
        }
    }

    file.close();

    // Decode y values and store points
    vector<pair<int, long long>> points;
    for (const auto& root : roots) {
        int x = root.first;
        int base = root.second.first;
        string value = root.second.second;
        
        long long y = baseToDecimal(value, base); // Convert y from its base to decimal
        points.push_back({x, y});
    }

    // Find the constant term 'c' using Lagrange interpolation
    long long secret = lagrangeInterpolation(points, k);

    // Output the result
    cout << "The secret (constant term 'c') is: " << secret << endl;

    return 0;
}
