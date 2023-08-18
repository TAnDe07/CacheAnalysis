
// Created by tanad on 11/27/2022.
//
//
#include <iostream>
#include <fstream>
#include <vector>
#include "math.h"
#include "iomanip"
using namespace std;

//helper
string hex2bin (string hex) {
    string bin = "";
    for (int i = 2; i < hex.size(); ++i) {
        switch (hex.at(i)) {
            case '0':
                bin += "0000";
                break;
            case '1':
                bin += "0001";
                break;
            case '2':
                bin += "0010";
                break;
            case '3':
                bin += "0011";
                break;
            case '4':
                bin += "0100";
                break;
            case '5':
                bin += "0101";
                break;
            case '6':
                bin += "0110";
                break;
            case '7':
                bin += "0111";
                break;
            case '8':
                bin += "1000";
                break;
            case '9':
                bin += "1001";
                break;
            case 'A':
                bin += "1010";
                break;
            case 'B':
                bin += "1011";
                break;
            case 'C':
                bin += "1100";
                break;
            case 'D':
                bin += "1101";
                break;
            case 'E':
                bin += "1110";
                break;
            case 'F':
                bin += "1111";
                break;
            case 'a':
                bin += "1010";
                break;
            case 'b':
                bin += "1011";
                break;
            case 'c':
                bin += "1100";
                break;
            case 'd':
                bin += "1101";
                break;
            case 'e':
                bin += "1110";
                break;
            case 'f':
                bin += "1111";
                break;
        }
    }

    return bin;
}

