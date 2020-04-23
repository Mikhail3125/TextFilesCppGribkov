#include "Stdafx.h"
using namespace std;
#define MAX_DATES 10

#ifndef _str
#define _str
struct str
{
    int date;
    int month;
    int year;
} dat[MAX_DATES];
#endif // !_str

void MidleLevelTask()
{
/*
Дан файл, содержащий различные даты. Каждая дата – это число, месяц и год. Найти  год с наименьшим номером
*/
	cout << "\Midle level task:\n";
    FILE* read;
    int n, i, min_year;

    //read from file to struct
    i = 0;
    read = fopen("years.txt", "rt");
    while (!feof(read))
    {
        fscanf(read, "%d.%d.%d", &dat[i].date, &dat[i].month, &dat[i].year);
        printf("%d-date read from file <<years.txt>> %d.%d.%d\n", i+1, dat[i].date, dat[i].month, dat[i].year);
        i++;
    }
    fclose(read);
    n = i++;  //years count
    // end of read

    min_year = dat[0].year;
    for (i = 1; i < n; i++)
    {
        if (dat[i].year < min_year)
            min_year = dat[i].year;
    }

    printf("\nMin year = %d", min_year);
}
