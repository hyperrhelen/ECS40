// Author: Helen Chac
//
// File: calendar.cpp written in C
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
void strtoken_time(Day *days, int locate, char *subject, char *start, char *end, char *location);
char* strtoken_line(char *string);
void read_inputfile(char *inputfile, Day *days, int appt_days);

void search_date(char *string, Day *days, int appt_days);
void search_subject(char *string, Day *days, int appt_days);
int day_cmp(const void *ptr, const void *ptr2);

int main(int argc, char **argv)
{
  Day *days;
  int size = 30, appt_days;

  if (argc != 3){
    printf("usage: calendar datafile inputfile\n");
    return -1;
  }
  days = (Day*)malloc(size*sizeof(Day));
  days = read_file(days, &size, argv[1], &appt_days);

  qsort(days, appt_days, sizeof(Day), day_cmp);
  read_inputfile(argv[2], days, appt_days);  
  return 0;
}//main()

int day_cmp(const void* ptr1, const void* ptr2)
{
  if (((Day*)ptr1)->month < ((Day*)ptr2)->month)
    return -1;
  else if (((Day*)ptr1)->month > ((Day*)ptr2)->month)
    return 1;
  if (((Day*)ptr1)->day < ((Day*)ptr2)->day)
    return -1;
  else if (((Day*)ptr1)->day > ((Day*)ptr2)->day)
    return 1;
  else
    return 0;
} //day_cmp()

Day* resize(Day *days, int *size)
{
  Day *temp;
  int i;

  temp = (Day*)malloc(((*size)*2) *sizeof(Day));
  for (i =0; i < *size; i++){
      temp[i] = days[i];
  } //for()
  free(days);
  *size = (*size) * 2;

  return temp;
}//resize()

Day* read_file(Day *days, int *size, char* filename, int *appt_days)
{
  FILE *fp = fopen(filename, "r");
  char line[1000], *ptr, subject[100], location[100], start_time[100], end_time[100] ;
  short month = 0, day = 0;
  int day_counter = 0, i;
  fgets(line, 1000, fp);
  while((ptr = fgets(line, 1000, fp)) != NULL){
    if ( day_counter == *size )
      days = resize(days, size);
    month = atoi(strtoken_line(line));
    day = atoi(strtoken_line(NULL));
    strtoken_line(NULL);
    for (i = 0; i < day_counter; i++)
      if ( days[i].month == month && days[i].day == day ){
        days[i].apptCount++;
         break;
      }//if()
    days[i].month = month;
    days[i].day = day;
    strcpy(subject, strtoken_line(NULL));
    strcpy(start_time, strtoken_line(NULL));
    strcpy(end_time, strtoken_line(NULL));
    strcpy(location, strtoken_line(NULL));
    days[i].appts[days[i].apptCount] = (Appt*)malloc(1*sizeof(Appt));
    days[i].appts[days[i].apptCount]->subject = (char*)malloc((strlen(subject)+1)*sizeof(char));
    days[i].appts[days[i].apptCount]->location = (char*)malloc((strlen(location)+1)*sizeof(char));
    strtoken_time(days, i, subject, start_time, end_time, location);
    if (i == day_counter)
      day_counter++; 
   }//while()
  (*appt_days) = day_counter;
  return days;
} // read_file() 

char* strtoken_line(char *string)
{
  char *ptr;
  ptr = strtok(string, "/\n\r,");
  return ptr;
}// strtoken_line()

