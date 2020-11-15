#ifndef COMMAND_H
#define COMMAND_H

namespace vector
{
    namespace util
    {
        /**
         * @brief Enum to denote the type of command
         * 
         */
        enum class COMMAND_TYPE 
        {
            UNK,
            VECTOR,
            IDENTIFY,
            AQUIRE,
            LAUNCH
        };

        /**
         * @brief Struct to embody a command
         * 
         */
        struct Command
        {
            COMMAND_TYPE command{COMMAND_TYPE::UNK};
            std::string subject;
            std::string object;
        };
    } // namespace util
} // namespace vector

#endif // COMMAND_H