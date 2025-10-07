#include <iostream>
#include <vector>
#include <string>

int main(){
    std::vector<std::string> hobbies;

    hobbies.push_back("Coding");
    hobbies.push_back("Listening to music");
    hobbies.push_back("Reading");

    std::cout << "My Hobbies: "<< std::endl;
    for( const std::string& hobby : hobbies){
        std::cout << "\t-> " << hobby << std::endl;
    }
}
