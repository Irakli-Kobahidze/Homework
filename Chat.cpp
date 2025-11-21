#include "Chat.h"

User::User(const std::string& login, const std::string& password, const std::string& name)
    : login(login), password(password), name(name) {
}

std::string User::getLogin() const { return login; }
std::string User::getPassword() const { return password; }
std::string User::getName() const { return name; }

Message::Message(const std::string& from, const std::string& to, const std::string& text)
    : from(from), to(to), text(text) {
}

std::string Message::getFrom() const { return from; }
std::string Message::getTo() const { return to; }
std::string Message::getText() const { return text; }

User* Chat::findUser(const std::string& login) {
    for (auto& user : users) {
        if (user.getLogin() == login) {
            return &user;
        }
    }
    return nullptr;
}

void Chat::registerUser() {
    std::string login, password, name;
    std::cout << "Регистрация\nЛогин: ";
    std::cin >> login;

    if (findUser(login) != nullptr) {
        throw std::runtime_error("Пользователь с таким логином уже существует");
    }

    std::cout << "Пароль: ";
    std::cin >> password;
    std::cout << "Имя: ";
    std::cin >> name;

    users.emplace_back(login, password, name);
    std::cout << "Пользователь зарегистрирован!\n\n";
}

void Chat::login() {
    std::string login, password;
    std::cout << "Вход\nЛогин: ";
    std::cin >> login;
    std::cout << "Пароль: ";
    std::cin >> password;

    User* user = findUser(login);
    if (user == nullptr || user->getPassword() != password) {
        throw std::runtime_error("Неверный логин или пароль");
    }

    loggedIn = true;
    currentUser = login;
    std::cout << "Добро пожаловать, " << user->getName() << "!\n\n";
}

void Chat::sendMessage() {
    if (!loggedIn) throw std::runtime_error("Необходимо войти в систему");

    std::string to, text;
    std::cout << "Отправить сообщение (для всех введите ALL)\nКому: ";
    std::cin >> to;
    std::cin.ignore();
    std::cout << "Текст: ";
    std::getline(std::cin, text);

    if (to != "ALL" && findUser(to) == nullptr) {
        throw std::runtime_error("Пользователь не найден");
    }

    messages.emplace_back(currentUser, to, text);
    std::cout << "Сообщение отправлено!\n\n";
}

void Chat::showMessages() const {
    if (!loggedIn) throw std::runtime_error("Необходимо войти в систему");

    std::cout << "1 - Общий чат\n2 - Личные сообщения\nВыберите действие: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) showChat();
    else if (choice == 2) showPrivateChat();
    else std::cout << "Неверный выбор\n\n";
}

void Chat::showChat() const {
    std::cout << "--- Общий чат ---\n";
    for (const auto& msg : messages) {
        if (msg.getTo() == "ALL") {
            std::cout << "[" << msg.getFrom() << "]: " << msg.getText() << "\n";
        }
    }
    std::cout << "-----------------\n\n";
}

void Chat::showPrivateChat() const {
    std::cout << "--- Личные сообщения ---\n";
    for (const auto& msg : messages) {
        if (msg.getTo() != "ALL" && (msg.getFrom() == currentUser || msg.getTo() == currentUser)) {
            std::cout << "[" << msg.getFrom() << " -> " << msg.getTo() << "]: " << msg.getText() << "\n";
        }
    }
    std::cout << "-------------------------\n\n";
}

bool Chat::isLoggedIn() const { return loggedIn; }

void Chat::run() {
    while (true) {
        try {
            if (!loggedIn) {
                std::cout << "1 - Вход\n2 - Регистрация\n3 - Выход\nВыберите действие: ";
                int choice;
                std::cin >> choice;

                if (choice == 1) login();
                else if (choice == 2) registerUser();
                else if (choice == 3) break;
                else std::cout << "Неверный выбор\n\n";
            }
            else {
                std::cout << "1 - Отправить сообщение\n2 - Просмотр сообщений\n3 - Выход\nВыберите действие: ";
                int choice;
                std::cin >> choice;

                if (choice == 1) sendMessage();
                else if (choice == 2) showMessages();
                else if (choice == 3) {
                    loggedIn = false;
                    std::cout << "Выход из аккаунта...\n\n";
                }
                else std::cout << "Неверный выбор\n\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n\n";
        }
    }
}