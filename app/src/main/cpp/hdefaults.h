	/*331:*/
	#line 6695 "format.w"


	/*334:*/
	#line 6785 "format.w"

typedef enum{
zero_int_no= 0,
pretolerance_no= 1,
tolerance_no= 2,
line_penalty_no= 3,
hyphen_penalty_no= 4,
ex_hyphen_penalty_no= 5,
club_penalty_no= 6,
widow_penalty_no= 7,
display_widow_penalty_no= 8,
broken_penalty_no= 9,
pre_display_penalty_no= 10,
post_display_penalty_no= 11,
inter_line_penalty_no= 12,
double_hyphen_demerits_no= 13,
final_hyphen_demerits_no= 14,
adj_demerits_no= 15,
looseness_no= 16,
time_no= 17,
day_no= 18,
month_no= 19,
year_no= 20,
hang_after_no= 21,
}int_no_t;
#define MAX_INT_DEFAULT hang_after_no
	/*:334*/	/*336:*/
	#line 6856 "format.w"

typedef enum{
zero_dimen_no= 0,
hsize_dimen_no= 1,
vsize_dimen_no= 2,
line_skip_limit_no= 3,
max_depth_no= 4,
hang_indent_no= 5,
emergency_stretch_no= 6,
quad_no= 7,
math_quad_no= 8
}dimen_no_t;
#define MAX_DIMEN_DEFAULT math_quad_no
	/*:336*/	/*338:*/
	#line 6900 "format.w"

typedef enum{
zero_xdimen_no= 0,
hsize_xdimen_no= 1,
vsize_xdimen_no= 2
}xdimen_no_t;
#define MAX_XDIMEN_DEFAULT vsize_xdimen_no
	/*:338*/	/*340:*/
	#line 6924 "format.w"

typedef enum{
zero_skip_no= 0,
fil_skip_no= 1,
fill_skip_no= 2,
line_skip_no= 3,
baseline_skip_no= 4,
above_display_skip_no= 5,
below_display_skip_no= 6,
above_display_short_skip_no= 7,
below_display_short_skip_no= 8,
left_skip_no= 9,
right_skip_no= 10,
top_skip_no= 11,
split_top_skip_no= 12,
tab_skip_no= 13,
par_fill_skip_no= 14
}glue_no_t;
#define MAX_GLUE_DEFAULT par_fill_skip_no
	/*:340*/	/*342:*/
	#line 7010 "format.w"

typedef enum{
zero_baseline_no= 0
}baseline_no_t;
#define MAX_BASELINE_DEFAULT zero_baseline_no
	/*:342*/	/*344:*/
	#line 7029 "format.w"

typedef enum{
zero_page_no= 0
}page_no_t;
#define MAX_PAGE_DEFAULT zero_page_no
	/*:344*/	/*346:*/
	#line 7048 "format.w"

typedef enum{
zero_range_no= 0
}range_no_t;
#define MAX_RANGE_DEFAULT zero_range_no
	/*:346*/
	#line 6697 "format.w"


extern int max_fixed[32],max_default[32];

extern int32_t int_defaults[MAX_INT_DEFAULT+1];
extern dimen_t dimen_defaults[MAX_DIMEN_DEFAULT+1];
extern xdimen_t xdimen_defaults[MAX_XDIMEN_DEFAULT+1];
extern glue_t glue_defaults[MAX_GLUE_DEFAULT+1];
extern baseline_t baseline_defaults[MAX_BASELINE_DEFAULT+1];
	/*:331*/
