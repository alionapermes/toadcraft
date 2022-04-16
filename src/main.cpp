#include <cstdlib>
#include <ctime>
#include <string>

#include "boost/algorithm/string/trim_all.hpp"
#include "boost/program_options.hpp"
#include "fmt/core.h"
#include "fmt/format.h"
#include "tgbot/tgbot.h"

#include "router.hpp"


int
main()
{
    using namespace fmt;
    namespace opt = boost::program_options;

    std::srand(std::time(nullptr));
    std::string token;

    opt::options_description desc;
    desc.add_options()
        (
            "token",
            opt::value(&token)->required(),
            "bot token"
        );
    opt::variables_map vm;
    opt::store(opt::parse_config_file("../toadcraft.conf", desc), vm);
    vm.notify();

    tc::Router router;
    TgBot::Bot bot(token);

    router.route(&bot);

    try {
        print("Bot username: {}\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll long_poll(bot);

        while (true) {
            print("Long poll started\n");
            long_poll.start();
        }
    } catch (const TgBot::TgException& e) {
        print("error: {}\n", e.what());
    }

    return 0;
}

