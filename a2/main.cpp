#include <cstring>
#include <iostream>

void t1();
void t2();
void t3();
void t4();
void t5();
void t6();

int main() {
  t1();
  t2();
  t3();
  t4();
  t5();
  t6();
  return 0;
}

void t1() {
  std::cout << "task 1" << '\n';

  int i = 3;
  int j = 5;
  int *p = &i;
  int *q = &j;

  std::cout << "i: " << i << '\n';
  std::cout << "j: " << j << '\n';
  std::cout << "p: 0x" << p << '\n';
  std::cout << "q: 0x" << q << '\n';

  *p = 7;
  *q += 4;
  *q = *p + 1;
  p = q;
  std::cout << *p << ", " << *q << '\n';
  // får ut 8 8, stemmer overens.
}

void t2() {
  char *line = nullptr;
  strcpy(line, "weed");

  // strcpy prøver å skrive til nullptr, som ikke er lov
}

void t3() {
  char text[5];
  char *pointer = text;
  char search_for = 'e';
  std::cin >> text;
  while (*pointer != search_for) {
    *pointer = search_for;
    pointer++;
  }

  // input kan ha mer enn 5 tegn, som vil crashe programmet

  // dersom input ikke har `search_for`, vil loopen prøve å gå utenfor
  // minneområdet, og så crashe
}

void t4() {
  int a = 5;
  int b; // & brukes for å hente en addresse og brukes ikke for initialisering
         // av variabler.
  int *c;
  c = &b;
  a = b + *c; // vi trenger ikke å dereferere a eller b.
  b = 2; // vi kan ikke endre addressen på den måten, men vi kan endre verdien.
}

void t5() {
  double number = 0;
  double *ptr = &number;
  double &numRef = number;

  // assignment
  number += 5;
  std::cout << number << '\n';
  *ptr += 5;
  std::cout << number << '\n';
  numRef += 5;
  std::cout << number << '\n';
}

int find_sum(const int *table, int length);

void t6() {
  int nums[20];
  for (int i = 0; i < 20; i++)
    nums[i] = i + 1;

  std::cout << find_sum(nums, 10) << '\n';
  std::cout << find_sum(nums + 10, 5) << '\n';
  std::cout << find_sum(nums + 15, 5) << '\n';
}

int find_sum(const int *table, int length) {
  int sum = 0;
  for (int i = 0; i < length; i++)
    sum += table[i];
  return sum;
}