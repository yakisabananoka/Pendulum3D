#pragma once
#include "Math/Vector3.h"

/// @brief 振り子
class Pendulum
{
public:
	/// @brief コンストラクタ
	/// @param gravity 重力ベクトル
	Pendulum(Vector3 gravity);
	~Pendulum() = default;

	/// @brief 振り子開始
	/// @param weightPos 錘の位置
	/// @param fulcrumPos 支点の位置
	/// @return true:成功 false:失敗
	bool Start(Vector3 weightPos, Vector3 fulcrumPos);

	/// @brief 更新
	/// @param delta デルタタイム
	void Update(float delta);

	/// @brief 描画
	void Draw(void);

	Pendulum(const Pendulum&) = delete;
	Pendulum& operator=(const Pendulum&) = delete;

	Pendulum(Pendulum&&) = default;
	Pendulum& operator=(Pendulum&&) = default;

private:
	Vector3 weightPos_;		//錘の位置
	Vector3 fulcrumPos_;	//支点の位置
	Vector3 gravity_;		//重力ベクトル
	Vector3 yNorm_;			//軸から錘の正規化済み垂直ベクトル
	float gMag_;			//重力の大きさ

	float theta_;			//角度
	float omega_;			//角速度

	float length_;			//長さ

	bool isStarted_;		//開始済みか
};
