#include "command_handlers.hpp"

#include "boost/algorithm/string/trim_all.hpp"
#include "fmt/format.h"


std::string
tc::onRoll(TgBot::Message::Ptr msg)
{
    boost::trim_all(msg->text);

    int randomed       = std::rand() % 100;
    size_t space_index = msg->text.find(' ');
    std::string answer;

    if (space_index > 0 && space_index < msg->text.size()) {
        answer = fmt::format(
            "Chance of\n[{}]: {}%",
            msg->text.substr(space_index + 1),
            randomed
        );
    } else
        answer = std::to_string(randomed);

    return answer;
}

std::string
tc::onWannaGf(TgBot::Message::Ptr msg)
{
    return
        "https://drive.google.com/drive/folders/"
        "1Pe2OAAG1FGmw5Zc29JCAWhCoIayuWi0F?usp=sharing";
}

std::string
tc::onWannaBf(TgBot::Message::Ptr msg)
{ return "t.me/secretdzen"; }

