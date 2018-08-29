#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//si el SO es windows, usar el system("cls")
#ifdef _WIN32
#define CLEAR "cls"
//Si no, usar system("clear");
#else
#define CLEAR "clear"
#endif
