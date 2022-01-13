#include <iostream>
#include <cmath>
#include <set>

using namespace std;

struct Point2D{	double x,y;};
struct Line2D{	double A,B,C;};

Line2D makeLine (Point2D M, Point2D N);
double distance (Line2D l, Point2D M);
double distance (Point2D M, Point2D N);
bool onOneSide (Line2D l, Point2D M, Point2D N);
Line2D makeOrtoLine (Line2D l, Point2D M);
bool isParalel (Line2D l1, Line2D l2);
Point2D intersection (Line2D l1, Line2D l2);

int main()
{
	Point2D A,B;
	A.x = 0; A.y =0;
	B.x = 1; B.y = 2;
	Line2D l = makeLine(A,B);
	cout<<l.A<<' '<<l.B<<' '<<l.C<<endl;
	return 0;
}
bool isParalel (Line2D l1, Line2D l2)
{
	return l1.A*l2.B == l1.B*l2.A;
}

Point2D intersection (Line2D l1, Line2D l2)
{
	Point2D ans;
	double znam = l1.A*l2.B - l2.A*l1.B;
	ans.x = (l1.B*l2.C - l2.B*l1.C)/ znam;
	ans.y = (l2.A*l1.C - l1.A*l2.C)/ znam;
	return ans;
}



Line2D makeOrtoLine (Line2D l, Point2D M)
{
	Line2D ans;
	ans.A = l.B;
	ans.B = -l.A;
	ans.C = l.A*M.y - l.B*M.x;
	return ans;
}

bool onOneSide (Line2D l, Point2D M, Point2D N)
{
	return (l.A*M.x+l.B*M.y+l.C)*(l.A*N.x+l.B*N.y+l.C) > 0;
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

