#if defined(LINUX)
#define CLEAR system("clear")
#elif defined(WINDOWS)
#define CLEAR system("cls")
#else
#define CLEAR printf("\e[1;1H\e[2J");
#endif