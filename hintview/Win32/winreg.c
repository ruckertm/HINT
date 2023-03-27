#include <windows.h>
#include "error.h"
#include "basetypes.h"
#include "winmain.h"
#include "settings.h"
#include "winreg.h"

extern int round_to_pixel_h, round_to_pixel_v;
extern double pixel_size_threshold;

#define PROJECT_KEY "HINT"
#define PROGRAM_KEY "HintView"

typedef struct {
	char *key;
	void *value;
	int type; } regtable[];

#define FLAG_SIZE (sizeof(DWORD)*8)


/* these values are used for the type field in the regtable.
   non negative type (values between 0 and FLAG_SIZE-1) are used for flags */
#define TYPE_INT32 (-1)  /* 32 bit integer */
#define TYPE_STRING (-2) /* zero terminated string. must be NULL or allocated with malloc!*/
#define TYPE_DOUBLE (-3) /* binary data, used for floating point values */
#define TYPE_UINT64 (-3) /* binary data, used for 64 bit unsigned integers */
#define KEY_FLAGS ((char *)1) /* integer set to 1 or 0 */

regtable regtab= {
	{"units",&unit,TYPE_INT32},
	{"input",&hin_name,TYPE_STRING},
	{"position",&pos,TYPE_UINT64},
	{"gamma",&gamma,TYPE_DOUBLE},
	{"scale",&scale,TYPE_DOUBLE},
	{"pxthr",&pixel_size_threshold,TYPE_DOUBLE},
	{KEY_FLAGS,&dark,0},
	{KEY_FLAGS,&autoreload,1},
	//{KEY_FLAGS,&round_to_pixel,2},
	{KEY_FLAGS,&round_to_pixel_h,2},
	{KEY_FLAGS,&round_to_pixel_v,3},
	{NULL,NULL,0}};

void write_regtab(void)
{ HKEY program_key=0, project_key=0, software_key=0;
  LONG r;
  int success=0;
  r = RegOpenKeyEx(HKEY_CURRENT_USER,"Software",0,KEY_ALL_ACCESS,&software_key);
  if (r==ERROR_SUCCESS)
  {  DWORD n;
	  r = RegCreateKeyEx(software_key,PROJECT_KEY,0,NULL,REG_OPTION_NON_VOLATILE,
               KEY_ALL_ACCESS,NULL,&project_key,&n);
     if (r==ERROR_SUCCESS)
	 {  r = RegCreateKeyEx(project_key,PROGRAM_KEY,0,NULL,REG_OPTION_NON_VOLATILE,
               KEY_ALL_ACCESS,NULL,&program_key,&n);
        if (r==ERROR_SUCCESS)
	    { int i=0;
		  int has_flags=0;
		  DWORD flags=0;
		  while(regtab[i].key!=NULL)
		  { if (regtab[i].type==TYPE_INT32)
		    { DWORD tmp=*(int*)regtab[i].value;
              RegSetValueEx(program_key,regtab[i].key,0,REG_DWORD,(BYTE*)&tmp,sizeof(DWORD));
		    }
		    else if (regtab[i].type==TYPE_DOUBLE)
		    { void *tmp=regtab[i].value;
              RegSetValueEx(program_key,regtab[i].key,0,REG_BINARY,(BYTE*)tmp,sizeof(double));
		    }
		    else if (regtab[i].type==TYPE_STRING)
		    { char **tmp=regtab[i].value;
		      char zero=0, *empty=&zero;	
              if (*tmp==NULL) tmp=&empty;
			  RegSetValueEx(program_key,regtab[i].key,0,REG_SZ,(BYTE*)*tmp,(DWORD)strlen((char*)*tmp)+1);
		    } 
		    else if (0<=regtab[i].type && regtab[i].type<FLAG_SIZE)
		    { int tmp = *(int*)regtab[i].value;
			  has_flags=1;
		      flags =((flags & ~(1<<regtab[i].type)) | ((tmp)?(1<<regtab[i].type):0));
		    }
			i++;
		  }
		  if (has_flags)	
		    RegSetValueEx(program_key,"flags",0,REG_DWORD,(BYTE*)&flags,sizeof(DWORD));
		  RegCloseKey(program_key);
		}
       RegCloseKey(project_key);
	 }
    RegCloseKey(software_key);
  }
}

void read_regtab(void)
{ HKEY program_key=0,project_key=0, software_key=0;
  LONG r;  /* get values from the registry */
  r = RegOpenKeyEx(HKEY_CURRENT_USER,"Software",0,KEY_ALL_ACCESS,&software_key);
  if (r==ERROR_SUCCESS)
  {  DWORD n;
	  r = RegCreateKeyEx(software_key,PROJECT_KEY,0,NULL,REG_OPTION_NON_VOLATILE,
               KEY_ALL_ACCESS,NULL,&project_key,&n);
     if (r==ERROR_SUCCESS)
	 { r = RegCreateKeyEx(project_key,PROGRAM_KEY,0,NULL,REG_OPTION_NON_VOLATILE,
               KEY_ALL_ACCESS,NULL,&program_key,&n);
        if (r==ERROR_SUCCESS)
	    { DWORD bc = sizeof(DWORD);
		  int i=0;
		  int has_flags=0;
		  DWORD flags=0;
		  r = RegQueryValueEx(program_key,"flags",0,NULL,(LPBYTE)&flags,&bc);
		  has_flags=(r==ERROR_SUCCESS);
		  while(regtab[i].key!=NULL)
		  { if (regtab[i].type==TYPE_INT32)
		    { DWORD tmp;
		      bc=sizeof(DWORD);
		  	  r = RegQueryValueEx(program_key,regtab[i].key,0,NULL,(LPBYTE)&tmp,&bc);
			  if (r==ERROR_SUCCESS)
			    *(int*)regtab[i].value=tmp;
		    }
		    else if (regtab[i].type==TYPE_DOUBLE)
		    { double tmp;
		      bc=sizeof(double);
		  	  r = RegQueryValueEx(program_key,regtab[i].key,0,NULL,(LPBYTE)&tmp,&bc);
			  if (r==ERROR_SUCCESS)
			    *(double*)regtab[i].value=tmp;
		    }
		    else if (regtab[i].type==TYPE_STRING)
		    { char *str;
			  r = RegQueryValueEx(program_key,regtab[i].key,0,NULL,NULL,&bc); /* get size */
			  if (r==ERROR_SUCCESS)
			  { str=(char *)malloc(bc);
			    if (str==NULL)
					hint_error("Out of memory reading registry",regtab[i].key);
				else
				{ r = RegQueryValueEx(program_key,regtab[i].key,0,NULL,(LPBYTE)str,&bc);
			      if (r!=ERROR_SUCCESS)
					hint_error("Error reading registry",regtab[i].key);
				  else
				  { char **sptr=(char**)regtab[i].value;
					  if (*sptr != NULL) free(*sptr);
				    *sptr=str;
				  }
				}
			  }
		    } 
		    else if (has_flags && 0<=regtab[i].type && regtab[i].type<FLAG_SIZE)
		    { *(int*)regtab[i].value = ((flags&(1<<regtab[i].type))!=0);
		    }
		   	i++;
		  }
          RegCloseKey(program_key);
		}
       RegCloseKey(project_key);
	 }
    RegCloseKey(software_key);
  }
}

