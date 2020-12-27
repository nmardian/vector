#ifndef DOGFIGHT_GAME_SETTINGS_H
#define DOGFIGHT_GAME_SETTINGS_H

#include "game/GameSettingsInterface.h"
#include "game/GameConstants.h"

namespace vector
{
    namespace game
    {
        class DogfightGameSettings : public GameSettingsInterface
        {
            public:

                /**
                 * @brief Constructor
                 * 
                 */
                DogfightGameSettings() = default;

                /**
                 * @brief Default destructor
                 * 
                 */
                virtual ~DogfightGameSettings() = default;

                /**
                 * @brief Get the GameType
                 * 
                 * @return vector::game::GAME_TYPE this Game's GameType
                 */
                vector::game::GAME_TYPE GetGameType() const override;

                /**
                 * @brief Get the number of Players for this GameType
                 * 
                 * @return uint8_t the number of Players for this GameType
                 */
                uint8_t GetNumPlayers() const override;

                /**
                 * @brief Set the number of Players
                 * 
                 * @param numPlayers the number of players to be set
                 * 
                 * @return whether the number of Players was set (ie. between Min and Max players)
                 */
                bool SetNumPlayers(const uint8_t numPlayers) override;

                /**
                 * @brief Get the number of Movers per team for this GameType
                 * 
                 * @return uint8_t the number of Movers per team for this GameType
                 */
                uint8_t GetNumMoversPerSide() const override;

                /**
                 * @brief Set the number of Movers on each side
                 * 
                 * @param numMoversPerSide the number of Movers on each side
                 * @return true if the number of Movers is between Min and Max
                 * @return false otherwise
                 */
                bool SetNumMoversPerSide(uint8_t numMoversPerSide) override;

                DogfightGameSettings(const DogfightGameSettings&) = delete;
                DogfightGameSettings& operator=(const DogfightGameSettings&) = delete;
                DogfightGameSettings(DogfightGameSettings&&) = delete;
                DogfightGameSettings& operator-(DogfightGameSettings&&) = delete;

            private:
                vector::game::GAME_TYPE m_GameType{vector::game::GAME_TYPE::DOGFIGHT};
                uint8_t m_NumPlayers{DOGFIGHT_DEFAULT_NUM_PLAYERS};
                uint8_t m_NumMoversPerSide{DOGFIGHT_DEFAULT_NUM_MOVERS_PER_SIDE};

        }; // class DogfightGameSettings
    } // namespace game
} // namepspace vector

#endif // DOGFIGHT_GAME_SETTINGS_H