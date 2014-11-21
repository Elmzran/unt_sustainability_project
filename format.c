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

/* Function prototypes for each data set */
void	find_company(char **str);
void	find_address(char **str);
void	find_city_state_zip(char **str);
void	find_country(char **str);
void	find_website(char **str);
void	find_phone(char **str);
void	find_tax(char **str);
void	finx_contact(char **str);
void	find_description(char **str);
void	find_naics(char **str);
void	find_sales(char **str);
void	find_exmployees(char **str);

/* Begin execution */
int main(int argc, char *argv[])
{
	FILE	*fold, *fnew;
	char	str[16][256];
	int	i = 0;

	/* Open up the files */
	fold = fopen(argv[1], "r");
	fnew = fopen(argv[2], "w");

	/* Loop through the file until the end */
	while (feof(fold) == 0)
	{
		/* Load in all data for one business */
		for (i = 0; strstr(str, "# OF EMPLOYEES:") == NULL; ++i)
			fscanf(fold, "%[^\n]s", str[i]);
	}
}
