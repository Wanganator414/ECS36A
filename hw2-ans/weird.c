/*
Written for ECS36A, Fall 2019

Eric Wang, October 19, 2019

Analyze output of the one-liner below
*/

/*Missing headers*/
/*This program manages to print the word "unix" in the console without the use of any preprocessor calls or libraries*/

main()
{
    printf(&1 ["\021%six\012\0"], (1)["have"] + "fun" - 0x60);
}

/*First thing to note is that apparently one can swap the order of bracket array notations when concerning strings, etc: "x"[1] == 1["x"]
    By the same token, the first line in the above program can be translated to:
        printf(&"\021%six\012\0"[1],"have"[1] + "fun" - 0x60);

    "\021" and "\012" are both control characters that will not be read. "\0" is the NUL character, so it will be printed.
    
    The '&' in front of the strings with array indices will result in a substring like effect where the only characters after the index notation will be printed.
    
    Similar to how substrings work in most languages, &"\021%six\012\0"[1] will end up equivlent to printf("%six").
    
    For the later parts: "have"[1] + "fun" - 0x60 will be the address of a + "fun" - 0x60. Where "a" in hexadecimal is 0x61, when minused by 0x60, will bne just 1.

    The above will yield "fun"+1, from a pointer perspective, "fun" will start from "f" and one pointer location later will be "u". 

    By the same token, "fun" + 1 will yield a substring of "un".

    Now, the entire line becomes printf("%six","fun" + 1); where the address of "fun"+1 will yield "un", and with the %s, "un" will be put in front of "ix".

    Thus: unix is printed. 
*/