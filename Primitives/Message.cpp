//
// Created by chryc on 29/12/2019.
//

#include "Message.h"

Message::Message(const string &content, const string &sender_id, const string &senderName, const string &media,
                 const bsoncxx::types::b_date &receptionDate) : Content(content), Sender_id(sender_id),
                                                                SenderName(senderName), Media(media),
                                                                ReceptionDate(receptionDate) {}

Message::Message(const string &content, const string &sender_id, const string &senderName, const string &media)
        : Content(content),
          Sender_id(sender_id),
          SenderName(senderName),
          Media(media) {}

bool Message::operator<(const Message &rhs) const {
    return ReceptionDate < rhs.ReceptionDate;
}

bool Message::operator>(const Message &rhs) const {
    return rhs < *this;
}

bool Message::operator<=(const Message &rhs) const {
    return !(rhs < *this);
}

bool Message::operator>=(const Message &rhs) const {
    return !(*this < rhs);
}

