#include json_parser.h
#include <sstream>
#include <cctype>

bool JsonParser::parse(const std::string& json, std::map<std::string, std::string>& result) {
    result.clear();
    std::string trimmed = trim(json);
    if (trimmed.empty() || trimmed[0] != '{' || trimmed[trimmed.length()-1] != '}') return false;
    std::string content = trimmed.substr(1, trimmed.length() - 2);
    size_t pos = 0;
    while (pos < content.length()) {
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ',')) pos++;
        if (pos >= content.length()) break;
        if (content[pos] != '"') return false;
        size_t key_start = ++pos;
        while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
        if (pos >= content.length()) return false;
        std::string key = content.substr(key_start, pos - key_start);
        pos++;
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ':')) pos++;
        if (pos >= content.length()) return false;
        std::string value;
        if (content[pos] == '"') {
            size_t val_start = ++pos;
            while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
            value = content.substr(val_start, pos - val_start);
            pos++;
        } else if (content[pos] == 't' || content[pos] == 'f') {
            if (content.substr(pos, 4) == "true") { value = true; pos += 4; }
            else if (content.substr(pos, 5) == "false") { value = false; pos += 5; }
            else return false;
        } else if (isdigit(content[pos]) || content[pos] == '-') {
            size_t num_start = pos;
            while (pos < content.length() && (isdigit(content[pos]) || content[pos] == '.' || content[pos] == '-')) pos++;
            value = content.substr(num_start, pos - num_start);
        } else return false;
        result[key] = value;
    }
    return true;
}

std::string JsonParser::build(const std::map<std::string, std::string>& data) {
    std::ostringstream oss;
    oss << ;
    bool first = true;
    for (const auto& kv : data) {
        if (!first) oss << ;
    return oss.str();
}

std::string JsonParser::escape(const std::string& str) {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
            case '"': oss << \"; break;
            case '\': oss << \\; break;
            case '\b': oss << b; break;
            case '\n': oss << n; break;
            case '\r': oss << r; break;
            case '\t': oss << t; break;
            default: oss << c;
        }
    }
    return oss.str();
}

std::string JsonParser::trim(const std::string& str) {
    size_t start = 0;
    while (start < str.length() && isspace(str[start])) start++;
    size_t end = str.length();
    while (end > start && isspace(str[end-1])) end--;
    return str.substr(start, end - start);
}

std::string JsonParser::build_with_nested(const std::map<std::string, std::string>& data,
                                           const std::map<std::string, std::map<std::string, std::string>>& nested) {
    std::ostringstream oss;
    oss << ;
    bool first = true;
    for (const auto& kv : data) {
        if (!first) oss << ;
    return oss.str();
}
ENDFILE cat > /home/linaro/project/whisper.cpp/service/src/json_parser.cpp << 'ENDFILE'
#include json_parser.h
#include <sstream>
#include <cctype>

bool JsonParser::parse(const std::string& json, std::map<std::string, std::string>& result) {
    result.clear();
    std::string trimmed = trim(json);
    if (trimmed.empty() || trimmed[0] != '{' || trimmed[trimmed.length()-1] != '}') return false;
    std::string content = trimmed.substr(1, trimmed.length() - 2);
    size_t pos = 0;
    while (pos < content.length()) {
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ',')) pos++;
        if (pos >= content.length()) break;
        if (content[pos] != '"') return false;
        size_t key_start = ++pos;
        while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
        if (pos >= content.length()) return false;
        std::string key = content.substr(key_start, pos - key_start);
        pos++;
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ':')) pos++;
        if (pos >= content.length()) return false;
        std::string value;
        if (content[pos] == '"') {
            size_t val_start = ++pos;
            while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
            value = content.substr(val_start, pos - val_start);
            pos++;
        } else if (content[pos] == 't' || content[pos] == 'f') {
            if (content.substr(pos, 4) == "true") { value = true; pos += 4; }
            else if (content.substr(pos, 5) == "false") { value = false; pos += 5; }
            else return false;
        } else if (isdigit(content[pos]) || content[pos] == '-') {
            size_t num_start = pos;
            while (pos < content.length() && (isdigit(content[pos]) || content[pos] == '.' || content[pos] == '-')) pos++;
            value = content.substr(num_start, pos - num_start);
        } else return false;
        result[key] = value;
    }
    return true;
}

std::string JsonParser::build(const std::map<std::string, std::string>& data) {
    std::ostringstream oss;
    oss << ;
    bool first = true;
    for (const auto& kv : data) {
        if (!first) oss << ;
    return oss.str();
}

std::string JsonParser::escape(const std::string& str) {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
            case '"': oss << \"; break;
            case '\': oss << \\; break;
            case '\b': oss << b; break;
            case '\n': oss << n; break;
            case '\r': oss << r; break;
            case '\t': oss << t; break;
            default: oss << c;
        }
    }
    return oss.str();
}

