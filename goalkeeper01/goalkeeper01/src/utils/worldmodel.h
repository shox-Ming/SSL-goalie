#ifndef WORLDMODEL_H
#define WORLDMODEL_H
#include <iostream>
#include "singleton.h"
#include "basevision.h"
#include "historylogger.h"
#include "robot.h"
#include "matchstate.h"
#include "ball.h"
#include "game_state.h"
class WorldModel
{
public:
	WorldModel();
	~WorldModel();
	const std::string& get_referee_msg() const;
	// 获取参议命令
	void set_referee_msg(const std::string& ref_msg);
	// 设置参议命令
	void set_cycle(int cycle){ current_cycle = cycle; }
	// 设置当前周期
	void setMatchState(FieldState state);
	// 设置比赛状态
	FieldState getMatchState();
	// 获取比赛状态
	void set_our_team(Vehicle* team){ our = team; }
	// 设置our team
	const Vehicle* get_our_team()const{ return our; }
	// 获取our team
	void set_opp_team(Vehicle* team){ opp = team; }
	// 设置opp team
	const Vehicle* get_opp_team()const{ return opp; }
	// 设置our team id
	void set_our_exist_id(bool * id){ our_robots_id = id; }
	// 设置our team id
	const bool* get_our_exist_id()const{ return our_robots_id; }
	// 设置opp team id
	void set_opp_exist_id(bool * id){ opp_robots_id = id; }
	// 设置opp team id
	const bool* get_opp_exist_id()const{ return opp_robots_id; }
	// 设置our team v
	void set_our_v(int id, point2f v);
	// 设置our team rot
	void set_our_rot(int id, float rot);
	// 设置our team cmd
	void set_our_cmd(int id, const point2f& v, const float& rot);
	// 获取our team cmd v
	const point2f& get_our_cmd_v(int id)const;
	// 获取our team cmd rot
	const float& get_our_cmd_rot(int id)const;
	// 获取我方玩家的旋转角度
	const PlayerVision& get_our_player(int id)const;
	// 获取我方玩家的位置
	const point2f& get_our_player_pos(int id)const;
	// 获取我方玩家的最后位置
	const point2f& get_opp_player_pos(int id)const;
	// 获取我方玩家的最后旋转角度
	float get_opp_player_dir(int id)const;
	// 获取我方玩家的最后位置
	const point2f& get_our_player_v(int id)const;
	// 获取我方玩家的最后速度
	const point2f& get_our_player_last_v(int id)const;
	// 获取我方玩家的最后旋转角度
	float get_our_player_dir(int id)const;
	// 获取我方玩家的最后旋转角度
	const float get_our_player_last_dir(int id)const;
	// 获取对方玩家的位置
	const PlayerVision& get_opp_player(int id)const;
	// 获取对手id的球员
	int get_our_goalie()const{ return our_goalie; }
	// 获取对手id的球员
	int get_opp_goalie()const{ return opp_goalie; }
	// 设置对手id的球员
	void set_our_goalie(int goalie_id){ our_goalie = goalie_id; }
	// 设置对手id的球员
	void set_opp_goalie(int goalie_id){ opp_goalie = goalie_id; }
	// 设置球员
	void set_ball(Ball* b){ match_ball = b; }
	// 获取球员的位置
	const BallVision& get_ball()const{ return match_ball->get_ball_vision(); }
	// 获取球员的位置
	const point2f& get_ball_pos(int c)const{ return match_ball->get_pos(c); }
	// 获取球员的位置
	const point2f& get_ball_pos()const{ return match_ball->get_pos(); }
	// 获取球员的速度
	const point2f& get_ball_vel()const{ return match_ball->get_vel(); }
	// 获取机器人的速度
	const int  robots_size()const { return max_robots; }
	// 设置是否踢球
	void set_kick(bool* kick_f) { kick = kick_f; }
	// 设置是否模拟踢球
	void set_sim_kick(bool* kick){ sim_kick = kick; }
	// 获取是否模拟踢球
	const bool* get_sim_kick()const{ return sim_kick; }
	// 判断机器人是否踢球
	bool is_kick(int id)const;
	// 判断机器人是否模拟踢球
	bool is_sim_kick(int id)const;
	// 设置游戏状态
	void set_game_state(GameState* state);
	// 获取游戏状态
	const GameState* game_states()const;
	// 设置是否模拟游戏
	void set_simulation(bool sim){ is_simulation = sim; }
	// 获取是否模拟游戏
	bool get_simulation()const{ return is_simulation; }
private:
	static const int max_robots = 12;
	// 定义我方机器人的指针
	Vehicle* our;
	// 定义对方机器人的指针
	Vehicle* opp;
	// 定义我方机器人是否踢球的布尔值
	bool* kick;
	// 定义我方机器人是否踢球的布尔值
	bool* sim_kick;
	// 定义我方机器人的球拍指针
	Ball* match_ball;
	// 定义我方机器人的球拍是否踢球的布尔值
	bool* our_robots_id;
	// 定义对方机器人的球拍是否踢球的布尔值
	bool* opp_robots_id;
	// 定义我方机器人的踢球的次数
	int our_goalie;
	// 定义对方机器人的踢球的次数
	int opp_goalie;
	// 定义当前的周期
	int current_cycle;
	// 定义参考消息
	std::string referee_msg;
	// 定义我方机器人的比赛状态
	FieldState match_state;
	// 定义我方机器人的比赛状态
	GameState* game_state;
	// 定义是否为模拟模式
	bool is_simulation;
};
#endif