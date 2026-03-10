#ifndef __MORLOC_TEXT_HPP__
#define __MORLOC_TEXT_HPP__

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

std::vector<std::string> morloc_split(const std::string& delim, const std::string& s) {
    std::vector<std::string> result;
    if (delim.empty()) {
        for (char c : s) {
            result.push_back(std::string(1, c));
        }
        return result;
    }
    size_t start = 0;
    size_t pos;
    while ((pos = s.find(delim, start)) != std::string::npos) {
        result.push_back(s.substr(start, pos - start));
        start = pos + delim.size();
    }
    result.push_back(s.substr(start));
    return result;
}

std::vector<std::string> morloc_lines(const std::string& s) {
    return morloc_split("\n", s);
}

std::vector<std::string> morloc_words(const std::string& s) {
    std::vector<std::string> result;
    std::istringstream iss(s);
    std::string word;
    while (iss >> word) {
        result.push_back(word);
    }
    return result;
}

std::vector<std::string> morloc_chars(const std::string& s) {
    std::vector<std::string> result;
    for (char c : s) {
        result.push_back(std::string(1, c));
    }
    return result;
}

std::string morloc_join(const std::string& delim, const std::vector<std::string>& xs) {
    std::string result;
    for (size_t i = 0; i < xs.size(); i++) {
        if (i > 0) result += delim;
        result += xs[i];
    }
    return result;
}

std::string morloc_unlines(const std::vector<std::string>& xs) {
    return morloc_join("\n", xs);
}

std::string morloc_unwords(const std::vector<std::string>& xs) {
    return morloc_join(" ", xs);
}

bool morloc_contains(const std::string& needle, const std::string& haystack) {
    return haystack.find(needle) != std::string::npos;
}

bool morloc_startsWith(const std::string& prefix, const std::string& s) {
    if (prefix.size() > s.size()) return false;
    return s.compare(0, prefix.size(), prefix) == 0;
}

bool morloc_endsWith(const std::string& suffix, const std::string& s) {
    if (suffix.size() > s.size()) return false;
    return s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::string morloc_toUpper(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string morloc_toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string morloc_trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(start, end - start + 1);
}

std::string morloc_trimStart(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";
    return s.substr(start);
}

std::string morloc_trimEnd(const std::string& s) {
    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    if (end == std::string::npos) return "";
    return s.substr(0, end + 1);
}

std::string morloc_replace(const std::string& old_str, const std::string& new_str, const std::string& s) {
    std::string result = s;
    size_t pos = result.find(old_str);
    if (pos != std::string::npos) {
        result.replace(pos, old_str.size(), new_str);
    }
    return result;
}

std::string morloc_replaceAll(const std::string& old_str, const std::string& new_str, const std::string& s) {
    std::string result = s;
    size_t pos = 0;
    while ((pos = result.find(old_str, pos)) != std::string::npos) {
        result.replace(pos, old_str.size(), new_str);
        pos += new_str.size();
    }
    return result;
}

std::string morloc_padLeft(int width, const std::string& fill, const std::string& s) {
    if (fill.empty() || (int)s.size() >= width) return s;
    int pad_needed = width - (int)s.size();
    std::string padding;
    while ((int)padding.size() < pad_needed) {
        padding += fill;
    }
    padding = padding.substr(0, pad_needed);
    return padding + s;
}

std::string morloc_padRight(int width, const std::string& fill, const std::string& s) {
    if (fill.empty() || (int)s.size() >= width) return s;
    int pad_needed = width - (int)s.size();
    std::string padding;
    while ((int)padding.size() < pad_needed) {
        padding += fill;
    }
    padding = padding.substr(0, pad_needed);
    return s + padding;
}

bool morloc_isBlank(const std::string& s) {
    for (char c : s) {
        if (!std::isspace(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

#endif
