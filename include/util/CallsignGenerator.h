#ifndef CALLSIGN_GENERATOR_H
#define CALLSIGN_GENERATOR_H

#include <string>
#include <vector>

namespace vector
{
    namespace util
    {
        class CallsignGenerator
        {
            public:

                /**
                 * @brief Destructor
                 * 
                 */
                virtual ~CallsignGenerator() = default;

                /**
                 * @brief Generate random friendly unit callsigns
                 * 
                 * @param numCallsigns the number of friendly callsigns to generate, max of 26
                 * @return std::vector<std::string> random friendly callsigns
                 */
                static std::vector<std::string> GenerateRandomFriendCallsigns(int numCallsigns);

                /**
                 * @brief Generate random enemy callsigns
                 * 
                 * @param numCallsigns the number of enemy callsigns to generate, max of 26
                 * @return std::vector<std::string> random enemy callsigns
                 */
                static std::vector<std::string> GenerateRandomEnemyCallsigns(int numCallsigns);

                CallsignGenerator() = delete;
                CallsignGenerator(const CallsignGenerator&) = delete;
                CallsignGenerator& operator=(const CallsignGenerator&) = delete;
                CallsignGenerator(CallsignGenerator&&) = delete;
                CallsignGenerator& operator=(CallsignGenerator&&) = delete;
        };
    } // namespace util
} // namespace vector

#endif // CALLSIGN_GENERATOR_H