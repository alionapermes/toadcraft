#include "router.hpp"

#include "boost/algorithm/string/trim_all.hpp"


void
tc::Router::route(TgBot::Bot* bot)
{
    using namespace fmt;

    _bot = bot;

    bot->getEvents().onCommand("roll", [&bot](TgBot::Message::Ptr msg) {
        boost::trim_all(msg->text);

        if (msg->from->username == "talkenson" && msg->text != "/roll") {
            bot->getApi().sendMessage(
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

        bot->getApi().sendMessage(
            msg->chat->id,
            answer,
            false,
            msg->messageId
        );
    });

    bot->getEvents().onCommand("wannagf", [&bot](TgBot::Message::Ptr msg) {
        bot->getApi().sendMessage(
            msg->chat->id,
            "https://drive.google.com/drive/folders/"
            "1Pe2OAAG1FGmw5Zc29JCAWhCoIayuWi0F?usp=sharing",
            false,
            msg->messageId
        );
    });

    bot->getEvents().onCommand("help", [&bot](TgBot::Message::Ptr msg) {
        if (msg->from->username == "talkenson") {
            bot->getApi().sendMessage(
                msg->chat->id,
                "тебе ничего уже не поможет",
                false,
                msg->messageId
            );
        }
    });

    bot->getEvents().onCommand("wannabf", [&bot](TgBot::Message::Ptr msg) {
        if (msg->from->username == "talkenson") {
            bot->getApi().sendMessage(
                msg->chat->id,
                "t.me/secretdzen",
                false,
                msg->messageId
            );
        }
    });
}

