#ifndef COLORS_H
#define COLORS_H

#define _RST "\033[0m"
#define _BLK "\033[30m"
#define _RED "\033[31m"
#define _GRN "\033[32m"
#define _YEL "\033[33m"
#define _BLU "\033[34m"
#define _MAG "\033[35m"
#define _CYN "\033[36m"
#define _WHT "\033[37m"

#define _BOLD "\033[1m"
#define _DIM "\033[2m"
#define _ITAL "\033[3m"
#define _UNDL "\033[4m"
#define _BLNK "\033[5m"
#define _REV "\033[7m"

#define RED(s) _RED s _RST
#define GREEN(s) _GRN s _RST
#define YELLOW(s) _YEL s _RST
#define BLUE(s) _BLU s _RST
#define PURPLE(s) _MAG s _RST
#define CYAN(s) _CYN s _RST
#define WHITE(s) _WHT s _RST

#define B_RED(s) _BOLD _RED s _RST
#define B_CYAN(s) _BOLD _CYN s _RST
#define B_PURPLE(s) _BOLD _MAG s _RST
#define B_GREEN(s) _BOLD _GRN s _RST
#define B_YELLOW(s) _BOLD _YEL s _RST
#define B_BLUE(s) _BOLD _BLU s _RST

#define GLITCH(s) _BLNK _RED s _RST
#define VOID_TXT(s) _REV _BLK s _RST

#define _CLR "\033[2J\033[H"

#endif