std::string JsonParser::trim(const std::string& str) {
    size_t start = 0;
    while (start < str.length() && isspace(str[start])) start++;
    size_t end = str.length();
    while (end > start && isspace(str[end-1])) end--;
    return str.substr(start, end - start);
}

std::string JsonParser::build_with_nested(const std::map<std::string, std::string>& data,
                                           const std::map<std::string, std::map<std::string, std::string>>& nested) {
    std::ostringstream oss;
    oss << ;
        first = false;
        oss << " << kv.first << ":" << escape(kv.second) << ";
    }
    for (const auto& kv : nested) {
        if (!first) oss << ;
    return oss.str();
}
ENDFILE cat > /home/linaro/project/whisper.cpp/service/src/json_parser.cpp << 'ENDFILE'
#include json_parser.h
#include <sstream>
#include <cctype>

bool JsonParser::parse(const std::string& json, std::map<std::string, std::string>& result) {
    result.clear();
    std::string trimmed = trim(json);
    if (trimmed.empty() || trimmed[0] != '{' || trimmed[trimmed.length()-1] != '}') return false;
    std::string content = trimmed.substr(1, trimmed.length() - 2);
    size_t pos = 0;
    while (pos < content.length()) {
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ',')) pos++;
        if (pos >= content.length()) break;
        if (content[pos] != '"') return false;
        size_t key_start = ++pos;
        while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
        if (pos >= content.length()) return false;
        std::string key = content.substr(key_start, pos - key_start);
        pos++;
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ':')) pos++;
        if (pos >= content.length()) return false;
        std::string value;
        if (content[pos] == '"') {
            size_t val_start = ++pos;
            while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
            value = content.substr(val_start, pos - val_start);
            pos++;
        } else if (content[pos] == 't' || content[pos] == 'f') {
            if (content.substr(pos, 4) == "true") { value = true; pos += 4; }
            else if (content.substr(pos, 5) == "false") { value = false; pos += 5; }
            else return false;
        } else if (isdigit(content[pos]) || content[pos] == '-') {
            size_t num_start = pos;
            while (pos < content.length() && (isdigit(content[pos]) || content[pos] == '.' || content[pos] == '-')) pos++;
            value = content.substr(num_start, pos - num_start);
        } else return false;
        result[key] = value;
    }
    return true;
}

std::string JsonParser::build(const std::map<std::string, std::string>& data) {
    std::ostringstream oss;
    oss << ;
    bool first = true;
    for (const auto& kv : data) {
        if (!first) oss << ;
    return oss.str();
}

std::string JsonParser::escape(const std::string& str) {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
            case '"': oss << \"; break;
            case '\': oss << \\; break;
            case '\b': oss << b; break;
            case '\n': oss << n; break;
            case '\r': oss << r; break;
            case '\t': oss << t; break;
            default: oss << c;
        }
    }
    return oss.str();
}

std::string JsonParser::trim(const std::string& str) {
    size_t start = 0;
    while (start < str.length() && isspace(str[start])) start++;
    size_t end = str.length();
    while (end > start && isspace(str[end-1])) end--;
    return str.substr(start, end - start);
}

std::string JsonParser::build_with_nested(const std::map<std::string, std::string>& data,
                                           const std::map<std::string, std::map<std::string, std::string>>& nested) {
    std::ostringstream oss;
    oss << ;
        first = false;
        oss << " << kv.first << ":;
        bool nested_first = true;
        for (const auto& nested_kv : kv.second) {
            if (!nested_first) oss << ;
    }
    oss << ;
    return oss.str();
}
ENDFILE cat > /home/linaro/project/whisper.cpp/service/src/json_parser.cpp << 'ENDFILE'
#include json_parser.h
#include <sstream>
#include <cctype>

