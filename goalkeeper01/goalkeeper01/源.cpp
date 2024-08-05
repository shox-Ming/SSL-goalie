#include"src\utils\worldmodel.h"
#include "src\utils\PlayerTask.h"
#include "src\utils\maths.h"
#include "src\utils\constants.h"
#include <vector>
#include <algorithm>//用于数组比较，暂时没用
using namespace std;

extern "C"_declspec(dllexport) PlayerTask player_plan(const WorldModel* model, int robot_id);

enum class GoalkeeperState {
	IDLE,
	DEFEND,
	SAVE
};

class Goalkeeper {
public:
	Goalkeeper() : state(GoalkeeperState::IDLE) {}

	void update(bool ballIsApproaching, bool ballIsInDangerZone) {
		switch (state) {
		case GoalkeeperState::IDLE:
			if (ballIsApproaching) {
				state = GoalkeeperState::DEFEND;
			}
			break;
		case GoalkeeperState::DEFEND: //1,?
			if (ballIsInDangerZone) {
				state = GoalkeeperState::SAVE;
			}
			else if (!ballIsApproaching) {
				state = GoalkeeperState::IDLE;
			}
			break;
		case GoalkeeperState::SAVE: //1,1
			if (!ballIsApproaching) {
				state = GoalkeeperState::IDLE; // 回到初始状态
			}
			break;
		}
	}

	GoalkeeperState getState() const {
		return state;
	}

private:
	GoalkeeperState state;
};


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

	point2f pos_left(-FIELD_WIDTH_H + 12.5, (GOAL_WIDTH / 2));
	point2f pos_right(-FIELD_WIDTH_H + 12.5, -(GOAL_WIDTH / 2));
	point2f doormid(-FIELD_WIDTH_H, 0);
	point2f doorleft(-FIELD_WIDTH_H, GOAL_WIDTH / 2);
	point2f doorright(-FIELD_WIDTH_H, -(GOAL_WIDTH / 2));
	point2f pos(170, 0);
	const point2f& vel = model->get_ball_vel();


	float R = 20;
	const float& add = 5;

	const point2f& ball_pos = model->get_ball_pos();
	const point2f& kicker_pos = model->get_opp_player_pos(opp1_id);
	const float&   kicker_dir = model->get_opp_player_dir(opp1_id);
	const point2f& receiver_pos = model->get_opp_player_pos(opp2_id);
	const float&   receiver_dir = model->get_opp_player_dir(opp2_id);
	const point2f& goalie_pos = model->get_our_player_pos(robot_id);
	point2f task_point = Maths::line_perp_across(ball_pos, vel.angle(), goalie_pos);

	float reciever_balldir = (ball_pos - receiver_pos).angle();
	float excute_dir = (receiver_pos - ball_pos).angle();
	float ball_kickerdir = (kicker_pos - ball_pos).angle();
	float kicker_balldir = (ball_pos - kicker_pos).angle();
	float kicker_receiverdir = (receiver_pos - kicker_pos).angle();

	float L = (kicker_pos - ball_pos).length();
	float D = (receiver_pos - ball_pos).length();
	float b2g = (ball_pos - goalie_pos).length();


	float kicker2doorleft = (doorleft - kicker_pos).angle();
	float kicker2doorright = (doorright - kicker_pos).angle();
	float receiver2doorleft = (doorleft - receiver_pos).angle();
	float receiver2doorright = (doorright - receiver_pos).angle();
	float ball2door = (doormid - ball_pos).length();


	//重新传参，确定持球球员
	bool kcloseb = L < D;
	point2f get_ball_player_pos;
	float get_ball_player_dir;
	float get_player_dir;
	float get_player2ball_dir;
	float get_player2door_dirleft;
	float get_player2door_dirright;
	point2f POS;

	const float LINE_X = -290;
	const float MIN_Y = -35;
	const float MAX_Y = 35;
	 
	auto calculate_pos_on_line = [&](const point2f& opp_pos, float opp_dir, const point2f& goalie_pos, float radius) -> point2f{
		point2f direction = Maths::vector2polar(radius, opp_dir);
		float t = (direction.x * (goalie_pos.x - opp_pos.x) + direction.y * (goalie_pos.y - opp_pos.y)) / ((direction.x * direction.x) + (direction.y * direction.y));
		float y = opp_pos.y + t * direction.y;

		// Clamp y to be within the line segment [a, b]

		return point2f(LINE_X, y);
	};


	if (kcloseb){
		get_ball_player_pos = kicker_pos;
		get_player_dir = kicker_dir;
		get_ball_player_dir = ball_kickerdir;
		get_player2ball_dir = kicker_balldir;
		get_player2door_dirleft = kicker2doorleft;
		get_player2door_dirright = kicker2doorright;
		POS = calculate_pos_on_line(kicker_pos, kicker_dir, goalie_pos, R);
	}
	else{
		get_ball_player_pos = receiver_pos;
		get_player_dir = receiver_dir;
		get_ball_player_dir = excute_dir;
		get_player2ball_dir = reciever_balldir;
		get_player2door_dirleft = receiver2doorleft;
		get_player2door_dirright = receiver2doorright;
		POS = calculate_pos_on_line(receiver_pos, receiver_dir, goalie_pos, R);
	}

	float get_player_len = (get_ball_player_pos - ball_pos).length();
	if (get_player_len < 12){
		get_ball_player_dir = get_player_dir;
	}
	//float realk2b = (ball_pos - kicker_pos).angle();

	/*
	int BallIsClosed = (ball2door < 200) ? 1 : 0;
	int RobotDirIn = ((kicker2doorleft <= kicker_dir) && (kicker_dir <= kicker2doorright)) ? 1 : 0;//是否处于射门范围
	vector<int> vec1 = { BallIsClosed, RobotDirIn };
	vector<int> vec2 = { 0, 0 };
	bool areEqual1 = (vec1 == vec2);
	*/

	bool ballIsApproaching = ball2door < 350;
	bool ballIsInDangerZone = (get_player2door_dirleft <= get_player2ball_dir) && (get_player2ball_dir <= get_player2door_dirright);


	Goalkeeper goalie;
	//test
	//bool ballIsApproaching = true;
	//bool ballIsInDangerZone = true;
	goalie.update(ballIsApproaching, ballIsInDangerZone);

	GoalkeeperState state = goalie.getState();
	switch (state) {
	case GoalkeeperState::IDLE:
		//		std::cout << "Idle" << std::endl;
		task.needCb = 0;
		task.isChipKick = 0;
		task.orientate = get_ball_player_dir;
		task.target_pos = POS;
		break;
	case GoalkeeperState::DEFEND:
		//		std::cout << "DEFEND" << std::endl;
		task.needCb = 1;
		task.orientate = get_ball_player_dir;
		task.target_pos = POS;
		break;
	case GoalkeeperState::SAVE:
		//		std::cout << "SAVE" << std::endl;
		task.needCb = 1;
		task.orientate = get_ball_player_dir;
//		task.target_pos = task_point;
		task.target_pos = POS;
		if (b2g < 9.5){
			task.kickPower = 127;
		}
		break;
	}
	/*
	Goalkeeper goalie;
	if (goalie.update(true, false))
	GoalkeeperState state = GoalkeeperState::IDLE;
	else if (ball.y < arc_center_left.y)
	area = LeftArc;
	else

	*/
	return task;
}
