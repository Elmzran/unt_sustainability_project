/*
Author: Jonathan Roosa (JonathanRoosa@my.unt.edu)

Date: 11/21/14

Purpose: Strip out all tabs and [ Yahoo! Maps ] content from the
business lists for the data project, forcing each piece of data
on its own line
*/
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE	*fold, *fnew;
	char	str[512];

	/* Open the file for reading */
	fold = fopen(argv[1], "r");
	fnew = fopen(argv[2], "w");

	/* Scan through the file*/
	while (feof(fold) == 0)
	{
		/* Read in the current line */
		fscanf(fold, "%[^\n\t]s", str);
		/* Checks if string contains "Yahoo!" */
		if (strstr(str, "Yahoo!") == NULL)
			/* If the string doesn't contain "Yahoo!", then print it out in the new file */
			fprintf(fnew, "%s\n", str);
		getc(fold);
	}

	/* Close both files */
	fclose(fold), fclose(fnew);

	return 0;
}