bool JsonParser::parse(const std::string& json, std::map<std::string, std::string>& result) {
    result.clear();
    std::string trimmed = trim(json);
    if (trimmed.empty() || trimmed[0] != '{' || trimmed[trimmed.length()-1] != '}') return false;
    std::string content = trimmed.substr(1, trimmed.length() - 2);
    size_t pos = 0;
    while (pos < content.length()) {
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ',')) pos++;
        if (pos >= content.length()) break;
        if (content[pos] != '"') return false;
        size_t key_start = ++pos;
        while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
        if (pos >= content.length()) return false;
        std::string key = content.substr(key_start, pos - key_start);
        pos++;
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ':')) pos++;
        if (pos >= content.length()) return false;
        std::string value;
        if (content[pos] == '"') {
            size_t val_start = ++pos;
            while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
            value = content.substr(val_start, pos - val_start);
            pos++;
        } else if (content[pos] == 't' || content[pos] == 'f') {
            if (content.substr(pos, 4) == "true") { value = true; pos += 4; }
            else if (content.substr(pos, 5) == "false") { value = false; pos += 5; }
            else return false;
        } else if (isdigit(content[pos]) || content[pos] == '-') {
            size_t num_start = pos;
            while (pos < content.length() && (isdigit(content[pos]) || content[pos] == '.' || content[pos] == '-')) pos++;
            value = content.substr(num_start, pos - num_start);
        } else return false;
        result[key] = value;
    }
    return true;
}

std::string JsonParser::build(const std::map<std::string, std::string>& data) {
    std::ostringstream oss;
    oss << ;
    bool first = true;
    for (const auto& kv : data) {
        if (!first) oss << ;
    return oss.str();
}

std::string JsonParser::escape(const std::string& str) {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
            case '"': oss << \"; break;
            case '\': oss << \\; break;
            case '\b': oss << b; break;
            case '\n': oss << n; break;
            case '\r': oss << r; break;
            case '\t': oss << t; break;
            default: oss << c;
        }
    }
    return oss.str();
}

std::string JsonParser::trim(const std::string& str) {
    size_t start = 0;
    while (start < str.length() && isspace(str[start])) start++;
    size_t end = str.length();
    while (end > start && isspace(str[end-1])) end--;
    return str.substr(start, end - start);
}

std::string JsonParser::build_with_nested(const std::map<std::string, std::string>& data,
                                           const std::map<std::string, std::map<std::string, std::string>>& nested) {
    std::ostringstream oss;
    oss << ;
        first = false;
        oss << " << kv.first << ":;
            nested_first = false;
            oss << " << nested_kv.first << ":" << escape(nested_kv.second) << ";
        }
        oss << ;
    }
    oss << ;
    return oss.str();
}
ENDFILE cat > /home/linaro/project/whisper.cpp/service/src/json_parser.cpp << 'ENDFILE'
#include json_parser.h
#include <sstream>
#include <cctype>

bool JsonParser::parse(const std::string& json, std::map<std::string, std::string>& result) {
    result.clear();
    std::string trimmed = trim(json);
    if (trimmed.empty() || trimmed[0] != '{' || trimmed[trimmed.length()-1] != '}') return false;
    std::string content = trimmed.substr(1, trimmed.length() - 2);
    size_t pos = 0;
    while (pos < content.length()) {
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ',')) pos++;
        if (pos >= content.length()) break;
        if (content[pos] != '"') return false;
        size_t key_start = ++pos;
        while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
        if (pos >= content.length()) return false;
        std::string key = content.substr(key_start, pos - key_start);
        pos++;
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ':')) pos++;
        if (pos >= content.length()) return false;
        std::string value;
        if (content[pos] == '"') {
            size_t val_start = ++pos;
            while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
            value = content.substr(val_start, pos - val_start);
            pos++;
        } else if (content[pos] == 't' || content[pos] == 'f') {
            if (content.substr(pos, 4) == "true") { value = true; pos += 4; }
            else if (content.substr(pos, 5) == "false") { value = false; pos += 5; }
            else return false;
        } else if (isdigit(content[pos]) || content[pos] == '-') {
            size_t num_start = pos;
            while (pos < content.length() && (isdigit(content[pos]) || content[pos] == '.' || content[pos] == '-')) pos++;
            value = content.substr(num_start, pos - num_start);
        } else return false;
        result[key] = value;
    }
    return true;
}

std::string JsonParser::build(const std::map<std::string, std::string>& data) {
    std::ostringstream oss;
    oss << ;
        first = false;
        oss << " << kv.first << ":" << escape(kv.second) << ";
    }
    oss << ;
    return oss.str();
}

std::string JsonParser::escape(const std::string& str) {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
            case '"': oss << \"; break;
            case '\': oss << \\; break;
            case '\b': oss << b; break;
            case '\n': oss << n; break;
            case '\r': oss << r; break;
            case '\t': oss << t; break;
            default: oss << c;
        }
    }
    return oss.str();
}

std::string JsonParser::trim(const std::string& str) {
    size_t start = 0;
    while (start < str.length() && isspace(str[start])) start++;
    size_t end = str.length();
    while (end > start && isspace(str[end-1])) end--;
    return str.substr(start, end - start);
}

