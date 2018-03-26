#include "utilstrencodings.h"

#include <cstdlib>
#include <cstring>
#include <sstream>

using namespace std;

int64_t atoi64(const char* psz)
{
    return strtoll(psz, NULL, 10);
}

int64_t atoi64(const std::string& str)
{
    return strtoll(str.c_str(), NULL, 10);
}

int atoi(const std::string& str)
{
    return atoi(str.c_str());
}

std::string FormatParagraph(const std::string& in, size_t width, size_t indent)
{
    std::stringstream out;
    size_t col = 0;
    size_t ptr = 0;
    while(ptr < in.size())
    {
        // Find beginning of next word
        ptr = in.find_first_not_of(' ', ptr);
        if (ptr == std::string::npos)
            break;
        // Find end of next word
        size_t endword = in.find_first_of(' ', ptr);
        if (endword == std::string::npos)
            endword = in.size();
        // Add newline and indentation if this wraps over the allowed width
        if (col > 0)
        {
            if ((col + endword - ptr) > width)
            {
                out << '\n';
                for(size_t i=0; i<indent; ++i)
                    out << ' ';
                col = 0;
            } else
                out << ' ';
        }
        // Append word
        out << in.substr(ptr, endword - ptr);
        col += endword - ptr + 1;
        ptr = endword;
    }
    return out.str();
}
