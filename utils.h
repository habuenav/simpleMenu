#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))
typedef String txtMenu;

bool isNumeric(String str)
{
for(uint8_t i=0;i<str.length();i++) { if(isDigit(str.charAt(i))) return true;}
return false;
}

template<typename T>
uint8_t size(T (&arr)) 
{
uint8_t n=NUMITEMS(arr);
n=(n>0)?n-1:n;  
if(arr[n][strlen(arr[n].c_str())-1]!=' ' && n>0){ arr[n]= String(arr[n]+' ');  }
else {  n=0; 
       do{ n++; }while(arr[n][strlen(arr[n].c_str())-1]!=' ');  }
return n+1;    
}

char *getStringLineStart(uint8_t line_idx, char *str )
{
  char e;
  uint8_t line_cnt = 1;
  
  if ( line_idx == 0 )
    return str;

  for(;;)
  {
    e = *str;
    if ( e == '\0' )
      break;
    str++;
    if ( e == '|' )
    {
      if ( line_cnt == line_idx )
  return (char*) str;
      line_cnt++;
    }
  }
  return NULL;  /* line not found */
}


uint8_t stringLineCnt( char *str)
{
  char e;
  uint8_t line_cnt = 1;
  if ( str == NULL )
    return 0;
  for(;;)
  {
    e = *str;
    if ( e == '\0' )
      break;
    str++;
    if ( e == '|' )
      line_cnt++;
  }
  return line_cnt;
}
void copyStringLine(char *dest, uint8_t line_idx, char *str)
{
  if ( dest == NULL )
    return;
  str = getStringLineStart( line_idx, str );
  if ( str != NULL )
  {
    for(;;)
    {
      if ( *str == '|' || *str == '\0' )
  break;
      *dest = *str;
      dest++;
      str++;
    }
  }
  *dest = '\0';
}

