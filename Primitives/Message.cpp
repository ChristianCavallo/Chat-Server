//
// Created by chryc on 29/12/2019.
//

#include "Message.h"

Message::Message(const string &content, const string &sender, const string &media,
                 const bsoncxx::types::b_date &receptionDate) : Content(content), Sender(sender), Media(media),
                                                                ReceptionDate(receptionDate) {}

Message::Message(const string &content, const string &sender, const string &media) : Content(content),
                                                                                                       Sender(sender),
                                                                                                       Media(media) {}

