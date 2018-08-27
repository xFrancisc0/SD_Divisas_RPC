#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Si el SO es windows, usar system("cls")
#ifdef _WIN32
#define CLEAR "cls"
// Si no, usar system("clear")
#else 
#define CLEAR "clear"
#endif

