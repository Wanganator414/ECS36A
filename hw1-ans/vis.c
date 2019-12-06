/*Reads characters from the standard input and print them on the 
standard output after expanding any non-printing characters to 
* their C character escape sequence.

Eric Wang September 26
*/

/*Tabbed all code to show hierarchy*/
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	/*Character placeholder for loop checking*/
	int ch;

	/*
	While entered value is not invalid (such as EOF(-1)), loop thru and check for escape characters
	*/
	while ((ch = getchar()) != EOF)
	{
		/*If not a printable charcater, check character to see if it matches any listed escape characters,if so print escape character*/
		/*Checks each case scenario until a true condition is met*/
		/*Check nonprintable values first*/
		switch (ch)
		{
			/* Print out tab character if true*/
		case '\t':
			printf("\\t");
			break;
			/*Print out backspace character if true*/
		case '\b':
			printf("\\b");
			break;
			/*Print out form feed charcater if true*/
		case '\f':
			printf("\\f");
			break;
			/*Print out null character if true*/
		case '\0':
			printf("\\0");
			break;
			/*Print out entered amount of backslashes if true*/
		case '\\':
			printf("\\\\");
			break;
			/*Print out vertical tab escape character if true*/
		case '\v':
			printf("\\v");
			break;
			/*Print out carriage return escape character if true*/
		case '\r':
			printf("\\r"); 
			break;
			/*Print out bell escape character if true*/
		case '\a': /*Added semi colon to original code*/
			printf("\\a");
			break;
			/*Print newline escape character and skip to next line when newline character detected*/
		case '\n':
			printf("\\n\n");
			break;
			/*If said character is not on the specified list, do the following*/
		default: /*Moved the printing of regular printable characters here to prioritize the listed nonprointable charcaters first*/
			/*Checks if 'ch' is a printable character returns 1 if true 0 if otherwise*/
			if (isprint(ch))
				/*Print out 'ch' if 'ch' is a printable character*/
				putchar(ch);
			else
			{
				/*Print any unprintable characters NOT on the list in 3 digit octal format*/
				printf("\\%03o", ch);
				break;
			}
		}
	}
	/*Return normal exit code if all goes well*/
	return (0);
}
