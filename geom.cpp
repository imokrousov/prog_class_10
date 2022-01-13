#include <iostream>
#include <cmath>
#include <set>

using namespace std;

struct Point2D{	double x,y;};
struct Line2D{	double A,B,C;};

Line2D makeLine (Point2D M, Point2D N);
double distance (Line2D l, Point2D M);
double distance (Point2D M, Point2D N);

int main()
{
	Point2D A,B;
	A.x = 0; A.y =0;
	B.x = 1; B.y = 2;
	Line2D l = makeLine(A,B);
	cout<<l.A<<' '<<l.B<<' '<<l.C<<endl;
	return 0;
}

double distance (Point2D M, Point2D N)
{
	return sqrt((M.x-N.x)*(M.x-N.x) + (M.y-N.y)*(M.y-N.y));
}


Line2D makeLine (Point2D M, Point2D N)
{
	Line2D ans;
	ans.A = N.y - M.y;
	ans.B = M.x - N.x;
	ans.C = M.y*(N.x-M.x) - M.x * (N.y - M.y);
	return ans;
}

double distance (Line2D l, Point2D M)
{
	return fabs(l.A*M.x + l.B*M.y +l.C)/sqrt(l.A*l.A + l.B*l.B);
}

double angle (Line2D l1, Line2D l2)
{
	return acos ((l1.A*l2.A + l1.B*l2.B)/ 
	(sqrt(l1.A*l1.A + l1.B*l1.B)*sqrt(l2.A*l2.A + l2.B*l2.B)) );
}













