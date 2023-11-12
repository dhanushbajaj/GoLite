/* ANSI C enumerated data type
 * Author: Svillen Ranev
*/
#include <stdio.h>

enum Days {Sun, Mon, Tue, Wed, Thu, Fri, Sat};
typedef enum Coins {Penny =1, Tupence, Nickel = Penny +4,
                   Dime = 10, Quarter = Nickel * Nickel} Coins;
enum esc_char { backspace = '\b',bell = '\a', newline  = '\n',
                Return = '\r', tab = '\t'} Esc;
// Variable names must be different from enumerators names
// Syntax: multiple declarations

// The list of enumerator can not be empty.
// Syntax: enum Empty {};

// Sun, Mon .. can be used in only one enum
// Syntax: multiple declarations
// enum  {Sun, Mon, Tue, Wed, Thu, Fri, Sat} someday;

int main_Enumerations(void){

    enum Days anyday;
    // legal here - overrides the global one
    int Tue;
    int i = Penny;
    Coins small_change, * ptr_coins;
    small_change = Penny;
    ptr_coins = &small_change;
    printf("*ptr_coins: %d\n",*ptr_coins);
    *ptr_coins = small_change;
    printf("*ptr_coins: %d\n",*ptr_coins);
    *ptr_coins = Dime;
    printf("*ptr_coins: %d\n", *ptr_coins);
    anyday = Mon;
    printf("anyday: %d\n", anyday);
    anyday = 4;
    anyday = 15;
    printf("anyday: %d\n", anyday);
    Tue = 5 + small_change;
    printf("Tue: %d\n", Tue);
    return 0;
}
