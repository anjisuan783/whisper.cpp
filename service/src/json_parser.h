#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>
#include <map>

class JsonParser {
public:
    static bool parse(const std::string& json, std::map<std::string, std::string>& result);
    static std::string build(const std::map<std::string, std::string>& data);
    static std::string build_with_nested(const std::map<std::string, std::string>& data,
                                          const std::map<std::string, std::map<std::string, std::string>>& nested);
    static std::string escape(const std::string& str);
    static std::string trim(const std::string& str);
};

#endif
