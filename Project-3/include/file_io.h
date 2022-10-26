
#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <vector>

/// @brief Write a csv file with the given data column by column.
/// @param fpath The path to the file to write
/// @param x First column of data
/// @param y Second column of data
/// @param separator The separator to use between columns. Defaults to ",".
/// @param index If true, write an index column. Default is false.
/// @param digits The number of digits to write for each number. Default is 7.
void two_columns_to_csv(const std::string &fpath, const std::vector<double> &x, const std::vector<double> &y, const std::string &separator = ",", bool index = false, size_t digits = 7);
void three_columns_to_csv(const std::string& fpath, const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z, const std::string &separator = ",", bool index = false, size_t digits = 7);

#endif