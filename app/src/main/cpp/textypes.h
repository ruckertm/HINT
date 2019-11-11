/*4:*/
#line 261 ".\\dummy.w"

#ifndef _TEX_TYPES_H_
#define _TEX_TYPES_H_
#include "basetypes.h"
/*10:*/
#line 350 ".\\dummy.w"

#include <stdint.h> 
#include <stdbool.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <math.h> 

#define odd(X)       ((X)&1)
#define chr(X)       ((unsigned char)(X))
#define ord(X)       ((int)(X))
#define abs(X)       ((X)> -(X)?(X):-(X))
#define round(X)     ((int)((X)>=0.0?floor((X)+0.5):ceil((X)-0.5)))

#if __SIZEOF_FLOAT__==4
typedef float float32_t;
#else
#error  float type must have size 4
#endif

/*:10*//*59:*/
#line 1480 ".\\dummy.w"

#define put(file)    fwrite(&((file).d),sizeof((file).d),1,(file).f)
#define get(file)    fread(&((file).d),sizeof((file).d),1,(file).f)

#define reset(file,name,mode)   ((file).f= fopen((char *)(name)+1,mode),\
                                 (file).f!=NULL?get(file):0)
#define rewrite(file,name,mode) ((file).f= fopen((char *)(name)+1,mode))
#define close(file)    fclose((file).f)
#define eof(file)    feof((file).f)
#define eoln(file)    ((file).d=='\n'||eof(file))
#define erstat(file)   ((file).f==NULL?-1:ferror((file).f))

#define read(file,x) ((x)= (file).d,get(file))
#define read_ln(file)  do get(file); while (!eoln(file))

#define write(file, format,...)    fprintf(file.f,format,## __VA_ARGS__)
#define write_ln(file,...)    write(file,__VA_ARGS__"\n")

#define wterm(format,...) write(term_out,format, ## __VA_ARGS__)
#define wterm_ln(format,...) wterm(format "\n", ## __VA_ARGS__)
#define wterm_cr         write(term_out,"\n")
#define wlog(format, ...) write(log_file,format, ## __VA_ARGS__)
#define wlog_ln(format, ...)   wlog(format "\n", ## __VA_ARGS__)
#define wlog_cr         write(log_file,"\n")

/*:59*/
#line 265 ".\\dummy.w"

/*13:*/
#line 427 ".\\dummy.w"

enum{mem_max= 30000};


enum{mem_min= 0};


enum{buf_size= 500};


enum{error_line= 72};
enum{half_error_line= 42};

enum{max_print_line= 79};
enum{stack_size= 200};
enum{max_in_open= 6};

enum{font_max= 75};

enum{font_mem_size= 20000};
enum{param_size= 60};
enum{nest_size= 40};
enum{max_strings= 3000};
enum{string_vacancies= 8000};


enum{pool_size= 32000};



enum{save_size= 600};

enum{trie_size= 8000};

enum{trie_op_size= 500};
enum{dvi_buf_size= 800};
enum{file_name_size= 40};
/*:13*/
#line 266 ".\\dummy.w"

/*21:*/
#line 572 ".\\dummy.w"

typedef uint8_t ASCII_code;

/*:21*//*28:*/
#line 807 ".\\dummy.w"

typedef uint8_t eight_bits;
typedef struct{FILE*f;text_char d;}alpha_file;
typedef struct{FILE*f;eight_bits d;}byte_file;

/*:28*//*41:*/
#line 1165 ".\\dummy.w"

typedef uint16_t pool_pointer;
typedef uint16_t str_number;
typedef uint8_t packed_ASCII_code;

/*:41*//*105:*/
#line 2213 ".\\dummy.w"

typedef int scaled;
typedef uint32_t nonnegative_integer;
typedef uint8_t small_number;

/*:105*//*114:*/
#line 2407 ".\\dummy.w"

typedef float32_t glue_ratio;

/*:114*//*118:*/
#line 2511 ".\\dummy.w"

typedef uint8_t quarterword;
typedef uint16_t halfword;
typedef uint8_t two_choices;
typedef uint8_t four_choices;
typedef struct{
halfword rh;
union{
halfword lh;
struct{quarterword b0;quarterword b1;};
};}two_halves;
typedef struct{
quarterword b0;
quarterword b1;
quarterword b2;
quarterword b3;
}four_quarters;
typedef struct{
union{
int i;
glue_ratio gr;
two_halves hh;
four_quarters qqqq;
};}memory_word;
typedef struct{FILE*f;memory_word d;}word_file;

/*:118*//*156:*/
#line 3232 ".\\dummy.w"

typedef uint8_t glue_ord;

/*:156*//*226:*/
#line 4379 ".\\dummy.w"

typedef struct{int16_t mode_field;
pointer head_field,tail_field;
int pg_field;
bs_t bs_field;
uint32_t np_field;
memory_word aux_field;
}list_state_record;

/*:226*//*283:*/
#line 5941 ".\\dummy.w"

typedef uint8_t group_code;

/*:283*//*314:*/
#line 6521 ".\\dummy.w"

typedef struct{
quarterword state_field,index_field;
halfword start_field,loc_field,limit_field,name_field;
}in_state_record;

/*:314*//*562:*/
#line 10750 ".\\dummy.w"

typedef uint8_t internal_font_number;
typedef uint16_t font_index;

/*:562*//*609:*/
#line 11920 ".\\dummy.w"

typedef uint16_t dvi_index;

/*:609*//*948:*/
#line 18139 ".\\dummy.w"

typedef uint16_t trie_pointer;

/*:948*//*953:*/
#line 18205 ".\\dummy.w"

typedef uint16_t hyph_pointer;

/*:953*/
#line 267 ".\\dummy.w"

#endif

/*:4*/
