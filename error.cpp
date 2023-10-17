#include "error.h"

Error::Error(QString const &text) noexcept
    :message(text) {

}
Error::Error(const Error &er) {
    this->message = er.message;
}

Error::~Error()  {

}

void Error::raise() const  {
    throw *this;
}

Error *Error::clone() const {
    return new Error(*this);
}

const char *Error::what() const noexcept {
    return this->message.toStdString().c_str();
}
