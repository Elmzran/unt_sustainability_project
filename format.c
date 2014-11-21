/*
Author: Jonathan Roosa (JonathanRoosa@my.unt.edu)

Date: 11/21/14

Purpose: This program will take all of the business data, sort through it,
format it, add delineators, blankspaces for missing data, and allow for
perfect importing into excel.
*/

#include <stdio.h>
#include <string.h>

/* 59 = ; char dec val */
#define DELIN 59
#define MAX_SIZE 256

/* Function prototypes for each data set */
void	find_company(FILE *fp, char str[][MAX_SIZE], int num);
void	find_address(FILE *fp, char str[][MAX_SIZE], int num);
void	find_city_state_zip(FILE *fp, char *str[], int num);
void	find_country(FILE *fp, char *str[], int num);
void	find_website(FILE *fp, char *str[], int num);
void	find_phone(FILE *fp, char *str[], int num);
void	find_tax(FILE *fp, char *str[], int num);
void	finx_contact(FILE *fp, char *str[], int num);
void	find_description(FILE *fp, char *str[], int num);
void	find_naics(FILE *fp, char *str[], int num);
void	find_sales(FILE *fp, char *str[], int num);
void	find_exmployees(FILE *fp, char *str[], int num);

/* Begin execution */
int main(int argc, char *argv[])
{
	FILE	*fold, *fnew;
	char	str[16][MAX_SIZE];
	int	i, j;

	/* Open up the files */
	fold = fopen(argv[1], "r");
	fnew = fopen(argv[2], "w");

	/* Loop through the file until the end */
	while (feof(fold) == 0)
	{
		/* Load in all data for one business */
		for (i = 0; strstr(str[i - 1], "# OF") == NULL; ++i)
		{
			/* Scan in the data to the current string */
			fscanf(fold, "%[^\n]s", str[i]);
			/* Skip the newline */
			getc(fold);
		}
		
		/* Iterate through all functions for proper formatting of data,
		so it can be imported into excel */
		find_company(fnew, str, i);
		find_address(fnew, str, i);

		/* Zero out all of the data. Will cause segfault if a for loop is used */
		str[0][0] = '\0';
		str[1][0] = '\0';
		str[2][0] = '\0';
		str[3][0] = '\0';
		str[4][0] = '\0';
		str[5][0] = '\0';
		str[6][0] = '\0';
		str[7][0] = '\0';
		str[8][0] = '\0';
		str[9][0] = '\0';
		str[10][0] = '\0';
	}

	/* Close the files */
	fclose(fold), fclose(fnew);

	return 0;
}

/* Search for and print the company name, always first (?) */
void find_company(FILE *fp, char str[][MAX_SIZE], int num)
{
	/* Print out the first data string, since it's always the company name */
	fprintf(fp, "%s%c\n", str[0], DELIN);

	/* Empty the string */
	str[0][0] = '\0';	

	return;
}

/* Search for and print the address, will not contain any of the unique data of the other sets,
and is never first */
void find_address(FILE *fp, char str[][MAX_SIZE], int num)
{
	i = 0;

	/**/
}
