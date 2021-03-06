#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string>

#include "util/Command.h"

namespace vector
{
    namespace util
    {
        class InputParser
        {
            public:
                /**
                 * @brief Destroy the Input Parser object
                 * 
                 */
                virtual ~InputParser() = default;

                /**
                 * @brief Parse and input string for commands
                 * 
                 * @param input     string to be parsed
                 * @return Command  command resulting from parsing the input string
                 */
                static Command Parse(const std::string& input);

                // Delete default constructor, copy and move constructors
                InputParser() = delete;
                InputParser(const InputParser& other) = delete;
                InputParser& operator=(const InputParser& other) = delete;
                InputParser(InputParser&& other) = delete;
                InputParser& operator=(InputParser&& other) = delete;

            private:

                /**
                 * @brief Trim leading and trailing whitespace from a string
                 * 
                 * @param input         string to be trimmed
                 * @return std::string  trimmed string
                 */
                static std::string TrimWhitespace(const std::string& input);
        };
    }
}

#endif // INPUT_PARSER_H