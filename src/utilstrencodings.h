/**
 * Utilities for converting data from/to strings.
 */
#ifndef BITCOIN_UTILSTRENCODINGS_H
#define BITCOIN_UTILSTRENCODINGS_H

#include <string>

signed char HexDigit(char c);

int64_t atoi64(const char* psz);
int64_t atoi64(const std::string& str);
int atoi(const std::string& str);

/**
 * Format a paragraph of text to a fixed width, adding spaces for
 * indentation to any added line.
 */
std::string FormatParagraph(const std::string& in, size_t width = 79, size_t indent = 0);

#endif // BITCOIN_UTILSTRENCODINGS_H
