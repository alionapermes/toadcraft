#include "fmt/format.h"
#include "tgbot/tgbot.h"


namespace tc {


class Router
{
private:
    TgBot::Bot* _bot;

public:
    Router() = default;

public:
    void route(TgBot::Bot* bot);
};


}

