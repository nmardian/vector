#include "util/CallsignGenerator.h"

#include <string>

namespace vector
{
    namespace util
    {
        std::vector<std::string> m_FriendlyCallsignList = {
            "able",
            "baker",
            "charlie",
            "dog",
            "easy",
            "fox",
            "george",
            "how",
            "item",
            "jig",
            "king",
            "love",
            "mike",
            "nan",
            "oboe",
            "peter",
            "queen",
            "roger",
            "sugar",
            "tare",
            "uncle",
            "victor",
            "william",
            "xray",
            "yoke",
            "zebra"
        };

        std::vector<std::string> m_EnemyCallsignList = {
            "anna",
            "boris",
            "vasily",
            "gregory",
            "dmitri",
            "yelena",
            "zhenya",
            "zinaida",
            "ivan",
            "konstantin",
            "leonid",
            "mikhail",
            "nikolai",
            "olga",
            "pavel",
            "roman",
            "semyon",
            "tatyana",
            "ulyana",
            "fyodor",
            "khariton",
            "chelovek",
            "shura",
            "yery",
            "yuri",
            "yakov"
        };

        std::vector<std::string> CallsignGenerator::GenerateRandomFriendCallsigns(int numCallsigns)
        {
            std::vector<std::string> result;

            auto callsignItr = m_FriendlyCallsignList.begin();
            for(int i = 0; i < numCallsigns; ++i)
            {
                if(callsignItr != m_FriendlyCallsignList.end())
                {
                    result.push_back(*callsignItr);
                    callsignItr++;
                }
            }

            return result;
        }

        std::vector<std::string> CallsignGenerator::GenerateRandomEnemyCallsigns(int numCallsigns)
        {
            std::vector<std::string> result;

            auto callsignItr = m_EnemyCallsignList.begin();
            for(int i = 0; i < numCallsigns; ++i)
            {
                if(callsignItr != m_EnemyCallsignList.end())
                {
                    result.push_back(*callsignItr);
                    callsignItr++;
                }
            }

            return result;
        }
    } // namespace util
} // namespace vector