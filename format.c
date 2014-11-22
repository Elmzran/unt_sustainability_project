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
	char	str[16][MAX_SIZE], strtemp[MAX_SIZE];
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

		/* Print a row delineator */
		fprintf(fnew, "~\n");
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
			fprintf(fp, "%s%c\n", str[i], DELIN);
			str[i][0] = '\0';
			break;
		}
		else
		{
			fprintf(fp, "%c\n", DELIN);
			break;
		}
	}

	return;
}

/* Search for and print the city, state, and zip */
void find_city_state_zip(FILE *fp, char str[][MAX_SIZE], int num)
{
	int i;

	/* Iterate through each string, looking for TX */
	for (i = 1; i < num; ++i)
	{
		/* Checks for the presence of TX */
		if (strstr(str[i], " TX") != NULL)
		{
			fprintf(fp, "%s%c\n", str[i], DELIN);
			str[i][0] = '\0';
			return;
		}
	}

	/* If a city, state, and zip aren't found, print the delin */
	fprintf(fp, "%c\n", DELIN);
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
				fprintf(fp, "%s%c\n", str[i], DELIN);
				str[i][0] = '\0';
				return;
			}
	}

	/* If a county isn't found, print the delin */
	fprintf(fp, "%c\n", DELIN);
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
			fprintf(fp, "%s%c\n", str[i], DELIN);
			str[i][0] = '\0';
			return;
		}

	/* If a website ins't found, print the delin */
	fprintf(fp, "%c\n", DELIN);
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
			fprintf(fp, "%s%c\n", str[i] + strlen(data), DELIN);
			str[i][0] = '\0';
			return;
		}

	/* If data[] isn't found, print the delin */
	fprintf(fp, "%c\n", DELIN);
	return;
}
