#include <stddef.h>

class Message{
public:
    Message(const char* data, unsigned count);

    Message(const Message& copy);

    Message(Message&& moved);

    ~Message();

    Message &Message::operator=(const Message &other);

    Message &Message::operator=(Message &&other);

    char* getText() const;
    void setSize(size_t new_size);
    size_t getSize() const;
    size_t getId() const;

private:
    char* text;  // текст сообщения
    size_t size;    // размер сообщения
    size_t id;  // номер сообщения
    static inline size_t counter;   // статический счетчик для генерации номера объекта
};