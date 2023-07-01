#if defined(LINUX)
#define CLEAR system("clear")
#elif defined(WINDOWS)
#define CLEAR system("cls")
#else
#define CLEAR printf("\n")
#endif