/*6:*/
#line 267 ".\\dummy.w"

#ifndef _TEX_TYPES_H_
#define _TEX_TYPES_H_
/*14:*/
#line 407 ".\\dummy.w"

enum{mem_max= 65534};


enum{mem_min= 0};


enum{buf_size= 1024};


enum{error_line= 72};
enum{half_error_line= 42};

enum{max_print_line= 79};
enum{stack_size= 200};
enum{max_in_open= 6};

enum{font_max= 75};

enum{font_mem_size= 20000};
enum{param_size= 60};
enum{nest_size= 40};
enum{max_strings= 15000};
enum{string_vacancies= 75000};


enum{pool_size= 200000};



enum{save_size= 600};

enum{trie_size= 20000};

enum{trie_op_size= 500};
enum{dvi_buf_size= 16384};
enum{file_name_size= 255};
/*:14*/
#line 270 ".\\dummy.w"

/*22:*/
#line 551 ".\\dummy.w"

typedef uint8_t ASCII_code;

/*:22*//*23:*/
#line 580 ".\\dummy.w"

typedef unsigned char text_char;

/*:23*//*30:*/
#line 789 ".\\dummy.w"

typedef uint8_t eight_bits;
typedef struct{FILE*f;text_char d;}alpha_file;
typedef struct{FILE*f;eight_bits d;}byte_file;

/*:30*//*43:*/
#line 1147 ".\\dummy.w"

typedef uint32_t pool_pointer;
typedef uint16_t str_number;
typedef uint8_t packed_ASCII_code;

/*:43*//*109:*/
#line 2226 ".\\dummy.w"

typedef int scaled;
typedef uint32_t nonnegative_integer;
typedef uint8_t small_number;

/*:109*//*119:*/
#line 2421 ".\\dummy.w"

typedef float32_t glue_ratio;

/*:119*//*123:*/
#line 2525 ".\\dummy.w"

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

/*:123*//*125:*/
#line 2584 ".\\dummy.w"

typedef halfword pointer;

/*:125*//*163:*/
#line 3255 ".\\dummy.w"

typedef uint8_t glue_ord;

/*:163*//*230:*/
#line 4390 ".\\dummy.w"

typedef struct{int16_t mode_field;
pointer head_field,tail_field;
int pg_field;
pointer bs_field,ls_field;
scaled lsl_field;
uint8_t*bs_pos;
scaled ds_field,dw_field,di_field,hs_field;
uint32_t np_field;
memory_word aux_field;
}list_state_record;

/*:230*//*288:*/
#line 5970 ".\\dummy.w"

typedef uint8_t group_code;

/*:288*//*319:*/
#line 6550 ".\\dummy.w"

typedef struct{
quarterword state_field,index_field;
halfword start_field,loc_field,limit_field,name_field;
}in_state_record;

/*:319*//*567:*/
#line 10779 ".\\dummy.w"

typedef uint8_t internal_font_number;
typedef uint16_t font_index;

/*:567*//*614:*/
#line 11955 ".\\dummy.w"

typedef uint16_t dvi_index;

/*:614*//*956:*/
#line 18166 ".\\dummy.w"

typedef uint16_t trie_pointer;

/*:956*//*961:*/
#line 18232 ".\\dummy.w"

typedef uint16_t hyph_pointer;

/*:961*//*1004:*/
#line 18913 ".\\dummy.w"


typedef struct{
pointer p;
int i;
pointer g;
scaled s;
}stream_t;

/*:1004*/
#line 271 ".\\dummy.w"

#endif

/*:6*/
