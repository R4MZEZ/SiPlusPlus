#include "Message.hpp"
#include <iostream>
  

Message::Message(const char* data, unsigned count){
    size = count;
    text = new char[size];
    for(unsigned i{}; i < size; i++){
        text[i] = data[i];
    }

    id = ++counter;
    std::cout << "Basic constructor " << id << std::endl;
}
// конструктор копирования
Message::Message(const Message& copy) : Message(copy.getText(), copy.size){
    std::cout << "Copy  constructor " << copy.id << " to " << id << std::endl;
}

// конструктор перемещения
Message::Message(Message&& moved){
    id = ++counter;
    text = moved.text;
    size = moved.size;
    moved.text = nullptr;
    std::cout << "Move constructor " << moved.id << " to " << id << std::endl;
}
// деструктор
Message::~Message(){ 
    std::cout << "Destructor "  << id << std::endl;
    delete[] text;
}

Message &Message::operator=(const Message &other){
    std::cout << "Copy assignment" << other.id << " to " << id << std::endl;
    if (this != &other){
        size = other.size;
        text = new char[size];
        for(unsigned i{}; i < size; i++){
            text[i] = other.text[i];
        }
    }
    return *this;
}

Message &Message::operator=(Message &&other) {
    std::cout << "Move assignment" << other.id << " to " << id << std::endl;
    if (this != &other){
        size = other.size;
        text = other.text;
    }
    return *this;
}

char* Message::getText() const { return text; }
size_t Message::getSize() const { return size; }
void Message::setSize(size_t new_size) { size = new_size; };
size_t Message::getId() const {return id;}
