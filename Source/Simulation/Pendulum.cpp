#include <DxLib.h>
#include "Pendulum.h"

#include <numbers>

Pendulum::Pendulum(Vector3 gravity) :
	gravity_(gravity), gMag_(gravity_.Magnitude()), theta_(0.0f), omega_(0.0f), length_(0.0f), isStarted_(false)
{
}

bool Pendulum::Start(Vector3 weightPos, Vector3 fulcrumPos)
{
	//同じ位置のとき(紐の長さが0のとき)は失敗
	if (weightPos == fulcrumPos)
	{
		return false;
	}

	weightPos_ = weightPos;
	fulcrumPos_ = fulcrumPos;

	auto lVec = weightPos_ - fulcrumPos_;		//支点→錘のベクトル(紐)
	length_ = lVec.Magnitude();										//紐の長さ

	auto grNorm = gravity_.Normalized();			//重力の正規化済みベクトル
	auto x = grNorm.Dot(lVec);									//重力ベクトルと錘から重力軸までのベクトルが交わる点と支点の大きさ

	yNorm_ = lVec - grNorm * x;										//錘から重力軸までのベクトル
	auto y = yNorm_.Magnitude();								//錘から重力軸までの距離
	yNorm_.Normalize();												//錘から重力軸までの正規化済みベクトル

	theta_ = atan2f(y, x);											//支点の近接二辺のそれぞれの大きさを使用して角度を出す
	omega_ = 0.0f;													//角速度は0で初期化

	isStarted_ = true;												//開始フラグ

	return true;
}

void Pendulum::Update(float delta)
{
	if (!isStarted_)
	{
		return;
	}

	auto coe = -gMag_ / length_;				//kの係数

	//ルンゲ=クッタ法の計算
	auto k1 = delta * coe * sin(theta_);
	auto m1 = delta * omega_;

	auto k2 = delta * coe * sin(theta_ + m1 / 2.f);
	auto m2 = delta * (omega_ + k1 / 2.f);

	auto k3 = delta * coe * sin(theta_ + m2 / 2.f);
	auto m3 = delta * (omega_ + k2 / 2.f);

	auto k4 = delta * coe * sin(theta_ + m3);
	auto m4 = delta * (omega_ + k3);

	omega_ += (k1 + 2.f * k2 + 2.f * k3 + k4) / 6.f;		//角速度の加算
	theta_ += (m1 + 2.f * m2 + 2.f * m3 + m4) / 6.f;		//角度の加算

	//角度から錘の位置を導出
	weightPos_ = fulcrumPos_ + length_ * cos(theta_) * gravity_.Normalized() + length_ * sin(theta_) * yNorm_;
}

void Pendulum::Draw(void)
{
	if(!isStarted_)
	{
		return;
	}

	VECTOR weightPos = { weightPos_.x,weightPos_.y,weightPos_.z };
	VECTOR fulcrumPos = { fulcrumPos_.x,fulcrumPos_.y,fulcrumPos_.z };

	//角度情報の描画
	DrawFormatString(0, 0, 0xffffff, "theta=%f", theta_ * 180.0f / std::numbers::pi_v<float>);
	DrawFormatString(0, 15, 0xffffff, "omega=%f", omega_ * 180.0f / std::numbers::pi_v<float>);
	DrawFormatString(0, 30, 0xffffff, "weightPos=(%3.1f,%3.1f,%3.1f)", weightPos_.x, weightPos_.y, weightPos_.z);

	DrawLine3D(weightPos, fulcrumPos, 0xffffff);											//紐の描画
	DrawSphere3D(weightPos, 30.f, 36, 0xff0000, 0xffffff, true);		//錘の描画
	DrawSphere3D(fulcrumPos, 10.f, 12, 0xffffff, 0xffffff, true);		//支点の描画
}
