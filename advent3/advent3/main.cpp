#include <iostream>

using namespace std;

bool isValid(int a, int b, int c)
{
    return (a + b > c &&
            b + c > a &&
            c + a > b);
}
int main()
{
    int validTriangles = 0;
    int a = 0;
    int b = 0; 
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    int g = 0;
    int h = 0;
    int i = 0;
    while (cin >> a)
    {
        cin >> b;
        cin >> c;

        cin >> d;
        cin >> e;
        cin >> f;

        cin >> g;
        cin >> h;
        cin >> i;

        if (isValid(a, d, g))
        {
            validTriangles++;
        }


        if (isValid(b, e, h))
        {
            validTriangles++;
        }


        if (isValid(c, f, i))
        {
            validTriangles++;
        }
    }

    cout << "triangles: " << validTriangles << endl;
    return 0;
}