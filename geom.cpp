#include <iostream>
#include <cmath>
#include <set>

using namespace std;

struct Point2D{	double x,y;};
struct Line2D{	double A,B,C;};
//-----------------------------------
struct Vec2D { double x,y;};
struct Vec3D { double x,y,z;};
struct Polygon {int point_count; Point2D * points;};

Line2D makeLine (Point2D M, Point2D N);
double distance (Line2D l, Point2D M);
double distance (Point2D M, Point2D N);
bool onOneSide (Line2D l, Point2D M, Point2D N);
Line2D makeOrtoLine (Line2D l, Point2D M);
bool isParalel (Line2D l1, Line2D l2);
Point2D intersection (Line2D l1, Line2D l2);
//------------------------------------------------------
long double length (Vec2D a);
long double length (Vec3D a);
Vec2D makeVec2D (Point2D A, Point2D B);
Vec2D sum (Vec2D, Vec2D);
Vec3D sum (Vec3D, Vec3D);
Vec2D product (Vec2D, long double);
Vec3D product (Vec3D, long double);
Vec3D makeVec3D (Vec2D);
long double scal_product(Vec3D a, Vec3D b);
long double scal_product(Vec2D a, Vec2D b);
Vec3D vec_product(Vec3D a, Vec3D b);
// --------------------------------------------------------
long double trian_square (Point2D A, Point2D B, Point2D C );
int rotation (Vec2D a, Vec2D b); // 1 влево, -1 вправо, 0 прямо
long double polygon_square ( Polygon P);
int * ConvexHull (Point2D * mas, int n);
long double cos_vec (Vec2D a, Vec2D b);

int main()
{
	const int n = 6;
	Point2D mas[n];
	
	mas[0].x = 0;
	mas[0].y = 0;
	mas[1].x = 0;
	mas[1].y = 2;
	mas[2].x = 2;
	mas[2].y = 6;
	mas[3].x = 2;
	mas[3].y = 0;
	mas[4].x = 1;
	mas[4].y = 1;
	mas[5].x = 100;
	mas[5].y = -5;
	int * ans = ConvexHull (mas, n);
	for (int i =0; i < n; i ++ ) cout<<ans[i];
	return 0;
}

int * ConvexHull (Point2D * mas, int n)
{
	int * ans = new int[n];
	for (int i =0; i <n; i++) ans[i]=0;
	int xmin = mas[0].x;
	int ymin = mas[0].y;
	int ind = 0;
	for (int i = 1; i < n; i++)
	{
		if (mas[i].y < ymin || ((mas[i].y == ymin ) && ( mas[i].x< xmin)  ))
		{
			xmin = mas[i].x;
			ymin = mas[i].y;
			ind = i;
		}
	}
	Point2D cur = mas[ind];
	Point2D prev = cur; prev.x+=1;
	int cur_ind = ind;
	int prev_ind = -1;
	while (true)
	{
		ans[cur_ind] = 1;
		Vec2D stable = makeVec2D(cur,prev);
		double min_cos = 2;
		int ind_min_cos = -1;
		for (int i =0; i < n; i++)
		{
			if (i == cur_ind) continue;
			Vec2D dynamic = makeVec2D(cur, mas[i] );
			if (cos_vec (stable,dynamic) < min_cos)
			{
				min_cos = cos_vec (stable,dynamic);
				ind_min_cos = i;
			}
		}
		if (ans[ind_min_cos] == 1) break;
		prev = cur;
		prev_ind = cur_ind;
		cur = mas[ind_min_cos];
		cur_ind = ind_min_cos;
	}
	return ans;
}

long double cos_vec (Vec2D a, Vec2D b){return scal_product(a,b)/ (length(a)*length(b));}

long double trian_square (Point2D A, Point2D B, Point2D C )
{
	Vec3D a = makeVec3D ( makeVec2D (A,B));
	Vec3D b = makeVec3D ( makeVec2D (A,C));
	return 0.5* length(vec_product(a,b)); // 0.5*vec_product(a,b).z;
}

int rotation (Vec2D a, Vec2D b)
{
	Vec3D aa = makeVec3D(a);
	Vec3D bb = makeVec3D(b);
	if (vec_product(aa,bb).z >0) return 1;
	if (vec_product(aa,bb).z <0) return -1;
	return 0;
}

long double polygon_square ( Polygon P)
{
	long double ans = 0;
	for (int i = 0 ; i < P.point_count-1; i++ )
	{
		Point2D A = P.points[i];
		Point2D B = P.points[i+1];
		ans += A.x*B.y - B.x*A.y;
	}
	Point2D A = P.points[P.point_count-1];
	Point2D B = P.points[0];
	ans += A.x*B.y - B.x*A.y;
	return fabs(ans)*0.5;
}




long double length (Vec2D a) {return sqrt(a.x*a.x + a.y*a.y);}
long double length (Vec3D a) {return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);}
Vec2D makeVec2D (Point2D A, Point2D B)
{
	Vec2D ans;
	ans.x = B.x-A.x;
	ans.y = B.y-A.y;
	return ans;
}
Vec2D sum (Vec2D a , Vec2D b)
{
	Vec2D ans;
	ans.x = a.x + b.x;
	ans.y = a.y + b.y;
	return ans;
}
Vec3D sum (Vec3D a , Vec3D b)
{
	Vec3D ans;
	ans.x = a.x + b.x;
	ans.y = a.y + b.y;
	ans.z = a.z + b.z;
	return ans;
}
Vec2D product (Vec2D a, long double coef)
{
	Vec2D ans;
	ans.x = a.x * coef;
	ans.y = a.y * coef;
	return ans;
}
Vec3D product (Vec3D a, long double coef)
{
	Vec3D ans;
	ans.x = a.x * coef;
	ans.y = a.y * coef;
	ans.z = a.z * coef;
	return ans;
}
Vec3D makeVec3D (Vec2D a)
{
	Vec3D ans;
	ans.x = a.x;
	ans.y = a.y;
	ans.z = 0;
	return ans;
}

long double scal_product(Vec3D a, Vec3D b){	return a.x*b.x + a.y*b.y + a.z*b.z;}
long double scal_product(Vec2D a, Vec2D b){	return a.x*b.x + a.y*b.y ;}
Vec3D vec_product(Vec3D a, Vec3D b)
{
	Vec3D ans;
	ans.x = a.y*b.z - a.z*b.y;
	ans.y = a.z*b.x - a.x*b.z;
	ans.z = a.x*b.y - a.y*b.x;
	return ans;
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