std::string JsonParser::build_with_nested(const std::map<std::string, std::string>& data,
                                           const std::map<std::string, std::map<std::string, std::string>>& nested) {
    std::ostringstream oss;
    oss << ;
    bool first = true;
    for (const auto& kv : data) {
        if (!first) oss << ;
    return oss.str();
}
ENDFILE cat > /home/linaro/project/whisper.cpp/service/src/json_parser.cpp << 'ENDFILE'
#include json_parser.h
#include <sstream>
#include <cctype>

bool JsonParser::parse(const std::string& json, std::map<std::string, std::string>& result) {
    result.clear();
    std::string trimmed = trim(json);
    if (trimmed.empty() || trimmed[0] != '{' || trimmed[trimmed.length()-1] != '}') return false;
    std::string content = trimmed.substr(1, trimmed.length() - 2);
    size_t pos = 0;
    while (pos < content.length()) {
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ',')) pos++;
        if (pos >= content.length()) break;
        if (content[pos] != '"') return false;
        size_t key_start = ++pos;
        while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
        if (pos >= content.length()) return false;
        std::string key = content.substr(key_start, pos - key_start);
        pos++;
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ':')) pos++;
        if (pos >= content.length()) return false;
        std::string value;
        if (content[pos] == '"') {
            size_t val_start = ++pos;
            while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
            value = content.substr(val_start, pos - val_start);
            pos++;
        } else if (content[pos] == 't' || content[pos] == 'f') {
            if (content.substr(pos, 4) == "true") { value = true; pos += 4; }
            else if (content.substr(pos, 5) == "false") { value = false; pos += 5; }
            else return false;
        } else if (isdigit(content[pos]) || content[pos] == '-') {
            size_t num_start = pos;
            while (pos < content.length() && (isdigit(content[pos]) || content[pos] == '.' || content[pos] == '-')) pos++;
            value = content.substr(num_start, pos - num_start);
        } else return false;
        result[key] = value;
    }
    return true;
}

std::string JsonParser::build(const std::map<std::string, std::string>& data) {
    std::ostringstream oss;
    oss << ;
        first = false;
        oss << " << kv.first << ":" << escape(kv.second) << ";
    }
    oss << ;
    return oss.str();
}

std::string JsonParser::escape(const std::string& str) {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
            case '"': oss << \"; break;
            case '\': oss << \\; break;
            case '\b': oss << b; break;
            case '\n': oss << n; break;
            case '\r': oss << r; break;
            case '\t': oss << t; break;
            default: oss << c;
        }
    }
    return oss.str();
}

std::string JsonParser::trim(const std::string& str) {
    size_t start = 0;
    while (start < str.length() && isspace(str[start])) start++;
    size_t end = str.length();
    while (end > start && isspace(str[end-1])) end--;
    return str.substr(start, end - start);
}

std::string JsonParser::build_with_nested(const std::map<std::string, std::string>& data,
                                           const std::map<std::string, std::map<std::string, std::string>>& nested) {
    std::ostringstream oss;
    oss << ;
        first = false;
        oss << " << kv.first << ":" << escape(kv.second) << ";
    }
    for (const auto& kv : nested) {
        if (!first) oss << ;
    return oss.str();
}
ENDFILE cat > /home/linaro/project/whisper.cpp/service/src/json_parser.cpp << 'ENDFILE'
#include json_parser.h
#include <sstream>
#include <cctype>

bool JsonParser::parse(const std::string& json, std::map<std::string, std::string>& result) {
    result.clear();
    std::string trimmed = trim(json);
    if (trimmed.empty() || trimmed[0] != '{' || trimmed[trimmed.length()-1] != '}') return false;
    std::string content = trimmed.substr(1, trimmed.length() - 2);
    size_t pos = 0;
    while (pos < content.length()) {
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ',')) pos++;
        if (pos >= content.length()) break;
        if (content[pos] != '"') return false;
        size_t key_start = ++pos;
        while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
        if (pos >= content.length()) return false;
        std::string key = content.substr(key_start, pos - key_start);
        pos++;
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ':')) pos++;
        if (pos >= content.length()) return false;
        std::string value;
        if (content[pos] == '"') {
            size_t val_start = ++pos;
            while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
            value = content.substr(val_start, pos - val_start);
            pos++;
        } else if (content[pos] == 't' || content[pos] == 'f') {
            if (content.substr(pos, 4) == "true") { value = true; pos += 4; }
            else if (content.substr(pos, 5) == "false") { value = false; pos += 5; }
            else return false;
        } else if (isdigit(content[pos]) || content[pos] == '-') {
            size_t num_start = pos;
            while (pos < content.length() && (isdigit(content[pos]) || content[pos] == '.' || content[pos] == '-')) pos++;
            value = content.substr(num_start, pos - num_start);
        } else return false;
        result[key] = value;
    }
    return true;
}