int main() {
    bool ending = false;
    while (ending == false) {
        string fileName;
        int cacheSize;
        int lineOrBlockSize;
        int associativity;
        int n;
        string replacement;

        //address in cache
        string setData = "";
        string tagData = "";
        int counter = 1;
        float hit = 0;
        int miss = 0;
        float total = 0;

        int offset = 0;
        int line = 0;
        int tag = 0;

        cout << "Enter full filename: ";
        cin >> fileName;

        cout << "Enter the number of bytes in the cache: ";
        cin >> cacheSize; // bytes in cache

        cout << "Enter the number of bytes in a block/line: ";
        cin >> lineOrBlockSize; // bytes in a block/line
        cout << "\n";

        cout << "Which cache would you like to use?" << endl;
        cout << "1. Direct Mapped" << endl;
        cout << "2. Fully Associative" << endl;
        cout << "3. N-way Set Associative" << endl;
        cout << "4. Exit" << endl;
        cin >> associativity; // how many lines


        ifstream myFile(fileName);
        string hex;
        vector<pair<string, string>> directMappedCache; //set, tag
        vector<pair<string, int>> fullyAssociativeCache; //tag, counter
        vector<pair<string, vector<pair<string, int>>>> setAssociativeCache; //set, tag, counter


        int totalLinesInCache = cacheSize / lineOrBlockSize;
        int totalSetInCache = 0;

        if (associativity == 1) {
            cout << "Direct Mapped" << endl;

            offset = log2(lineOrBlockSize);
            line = log2(totalLinesInCache);
            tag = 32 - offset - line;

            totalSetInCache = totalLinesInCache / associativity;
        }
        else if (associativity == 2) {
            offset = log2(lineOrBlockSize);
            tag = 32 - offset;

            cout << "Which replacement policy would you like to use?" << endl;
            cout << "1. FIFO" << endl;
            cout << "2. LRU" << endl;
            cin >> replacement;
            cout << "Fully Associative";

            totalSetInCache = 1;
        }
        else if (associativity == 3) {
            cout << "What value of N you would line to use?" << endl;
            cin >> n;

            offset = log2(lineOrBlockSize);
            line = log2(totalLinesInCache / n);
            tag = 32 - offset - line;

            cout << "Which replacement policy would you like to use?" << endl;
            cout << "1. FIFO" << endl;
            cout << "2. LRU" << endl;
            cin >> replacement;
            cout << n << "-way Set Associative";

            totalSetInCache = totalLinesInCache / n;
        }
        else {
            ending = true;
            break;
        }

        if (replacement == "1") {
            cout << ", FIFO" << endl;
        }
        else if (replacement == "2") {
            cout << ", LRU" << endl;
        }

        while (myFile.is_open()) {
            getline(myFile, hex);
            if (hex == "") {
                break;
            }

            hex.erase(0, 2);
            hex.erase(11, hex.size() - 1);
            string bin = hex2bin(hex); //convert to binary

            //Direct
            if (associativity == 1) {

                tagData = bin.substr(0, tag);
                bin = bin.erase(0, tag);
                setData = bin.substr(0, line);

                //if set and tag exist, return hit
                //else if set exists and tag does not replace tag and return miss
                bool exists = false;
                for (int i = 0; i < directMappedCache.size(); ++i) {
                    if (directMappedCache.at(i).first == setData) {
                        exists = true;
                        if (directMappedCache.at(i).second == tagData) {
                            hit++;
                        } else {
                            directMappedCache.at(i).second = tagData;
                            miss++;
                        }
                        break;
                    }
                }
                //if set does not exist, create new set
                if (!exists && (directMappedCache.size() < totalSetInCache)) {
                    directMappedCache.emplace_back(setData, tagData);
                    miss++;
                }
            }
                //Fully
            else if (associativity == 2) {

                tagData = bin.substr(0, tag);
                bool exists = false;

                //FIFO, tag exist, return hit
                if (replacement == "1") {
                    for (int i = 0; i < fullyAssociativeCache.size(); ++i) {
                        if (fullyAssociativeCache.at(i).first == tagData) {
                            hit++;
                            exists = true;
                            break;
                        }
                    }
                }
                    //LRU, tag exist, return hit
                else if (replacement == "2") {
                    for (int i = 0; i < fullyAssociativeCache.size(); ++i) {
                        if (fullyAssociativeCache.at(i).first == tagData) {
                            fullyAssociativeCache.at(i).second = counter;
                            hit++;
                            exists = true;
                            break;
                        }
                    }
                }
                //if tag does not exist, create new tag
                if (exists == false && (fullyAssociativeCache.size() < totalLinesInCache)) {
                    fullyAssociativeCache.emplace_back(tagData, counter);
                    miss++;
                }
                    //if cache is full, replaces
                else if (exists == false && (fullyAssociativeCache.size() == totalLinesInCache)) {
                    int temp = fullyAssociativeCache.at(0).second;
                    int index = 0;
                    for (int i = 1; i < fullyAssociativeCache.size(); ++i) {
                        if (temp > fullyAssociativeCache.at(i).second) {
                            temp = fullyAssociativeCache.at(i).second;
                            index = i;
                        }
                    }
                    fullyAssociativeCache.at(index).first = tagData;
                    fullyAssociativeCache.at(index).second = counter;
                    miss++;
                }
            }
                //Set
            else {
                tagData = bin.substr(0, tag);
                bin = bin.erase(0, tag);
                setData = bin.substr(0, line);
                bool exists = false;
                bool setExists = false;

                for (int i = 0; i < setAssociativeCache.size(); ++i) {
                    //set exists
                    if (setAssociativeCache.at(i).first == setData) {
                        setExists = true;
                        //tag exists FIFO
                        if (replacement == "1") {
                            for (int j = 0; j < setAssociativeCache.at(i).second.size(); ++j) {
                                if (setAssociativeCache.at(i).second.at(j).first == tagData) {
                                    exists = true;
                                    hit++;
                                    break;
                                }
                            }
                        }
                            //tag exists LRU
                        else if (replacement == "2") {
                            for (int j = 0; j < setAssociativeCache.at(i).second.size(); ++j) {
                                if (setAssociativeCache.at(i).second.at(j).first == tagData) {
                                    setAssociativeCache.at(i).second.at(j).second = counter;
                                    exists = true;
                                    hit++;
                                    break;
                                }
                            }
                        }
                        //set is not full and tag does not exist
                        if (setAssociativeCache.at(i).second.size() < n && exists == false) {
                            setAssociativeCache.at(i).second.emplace_back(tagData, counter);
                            miss++;
                            break;
                        }
                            //set is full and tag does not exist
                        else if (setAssociativeCache.at(i).second.size() == n && exists == false) {
                            int temp = setAssociativeCache.at(i).second.at(0).second;
                            int index = 0;
                            //iterate through set, to find lower count
                            for (int a = 1; a < setAssociativeCache.at(i).second.size(); ++a) {
                                //find lower count
                                if (temp > setAssociativeCache.at(i).second.at(a).second) {
                                    temp = setAssociativeCache.at(i).second.at(a).second;
                                    index = a;
                                }
                            }
                            setAssociativeCache.at(i).second.at(index).first = tagData;
                            setAssociativeCache.at(i).second.at(index).second = counter;
                            miss++;
                            break;
                        }
                    }
                }
                //if set does not exist and is not full, create new set
                if (setExists == false && (setAssociativeCache.size() < totalSetInCache)) {
                    vector<pair<string, int>> add;
                    add.emplace_back(tagData, counter);
                    setAssociativeCache.emplace_back(setData, add);
                    miss++;
                }
            }
            total++;
            counter++;
        }

        float hitRatio = hit / total;
        cout << "Hits: " << fixed << setprecision(0) <<  hit << endl;
        cout << "Misses: " << fixed << setprecision(0)<< miss << endl;
        cout << "Total: " << fixed << setprecision(0) << total << endl;
        cout << "Hit Ratio: " << fixed << setprecision(3) << hitRatio << endl;
        cout << "\n";
    }
}