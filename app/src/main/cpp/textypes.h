/*6:*/
#line 267 "dummy.w"

#ifndef _TEX_TYPES_H_
#define _TEX_TYPES_H_
/*14:*/
#line 407 "dummy.w"

enum{mem_max= 65534};


enum{mem_min= 0};


enum{buf_size= 2048};


enum{error_line= 72};
enum{half_error_line= 42};

enum{max_print_line= 79};
enum{stack_size= 200};
enum{max_in_open= 6};

enum{font_max= 250};

enum{font_mem_size= 65535};
enum{param_size= 60};
enum{nest_size= 400};
enum{max_strings= 30000};
enum{string_vacancies= 75000};


enum{pool_size= 400000};



enum{save_size= 600};

enum{trie_size= 65534};

enum{trie_op_size= 65534};
enum{dvi_buf_size= 8};
enum{file_name_size= 1024};
/*:14*/
#line 270 "dummy.w"

/*22:*/
#line 551 "dummy.w"

typedef uint8_t ASCII_code;

/*:22*//*23:*/
#line 580 "dummy.w"

typedef unsigned char text_char;

/*:23*//*30:*/
#line 789 "dummy.w"

typedef uint8_t eight_bits;
typedef struct{FILE*f;text_char d;}alpha_file;
typedef struct{FILE*f;eight_bits d;}byte_file;

/*:30*//*43:*/
#line 1174 "dummy.w"

typedef uint32_t pool_pointer;
typedef uint16_t str_number;
typedef uint8_t packed_ASCII_code;

/*:43*//*109:*/
#line 2253 "dummy.w"

typedef int scaled;
typedef uint32_t nonnegative_integer;
typedef uint8_t small_number;

/*:109*//*119:*/
#line 2448 "dummy.w"

typedef float32_t glue_ratio;

/*:119*//*123:*/
#line 2552 "dummy.w"

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
#line 2611 "dummy.w"

typedef halfword pointer;

/*:125*//*163:*/
#line 3282 "dummy.w"

typedef uint8_t glue_ord;

/*:163*//*230:*/
#line 4417 "dummy.w"

typedef struct{int16_t mode_field;
pointer head_field,tail_field;
int pg_field;
pointer bs_field,ls_field;
scaled lsl_field;
uint8_t*bs_pos;
scaled hs_field;
scaled ds_field,dw_field,di_field;
scaled ht_field;
uint32_t np_field;
memory_word aux_field;
}list_state_record;

/*:230*//*288:*/
#line 6000 "dummy.w"

typedef uint8_t group_code;

/*:288*//*319:*/
#line 6580 "dummy.w"

typedef struct{
quarterword state_field,index_field;
halfword start_field,loc_field,limit_field,name_field;
}in_state_record;

/*:319*//*567:*/
#line 10796 "dummy.w"

typedef uint8_t internal_font_number;
typedef uint16_t font_index;

/*:567*//*614:*/
#line 11972 "dummy.w"

typedef uint8_t dvi_index;

/*:614*//*956:*/
#line 18183 "dummy.w"

typedef uint16_t trie_pointer;

/*:956*//*961:*/
#line 18249 "dummy.w"

typedef uint16_t hyph_pointer;

/*:961*//*1004:*/
#line 18930 "dummy.w"


typedef struct{
pointer p;
int i;
pointer g;
scaled s;
}stream_t;

/*:1004*/
#line 271 "dummy.w"

#endif

/*:6*/
