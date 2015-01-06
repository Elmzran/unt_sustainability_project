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
void	find_city_state_zip(FILE *fp, char str[][MAX_SIZE], int num);
void	find_county(FILE *fp, char str[][MAX_SIZE], int num);
void	find_website(FILE *fp, char str[][MAX_SIZE], int num);
void	find_misc(FILE *fp, char str[][MAX_SIZE], int num, char data[]);

/* Begin execution */
int main(int argc, char *argv[])
{
	FILE	*fold, *fnew;
	char	str_init[512], str[16][MAX_SIZE], strtemp[MAX_SIZE];
	int	i, j;

	/* This first section is the consolidation of strip.c into format.c
	The following chunk of code will strip out all of the tabs and the
	[ Yahoo! Maps ] text block. */

	/* Open the files for stripping */
	fold = fopen(argv[1], "r");
	fnew = fopen("temp.txt", "w");

	/* Scan through the file */
	while (feof(fold) == 0)
	{
		/* Read in the current line */
		fscanf(fold, "%[^\n\t]s", str_init);
		/* Checks if string contains "Yahoo!" */
		if (strstr(str_init, "Yahoo!") == NULL)
			/* If the string doesn't contain "Yahoo!", then print it out in the new file */
			if (feof(fold) == 0)
				fprintf(fnew, "%s\n", str_init);
		/* Advance to the next line */
		getc(fold);
		/* Empty the string */
		str_init[0] = '\0';
	}

	/* Close the files from the stripping */
	fclose(fold), fclose(fnew);

	/* Zeros out the string array */
	for (i = 0; i < 16; ++i)
		str[i][0] = '\0';

	/* Open up the files for formatting */
	fold = fopen("temp.txt", "r");
	fnew = fopen(argv[2], "w");

	/* Loop through the file until the end */
	while (feof(fold) == 0)
	{
		/* Load in all data for one business */
		for (i = 0; strstr(str[i - 1], "# OF") == NULL && feof(fold) == 0; ++i)
		{
			/* Scan in the data to the current string */
			fscanf(fold, "%[^\n]s", str[i]);
			/* Skip the newline */
			getc(fold);
		}

		/* Iterate through all functions for proper formatting of data,
		so it can be imported into excel, check for end of file to prevent
		segfault */
		if (feof(fold) == 0)
		{
			find_company(fnew, str, i);
			find_address(fnew, str, i);
			find_city_state_zip(fnew, str, i);
			find_county(fnew, str, i);
			find_website(fnew, str, i);
			find_misc(fnew, str, i, "PHONE: ");
			find_misc(fnew, str, i, "FAX: ");
			find_misc(fnew, str, i, "CONTACT: ");
			find_misc(fnew, str, i, "DESCRIPTION: ");
			find_misc(fnew, str, i, "NAICS: ");
			find_misc(fnew, str, i, "SALES: ");
			find_misc(fnew, str, i, "# OF EMPLOYEES: ");
		}

		/* Print a row delineator */
		if (feof(fold) == 0)
			fprintf(fnew, "\n");
	}

	/* Close the files */
	fclose(fold), fclose(fnew);

	return 0;
}

/* Search for and print the company name, always first (?) */
void find_company(FILE *fp, char str[][MAX_SIZE], int num)
{
	/* Print out the first data string, since it's always the company name */
	fprintf(fp, "%s%c", str[0], DELIN);

	/* Empty the string */
	str[0][0] = '\0';

	return;
}

/* Search for and print the address, which occurs before city, state, zip, so if TX is found,
then the business has no address available */
void find_address(FILE *fp, char str[][MAX_SIZE], int num)
{
	int i;

	/* Iterate through each str */
	for (i = 1; i < num; ++i)
	{
		/* Checks for the presence of TX */
		if (strstr(str[i], " TX") == NULL)
		{
			fprintf(fp, "%s%c", str[i], DELIN);
			str[i][0] = '\0';
			break;
		}
		else
		{
			/* Print one DELIN for the lack of city, state, and zip */
			fprintf(fp, "%c", DELIN);
			break;
		}
	}

	return;
}

/* Search for and print the city, state, and zip */
void find_city_state_zip(FILE *fp, char str[][MAX_SIZE], int num)
{
	/* IDENTIFIERS */
	int i;
	char city[MAX_SIZE], state[MAX_SIZE], zip[MAX_SIZE];

	/* Iterate through each string, looking for TX */
	for (i = 1; i < num; ++i)
	{
		/* Checks for the presence of TX */
		if (strstr(str[i], " TX") != NULL)
		{
			/* Scan in city, state, and the first five digits of the zip from CITY, STATE, ZIP string */
			sscanf(str[i], "%[^,] %[^0123456789] %5s", city, state, zip);
			/* Shifts state string forward 1 to eliminate comma, and removes last whitespace */
			state[0] = state[2];
			state[1] = state[3];
			state[2] = '\0';
			/* Print city, state, and zip, with DELIN so each has their own column */
			fprintf(fp, "%s%c", city, DELIN);
			fprintf(fp, "%s%c", state, DELIN);
			fprintf(fp, "%s%c", zip, DELIN);
			str[i][0] = '\0';
			return;
		}
	}

	/* If a city, state, and zip aren't found, print the proper amounts of delin */
	fprintf(fp, "%c", DELIN);
	fprintf(fp, "%c", DELIN);
	fprintf(fp, "%c", DELIN);
	return;
}

/* Search for and print the county */
void find_county(FILE *fp, char str[][MAX_SIZE], int num)
{
	int i, j;

	/* Iterate through each string, looking for the lack of certain substrings */
	for (i = 1; i < num; ++i)
	{
		/* Checks for the presence of county and lack of other substrings */
		if (strstr(str[i], " County") != NULL)
			if (strstr(str[i], "DESCRIPTION") == NULL && strstr(str[i], " TX") == NULL)
			{
				/* Remove the extra space at the end of county lines */
				for (j = 0; str[i][j] != '\0'; ++j);
				str[i][j - 1] = '\0';

				/* Print out the data into the file */
				fprintf(fp, "%s%c", str[i], DELIN);
				str[i][0] = '\0';
				return;
			}
	}

	/* If a county isn't found, print the delin */
	fprintf(fp, "%c", DELIN);
	return;
}

/* Search for and print the website */
void find_website(FILE *fp, char str[][MAX_SIZE], int num)
{
	int i;

	/* Iterate through each string, looking for http:// */
	for (i = 1; i < num; ++i)
		/* Checks for the presence of http:// */
		if (strstr(str[i], "http://") != NULL)
		{
			fprintf(fp, "%s%c", str[i], DELIN);
			str[i][0] = '\0';
			return;
		}

	/* If a website ins't found, print the delin */
	fprintf(fp, "%c", DELIN);
	return;
}

/* Find a misc data field */
void find_misc(FILE *fp, char str[][MAX_SIZE], int num, char data[])
{
	int i;

	/* Iterate through each string, looking for data[] */
	for (i = 1; i < num; ++i)
		/* Checks for the presence of the string data[] */
		if (strstr(str[i], data) != NULL)
		{
			fprintf(fp, "%s%c", str[i] + strlen(data), DELIN);
			str[i][0] = '\0';
			return;
		}

	/* If data[] isn't found, print the delin */
	fprintf(fp, "%c", DELIN);
	return;
}
