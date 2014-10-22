// exampes of strcmp, strncpy, strtok for discussion3 of ECS 40a
#include <cstdio>
#include <cstdlib>
#include <cstring>

void compareString(const char *);
char* copyString(const char*);
void getDate(const char*, short &, short &);

// example for strcmp
void compareString(const char *pstr) {
  // string equals "AM"
  if (!strcmp(pstr, "AM")) {
    printf("%s matches AM\n", pstr);;
  }
  // string equals "PM"
  else if (!strcmp(pstr, "PM")) {
    printf("%s matches PM\n", pstr);;
  }
  else {
    printf("%s matches neither\n", pstr);;
  }
}

// example for strncpy
char* copyString(const char* p) {
  size_t n = strlen(p);
  char *q = (char*) malloc(n + 1);

  strncpy(q, p, n);
  q[n] = '\0';
  return q;
}

// example of strtok
void getDate(char* date, short &month, short &day) {
  char* pstr;
  /* month and day is separated by "/" */
  pstr = strtok(date, "/");
  if (pstr) {
    month = atoi(pstr);
    pstr = strtok(NULL, "");
    if (pstr) {
      day = atoi(pstr);
    }
  }
}

int main() {
  // strings is an array of four strings
  const char* strings[4] = {"HI", "AM", "HELLO", "PM"};  
  for (size_t i = 0; i != 4; ++i) {
    compareString(strings[i]);
  }

  // dynamically create a new string pstr2
  char *pstr2 = copyString(strings[0]);
  printf("\noriginal string: %s, copied string: %s\n", strings[0], pstr2);
  free(pstr2);

  // get month and day from a string date
  char date[] = "4/24";
  short month = 0, day = 0;
  getDate(date, month, day);
  printf("\nDate: %2hd/%-2hd\n", month, day);

  return 0;
}
