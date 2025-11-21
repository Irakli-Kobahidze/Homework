#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class User {
public:
    User(const std::string& login, const std::string& password, const std::string& name);
    std::string getLogin() const;
    std::string getPassword() const;
    std::string getName() const;

private:
    std::string login;
    std::string password;
    std::string name;
};

class Message {
public:
    Message(const std::string& from, const std::string& to, const std::string& text);
    std::string getFrom() const;
    std::string getTo() const;
    std::string getText() const;

private:
    std::string from;
    std::string to;
    std::string text;
};

class Chat {
public:
    void registerUser();
    void login();
    void sendMessage();
    void showMessages() const;
    bool isLoggedIn() const;
    void run();

private:
    std::vector<User> users;
    std::vector<Message> messages;
    bool loggedIn = false;
    std::string currentUser;

    User* findUser(const std::string& login);
    void showChat() const;
    void showPrivateChat() const;
};