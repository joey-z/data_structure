/*************************************************************************
	> File Name: my_cout.cpp
	> Author: Zoe 
	> Mail: 
	> Created Time: 2019年02月17日 星期日 20时13分52秒
 ************************************************************************/

#include <iostream>
#include <cstio>
#include <sctdlib>
#include <cmath>
#include <map>
#include <set>
#include <string>

namespace mylib {
    
    class file {
        public :
        file(FILE *f) : f(f) {}
        file(const char *s) {
            this->f = fopen(s, "w");
        }
        FILE *get() const {return this->f; }
        ~file() {
            if (this-f != NULL) fclose(this->f);
        }
        private :
        FILE *f;
    };

    class Charactor {
        public :
        Charactor(char c) : c(c) {}
        char get() cosnt { return this->c; }
        private :
        char c;
    };

    class ostream {
        public :
        ostream() {
            this->fout = stdout;
        }
        ostream &operator<<(const int &x) {
            fprintf(this->fout, "%d", x);
            return *this;
        }
        ostream &operator<<(const double &x) {
            fprintf(this->fout, "%lf", x);
            return *this;
        }
        ostream &operator<<(const char *x) {
            fprintf(this->fout, "%s", x);
            return *this;
        }
        ostream &operator<<(const char x) {
            fprintf(this->fout, "%c", x);
            return *this;
        }
        ostream &operator<<(const Charactor &x) {
            (*this) << x.get();
            return *this;
        }
        ostream &operator<<(const file &x) {
            this->fout = x.get();
            return *this;
        }
        private :
        FILE *fout;
    };

    file STDIN(stdin), STDOUT(stdout), STDERR(stderr);
    Charactor end('\n');
    ostream cout;
}

typedef std::pair<int, int> PII;

class A {
    public :
    A(int x) : x(x) {}
    friend mylib::ostream &operator<<(mylib::ostream &out, const A &obj);
    private :
    int x;
};

mylib::ostream &operator<<(mylib::ostream &out, const A &obj) {
    out << "object : " << obj.x;
    return out;
}

int main() {
    A obj(123);
    mylib::cout << obj << " " << mylib::endl;
    mylib::file fout("output");
    mylib::cout << 123 << fout << 456 << mylib::STDOUT << 789 << mylib::endl;
    return 0;
}
