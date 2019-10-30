
#include <glm/glm.hpp>

typedef glm::u8vec4 Color;
typedef glm::vec2   FVec2;
typedef glm::ivec2  IVec2;

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