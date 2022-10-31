#include <iostream>

namespace N {
    void Nfunc() {
        std::cout << "N function.\n";
    }
}

namespace M {
    void Mfunc() {
        std::cout << "M function.\n";
    }
}

int main() {
    using namespace N;
    using namespace M;

    Mfunc();
    Nfunc(); 

    return 0;
}