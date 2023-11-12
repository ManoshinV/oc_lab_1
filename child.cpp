#include <iostream>
#include <unistd.h>
#include <vector>
#include <fcntl.h>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    int file = open(argv[1], O_WRONLY);
    if (file == -1) {
        write(STDERR_FILENO, "An error occured with opening a file", 37);
        return 1;
    }

    int ft = ftruncate(file, 0);
    if (ft == -1) {
        write(STDERR_FILENO, "An error occured with clearing a file", 38);
        return 2;
    }

    char c;
    string s;
    float ans;
    bool first = 1;
    while (read(STDIN_FILENO, &c, 1)) {
        if(c != '\n' && c != ' ') {
            s += c;
        } else {
            if(first) {
                first = 0;
                ans = stof(s);
            } else {
                if(stof(s) == float(0)) {
                    write(STDERR_FILENO, "Err zero", 8);
                    return 3;
                }
                ans /= stof(s);
            }
            s.clear();
            if(c == '\n') {
                first = 1;
                s = to_string(ans);  
                for(int i = 0; i < s.size(); ++i) { 
                    write(file, &s[i], 1);
                }
                write(file, " ", 1);
                s.clear();
            }
        }
    }
    return 0;
}
