// Helen Chac
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
  short hour;
  short minutes;

}Time;
typedef struct
{
  Time startTime;
  Time endTime;
  char* subject;
  char* location;
}Appt;
typedef struct
{
  short month;
  short day;
  Appt* appts[8];
  short apptCount;
}Day;
Day* read_file(Day *days, int *size, char* filename, int *appt_days);
Day* resize(Day *days, int *size);
void strtoken_time(Day *days, int locator, char *subject, char *start, char *end, char *location);
char* strtoken_line(char *string);
void read_inputfile(char *inputfile, Day *days, int appt_days);

void search_date(char *string, Day *days, int appt_days);
void search_subject(char *string, Day *days, int appt_days);

int main(int argc, char **argv)
{
  Day *days;
  int size = 30, appt_days;

  if (argc != 3)
  {
    printf("usage: calendar datafile inputfile\n");
    return -1;
  }
  days = (Day*)malloc(size*sizeof(Day));
  days = read_file(days, &size, argv[1], &appt_days);

  read_inputfile(argv[2], days, appt_days);  
  return 0;
}

Day* resize(Day *days, int *size)
{
  Day *temp;
  int i;
//  *size = (*size)*2;
//  printf("enters here\n");
  temp = (Day*)malloc(((*size)*2) *sizeof(Day));
  for (i =0; i < *size; i++)
  {
      temp[i] = days[i];
  }
  free(days);
  *size = (*size) * 2;

  return temp;
}//

Day* read_file(Day *days, int *size, char* filename, int *appt_days)
{
  FILE *fp = fopen(filename, "r");
  *appt_days = 0;
  char line[1000], *ptr, subject[100], location[100], start_time[100], end_time[100] ;
  short month = 0, day = 0;
  int day_counter = 0, i;
  fgets(line, 1000, fp);
   while((ptr = fgets(line, 1000, fp)) != NULL)
  {
    if ( day_counter == *size )
      days = resize(days, size);
    month = atoi(strtoken_line(line));
    day = atoi(strtoken_line(NULL));
    strtoken_line(NULL);
    for (i = 0; i < day_counter; i++)
      if ( days[i].month == month && days[i].day == day )
      {
        days[i].apptCount++;
        break;
      }
    days[i].month = month;
    days[i].day = day;
    strcpy(subject, strtoken_line(NULL));
    strcpy(start_time, strtoken_line(NULL));
    strcpy(end_time, strtoken_line(NULL));
    strcpy(location, strtoken_line(NULL));
    
    days[i].appts[days[i].apptCount] = (Appt*)malloc(1*sizeof(Appt));
    days[i].appts[days[i].apptCount]->subject = (char*)malloc((strlen(subject)+1)*sizeof(char));
    days[i].appts[days[i].apptCount]->location = (char*)malloc((strlen(location)+1)*sizeof(char));
//    day(day_counter).appts = (Appt*)malloc(1*sizeof(Appt));
    strtoken_time(days, i, subject, start_time, end_time, location);
//    days[i].appts[days[i].apptCount]
//    printf("month: %d day: %d\n", days[i].month, days[i].day);
//    printf("%s %s\n", subject, location);
//    printf("start time: %02d:%02d ; end time: %02d:%02d\n", 
//    printf("%s - %s\n", days[i].appts[days[i].apptCount]->subject, days[i].appts[days[i].apptCount]->location);
//    printf("start time: %d:%d, end time: %d %d\n", days[i].appts[days[i].apptCount]->startTime.hour, days[i].appts[days[i].apptCount]->startTime.minutes, days[i].appts[days[i].apptCount]->endTime.hour, days[i].appts[days[i].apptCount]->endTime.minutes);
    if (i == day_counter)
      day_counter++; 
    }
//    days[i].appts[days.apptCount] = strtoken_time(days, i, subject, start_time, end_time, location);
/*
  for ( i = 0; i < day_counter; i++)
  {
    printf("month: %d day: %d\n", days[i].month, days[i].day);
    printf("apptCount: %d\n", days[i].apptCount);
    for (int j = 0; j <= days[i].apptCount; j++)
    {
      printf("subject: %s, location: %s \n", days[i].appts[j]->subject, days[i].appts[j]->location);
      printf("start: %d:%d, end: %d:%d \n", days[i].appts[j]->startTime.hour, days[i].appts[j]->startTime.minutes, days[i].appts[j]->endTime.hour, days[i].appts[j]->endTime.minutes);
    }
  }
*/
  (*appt_days) = day_counter;
//  printf("line = %d size = %d\n", day_counter, *size);
  return days;
} 

char* strtoken_line(char *string)
{
  char *ptr;
  ptr = strtok(string, "/\n\r,");
  return ptr;
}

