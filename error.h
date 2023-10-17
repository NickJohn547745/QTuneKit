#ifndef ERROR_H
#define ERROR_H

#include <QException>

class Error : public QException
{
public:
    Error(const QString &text = "") noexcept;
    Error(const Error &er);
    ~Error() override;

    void raise() const override;
    Error *clone() const override;
    const char *what() const noexcept override;

private:
    QString message;
};

#endif  // ERROR_H
