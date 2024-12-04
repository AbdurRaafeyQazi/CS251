#include <stdio.h>

/*
factorial

2. if statement -> base case

1. else statement -> recursive procedure

--------------------------
How to do ?

divide problem into smaller problems -> fact4 

This is called dividing problem in smaller pieces

fact(1) = 1
fact(2) = 2 * 1 = 2 * fact(1)
fact(3) = 3 * 2 * 1 = 3 * fact(2)
fact(4) = 4 * 3 * 2 * 1 = 4 * fact(3)

fact(n) = n * fact(n - 1)

// What to choose base case as ? When you call the recursive function, it should be at a value where the function wont call itself


*/

// int fact(int n)
// {
// 	if(n == 1)
// 	{
// 		return 1;
// 	}else{
// 		return n * fact(n - 1);
// 	}
// }

// int main()
// {
// 	int n;
// 	printf("Enter a number: ");
// 	scanf("%d", &n);
// 	printf("Factorial of %d is %d\n", n , fact(n));
// }


// TYPES OF RECURSION -> DIRECT, INDIRECT, TAIL, NON-TAIL
// FIRST 2


// Direct recursion means that the function calls the same function
// In-direct recursion, fun calls fun2 and fun2 calls fun // Makes a U-Turn.

// PROGRAM 1 
/*
Print numbers from 1 to 10 in such a way that when number is odd,
add 1 when numer is 

*/

void odd();
void even();
int n = 1;

void even()
{
	if(n <= 10)
	{
		printf("%d ", n - 1);
		n++;
		odd();
	}
}

void odd()
{
	if(n <= 10)
	{
		printf("%d ", n + 1);
		n++;
		even();
	}
	return;
}

int main()
{
odd();
}


