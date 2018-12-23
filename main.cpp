#include <iostream>
#include <fstream>
#include <ctime>
#include <set>
#include <string>

#include <stdlib.h>

#include "CollectionArea.hpp"
#include "Device.hpp"

using std::cout;
using std::ifstream;
using std::vector;
using std::set;
using std::string;

void day16();
void day18();

int main() {
    
    day16();
    
}

vector<int> & parseReg(ifstream &, vector<int> &);
vector<int> & parseInstr(ifstream &, vector<int> &);
void printVec(const vector<int> &);


void day16() {
    
    ifstream input("/Users/greg/Library/Mobile Documents/com~apple~CloudDocs/Xcode/aoc/day16.txt");
    
    vector<Device::opcode> opcodes(16);
    
    for (int i = 0; i < opcodes.size(); i++) {
        opcodes[i] = (Device::opcode) i;
    }
    
    vector<set<Device::opcode>> codes(16, set<Device::opcode>(opcodes.begin(), opcodes.end()));
    
    Device device;
    
    vector<int> begin(4, 0);
    vector<int> end(4, 0);
    vector<int> instr(4, 0);
    
    unsigned int count = 0;
    unsigned int matches = 0;
    
    while (true) {
        try {
            begin = parseReg(input, begin);
            
            instr = parseInstr(input, instr);
            
            end = parseReg(input, end);

        }
        catch (...){
            break;
        }
        
        matches = 0;
        for (int i = 0; i < opcodes.size(); i++) {
            device.setReg(begin);
            try {
                const vector<int> & result = device.safeRunOp(opcodes[i], instr[1], instr[2], instr[3]);
                
                cout << "Actual: ";
                printVec(result);
                
                if (result == end)
                    matches++;
            }
            catch (...) {
                continue;
            }
        }
        
        if (matches >= 3) count++;
    }
    
    cout << "Count: " << count << '\n';
    
}

void printVec(const vector<int> & vec) {
    for (const auto x : vec)
        cout << x << ' ';
    cout << '\n';
}


vector<int> & parseReg(ifstream & in, vector<int> & result) {
    
    string buffer;
    in >> buffer;
    
    if (buffer[0] != 'B' and buffer[0] != 'A')
        throw false;
    
    in >> buffer;
        
    result[0] = atoi(&buffer[1]);
    
    for (int i = 1; i < result.size(); i++) {
        in >> buffer;
        result[i] = atoi(&buffer[0]);
    }

    return result;
    
}

vector<int> & parseInstr(ifstream & in, vector<int> & result) {
    
    for (int i = 0; i < result.size(); i++)
        in >> result[i];
    
    return result;
    
}

void day18() {
    ifstream input("/Users/greg/Library/Mobile Documents/com~apple~CloudDocs/Xcode/aoc/input.txt");
    CollectionArea ca(input, 50, 50);
    CollectionArea ca2 = ca;
    
    const unsigned int numToCalculate = 1000000000;
    
    for (unsigned int i = 0; i < 300; i++)
        ca.simulateMinute();
    
    
    
    const unsigned int sequenceLength = 5;
    const unsigned int sequenceStart = ca.getMinutesSimulated();
    vector<unsigned int> valueSequence(sequenceLength);
    
    for (unsigned int i = 0; i < sequenceLength; i++) {
        valueSequence[i] = ca.getResourceValue();
        ca.simulateMinute();
    }
    
    unsigned int lengthSoFar = 0;
    unsigned int startSoFar = 0;
    bool inSequence = false;
    
    while (lengthSoFar < sequenceLength) {
        if (ca.getResourceValue() == valueSequence[lengthSoFar]) {
            lengthSoFar++;
            if (lengthSoFar == 1) {
                startSoFar = ca.getMinutesSimulated();
                inSequence = true;
            }
            
        }
        else if (inSequence) {
            lengthSoFar = 0;
        }
        ca.simulateMinute();
        cout << ca.getResourceValue() << '\n';
    }
    
    const unsigned int period = startSoFar - sequenceStart;
    
    cout << "Period: " << period << " minutes\n";
    
    const unsigned int equivCalc = numToCalculate % period;
    
    for (unsigned int i = 0; i < equivCalc; i++) {
        ca2.simulateMinute();
    }
    
    cout << "\nSolution:\n";
    cout << ca2;
    cout << "Resource Value: " << ca2.getResourceValue() << '\n';
}
