
#include <glm/glm.hpp>

typedef glm::u8vec4 Color;
typedef glm::vec2   FVec2;
typedef glm::ivec2  IVec2;

inline const Color ColorRed{155, 0, 0, 255};
inline const Color ColorGreen{0, 155, 0, 255};
inline const Color ColorYellow{155, 155, 0, 255};
inline const Color ColorGrey{155, 155, 155, 255};

enum EBackend
{
    EBackendSFML,
    EBackendDefault = EBackendSFML,
    EBackendSDL,
    EBackendAllegro,
    EBackendCOUNT
};

enum EKey
{
    EKey1,
    EKey2,
    EKey3,
    EKeyUP,
    EKeyDOWN,
    EKeyLEFT,
    EKeyRIGHT,
    EKeyESC,
    EKeySPACE,
    EKeyCOUNT
};