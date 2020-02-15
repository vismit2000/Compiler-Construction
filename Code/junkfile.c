#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
bool is_alphabet(char c)
{
	if((c>='a' && c<='z')||(c>='A' && c<='Z'))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool is_digit(char c)
{
	if(c>='0' && c<='9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool is_delim( char c )
{
	if( (c == ' ') || (c == '\t') || (c == '\r') || (c == '\n') )
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
	do getc()  in each non-accepting state
		ungetc() in each retracting state
		and nothin in accepting states + non-retracting
*/

int main(int argc,char* argv[]){
	FILE* fp;
	fp = fopen(argv[1],"r");
	if(fp==NULL){
		printf("FILE OPEN ERROR");
		exit(1);
	}
	char c= '';
	int state=0;
	int id_count=0;

	while(c!=EOF){
	//for identifer and num
		switch(state){
			case 0:
				{
					c= getc(fp);
					if(is_alphabet(c)) 
					{
						id_count++;
						state=1;
					}
					else if(is_digit(c)) 
					{
						state=3;
					}
					else if( is_delim(c) )
					{
						state = 13;
					}
					else if( '.' == c)
					{
						state = 38;
					}
					else if( ';' == c )
					{
						state = 40;
					}
					else if( ',' == c )
					{
						state = 41;
					}
					else if( '['  == c)
					{
						state = 42;
					}
					else if( ']' == c )
					{
						state = 43;
					}
					else if( '(' == c )
					{
						state = 44;
					}
					else if( ')' == c )
					{
						state = 45;
					}
					else if( '+' == c )
					{
						state = 15;
					}
					else if( '-' == c )
					{
						state = 16;
					}
					else if( '*' == c )
					{
						state = 17;
					}
					else if( '/' == c )
					{
						state = 22;
					}
					else if( '<' == c )
					{
						state = 23;
					}
					else if( '>' == c )
					{
						state = 27;
					}
					else if( '=' == c )
					{
						state = 31;
					}
					else if( '!' == c )
					{
						state = 33;
					}
					else if( ':' == c )
					{
						state = 35;
					}
					else if( EOF == c)
					{
						state = 46;
					}
					else
					{
						state = TRAP_STATE;
					}
					c = getc(fp);
				}
				break;

			case 1:
				{
					if( (is_alphabet(c) || is_digit(c) || '_' == c ) && id_count<20) 
					{
						c=getc(fp);
						id_count++;
						state = 1;
					}
					else
					{
						state=2;
					}
				}
				break;
			case 2: 
				{
					ungetc(c,fp);
					//lookup till end_ptr-1
					printf("ID ");	// or KW
					state=0;
				}
				break;
			case 3: 
				{
					if(is_digit(c))
					{
						c = getc(fp);
						state=3;
					}
					else if('.' == c)
					{
						c = getc(fp);
						state = 5;
					}
					else
					{
						state = 4;
					}
				}
				break;
			case 4: 
				{
					ungetc(c,fp);
					// do atoi() to get value  till end_ptr-1
					printf("NUM ");
					state=0;
				}
				break;
			case 5:
				{
					if(is_digit(c))
					{
						c = getc(fp);
						state=7;
					}
					else if( '.' == c)
					{
						state = 6;
					}
					else
					{
						state = TRAP_STATE;
					}
				}
				break;
			case 6:
				{
					ungetc('.', fp);
					ungetc('.', fp);
					// atoi( ( f_ptr .. end_ptr - 2 )
					printf("NUM ");
					state = 0;
				}
			case 7: 
				{
					if(is_digit(c))
					{
						c = getc(fp);
						state = 7;
					}
					else if('E' == c || 'e' == c)
					{
						c= getc(fp);
						state=9;
					}
					else
					{
						state = 8;
					} 
				}
				break;
			case 8: 
				{
					ungetc(c,fp);
					// do atof()  till end_ptr-1
					printf("RNUM");
					state=0;
				}
				break;
			case 9: 
				{
					if('+' == c || '-' == c)
					{
						c = getc(fp);
						state=10;
					}
					else if(is_digit(c))
					{
						c = getc(fp);
						state=11;
					}
					else
					{
						state = TRAP_STATE;
					}
				}
					break;
			case 10: 
				{
					if(is_digit(c))
					{
						c = getc(fp);
						state=11;
					}
					else
					{
						state = TRAP_STATE;
					}
				}
				break;
			case 11: 
				{
					if(is_digit(c))
					{
						c = getc(fp);
						state=11;
					}
					else 
					{
						state=12;
					}
				}
				break;
			case 12: 
				{
					ungetc(c,fp);
					//atof() end_ptr-1
					printf("RNUM ");
					state = 0;
				}
				break;
			case 13:
				{
					if ( is_delim(c) )
					{
						c = getc(fp);
						state = 13;
					}
					else
					{
						state = 14;
					}
				}
				break;
			case 14:
				{
					ungetc(c, fp);
					state = 0;
				}
				break;
			case 15:
				{
					//arith_op , PLUS
					printf("PLUS ");
					state = 0;
				}
				break;
			case 16:
				{
					//arith_op , MINUS
					printf("MINUS ");
					state = 0;
				}
				break;
			case 17:
				{
					if( '*' == c)
					{
						c = getc(fp);
						state = 19;
					}
					else
					{
						state = 18;
					}
				}
				break;
			case 18:
				{
					ungetc(c, fp);
					//arith_op, mul
					printf("MUL ");
					state = 0;
				}
				break;
			case 19:
				{	
					if( '*' == c)
					{
						c = getc(fp);
						state = 20;
					}
					else
					{
						state = 19;
					}
				}
				break;
			case 20:
				{
					if( '*' == c)
					{
						state = 21;
					}
					else
					{
						c = getc(fp);
						state = 19;
					}
				}
				break;
			case 21:
				{
					printf("COMMENT ");	//ignore this token
					state = 0;
				}
				break;
			case 22:
				{
					printf("DIV ");
					state = 0;
				}
				break;
			case 23:
				{
					if('=' == c)
					{
						state = 25;
					}
					else if('<' == c)
					{
						state = 26;
					}
					else
					{
						state = 24;
					}
				}
				break;
			case 24:
				{
					ungetc(c, fp);
					printf("LT ");
				}
				break;
			case 25:
				{
					printf("LE ");
					state = 0;
				}
				break;
			case 26:
				{
					printf("DEF ");
					state = 0;
				}
				break;
			case 27:
				{
					if('=' == c)
					{
						state = 29;
					}
					else if('>' == c)
					{
						state = 30;
					}
					else
					{
						state = 28;
					}
				}
				break;
			case 28:
				{
					ungetc(c, fp);
					printf("GT ");
				}
				break;
			case 29:
				{
					printf("GE ");
					state = 0;
				}
				break;
			case 30:
				{
					printf("ENDDEF ");
					state = 0;
				}
				break;
			case 31:
				{	
					if('=' == c)
					{
						state = 32;
					}
					else
					{
						state = TRAP_STATE;
					}
				}
				break;
			case 32:
				{
					printf("EQ ");
					state = 0;
				}
				break;
			case 33:
				{	
					if('=' == c)
					{
						state = 34;
					}
					else
					{
						state = TRAP_STATE;
					}
				}
				break;
			case 34:
				{
					printf("NE ");
					state = 0;
				}
				break;
			case 35:
				{
					if('=' == c)
					{
						state = 36;
					}
					else
					{
						state = 37;
					}
				}
				break;
			case 36:
				{
					printf("ASSIGNOP ");
					state = 0;
				}
				break;
			case 37:
				{
					ungetc( c, fp );
					print("COLON ");
					state = 0;
				}
				break;
			case 38:
				{
					if( '.' == c)
					{
						state = 39;
					}
					else
					{
						state = TRAP_STATE;
					}
				}
				break;
			case 39:
				{
					printf("RANGEOP ");
					state = 0;
				}
				break;
			case 40:
				{
					ungetc(c, fp);
					printf("SEMICOL ");
					state = 0;
				}
				break;
			case 41:
				{
					ungetc(c, fp);
					printf("COMMA ");
					state = 0;
				}
				break;
			case 42:
				{
					ungetc(c, fp);
					printf("SQBO ");
					state = 0;
				}
				break;
			case 43:
				{
					ungetc(c, fp);
					printf("SQBC ");
					state = 0;
				}
				break;
			case 44:
				{
					ungetc(c, fp);
					printf("BO ");
					state = 0;
				}
				break;
			case 45:
				{
					ungetc(c, fp);
					printf("BC ");
					state = 0;
				}
				break;
			case 46:
				{
					ungetc(c, fp);
					printf("LEXING DONE... ");
					state = 0;
					//exit(0);
				}
				break;
			case TRAP_STATE:
			default:
				{
					// ungetc() the character read
					//lex_error() line_no, msg
					// state = 0
				}
		}	//  End of switch
	}	// End of while
}	// End of main