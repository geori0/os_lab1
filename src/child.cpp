#include "os.h"
#include "prime.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>      

int main() {
    std::string file_name_child;
    std::cin >> file_name_child;
    std::ofstream out(file_name_child, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return 1;
    }
    int child_number;
    int signal;
    while(PipeRead(0, &child_number, sizeof(child_number))) {
        if (!Prime(child_number) && (child_number > 1)) {
            out << child_number << std::endl;
            signal = 0;
        } else {
            signal = 1;
        }
        PipeWrite(1, &signal, sizeof(signal));
        if (signal == 1) {
            break;
        }
    }
    out.close();
    return 0;
}
