#include <cstring>
#include <unistd.h>


class   N {
    private:
        int     value;
        char    annotation[100];
    public:
        N(int value) {
            this->value = value;
        }

        virtual ~N() {}

        virtual int operator+(N& obj) {
            return this->value + obj.value;
        }

        virtual int operator-(N& obj) {
            return this->value - obj.value;
        }

        void    setAnnotation(char *str) {
            memcpy(this->annotation, str, strlen(str));
        }
};

int main(int ac,char **av) {
    N   *obj1;
    N   *obj2;

    if (ac < 2)
        _exit(1);
    
    obj1 = new N(5);
    obj2 = new N(6);

    obj1->setAnnotation(av[1]);
    return (*obj2 + *obj1);
}