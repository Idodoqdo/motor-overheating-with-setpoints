#include "Kuleshov_Forward.h"

int main() {
    
    double T_env{0};
try {

    if (!(std::cin >> T_env)) throw "Error";

    Engine rez(T_env);

    std::cout << rez.get_t() << std::endl;

} catch (const char *Error) {

    std::cout << Error << '\n';
}
   
    return 0;
}