void strtoken_time(Day *days, int locate, char *subject, char *start, char *end, char *location)
{
  int hour; 
  if (strstr(start, "AM")) {
    hour = atoi(strtok(start,":"));
    if (hour != 12)
      days[locate].appts[days[locate].apptCount]->startTime.hour = hour;
    else
      days[locate].appts[days[locate].apptCount]->startTime.hour = 0;
  } // if AM
  else if (strstr(start, "PM")) {
    hour = atoi(strtok(start,":"));
    if (hour != 12)
      days[locate].appts[days[locate].apptCount]->startTime.hour = hour + 12;
    else
      days[locate].appts[days[locate].apptCount]->startTime.hour = 12;
  } // else if PM
  days[locate].appts[days[locate].apptCount]->startTime.minutes = atoi(strtok(NULL, ":"));
  if (strstr(end, "AM")){
    hour = atoi(strtok(end,":"));
    if (hour != 12)
      days[locate].appts[days[locate].apptCount]->endTime.hour = hour;
    else
      days[locate].appts[days[locate].apptCount]->endTime.hour = 0;
  } // if AM
  else if (strstr(end, "PM")){
    hour = atoi(strtok(end,":"));
    if (hour != 12)
      days[locate].appts[days[locate].apptCount]->endTime.hour = hour +12;
    else
      days[locate].appts[days[locate].apptCount]->endTime.hour = 12;
  } // else if
  days[locate].appts[days[locate].apptCount]->endTime.minutes = atoi(strtok(NULL, ":"));
  strcpy(days[locate].appts[days[locate].apptCount]->subject, subject);
  strcpy(days[locate].appts[days[locate].apptCount]->location, location);
}//strtoken_time()

void read_inputfile(char *inputfile, Day *days, int appt_days)
{
  FILE *fp = fopen(inputfile, "r");
  char line[1000], line_input[1000], *ptr;
  int input, i = 1;
  fgets(line, 1000, fp);
  while ( ( fgets(line, 1000, fp)) != NULL)
  {
    strcpy(line_input, line);
    input = atoi(strtok(line, ",\r\n"));
    ptr = strtok(NULL, ",\r\n" );
    printf("CSV Entry- %d)   %s\n", i, line_input);
    if ( input == 1 )
      search_date(ptr, days, appt_days);
    else if (input == 2)
      search_subject(ptr, days, appt_days);
    else
      printf("Invalid Choice\n");
    i++;
  }//while()
}//read_inputfile()

void search_date(char *string, Day *days, int appt_days)
{
  char string2[100];
  int i, j, month, day, found = 0;
  strcpy(string2, string);
  printf("Month and day (mm/dd) >> %s\r\n", string);
  if (!isalpha(string[0])){
    month = atoi(strtok(string2, "/\r\n"));
    day = atoi(strtok(NULL, "\r/\n"));
    if ( month >= 13 || month <= 0 || day <= 0 || day >= 32){
      found = 1;
      printf("%s is not a valid date.\n", string);
    }// if month isn't avalid date
  else if ( month > 0 && month < 13 && day > 0 && day < 32 )
    for (i = 0; i <= appt_days; i++)
    {
      if (days[i].month == month && days[i].day == day)
      {
        printf("Start End   Subject         Location\n");
        for (j = 0; j <= days[i].apptCount; j++){
          found = 1;
          printf("%02hd:%02hd %02hd:%02hd %-15s %-s\r\n",
          days[i].appts[j]->startTime.hour, days[i].appts[j]->startTime.minutes, 
          days[i].appts[j]->endTime.hour, days[i].appts[j]->endTime.minutes, 
          days[i].appts[j]->subject, days[i].appts[j]->location);
        }//for()
      }//if()
    }//for()
    if (found == 0) 
      printf("There are no appointments for that date.\n");
  }//if()
  else
    printf("%s is not a valid date.\n", string);
} // void search_date()

void search_subject(char *string, Day *days, int appt_days)
{
  int i, j, found = 0;
  char copy[100], *ptr;
  ptr = strtok(string, "\r\n^M");
  strcpy(copy, ptr);
  for (i = 0; i < appt_days; i++){
    for (j = 0; j <= days[i].apptCount ; j++)
      if (strcmp(string, days[i].appts[j]->subject)==0){ 
        if (found == 0)
          printf("Date  Start End   Subject         Location\n"); 
        printf("%2hd/%-2hd %02hd:%02hd %02hd:%02hd %-15s %-s\r\n",
        days[i].month, days[i].day, days[i].appts[j]->startTime.hour, days[i].appts[j]->startTime.minutes, 
        days[i].appts[j]->endTime.hour, days[i].appts[j]->endTime.minutes, days[i].appts[j]->subject, days[i].appts[j]->location );
        found++;
      }//if()
  }//for()
  if (found ==0)
    printf("%s was not found as a subject in the calendar.\n", copy);
}//search_subject()
