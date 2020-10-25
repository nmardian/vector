#ifndef COMMAND_H
#define COMMAND_H

namespace vector
{
    namespace util
    {
        enum class COMMAND_TYPE 
        {
            UNK,
            VECTOR,
            IDENTIFY,
            AQUIRE,
            LAUNCH
        };

        struct Command
        {
            COMMAND_TYPE command{COMMAND_TYPE::UNK};
        };
    } // namespace util
} // namespace vector

#endif // COMMAND_H