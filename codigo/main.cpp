#include <iostream>
#include <filesystem>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    cout << "Carpeta actual: " << std::filesystem::current_path() << endl;
    for (const auto& e : std::filesystem::directory_iterator(std::filesystem::current_path())) {
        cout << "[" << e.path().filename().string() << "]" << endl;
    }
    cout << "existe entrada.txt? " << std::filesystem::exists("entrada.txt") << endl;

    return 0;
}