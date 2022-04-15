#include <cstdlib>
#include <ctime>
#include <string>

#include "boost/algorithm/string/trim_all.hpp"
#include "boost/program_options.hpp"
#include "fmt/core.h"
#include "fmt/format.h"
#include "tgbot/tgbot.h"


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

    TgBot::Bot bot(token);

    bot.getEvents().onCommand("roll", [&bot](TgBot::Message::Ptr msg) {
        boost::trim_all(msg->text);

        if (msg->from->username == "talkenson" && msg->text != "/roll") {
            bot.getApi().sendMessage(
                msg->chat->id,
                "иди нахуй",
                false,
                msg->messageId
            );
            return;
        }

        int randomed       = std::rand() % 100;
        size_t space_index = msg->text.find(' ');
        std::string answer;

        if (space_index > 0 && space_index < msg->text.size()) {
            answer = format(
                "Chance of\n[{}]: {}%",
                msg->text.substr(space_index + 1),
                randomed
            );
        } else
            answer = std::to_string(randomed);

        bot.getApi().sendMessage(msg->chat->id, answer);
    });

    bot.getEvents().onCommand("wannagf", [&bot](TgBot::Message::Ptr msg) {
        bot.getApi().sendMessage(
            msg->chat->id,
            "https://drive.google.com/drive/folders/"
            "1Pe2OAAG1FGmw5Zc29JCAWhCoIayuWi0F?usp=sharing"
        );
    });

    bot.getEvents().onCommand("help", [&bot](TgBot::Message::Ptr msg) {
        if (msg->from->username == "talkenson") {
            bot.getApi().sendMessage(
                msg->chat->id,
                "тебе ничего уже не поможет",
                false,
                msg->messageId
            );
        }
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

