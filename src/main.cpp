#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include "unistd.h"


#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

string  ReadFile(string linkFile){
    string line;

    ifstream in(linkFile); // open file to read
    if (in.is_open())
    {
        while (getline(in, line))
        {
            cout << line << std::endl;
        }
    }
    in.close();     // close file

    return line ;
};


int main() {
    string token("5764776656:AAG0JHg0sWGnszjM5Fqm5nG82zqyAVoydi0");
    printf("Token: %s\n", token.c_str());

    Bot bot(token);

//audio message
    const string audioFilePath = "Inputs/Bot_audio.ogg";
    const string audioMimeType = "audio/ogg";

    //video message
    const string videoFilePath = "Inputs/bot_video.mp4";
    const string videoMimeType = "video/mp4";

    // first message text
    const string first_FilePath = "Inputs/first_message.txt";
    const string txt_MimeType = "text/txt";

    // second message text
    const string second_FilePath = "Inputs/second_message.txt";
    const string secondP1_FilePath = "Inputs/second_part_one.txt";
    //third
    const string third_FilePath = "Inputs/fird_message.txt";
    //fourth
    const string fourth_FilePath = "Inputs/fourth_message.txt";
    //fourth
    const string fifth_FilePath = "Inputs/fifth_message.txt";

    //link message
    const string link_message_FilePath = "Inputs/link_message.txt";

    // url message link
    const string url_FilePath = "Inputs/url.txt";

    //url button
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> row0;
    InlineKeyboardButton::Ptr Button_url(new InlineKeyboardButton);
    Button_url->text = ReadFile(link_message_FilePath);
    //Button_url->callbackData = ReadFile(link_message_FilePath);
    Button_url->url=ReadFile(url_FilePath);
    row0.push_back(Button_url);
    keyboard->inlineKeyboard.push_back(row0);


//first text message
    bot.getEvents().onCommand("start", [&bot, &keyboard , &first_FilePath, &second_FilePath, &secondP1_FilePath,&third_FilePath, &fourth_FilePath, &fifth_FilePath,&videoFilePath, &videoMimeType,  &audioFilePath, &audioMimeType ](Message::Ptr message) {
        string FileText;

        bot.getApi().sendVoice(message->chat->id, InputFile::fromFile(audioFilePath,audioMimeType));
        sleep(15);
        bot.getApi().sendVideo(message->chat->id,InputFile::fromFile(videoFilePath,videoMimeType) );
        sleep(60);


        FileText= ReadFile(first_FilePath);
        bot.getApi().sendMessage(message->chat->id,FileText );

      //  FileText= ReadFile(secondP1_FilePath);
        //bot.getApi().sendMessage(message->chat->id,FileText );
         FileText= ReadFile(second_FilePath);
        bot.getApi().sendMessage(message->chat->id,FileText );

         FileText= ReadFile(third_FilePath);
        bot.getApi().sendMessage(message->chat->id,FileText );
        string response = "open link ";
        bot.getApi().sendMessage(message->chat->id, response, false, 0, keyboard, "Markdown");

        FileText= ReadFile(fourth_FilePath);
        bot.getApi().sendMessage(message->chat->id,FileText );

        FileText= ReadFile(fifth_FilePath);
        bot.getApi().sendMessage(message->chat->id,FileText );

        bot.getApi().sendMessage(message->chat->id,"https://t.me/shaxnoza2022UZ");
    });






    signal(SIGINT, [](int s) {
        printf("SIGINT got\n");
        exit(0);
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        bot.getApi().deleteWebhook();

        TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (exception& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}
