#if ! defined SEQ66_STRFUNCTIONS_HPP
#define SEQ66_STRFUNCTIONS_HPP

/**
 * \file          strfunctions.hpp
 *
 *    Provides the declarations for safe replacements for some C++
 *    file functions.
 *
 * \author        Chris Ahlstrom
 * \date          2018-11-23
 * \updates       2020-12-17
 * \version       $Revision$
 *
 *    Also see the strfunctions.cpp module.
 */

#include <memory>                       /* std::unique_ptr<> template class */
#include <string>                       /* std::string class                */
#include <vector>                       /* std::vector class                */

#include "midi/midibytes.hpp"           /* seq66::midibool type             */

/*
 *  Do not document a namespace; it breaks Doxygen.
 */

namespace seq66
{

/**
 *  Lists of characters to trim from strings.
 */

const std::string SEQ66_TRIM_CHARS        = " \t\r\n\v\f";
const std::string SEQ66_TRIM_CHARS_QUOTES = " \t\r\n\v\f\"'";
const std::string SEQ66_TRIM_CHARS_PATHS  = " /\\";

/*
 * Global (free) string functions.
 */

extern bool is_empty_string (const std::string & item);
extern std::string empty_string ();
extern bool is_questionable_string (const std::string & item);
extern std::string questionable_string ();
extern bool contains (const std::string & original, const std::string & target);
extern std::string strip_comments (const std::string & item);
extern std::string strip_quotes (const std::string & item);
extern std::string add_quotes (const std::string & item);
extern std::string double_quotes ();
extern bool strncompare (const std::string & a, const std::string & b, size_t n);
extern bool strcasecompare (const std::string & a, const std::string & b);
extern std::string & ltrim
(
    std::string & str, const std::string & chars = SEQ66_TRIM_CHARS
);
extern std::string & rtrim
(
    std::string & str, const std::string & chars = SEQ66_TRIM_CHARS
);
extern std::string trim
(
    const std::string & str, const std::string & chars = SEQ66_TRIM_CHARS
);
extern std::string string_replace
(
    const std::string & source,
    const std::string & target,
    const std::string & replacement,
    int n = -1
);
extern bool string_to_bool (const std::string & s, bool defalt = false);
extern double string_to_double (const std::string & s, double defalt = 0.0);
extern long string_to_long (const std::string & s, long defalt = 0L);
extern int string_to_int (const std::string & s, int defalt = 0);
extern midibyte string_to_midibyte (const std::string & s, midibyte defalt = 0);
extern std::string shorten_file_spec (const std::string & fpath, int leng);
extern bool string_not_void (const std::string & s);
extern bool string_is_void (const std::string & s);
extern bool strings_match (const std::string & target, const std::string & x);
extern std::string bool_to_string (bool x);
extern char bool_to_char (bool x);
extern int tokenize_stanzas
(
    std::vector<std::string> & tokens,
    const std::string & source,
    std::string::size_type bleft = 0,
    const std::string & brackets = ""
);
extern std::vector<std::string> tokenize
(
    const std::string & source,
    const std::string delimiter = " "
);
extern std::string write_stanza_bits
(
    const midibooleans & bitbucket,
    bool newstyle = true
);
extern void push_8_bits (midibooleans & target, unsigned bits);
extern bool parse_stanza_bits
(
    midibooleans & target,
    const std::string & mutestanza
);

/*
 *  This comes, slightly modified to avoid throwing an exception, from:
 *
 * https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
 *
 *  Extra space for '\0', but it won't be included in the result.
 *
 *  It is useful for C++11.  Once C++20 becomes common, the following could be
 *  used:
 *
\verbatim
 *      #include <format>
 *      std::string result = std::format("{} {}!", "Hello", "world");
\endverbatim
 */

template<typename ... Args>
std::string string_format (const std::string & format, Args ... args)
{
    std::string result;
    size_t sz = std::snprintf(nullptr, 0, format.c_str(), args ...);
    if (sz > 0)
    {
        std::unique_ptr<char []> buf(new char[sz + 1]);
        std::snprintf(buf.get(), sz + 1, format.c_str(), args ...);
        result = std::string(buf.get(), buf.get() + sz);
    }
    return result;
}

}           // namespace seq66

#endif      // SEQ66_STRFUNCTIONS_HPP

/*
 * strfunctions.hpp
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */

