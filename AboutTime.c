#include "Common.h"

#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>


int printTime(char *ampm)
{
	char buff[128];//, ampm[] = "AM";
	__time64_t lgtime;
	struct __timeb64 timstruct;
	struct tm *today, *thegmt, xmas = { 0, 0, 12, 25, 11, 90 };
	/* set time zone from TZ environment variable. If TZ is not set,
	 * the operating system is queried to obtain the default value
	 * for the variable.*/
	_tzset();
	/* get UNIX-style time and display as number and string. */
	_time64(&lgtime);
	printf("Time in seconds since UTC 1/1/70:\t%ld seconds\n", lgtime);
	printf("UNIX time and date:\t\t\t%s", _ctime64(&lgtime));
	/* display UTC. */
	thegmt = _gmtime64(&lgtime);
	printf("Coordinated universal time, UTC:\t%s", asctime(thegmt));
	/* display operating system-style date and time. */
	_strtime(buff);
	printf("OS time:\t\t\t\t%s\n", buff);
	_strdate(buff);
	printf("OS date:\t\t\t\t%s\n", buff);
	/* convert to time structure and adjust for PM if necessary. */
	today = _localtime64(&lgtime);
	if (today->tm_hour >= 12) {
		strcpy(ampm, "PM");
		today->tm_hour -= 12;
	}
	/* adjust if midnight hour. */
	if (today->tm_hour == 0)
		today->tm_hour = 12;
	/* pointer addition is used to skip the first 11
	 * characters and printf() is used to trim off terminating
	 * characters.*/
	printf("12-hour time:\t\t\t\t%.8s %s\n", asctime(today) + 11, ampm);
	/* print additional time information. */
	_ftime64(&timstruct);
	printf("Plus milliseconds:\t\t\t%u\n", timstruct.millitm);
	printf("Zone difference in hours from UTC:\t%u hours\n",
			timstruct.timezone / 60);
	printf("Time zone name:\t\t\t\t%s\n", _tzname[0]);
	printf("Daylight savings:\t\t\t%s\n",
			timstruct.dstflag ? "YES" : "NOT SET");
	/* make time for noon on Christmas, 1990. */
	if (_mktime64(&xmas) != (__time64_t ) -1)
		printf("Christmas\t\t\t\t%s", asctime(&xmas));
	/* use time structure to build a customized time string. */
	today = _localtime64(&lgtime);
	/* use strftime to build a customized time string. */
	strftime(buff, 128, "Today is %A, day %d of %B in the year %Y.\n", today);
	printf(buff);
	return 0;
}
