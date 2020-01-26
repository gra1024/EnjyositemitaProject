#include "DxLib.h"
#include "task.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(FALSE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定
	SetGraphMode(1280, 720, 32);

	int close;

	Task task;
	task.setup();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {//画面更新 & メッセージ処理 & 画面消去
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;//escapeで強制終了
		}

		close = task.sceneChoice();//更新
		ScreenFlip();//描画

		if (close == 1) {
			break;
		}
	}


	DxLib_End(); // DXライブラリ終了処理
	return 0;
}