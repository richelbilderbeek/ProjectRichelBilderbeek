
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 9)
#warning Newest compiler
#else
#error Your compiler is older than mine
#endif

int main() { }
