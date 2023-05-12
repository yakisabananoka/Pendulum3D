#include <DxLib.h>
#include "Graphics/Drawable/Screen.h"
#include "Graphics/Camera/PerspectiveCamera.h"
#include "Common/Time.h"
#include "Simulation/Pendulum.h"


//エントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);

	auto& backScreen = Screen::GetBackScreen();
	PerspectiveCamera camera;
	camera.SetPosition({ 0.0f,0.0f,-500.0f });

	Pendulum pendulum({ 0.0f,-980.f,0.0f });
	pendulum.Start({ 300.0f,50.0f,0.0f }, { 0.0f,200.0f,0.0f });

	Time timeManager;

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		pendulum.Update(timeManager.Update());

		backScreen.Setup();
		backScreen.Clear();

		camera.Setup();

		pendulum.Draw();

		Screen::Flip();
	}

	DxLib_End();

	return 0;
}
