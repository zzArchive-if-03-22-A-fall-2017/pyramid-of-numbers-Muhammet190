#include <stdio.h>
#include <string.h>
#define MAX_DIGITS 80

struct BigInt {
int digits_count;
unsigned int the_int[MAX_DIGITS];
};


int strtobig_int(const char *str, int len, struct BigInt *big_int);
void print_big_int(const struct BigInt *big_int);
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result);
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result);
void copy_big_int(const struct BigInt *from, struct BigInt *to);


int main(int argc, char *argv[])
{
char input[MAX_DIGITS + 1];
printf("Geben sie eine nummer ein: ");
scanf("%s",input);
int len = strlen(input);
if (len > MAX_DIGITS) {
return 0;
}
for (int i = 0; i < len; i++) {
if (!(input[i] > 47 && input[i] < 58)) {
printf("Error code -1\n");
return 0;
}
}
struct BigInt big_int;
struct BigInt big_result;
big_int.digits_count = strtobig_int(input, len, &big_int);
big_result.digits_count =big_int.digits_count;

for (int i = 2; i <= 9; i++)
{
print_big_int(&big_int);
printf(" * %d = ", i);
multiply(&big_int, i, &big_result);
print_big_int(&big_result);
printf("\n");
copy_big_int(&big_result, &big_int);
}
copy_big_int(&big_result, &big_int);
for (int i = 2; i < 10; i++)
{
print_big_int(&big_int);
printf(" / %d = ", i);
divide(&big_int, i, &big_result);
print_big_int(&big_result);
printf("\n");
copy_big_int(&big_result, &big_int);
}
return 0;
}

void multiply( const struct BigInt * big_int, int factor, struct BigInt * big_result)
{
int result = 1;
int carry = 0;
for (int i = 0; i < big_int->digits_count; i++)
{
result = big_int->the_int[i] * factor + carry;
carry = result/10;
big_result->the_int[i] = result%10;
}
if (0 < carry)
{
int location = big_result->digits_count;
big_result->digits_count++;
big_result->the_int[location] = carry;
}
}

int strtobig_int(const char *str, int len, struct BigInt *big_int)
{
int digits_count = 0;
len--;
for (int i = 0;i < len+1; i++)
{
big_int->the_int[len-i] = str[i]-'0';
digits_count++;
}
return digits_count;
}

void print_big_int(const struct BigInt *big_int)
{
for (int i = big_int->digits_count-1; i >=0 ; i--)
{
printf("%d",big_int->the_int[i]);
}
}

void copy_big_int(const struct BigInt *from, struct BigInt *to)
{
for (int i = 0; i < from->digits_count; i++)
{
to->the_int[i] = from->the_int[i];
}
if (from->digits_count != to->digits_count)
{
to->digits_count = from->digits_count;
}
}
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result)
{

int quotient= 0;
int rest = 0;
int digits_sum= 0;
int count_zeros = 0;
for (int i = big_int->digits_count-1; i >=0; i--)
{
quotient=big_int->the_int[i] + (rest*10);
big_result->the_int[i] = quotient/divisor;
rest= quotient %divisor;
digits_sum+= big_result->the_int[i];
if ( big_result->the_int[i] == 0 && digits_sum == 0) {
count_zeros++;
}
}
big_result->digits_count -= count_zeros;


}
