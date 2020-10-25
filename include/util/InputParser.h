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
            
                InputParser() = delete;
                virtual ~InputParser() = default;

                static Command Parse(const std::string& input);

            private:
                static std::string TrimWhitespace(const std::string& input);
        };
    }
}

#endif // INPUT_PARSER_H