void strtoken_time(Day *days, int locator, char *subject, char *start, char *end, char *location)
{
  int hour; 
  if (strstr(start, "AM"))
  {
    days[locator].appts[days[locator].apptCount]->startTime.hour = atoi(strtok(start, ":"));
  }
  else if (strstr(start, "PM"))
  {
    hour = atoi(strtok(start,":"));
    if (hour != 12)
      days[locator].appts[days[locator].apptCount]->startTime.hour = hour + 12;
    else
      days[locator].appts[days[locator].apptCount]->startTime.hour = 12;
      
  }
  days[locator].appts[days[locator].apptCount]->startTime.minutes = atoi(strtok(NULL, ":"));
  if (strstr(end, "AM"))
    days[locator].appts[days[locator].apptCount]->endTime.hour = atoi(strtok(end, ":"));
  else if (strstr(end, "PM"))
  {
    hour = atoi(strtok(end,":"));
//    printf("hour: %d\n", hour);
    if (hour != 12)
      days[locator].appts[days[locator].apptCount]->endTime.hour = hour +12;
    else
      days[locator].appts[days[locator].apptCount]->endTime.hour = 12;

  }
/*
  printf("%s\n", end);
  printf("segfault here : ( \n");
  char *temp = strtok(NULL, ":");
  printf("temp: %s\n", temp);
*/
  days[locator].appts[days[locator].apptCount]->endTime.minutes = atoi(strtok(NULL, ":"));
  strcpy(days[locator].appts[days[locator].apptCount]->subject, subject);
  strcpy(days[locator].appts[days[locator].apptCount]->location, location);

}

void read_inputfile(char *inputfile, Day *days, int appt_days)
{
  FILE *fp = fopen(inputfile, "r");
  char line[1000], line_input[1000], *ptr;
  int input, i = 1;
  fgets(line, 1000, fp);
  while ( ( fgets(line, 1000, fp)) != NULL)
  {
    strcpy(line_input, line);
    input = atoi(strtok(line, ","));
    ptr = strtok(NULL, "\n," );
    printf("CSV Entry- %d)   %s\n", i, line_input);
    if ( input == 1 )
    {
//      printf("Month and day(mm/dd) >> ");
      search_date(ptr, days, appt_days);
    }
    else if (input == 2)
    {
//      printf("
      search_subject(ptr, days, appt_days);
    } 
    else
      printf("Invalid Choice\n");
    i++;
  }

}//read_inputfile()

void search_date(char *string, Day *days, int appt_days)
{
  char string2[100], *ptr;
  int i, j, month, day;
  strcpy(string2, string);
  ptr = strchr(string, '\r');
  *ptr = '\0';
  printf("Month and day (mm/dd) >> %s\n", string);
  if (!isalpha(string[0])){
//    printf("%s is not a valid date.\n", string2);
  month = atoi(strtok(string2, "/\r\n"));
  day = atoi(strtok(string2, "\r/\n"));
  if ( month > 0 && month < 13 && day > 0 && day < 32 )
    for (i = 0; i < appt_days; i++)
    {
      if (days[i].month == month && days[i].day == day)
      {
        printf("Start End   Subject         Location\n");
        for (j = 0; j < days[i].apptCount; j++)
        {
//          found++;
          printf("%02hd:%02hd %02hd:%02hd %-15s %-s\n", 
days[i].appts[j]->startTime.hour, days[i].appts[j]->startTime.minutes, 
days[i].appts[j]->endTime.hour, days[i].appts[j]->endTime.minutes, 
days[i].appts[j]->subject, days[i].appts[j]->location);
        }
      }
    }
  else
    printf("%s is not a valid date.\n", string);
    
  }
  else
//  if(!found)
    printf("%s is not a valid date.\n", string);
//    printf("%s is not a valid date.\n", string);
/*
  printf("string: %s\n", string);
  printf("%s", string);
  printf(" is not a valid date.\n");
*/
}

void search_subject(char *string, Day *days, int appt_days)
{
  int i, j, found = 0;
  char copy[100], *ptr;
  ptr = strtok(string, "\r\n^M");
  strcpy(copy, ptr);
  for (i = 0; i < appt_days; i++)
  {
    for (j = 0; j <= days[i].apptCount ; j++)
      if (strcmp(string, days[i].appts[j]->subject)==0)
      {
        if (found == 0)
          printf("Date  Start End   Subject         Location\n"); 
        printf("%2hd/%-2hd %02hd:%02hd %02hd:%02hd %-15s %-s\n", days[i].month, days[i].day, days[i].appts[j]->startTime.hour, days[i].appts[j]->startTime.minutes, days[i].appts[j]->endTime.hour, days[i].appts[j]->endTime.minutes, days[i].appts[j]->subject, days[i].appts[j]->location );
        found++;
      }
  }
  if (found ==0)
    printf("%s was not found as a subject in the calendar.\n", copy);
}
