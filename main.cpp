#define NDEBUG

#include "headers/print_ip.h"

int main(int, char**){

    const std::string str{"1.2.3.4.5.6.7.8.9.10.11"};
    short sh = 0;
    std::vector vec{127, 1, 3, 11};
    std::list lst{127, 1, 3, 255, 11};
    auto tpl = std::make_tuple(12, 13, 14, 15);

    generator_ip(char(-1));
    generator_ip(sh);
    generator_ip(2130706433);
    generator_ip(8875824491850138409);
    generator_ip(str);
    generator_ip(vec);
    generator_ip(lst);
    generator_ip(tpl);
    //[[maybe_unused]] char a;
    //a = getchar();
    return 0;
}
