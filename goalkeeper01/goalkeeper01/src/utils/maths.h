#ifndef MATHSS_H
#define MATHSS_H
#include <math.h>
#include "constants.h"
#include "vector.h"
#include <vector>
enum RoleStyle{
	KickerS,
	ReceiveS,
	MiddleS,
	TierS,
	AssisterS,
	GoalieS,
	Nothing
};
namespace FieldPoint{
	extern	point2f Goal_Center_Point;
	extern	point2f Penalty_Kick_Point;
	extern	point2f Goal_Left_Point;
	extern  point2f Goal_Right_Point;
	extern  point2f Goal_Center_Left_One_Point;
	extern  point2f Goal_Center_Left_Two_Point;
	extern  point2f Goal_Center_Right_One_Point;
	extern  point2f Goal_Center_Right_Two_Point;
	extern  point2f Goal_Penalty_Area_L_Right;
	extern  point2f Goal_Penalty_Area_L_Left;
	extern  point2f Penalty_Area_L_A;
	extern  point2f Penalty_Area_L_B;
	extern  point2f Penalty_Arc_Center_Right;
	extern  point2f Penalty_Arc_Center_Left;
	extern  point2f Penalty_Rectangle_Left;
	extern  point2f Penalty_Rectangle_Right;
}

namespace Maths{
#define SMALL_NUM   0.00000001 // 避免除法溢出

#define EPSINON    0.00001

#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y)

#define perp(u,v)  ((u).x * (v).y - (u).y * (v).x)  

#ifndef PI
#define PI						3.1415926535898
#endif

#ifndef RAD2DEG					
#define RAD2DEG					57.295779513082
#endif

#ifndef DEG2RAD					
#define DEG2RAD					0.017453292519943
#endif
	
	
	template<class T>
	T clip(T val, T min_val, T max_val){
		if (max_val < min_val) return val;
		if (val > max_val) val = max_val;
		if (val < min_val) val = min_val;
		return val;
	}

	float normalize(float theta);

    //计算点p到线段的距离
    point2f vector2polar(float length, float dir);
	//计算圆段的交点
	point2f circle_segment_intersection(const point2f& start_point, const double circle_r, const  point2f& end_point);

	//计算圆极型曲线的交点
	point2f archimedes_spiral(const point2f& spiral_center, float spiral_center_size, const point2f& pos, float spiral_buff);
	
	//计算线段和线段之间的交点
	int sign(float d);

	//计算向量a和b的夹角
	float vector_angle(const point2f& a,const point2f& b,const point2f& c);

	//C++函数，用于计算直线的最小二乘法拟合。它接受一个点集（一组点，每个点包含两个浮点数x和y），并返回一个表示直线的类型
	float least_squares(const std::vector<point2f>& point);
	//最小二乘法（Least Squares Fit）是一种用于计算直线平滑曲线的算法。
	//它通过找到满足给定条件的最佳线性方程来最小化拟合误差。
	//在这个例子中，我们试图找到一条直线，使得所有点与直线的距离之和最小。
	//最后，least_squares()函数返回一个std::vector<point2f>，表示拟合直线的所有点。


	//计算线段a和线段b之间的交点
	point2f line_perp_across(const point2f& p1, float slope, const point2f& p2);//slope斜率

	//判断点p是否在范围内
	bool  in_range(const point2f& p1, const point2f& left_down, const point2f& right_up);

	//计算点p的极型曲线的交点
	point2f across_point(const point2f& p1, const point2f& p2, const point2f& q1, const point2f& q2);

	//判断点p是否在圆内
	bool is_inside_penatly(const point2f& p);
	
}
#endif