std::string JsonParser::build(const std::map<std::string, std::string>& data) {
    std::ostringstream oss;
    oss << ;
        first = false;
        oss << " << kv.first << ":" << escape(kv.second) << ";
    }
    oss << ;
    return oss.str();
}

std::string JsonParser::escape(const std::string& str) {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
            case '"': oss << \"; break;
            case '\': oss << \\; break;
            case '\b': oss << b; break;
            case '\n': oss << n; break;
            case '\r': oss << r; break;
            case '\t': oss << t; break;
            default: oss << c;
        }
    }
    return oss.str();
}

std::string JsonParser::trim(const std::string& str) {
    size_t start = 0;
    while (start < str.length() && isspace(str[start])) start++;
    size_t end = str.length();
    while (end > start && isspace(str[end-1])) end--;
    return str.substr(start, end - start);
}

std::string JsonParser::build_with_nested(const std::map<std::string, std::string>& data,
                                           const std::map<std::string, std::map<std::string, std::string>>& nested) {
    std::ostringstream oss;
    oss << ;
        first = false;
        oss << " << kv.first << ":;
        bool nested_first = true;
        for (const auto& nested_kv : kv.second) {
            if (!nested_first) oss << ;
    }
    oss << ;
    return oss.str();
}
ENDFILE cat > /home/linaro/project/whisper.cpp/service/src/json_parser.cpp << 'ENDFILE'
#include json_parser.h
#include <sstream>
#include <cctype>

bool JsonParser::parse(const std::string& json, std::map<std::string, std::string>& result) {
    result.clear();
    std::string trimmed = trim(json);
    if (trimmed.empty() || trimmed[0] != '{' || trimmed[trimmed.length()-1] != '}') return false;
    std::string content = trimmed.substr(1, trimmed.length() - 2);
    size_t pos = 0;
    while (pos < content.length()) {
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ',')) pos++;
        if (pos >= content.length()) break;
        if (content[pos] != '"') return false;
        size_t key_start = ++pos;
        while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
        if (pos >= content.length()) return false;
        std::string key = content.substr(key_start, pos - key_start);
        pos++;
        while (pos < content.length() && (isspace(content[pos]) || content[pos] == ':')) pos++;
        if (pos >= content.length()) return false;
        std::string value;
        if (content[pos] == '"') {
            size_t val_start = ++pos;
            while (pos < content.length() && content[pos] != '"') { if (content[pos] == '\' && pos + 1 < content.length()) pos++; pos++; }
            value = content.substr(val_start, pos - val_start);
            pos++;
        } else if (content[pos] == 't' || content[pos] == 'f') {
            if (content.substr(pos, 4) == "true") { value = true; pos += 4; }
            else if (content.substr(pos, 5) == "false") { value = false; pos += 5; }
            else return false;
        } else if (isdigit(content[pos]) || content[pos] == '-') {
            size_t num_start = pos;
            while (pos < content.length() && (isdigit(content[pos]) || content[pos] == '.' || content[pos] == '-')) pos++;
            value = content.substr(num_start, pos - num_start);
        } else return false;
        result[key] = value;
    }
    return true;
}

std::string JsonParser::build(const std::map<std::string, std::string>& data) {
    std::ostringstream oss;
    oss << ;
        first = false;
        oss << " << kv.first << ":" << escape(kv.second) << ";
    }
    oss << ;
    return oss.str();
}

std::string JsonParser::escape(const std::string& str) {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
            case '"': oss << \"; break;
            case '\': oss << \\; break;
            case '\b': oss << b; break;
            case '\n': oss << n; break;
            case '\r': oss << r; break;
            case '\t': oss << t; break;
            default: oss << c;
        }
    }
    return oss.str();
}

std::string JsonParser::trim(const std::string& str) {
    size_t start = 0;
    while (start < str.length() && isspace(str[start])) start++;
    size_t end = str.length();
    while (end > start && isspace(str[end-1])) end--;
    return str.substr(start, end - start);
}

std::string JsonParser::build_with_nested(const std::map<std::string, std::string>& data,
                                           const std::map<std::string, std::map<std::string, std::string>>& nested) {
    std::ostringstream oss;
    oss << ;
        first = false;
        oss << " << kv.first << ":;
            nested_first = false;
            oss << " << nested_kv.first << ":" << escape(nested_kv.second) << ";
        }
        oss << ;
    }
    oss << ;
    return oss.str();
}
