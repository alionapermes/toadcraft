#include <cstdlib>
#include <ctime>
#include <string>

#include "boost/algorithm/string.hpp"
#include "boost/program_options.hpp"
#include "fmt/core.h"
#include "fmt/format.h"
#include "tgbot/tgbot.h"


int main()
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


    TgBot::Bot bot(token);
    bot.getEvents().onCommand("roll", [&bot](TgBot::Message::Ptr msg) {
        using namespace boost;

        int randomed = std::rand() % 100;
        std::string answer;
        std::vector<std::string> parts;

        split(parts, msg->text, is_any_of(" "), token_compress_on);

        if (parts.size() > 1)
            answer = std::to_string(randomed);
        else
            answer = fmt::format("Chance of\n[{}]: {}", parts[1], randomed);

        bot.getApi().sendMessage(msg->chat->id, answer);
    });

    bot.getEvents().onCommand("wannagf", [&bot](TgBot::Message::Ptr msg) {
        bot.getApi().sendMessage(
            msg->chat->id,
            "https://drive.google.com/drive/folders/"
            "1Pe2OAAG1FGmw5Zc29JCAWhCoIayuWi0F?usp=sharing"
        );
    });

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

