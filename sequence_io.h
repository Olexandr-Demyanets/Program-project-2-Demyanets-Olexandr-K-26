#ifndef SEQUENCE_IO_H
#define SEQUENCE_IO_H

#include <cstddef>
#include <string>
#include <vector>

std::vector<int> generateSequence(std::size_t length, int minVal, int maxVal);
void saveSequenceToFile(const std::vector<int>& seq, const std::string& filename);
std::vector<int> readSequenceFromFile(const std::string& filename);

#endif
