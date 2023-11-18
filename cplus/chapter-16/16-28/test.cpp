#include "pointers.h"
int main() {
    Shared_Ptr<int> sp1(new int(42));
    Unique_Ptr<int,Delete> sp2(new int(43), Delete());
    return 0;
}

