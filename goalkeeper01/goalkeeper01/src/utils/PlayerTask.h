#ifndef BASETASK_H
#define BASETASK_H
#include "vector.h"
#include "singleton.h"
#include <string>
#define error_robot_id 9999
#define get_ball_threshold 16
enum RobotRole
{
	NoRole,
	Kicker,
	LeftMiddle,
	RightMiddle,
	LeftBack,
	RightBack,
	GoalieRole
};
class PlayerRole
{
public:
	PlayerRole(){ role = NoRole; num_id = error_robot_id; };
	~PlayerRole(){};
	RobotRole role;
	int num_id;
};


//抽象基本任务；依据skill需要可以设置不同的任务；skill执行的任务继承PlayeTask；
class PlayerTask
{
public:
	PlayerTask(){ memset(this,0,sizeof(PlayerTask)); };
	PlayerTask(const PlayerTask& task){
		memcpy(this,&task,sizeof(PlayerTask));
	}
	~PlayerTask(){};
	int flag;
	RobotRole role;                                             //球员角色
	point2f target_pos;											// 全局目标点
	double orientate;												// 全局目标到点朝向
	point2f global_vel;											// 全局目标到点平动速度	
	double rot_vel;													// 全局目标到点转动速度
	int rot_dir;														// 旋转的方向
	/// 运动参数 ： 用于底层运动控制 ，指定标签辅助
	double maxAcceleration;										// 最大加速度
	double maxDeceleration;										// 最大减速度

	/// 踢球参数 ： 用于平射挑射控制 ，默认使用
	bool needKick;													// 踢球动作执行开关
	bool isPass;													// 是否进行传球
	bool needCb;													// 是否需要吸球
	bool isChipKick;												// 挑球还是平射
	double kickPrecision;											// 踢球朝向精度
	double kickPower;												// 踢球力度
	double chipKickPower;											// 挑球力度	
};

class CTaskMeditator
{
public:
	CTaskMeditator(){ 
		// 初始化task_list数组
		task_list = new PlayerTask[MaxRobotsTask]();
		// 初始化is_at_point数组
		is_at_point = new bool[MaxRobotsTask]();
	}
	~CTaskMeditator(){
		// 释放task_list数组
		if (task_list) {
			delete task_list;
			task_list = NULL;
		}
		// 释放is_at_point数组
		if (is_at_point){
			delete is_at_point;
			is_at_point = NULL;
		}
	};
	// 设置任务
	void set_task(int id,const PlayerTask& task){
		// 如果id超出范围，则返回
		if (id < 0 || id>11) return;
		// 将任务放入task_list数组中
		task_list[id] = task;
	}

	// 获取任务
	const PlayerTask& get_task(int id){
		// 如果id超出范围，则返回task_list数组中的第一个任务
		if (id < 0 || id>11) return task_list[0];
		// 返回task_list数组中id对应的任务
		return task_list[id];
	}
	// 获取当前位置是否到达目标点
	const bool arrive_point(int id, const point2f& current_pos, const float& dir){
		// 如果id超出范围，则返回false
		if (id < 0 || id>11) return false;
		// 如果当前位置到达目标点距离小于arrive_point_range，且方向与任务相同，则is_at_point数组中id对应的值为true，否则为false
		if ((current_pos - task_list[id].target_pos).length() < arrive_point_range/*&&(fabs(anglemod(dir - task_list[id].orientate)))<5*PI/180*/)
			is_at_point[id] = true;
		else
			is_at_point[id] = false;
		// 返回is_at_point数组中id对应的值
		return is_at_point[id];
	}
private:
	// 最大任务数量
	static const int MaxRobotsTask = 6;
	// 定义任务类型
	static const int arrive_point_range = 10;
	// 定义任务类型数组
	PlayerTask *task_list;
	// 定义is_at_point数组
	bool* is_at_point;
};
typedef Singleton<CTaskMeditator> TaskMeditator;
#endif