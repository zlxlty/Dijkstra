/*
 * @Author: Tianyi Lu
 * @Description: 
 * @Date: 2021-10-09 22:59:58
 * @LastEditors: Tianyi Lu
 * @LastEditTime: 2021-10-09 22:59:59
 */
/*
 * @Author: Tianyi Lu
 * @Description: 
 * @Date: 2021-10-04 23:10:24
 * @LastEditors: Tianyi Lu
 * @LastEditTime: 2021-10-05 10:44:30
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _point {
    int x;
    int y;
} Point;

int main(int argc, char const *argv[])
{
    int size = 20;
    Point **points;
    points = (Point**)malloc(sizeof(Point*)*size);
    Point* point1 = (Point*)malloc(sizeof(Point));
    point1->x = 2;
    point1->y = 4;
    points[1] = point1;
    printf("%d\n", points[1]->x);

    int x = 3/2;

    printf("%d\n", x);

    for (int i=0; i<size; i++) {
        free(points[i]);
    }

    free(points);
    return 0;
}

