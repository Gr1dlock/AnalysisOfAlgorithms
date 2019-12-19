#ifndef SUBSTRING_H
#define SUBSTRING_H

#include <string>
#include <vector>
#include <unordered_map>

int standartSearch(const std::string &text, const std::string &substring);
int searchKMP(const std::string &text, const std::string &substring);
int searchBM(const std::string &text, const std::string &ubstring);

#endif // SUBSTRING_H
