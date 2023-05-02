// End Point Code

#include <stdio.h>

#define Xmin -100
#define Xmax 100
#define Ymin -100
#define Ymax 100

int endCode(int, int);
void decToBinary(int);

int xmin = -100, xmax = 100, ymin = -100, ymax = 100;

int main() {
	int xd, yd, code;

	printf("Window(%d, %d, %d, %d)\n", Xmin, Xmax, Ymin, Ymax);
    printf("\nEnter coordinates of the point :\n");
    scanf("%d %d", &xd, &yd);

    code = endCode(xd, yd);
    printf("\nEnd point code for (%d, %d) = ", xd, yd);
    decToBinary(code);
    printf("\n");
	return 0;
}

int endCode(int x, int y) {
	int c = 0;
	if(x < Xmin)
		c |= 1;
	if(x > Xmax)
		c |= 2;
	if(y < Ymin)
		c |= 4;
	if(y > Ymax)
		c |= 8;
	return c;
}

void decToBinary(int n) {
    int num[] = {0,0,0,0};
    int i = 0;
    while (n > 0) {
        num[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (i=3; i>=0; i--)
        printf("%d", num[i]);
}