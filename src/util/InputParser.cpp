#include "util/InputParser.h"

#include <unordered_map>

namespace vector
{
    namespace util
    {
        const std::string COMMAND_STR_UNK = "unk";
        const std::string COMMAND_STR_VECTOR = "vector";
        const std::string COMMAND_STR_IDENTIFY = "identify";
        const std::string COMMAND_STR_AQUIRE = "aquire";
        const std::string COMMAND_STR_LAUNCH = "launch";

        const std::string VALID_COMMAND_CHARS = "qwertyuiopasdfghjklzxcvbnm1234567890";

        const std::unordered_map<std::string, COMMAND_TYPE> m_StringToCmdTypeMap = 
        {
            {COMMAND_STR_UNK, COMMAND_TYPE::UNK},
            {COMMAND_STR_VECTOR, COMMAND_TYPE::VECTOR},
            {COMMAND_STR_IDENTIFY, COMMAND_TYPE::IDENTIFY},
            {COMMAND_STR_AQUIRE, COMMAND_TYPE::AQUIRE},
            {COMMAND_STR_LAUNCH, COMMAND_TYPE::LAUNCH}
        };

        Command InputParser::Parse(const std::string& input)
        {
            Command result;
            std::string token;
            size_t start = 0;
            size_t end = 0;

            std::string trimmedStr = TrimWhitespace(input);
            end = trimmedStr.find(" ", start);
            
            token = trimmedStr.substr(start, end);
            auto mapItr = m_StringToCmdTypeMap.find(token);

            COMMAND_TYPE cmdType{COMMAND_TYPE::UNK};
            if(mapItr != m_StringToCmdTypeMap.end())
            {
                cmdType = mapItr->second; 
            }

            result.command = cmdType;

            return result;
        }

        std::string InputParser::TrimWhitespace(const std::string& input)
        {
            auto start = input.find_first_not_of(" ");
            auto end = input.find_last_of(VALID_COMMAND_CHARS);
            
            if(start != std::string::npos)
            {
                return input.substr(start, (end - start) + 1);
            }
            return input;
        }
    } // namespace util
} // namespace vector