#include "Message.hpp"
#include <vector>
#include <stdio.h>
#include <list>
#include <iostream>

void static_test(){
    Message static_msg("help", 4);
    Message* dynamic_msg = new Message("please", 6);
    delete dynamic_msg;
}

void vector_test() {
	std::vector<Message> vector;
	vector.push_back(Message("First vector element", 21));
	vector.push_back(Message("Second vector element", 22));
	vector.push_back(Message("Third vector element", 21));
    vector.push_back(Message("Fourth vector element", 22));
	vector.push_back(Message("Fifth vector element", 21));
	for (auto &item : vector)
		printf("%s\n", item.getText());
}

void list_test() {
	std::list<Message> list;
	list.push_back(Message("First list element", 21));
	list.push_back(Message("Second list element", 22));
	list.push_back(Message("Third list element", 21));
	list.push_back(Message("Fourth list element", 22));
	list.push_back(Message("Fifth list element", 21));
	for (auto &item : list)
		printf("%s\n", item.getText());
}

Message value_param(Message msg){
    msg.setSize(999);
    return msg;
}

void value_param_func_test(){
	Message static_msg("help", 4);
    printf("Old size: %ld\n", static_msg.getSize());
    Message new_msg = value_param(static_msg);
    printf("New size: %ld\n", static_msg.getSize());
}


void ref_param(Message* msg){
    msg->setSize(999);
}

void ref_param_func_test(){
    Message msg("help", 4);
    printf("Old size: %ld\n", msg.getSize());
    ref_param(&msg);
    printf("New size: %ld\n", msg.getSize());
}

int main(){
	std::cout << "--- STATIC TEST START ---" << std::endl;
	static_test();
	std::cout << "--- STATIC TEST END -----" << std::endl;

	std::cout << "--- VECTOR TEST START ---" << std::endl;
	vector_test();
	std::cout << "--- VECTOR TEST END -----" << std::endl;

	std::cout << "--- LIST TEST START -----" << std::endl;
	list_test();
	std::cout << "--- LIST TEST END -------" << std::endl;

	std::cout << "--- FUNC TEST START -----" << std::endl;
    value_param_func_test();
	std::cout << "--- FUNC TEST END -------" << std::endl;

	std::cout << "--- REF FUNC TEST START -----" << std::endl;
    ref_param_func_test();
	std::cout << "--- REF FUNC TEST END -------" << std::endl;
}