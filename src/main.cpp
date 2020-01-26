#include "DxLib.h"
#include "task.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(FALSE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	SetGraphMode(1280, 720, 32);

	int close;

	Task task;
	task.setup();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {//��ʍX�V & ���b�Z�[�W���� & ��ʏ���
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;//escape�ŋ����I��
		}

		close = task.sceneChoice();//�X�V
		ScreenFlip();//�`��

		if (close == 1) {
			break;
		}
	}


	DxLib_End(); // DX���C�u�����I������
	return 0;
}