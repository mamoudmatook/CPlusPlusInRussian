#include <iostream>
#include <string>
using namespace std;
// void SendSms(const string &number, const string &message);
// void SendEmail(const string &email, const string &message);
class INotifier
{
public:
    virtual void Notify(const string &message) = 0;
};

class SmsNotifier : public INotifier
{
public:
    SmsNotifier(const string &phone_number) : _phone_number(phone_number) {}
    void Notify(const string &message) override
    {
        SendSms(_phone_number, message);
    }

private:
    string _phone_number;
};

class EmailNotifier : public INotifier
{
public:
    EmailNotifier(const string &email_address) : _email_address(email_address) {}
    void Notify(const string &message) override
    {
        SendEmail(_email_address, message);
    }

private:
    string _email_address;
};

// void SendSms(const string &number, const string &message)
// {
//     cout << "Send '" << message << "' to number " << number << endl;
// }

// void SendEmail(const string &email, const string &message)
// {
//     cout << "Send '" << message << "' to e-mail " << email << endl;
// }

// void Notify(INotifier &notifier, const string &message)
// {
//     notifier.Notify(message);
// }

// int main()
// {
//     SmsNotifier sms{"+7-495-777-77-77"};
//     EmailNotifier email{"na-derevnyu@dedushke.ru"};

//     Notify(sms, "I have White belt in C++");
//     Notify(email, "And want a Yellow one");
//     return 0;
// }