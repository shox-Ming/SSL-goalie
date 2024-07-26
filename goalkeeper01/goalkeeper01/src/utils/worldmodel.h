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
	// ��ȡ��������
	void set_referee_msg(const std::string& ref_msg);
	// ���ò�������
	void set_cycle(int cycle){ current_cycle = cycle; }
	// ���õ�ǰ����
	void setMatchState(FieldState state);
	// ���ñ���״̬
	FieldState getMatchState();
	// ��ȡ����״̬
	void set_our_team(Vehicle* team){ our = team; }
	// ����our team
	const Vehicle* get_our_team()const{ return our; }
	// ��ȡour team
	void set_opp_team(Vehicle* team){ opp = team; }
	// ����opp team
	const Vehicle* get_opp_team()const{ return opp; }
	// ����our team id
	void set_our_exist_id(bool * id){ our_robots_id = id; }
	// ����our team id
	const bool* get_our_exist_id()const{ return our_robots_id; }
	// ����opp team id
	void set_opp_exist_id(bool * id){ opp_robots_id = id; }
	// ����opp team id
	const bool* get_opp_exist_id()const{ return opp_robots_id; }
	// ����our team v
	void set_our_v(int id, point2f v);
	// ����our team rot
	void set_our_rot(int id, float rot);
	// ����our team cmd
	void set_our_cmd(int id, const point2f& v, const float& rot);
	// ��ȡour team cmd v
	const point2f& get_our_cmd_v(int id)const;
	// ��ȡour team cmd rot
	const float& get_our_cmd_rot(int id)const;
	// ��ȡ�ҷ���ҵ���ת�Ƕ�
	const PlayerVision& get_our_player(int id)const;
	// ��ȡ�ҷ���ҵ�λ��
	const point2f& get_our_player_pos(int id)const;
	// ��ȡ�ҷ���ҵ����λ��
	const point2f& get_opp_player_pos(int id)const;
	// ��ȡ�ҷ���ҵ������ת�Ƕ�
	float get_opp_player_dir(int id)const;
	// ��ȡ�ҷ���ҵ����λ��
	const point2f& get_our_player_v(int id)const;
	// ��ȡ�ҷ���ҵ�����ٶ�
	const point2f& get_our_player_last_v(int id)const;
	// ��ȡ�ҷ���ҵ������ת�Ƕ�
	float get_our_player_dir(int id)const;
	// ��ȡ�ҷ���ҵ������ת�Ƕ�
	const float get_our_player_last_dir(int id)const;
	// ��ȡ�Է���ҵ�λ��
	const PlayerVision& get_opp_player(int id)const;
	// ��ȡ����id����Ա
	int get_our_goalie()const{ return our_goalie; }
	// ��ȡ����id����Ա
	int get_opp_goalie()const{ return opp_goalie; }
	// ���ö���id����Ա
	void set_our_goalie(int goalie_id){ our_goalie = goalie_id; }
	// ���ö���id����Ա
	void set_opp_goalie(int goalie_id){ opp_goalie = goalie_id; }
	// ������Ա
	void set_ball(Ball* b){ match_ball = b; }
	// ��ȡ��Ա��λ��
	const BallVision& get_ball()const{ return match_ball->get_ball_vision(); }
	// ��ȡ��Ա��λ��
	const point2f& get_ball_pos(int c)const{ return match_ball->get_pos(c); }
	// ��ȡ��Ա��λ��
	const point2f& get_ball_pos()const{ return match_ball->get_pos(); }
	// ��ȡ��Ա���ٶ�
	const point2f& get_ball_vel()const{ return match_ball->get_vel(); }
	// ��ȡ�����˵��ٶ�
	const int  robots_size()const { return max_robots; }
	// �����Ƿ�����
	void set_kick(bool* kick_f) { kick = kick_f; }
	// �����Ƿ�ģ������
	void set_sim_kick(bool* kick){ sim_kick = kick; }
	// ��ȡ�Ƿ�ģ������
	const bool* get_sim_kick()const{ return sim_kick; }
	// �жϻ������Ƿ�����
	bool is_kick(int id)const;
	// �жϻ������Ƿ�ģ������
	bool is_sim_kick(int id)const;
	// ������Ϸ״̬
	void set_game_state(GameState* state);
	// ��ȡ��Ϸ״̬
	const GameState* game_states()const;
	// �����Ƿ�ģ����Ϸ
	void set_simulation(bool sim){ is_simulation = sim; }
	// ��ȡ�Ƿ�ģ����Ϸ
	bool get_simulation()const{ return is_simulation; }
private:
	static const int max_robots = 12;
	// �����ҷ������˵�ָ��
	Vehicle* our;
	// ����Է������˵�ָ��
	Vehicle* opp;
	// �����ҷ��������Ƿ�����Ĳ���ֵ
	bool* kick;
	// �����ҷ��������Ƿ�����Ĳ���ֵ
	bool* sim_kick;
	// �����ҷ������˵�����ָ��
	Ball* match_ball;
	// �����ҷ������˵������Ƿ�����Ĳ���ֵ
	bool* our_robots_id;
	// ����Է������˵������Ƿ�����Ĳ���ֵ
	bool* opp_robots_id;
	// �����ҷ������˵�����Ĵ���
	int our_goalie;
	// ����Է������˵�����Ĵ���
	int opp_goalie;
	// ���嵱ǰ������
	int current_cycle;
	// ����ο���Ϣ
	std::string referee_msg;
	// �����ҷ������˵ı���״̬
	FieldState match_state;
	// �����ҷ������˵ı���״̬
	GameState* game_state;
	// �����Ƿ�Ϊģ��ģʽ
	bool is_simulation;
};
#endif