#include"src\utils\worldmodel.h"
#include "src\utils\PlayerTask.h"
#include "src\utils\maths.h"
#include "src\utils\constants.h"
extern "C"_declspec(dllexport) PlayerTask player_plan(const WorldModel* model, int robot_id);

PlayerTask player_plan(const WorldModel* model, int robot_id){
	PlayerTask task;

	int opp1_id = -7; // 初始化对手ID为-7
	for (int i = 0; i < 6; i++)
	{
		// 如果当前ID是robot_id或者是对方守门员，跳过本次循环
		if (i == robot_id || i == model->get_opp_goalie())
			continue;

		// 检查当前ID的对手是否存在
		if (model->get_opp_exist_id()[i])
		{
			opp1_id = i; // 将对手ID赋值给opp1_id
			break;       // 找到后提前退出循环
		}
	}

	int opp2_id = -7; // 初始化对手ID为-7
	for (int j = 0; j < 6; j++)
	{
		// 如果当前ID是robot_id、对方守门员或第一个找到的对手ID，跳过本次循环
		if (j == robot_id || j == model->get_opp_goalie() || j == opp1_id)
			continue;

		// 检查当前ID的对手是否存在
		if (model->get_opp_exist_id()[j])
		{
			opp2_id = j; // 将对手ID赋值给opp2_id
			break;       // 找到后提前退出循环
		}
	}

	point2f pos(170, 0);
	float R = 20;
	const float& add = 5;
	const point2f& ball_pos = model->get_ball_pos();
	const point2f& kicker_pos = model->get_our_player_pos(robot_id);
	const float&   kicker_dir = model->get_our_player_dir(robot_id);
	const point2f& receiver_pos = model->get_our_player_pos(opp1_id);
	float excute_dir = (receiver_pos - ball_pos).angle();
	float ball_kickerdir = (kicker_pos - ball_pos).angle();
	float kicker_balldir = (ball_pos - kicker_pos).angle();
	float kicker_receiverdir = (receiver_pos - kicker_pos).angle();
	float L = (kicker_pos - ball_pos).length();
	float D = (receiver_pos - ball_pos).length();