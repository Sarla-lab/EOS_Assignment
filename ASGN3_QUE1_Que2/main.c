#include <stdio.h>
#include "circle.h"
#include "square.h"
#include "rectangle.h"

int main()
{
    float r, s, l, w;

    printf("Enter radius of circle: ");
    scanf("%f", &r);
    printf("Circle area = %.2f\n", circle_area(r));
    printf("Circle circumference = %.2f\n\n", circle_circum(r));

    printf("Enter side of square: ");
    scanf("%f", &s);
    printf("Square area = %.2f\n", square_area(s));
    printf("Square perimeter = %.2f\n\n", square_perimeter(s));

    printf("Enter length and width of rectangle: ");
    scanf("%f %f", &l, &w);
    printf("Rectangle area = %.2f\n", rectangle_area(l, w));
    printf("Rectangle perimeter = %.2f\n", rectangle_perimeter(l, w));

    return 0;
}


