/*230:*/
#line 4435 ".\\dummy.w"

#include "htex.h"
#include "hformat.h"
#include "hdefaults.h"
#include "texdef.h"
/*227:*/
#line 4404 ".\\dummy.w"

list_state_record nest[nest_size+1];
uint8_t nest_ptr;
uint8_t max_nest_stack;
list_state_record cur_list;
int16_t shown_mode;

/*:227*/
#line 4440 ".\\dummy.w"



void push_nest(void)
{if(nest_ptr> max_nest_stack)
{max_nest_stack= nest_ptr;
if(nest_ptr==nest_size)QUIT("Overflow in semantic nest size %d",nest_size);
}
nest[nest_ptr]= cur_list;
incr(nest_ptr);head= get_avail();tail= head;prev_graf= 0;
needs_bs= false;cur_bs= baseline_skip;cur_ls= line_skip;cur_lsl= line_skip_limit;
}

/*:230*//*231:*/
#line 4458 ".\\dummy.w"


void pop_nest(void)
{free_avail(head);decr(nest_ptr);cur_list= nest[nest_ptr];
}

/*:231*/
