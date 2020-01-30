#pragma warning(disable: 4996)
#include "task.h"
#include "erslib19.h"

/* ### �����ݒ� ### */
void Task::setup() {
	imageHandle_background[0] = LoadGraph("../data/img/background/startMenu.png");
	imageHandle_background[1] = LoadGraph("../data/img/background/close0.png");
	imageHandle_background[2] = LoadGraph("../data/img/background/close1.png");
	imageHandle_background[3] = LoadGraph("../data/img/background/batsu0.png");
	imageHandle_background[4] = LoadGraph("../data/img/background/batsu1.png");
	imageHandle_background[5] = LoadGraph("../data/img/background/arrow.png");
	imageHandle_background[6] = LoadGraph("../data/img/background/playFlame.png");
	imageHandle_background[7] = LoadGraph("../data/img/background/factory.png");
	imageHandle_background[8] = LoadGraph("../data/img/background/bar.png");
	imageHandle_background[9] = LoadGraph("../data/img/background/onemore.png");
	imageHandle_background[10] = LoadGraph("../data/img/background/finish.png");

	imageHandle_effect[0] = LoadGraph("../data/img/effect/cursor.png");
	imageHandle_effect[1] = LoadGraph("../data/img/effect/advertisement.png");
	imageHandle_effect[2] = LoadGraph("../data/img/effect/smoke.png");
	imageHandle_effect[3] = LoadGraph("../data/img/effect/crane.png");
	imageHandle_effect[4] = LoadGraph("../data/img/effect/explosion.png");
	
	imageHandle_car[0] = LoadGraph("../data/img/car/junk.png");
	imageHandle_car[1] = LoadGraph("../data/img/car/standard1.png");
	imageHandle_car[2] = LoadGraph("../data/img/car/standard2.png");
	imageHandle_car[3] = LoadGraph("../data/img/car/standard3.png");
	imageHandle_car[4] = LoadGraph("../data/img/car/standard4.png");
	imageHandle_car[5] = LoadGraph("../data/img/car/standard5.png");
	imageHandle_car[6] = LoadGraph("../data/img/car/standard6.png");
	imageHandle_car[7] = LoadGraph("../data/img/car/standard7.png");
	imageHandle_car[8] = LoadGraph("../data/img/car/bike.png");
	imageHandle_car[9] = LoadGraph("../data/img/car/police.png");
	imageHandle_car[10] = LoadGraph("../data/img/car/carrier.png");
	imageHandle_car[11] = LoadGraph("../data/img/car/bigTruck.png");
	imageHandle_car[12] = LoadGraph("../data/img/car/lightTruck.png");

	soundHandle[0] = LoadSoundMem("../data/sound/kazakiri.mp3");//game
	soundHandle[1] = LoadSoundMem("../data/sound/bomb1.mp3");//title
	soundHandle[2] = LoadSoundMem("../data/sound/bomb2.mp3");//game

	movieHandle[0] = LoadGraph("../data/movie/advertisement.mp4");
	movieHandle[1] = LoadGraph("../data/movie/result.mp4");

	fontHandle[0] = CreateFontToHandle("���C���I", 18, 9, DX_FONTTYPE_NORMAL);//�v���C�񐔋y�уX�R�A
	fontHandle[1] = CreateFontToHandle("���C���I", 15, 5, DX_FONTTYPE_NORMAL);//�X�R�A�����L���O
	fontHandle[2] = CreateFontToHandle("���C���I", 25, 9, DX_FONTTYPE_NORMAL);//�X�R�A��
	fontHandle[3] = CreateFontToHandle("���C���I", 40, 9, DX_FONTTYPE_NORMAL);//�X�R�A���

	saveDataUpdate(0, 0);

	inputFromRemoteControl.com = 1;
	inputFromRemoteControl.r = ERS_Open(1, BUFSIZE, BUFSIZE);
	ERS_Config(inputFromRemoteControl.com, ERS_9600);

	scene = 1;
	selector = 1;
	LagCounter = 0;
	checkHit = 0;
	countTimer = 0;
}

/* ### �V�[���I���^�X�N ### */
int Task::sceneChoice() {
	if (scene == 1) close = showMenu();
	else if (scene == 2) showAdvertisement();
	else if (scene == 3) showGame();
	else if (scene == 4) showResult();
	return close;
}

/* ### �V�[��1�A���j���[��� ### */
int Task::showMenu() {
	/* �w�i�̕`�� */
	DrawGraph(0, 0, imageHandle_background[0], TRUE); //�w�i

	/* �J�[�\���ɍ��킹�ĕ`�� */
	if (selector == 1) {
		DrawGraph(0, 0, imageHandle_background[3], TRUE); //�~�{�^��
		DrawGraph(0, 0, imageHandle_background[1], TRUE); //��ʂ����{�^��
		DrawGraph(322, 231, imageHandle_background[5], TRUE); //����Đ��{�^��
		DrawGraph(480, 360, imageHandle_effect[0], TRUE); //�J�[�\��
	}
	else {
		DrawGraph(0, 0, imageHandle_background[4], TRUE); //�~�{�^��
		DrawGraph(0, 0, imageHandle_background[2], TRUE); //��ʂ����{�^��
		DrawExtendGraph(332, 238, 564, 397, imageHandle_background[5], TRUE); //����Đ��{�^��
		DrawGraph(50, 40, imageHandle_effect[0], TRUE); //�J�[�\��
	}

	/* �Đ��񐔁A�X�R�A�����L���O�̕`�� */
	string str = formatScore(saveData.played, 1);
	int shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[0]);
	DrawStringToHandle(213 - shift, 673, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[0]);
	str = formatScore(saveData.score[0], 0);
	shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[1]);
	DrawStringToHandle(1229 - shift, 295, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[1]);
	str = formatScore(saveData.score[1], 0);
	shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[1]);
	DrawStringToHandle(1229 - shift, 405, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[1]);
	str = formatScore(saveData.score[2], 0);
	shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[1]);
	DrawStringToHandle(1229 - shift, 501, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[1]);
	str = formatScore(saveData.score[3], 0);
	shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[1]);
	DrawStringToHandle(1229 - shift, 592, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[1]);
	str = formatScore(saveData.score[4], 0);
	shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[1]);
	DrawStringToHandle(1229 - shift, 692, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[1]);
	str = formatScore(saveData.score[5], 0);
	shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[1]);
	DrawStringToHandle(1229 - shift, 189, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[1]);

	/* �J�[�\���ړ� */
	if (ERS_CheckRecv(inputFromRemoteControl.com) > 0) {
		inputFromRemoteControl.r = ERS_Recv(inputFromRemoteControl.com, inputFromRemoteControl.buf, 1);
		inputFromRemoteControl.r = ERS_Send(inputFromRemoteControl.com, inputFromRemoteControl.buf, 1);
		if (inputFromRemoteControl.buf[0] == 'a' || inputFromRemoteControl.buf[0] == 'A' || CheckHitKey(KEY_INPUT_A) == 1) {
			selector--;

			if (selector < 1) selector = 2;
		}
		if (inputFromRemoteControl.buf[0] == 'd' || inputFromRemoteControl.buf[0] == 'D' || CheckHitKey(KEY_INPUT_D) == 1) {
			selector++;
			if (selector > 2) selector = 1;
		}
		/* �V�[���ړ� */
		if (inputFromRemoteControl.buf[0] == 'z' || inputFromRemoteControl.buf[0] == 'Z' || CheckHitKey(KEY_INPUT_Z) == 1) {
			if (selector == 1) {
				selector = 1;
				scene++;//���̃V�[���Ɉړ�
			}
			else {
				return 1;//�V�X�e���I��
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		selector--;
		if (selector < 1) selector = 2;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		selector++;
		if (selector > 2) selector = 1;
	}

	/* �V�[���ړ� */
	if (CheckHitKey(KEY_INPUT_Z) == 1) {
		if (selector == 1) {
			selector = 1;
			scene++;//���̃V�[���Ɉړ�
		}
		else {
			return 1;//�V�X�e���I��
		}
	}

	return 0;
}

/* ### �V�[���Q�A�L�� ### */
void Task::showAdvertisement() {
	/* ����𗬂��n�߂� */
	if (countTimer == 0) {
		PlayMovieToGraph(movieHandle[0]);
		advertising.skipButton.x = 300;
		advertising.skipButton.y = 0;
	}

	/* ����̕`�� */
	DrawExtendGraph(195, 65, 1085, 550, movieHandle[0], FALSE);

	/* �w�i�̕`�� */
	DrawGraph(195, 550, imageHandle_background[8], TRUE);
	/* �X�L�b�v�{�^���̕`�� */
	if (countTimer > 150) {
		if (advertising.skipButton.x > 9) {
			if (advertising.skipButton.x > 100) {
				advertising.skipButton.x -= 10;
			}
			else {
				advertising.skipButton.x -= 10;
			}
		}
		DrawGraph(advertising.skipButton.x, advertising.skipButton.y, imageHandle_effect[1], TRUE);
	}
	DrawBox(0, 66, 196, 600, colorDarkGray, TRUE);
	DrawBox(1084, 66, 1280, 600, colorDarkGray, TRUE);
	DrawGraph(0, 0, imageHandle_background[6], TRUE);

	int barLength = countTimer * 890 / (30 * 64) + 195;
	DrawLine(195, 550, barLength, 550, colorYellow, 3);
	DrawCircle(barLength, 550, 5, colorYellow, TRUE);

	/* �Đ��񐔂̕`�� */
	string str = formatScore(saveData.played, 1);
	int shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[2]);
	DrawStringToHandle(353 - shift, 673, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[2]);
	str = formatScore(saveData.score[0], 0);
	shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[1]);
	DrawStringToHandle(1225 - shift, 658, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[1]);

	/* ������X�L�b�v���� */
	if (ERS_CheckRecv(inputFromRemoteControl.com) > 0) {
		inputFromRemoteControl.r = ERS_Recv(inputFromRemoteControl.com, inputFromRemoteControl.buf, 1);
		inputFromRemoteControl.r = ERS_Send(inputFromRemoteControl.com, inputFromRemoteControl.buf, 1);
		if (inputFromRemoteControl.buf[0] == 'z' || inputFromRemoteControl.buf[0] == 'Z') {
			if (countTimer > 160) {
				countTimer = 2001;
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_Z) == 1) {
		if (countTimer > 160) {
			countTimer = 2001;
		}
	}
	countTimer++;

	/* ������I�����A�V�[���ړ����� */
	if (countTimer > 1900) {
		PauseMovieToGraph(movieHandle[0]);
		SeekMovieToGraph(movieHandle[0], 0);
		
		gameSystem.selectScene = 0;
		gameSystem.timeLimit = 0;
		gameSystem.totalScore = 0;
		game.flameCountExplosion = 10;
		game.flameCountSmork = 20;
		game.checkAppearLighttruck = 0;
		game.confirmationPreliminaryOperationMotionMagic = 0;
		LagCounter = 0;
		checkHit = 0;
		
		countTimer = 0;
		scene = 3;
	}
}

/* ### �V�[��3�A���C���V�X�e����� ### */
void Task::showGame() {
	/* �w�i�̕`�� */
	DrawGraph(140, 52, imageHandle_background[7], TRUE);
	DrawGraph(195, 550, imageHandle_background[8], TRUE);
	DrawBox(0, 66, 196, 600, colorDarkGray, TRUE);
	DrawBox(1084, 66, 1280, 600, colorDarkGray, TRUE);




	/* �Ԃ̏��� */
	if (gameSystem.selectScene == 0) {
		int rand = GetRand(10);//11�탉���_��
		game.carData.species = rand + 1;
		if (game.carData.species > 0 && game.carData.species < 5) {//�y������
			game.carData.currentHP = game.carData.maxHP = 100;
			game.carData.genus = 1;
		}
		else if (game.carData.species > 4 && game.carData.species < 8) {//��p��
			game.carData.currentHP = game.carData.maxHP = 150;
			game.carData.genus = 2;
		}
		else if (game.carData.species == 8) {//�o�C�N
			game.carData.currentHP = game.carData.maxHP = 50;
			game.carData.genus = 3;
		}
		else if (game.carData.species == 9) {//�p�g�J�[
			game.carData.currentHP = game.carData.maxHP = 200;
			game.carData.genus = 4;
		}
		else if (game.carData.species == 10) {//�L�����A�J�[
			game.carData.currentHP = game.carData.maxHP = 250;
			game.carData.genus = 5;
		}
		else {//�g���b�N
			game.carData.currentHP = game.carData.maxHP = 400;
			game.carData.genus = 6;
		}
		if (game.checkAppearLighttruck == 1) {//�y�g��
			game.checkAppearLighttruck = 0;
			game.carData.species = 12;
			game.carData.currentHP = game.carData.maxHP = 150;
			game.carData.genus = 7;
		}

		game.carData.coordinate.x = (1280 / 2) - (450 / 2);
		game.carData.coordinate.y = -340;
		game.craneData.x = (1280 / 2) - (520 / 2);
		game.craneData.y = -620;
		gameSystem.selectScene = 1;
	}

	/* �Ԃ��ړ� */
	else if (gameSystem.selectScene == 1) {
		if (game.carData.coordinate.y >= 190) {
			gameSystem.selectScene++;
		}
	}

	/* �ԑҋ@�����͑҂� */
	else if (gameSystem.selectScene == 2) {
		if (game.carData.genus != 3) {
			if (checkHit == 0) {
				if (ERS_CheckRecv(inputFromRemoteControl.com) > 0) {
					inputFromRemoteControl.r = ERS_Recv(inputFromRemoteControl.com, inputFromRemoteControl.buf, 1);
					inputFromRemoteControl.r = ERS_Send(inputFromRemoteControl.com, inputFromRemoteControl.buf, 1);
					if (inputFromRemoteControl.buf[0] == 'p' || inputFromRemoteControl.buf[0] == 'P') gameCalcCarDamage(1);//�؂艺��
					else if (inputFromRemoteControl.buf[0] == 'o' || inputFromRemoteControl.buf[0] == 'O') gameCalcCarDamage(2);//�؂�グ
					//else if (buf[0] == 'i' || buf[0] == 'I') gameCalcCarDamage(3);//�U��
					else if (inputFromRemoteControl.buf[0] == 'u' || inputFromRemoteControl.buf[0] == 'U') gameCalcCarDamage(4);//�o�C�N��
					if (inputFromRemoteControl.buf[0] == 'g' || inputFromRemoteControl.buf[0] == 'G')game.confirmationPreliminaryOperationMotionMagic = 10;
					if (inputFromRemoteControl.buf[0] == 'y' || inputFromRemoteControl.buf[0] == 'Y') gameCalcCarDamage(5);
					//���@
				}
				if (CheckHitKey(KEY_INPUT_P) == 1) gameCalcCarDamage(1);//�؂艺��
				else if (CheckHitKey(KEY_INPUT_O) == 1) gameCalcCarDamage(2);//�؂�グ
				//else if (CheckHitKey(KEY_INPUT_I) == 1) gameCalcCarDamage(3);//�U��
				else if (CheckHitKey(KEY_INPUT_U) == 1) gameCalcCarDamage(4);//�o�C�N��
				if (CheckHitKey(KEY_INPUT_G) == 1)game.confirmationPreliminaryOperationMotionMagic = 10;
				if (CheckHitKey(KEY_INPUT_Y) == 1) gameCalcCarDamage(5);
			}
		}
		else {
			if (checkHit == 0) {
				if (ERS_CheckRecv(inputFromRemoteControl.com) > 0) {
					inputFromRemoteControl.r = ERS_Recv(inputFromRemoteControl.com, inputFromRemoteControl.buf, 1);
					inputFromRemoteControl.r = ERS_Send(inputFromRemoteControl.com, inputFromRemoteControl.buf, 1);
					if (inputFromRemoteControl.buf[0] == 'u' || inputFromRemoteControl.buf[0] == 'U') gameCalcCarDamage(4);//�o�C�N��
				}
				if (CheckHitKey(KEY_INPUT_U) == 1) gameCalcCarDamage(4);//�o�C�N��
			}
		}

	}
	if (game.confirmationPreliminaryOperationMotionMagic > 0) {
		DrawStringToHandle(800, 500, "���@���������I", colorRed, fontHandle[0]);
	}


	/* �_���[�W���o */
	else if (gameSystem.selectScene == 3) {


		scene = 2;
	}
	/* �j�󉉏o */
	else if (gameSystem.selectScene == 4) {
		DrawGraph(game.carData.coordinate.x, game.carData.coordinate.y, imageHandle_car[game.carData.species], TRUE);
		if (game.flameCountSmork == 10) game.carData.species = 0;//�`�ʂ���Ԃ�p�ԂɕύX
		if (game.flameCountSmork > 19) gameSystem.selectScene = 0;
	}
	game.confirmationPreliminaryOperationMotionMagic--;
	gameDraw();
	gameDrawStatusBar();

	DrawGraph(0, 0, imageHandle_background[6], TRUE);
	gameSystem.totalScore += GetRand(5);
	string str = formatScore(gameSystem.totalScore, 0);
	int shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[2]);
	DrawStringToHandle(353 - shift, 673, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[2]);
	str = formatScore(saveData.score[0], 0);
	shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[1]);
	DrawStringToHandle(1225 - shift, 658, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[1]);

	/* BGM�𗬂��n�߂� */
	if (!CheckSoundMem(soundHandle[0])) {
		PlaySoundMem(soundHandle[0], DX_PLAYTYPE_LOOP, TRUE);
	}
	countTimer++;
	//�^�C�}�[�̕\�����Q�[���I���̏���
	int finish = drawTimeLimitBar(gameSystem.timeLimit, 42, colorRed);
	if (finish == 1) {
		StopSoundMem(soundHandle[0]);
		countTimer = 0;
		scene++;
	}
	/*if (CheckHitKey(KEY_INPUT_R) == 1){
		StopSoundMem(soundHandle[0]);
		countTimer = 0;
		scene++;
	}*/






	HitLag(0);
	gameSystem.timeLimit++;
}

/* ### �V�[��4�A���ʔ��\��� ### */
void Task::showResult() {
	if (countTimer == 0) {
		PlayMovieToGraph(movieHandle[1]);
		saveDataUpdate(1, gameSystem.totalScore);
		selector = 1;
	}
	/* ����̕`�� */
	DrawExtendGraph(195, 65, 1085, 550, movieHandle[1], FALSE);

	DrawGraph(0, 0, imageHandle_background[9], TRUE);
	DrawGraph(0, 0, imageHandle_background[10], TRUE);

	DrawGraph(195, 550, imageHandle_background[8], TRUE);
	DrawBox(0, 66, 196, 600, colorDarkGray, TRUE);
	DrawBox(1084, 66, 1280, 600, colorDarkGray, TRUE);
	DrawGraph(0, 0, imageHandle_background[6], TRUE);

	string str = formatScore(gameSystem.totalScore, 0);
	int shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[2]);
	DrawStringToHandle(353 - shift, 673, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[2]);
	str = formatScore(saveData.score[0], 0);
	shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[1]);
	DrawStringToHandle(1225 - shift, 658, str.c_str(), colorHandleForNumberOfPlayed, fontHandle[1]);

	if (selector == 1) {
		DrawGraph(360, 493, imageHandle_effect[0], TRUE); //�J�[�\��
	}
	else {
		DrawGraph(974, 493, imageHandle_effect[0], TRUE); //�J�[�\��
	}

	if (countTimer > 190) {
		str = formatScore(gameSystem.totalScore, 0);
		shift = GetDrawStringWidthToHandle(str.c_str(), str.length(), fontHandle[3]);
		DrawStringToHandle(870 - shift, 315, str.c_str(), colorRed, fontHandle[3]);
	}
	int a = 0;
	if (ERS_CheckRecv(inputFromRemoteControl.com) > 0) {
		inputFromRemoteControl.r = ERS_Recv(inputFromRemoteControl.com, inputFromRemoteControl.buf, 1);
		inputFromRemoteControl.r = ERS_Send(inputFromRemoteControl.com, inputFromRemoteControl.buf, 1);
		if (inputFromRemoteControl.buf[0] == 'a' || inputFromRemoteControl.buf[0] == 'A') {
			selector--;
			if (selector < 1) selector = 2;
		}
		if (inputFromRemoteControl.buf[0] == 'd' || inputFromRemoteControl.buf[0] == 'D') {
			selector++;
			if (selector > 2) selector = 1;
		}
		if (inputFromRemoteControl.buf[0] == 'z' || inputFromRemoteControl.buf[0] == 'Z') {
			a = 1;
		}
	}
	if (CheckHitKey(KEY_INPUT_A) == 1) {
		selector--;
		if (selector < 1) selector = 2;
	}
	if (CheckHitKey(KEY_INPUT_D) == 1) {
		selector++;
		if (selector > 2) selector = 1;
	}
	if (CheckHitKey(KEY_INPUT_Z) == 1) {
		a = 1;
	}
	if (countTimer > 4000) {
		selector = 2;
		a = 1;
	}
	countTimer++;

	if (a == 1) {
		PauseMovieToGraph(movieHandle[1]);
		SeekMovieToGraph(movieHandle[1], 0);
		countTimer = 0;
		if (selector == 1) {
			scene = 2;//���̃V�[���Ɉړ�
		}
		else {
			scene = 1;//�V�X�e���I��
		}
		selector = 1;
	}



}

/* ### Game�̕`�� ### */
void Task::gameDraw() {
	//�ԁA�A�[���̓���
	if (gameSystem.selectScene == 1) {
		DrawGraph(game.carData.coordinate.x, game.carData.coordinate.y, imageHandle_car[game.carData.species], TRUE);
		DrawGraph(game.craneData.x, game.craneData.y, imageHandle_effect[3], TRUE);
		game.carData.coordinate.y += SPEED_MOVE_CAR;
		game.craneData.y += SPEED_MOVE_CAR;
	}

	//�Ԃ̕`��
	if (gameSystem.selectScene == 2) {
		DrawGraph(game.carData.coordinate.x, game.carData.coordinate.y, imageHandle_car[game.carData.species], TRUE);
	}

	//�A�[���̑ޏ�
	if (gameSystem.selectScene > 1 && gameSystem.selectScene < 5) {
		if (game.craneData.y >= -620) {
			DrawGraph(game.craneData.x, game.craneData.y, imageHandle_effect[3], TRUE);
			game.craneData.y -= SPEED_MOVE_CAR;
		}
	}

	//�����֌W
	if (game.flameCountExplosion < 10) {
		if (game.flameCountExplosion < 3) {
			PlaySoundMem(soundHandle[2], DX_PLAYTYPE_BACK, TRUE);
		}
		for (int i = 0; i < 3; i++) {
			if (game.flameCountExplosion < 5) {
				game.explosionData[i][0].x -= 15;
				game.explosionData[i][0].y -= 30;
				game.explosionData[i][1].x += 15;
				DrawExtendGraph(game.explosionData[i][0].x, game.explosionData[i][0].y, game.explosionData[i][1].x, game.explosionData[i][1].y, imageHandle_effect[4], TRUE);
			}
			else if (game.flameCountExplosion >= 5 && game.flameCountExplosion < 10) {
				int blend = 255 - ((game.flameCountExplosion - 5) * 50);
				SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, blend);
				DrawExtendGraph(game.explosionData[i][0].x, game.explosionData[i][0].y, game.explosionData[i][1].x, game.explosionData[i][1].y, imageHandle_effect[4], TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			}
		}
		game.flameCountExplosion++;
	}

	//�����֌W
	if (game.flameCountSmork < 20) {
		if (game.flameCountSmork == 0) {
			PlaySoundMem(soundHandle[1], DX_PLAYTYPE_BACK, TRUE);
		}
		if (game.flameCountSmork < 10) {
			game.smorkData[0].x -= 25;
			game.smorkData[0].y -= 50;
			game.smorkData[1].x += 25;
			DrawExtendGraph(game.smorkData[0].x, game.smorkData[0].y, game.smorkData[1].x, game.smorkData[1].y, imageHandle_effect[2], TRUE);
		}
		else if (game.flameCountSmork >= 10 && game.flameCountSmork < 20) {
			int blend = 255 - ((game.flameCountSmork - 10) * 25);
			SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, blend);
			DrawExtendGraph(game.smorkData[0].x, game.smorkData[0].y, game.smorkData[1].x, game.smorkData[1].y, imageHandle_effect[2], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		game.flameCountSmork++;
	}
}

/* ### Game�̎Ԃ̃_���[�W�̌v�Z�� ### */
void Task::gameCalcCarDamage(int motion) {
	//�_���[�W�̌v�Z
	if (motion == 1) game.carData.currentHP -= 75;//�؂艺��
	else if (motion == 2) game.carData.currentHP -= 60;//�؂�グ
	//else if (motion == 3) game.carData.currentHP -= 60;//�U��
	else if (motion == 4) game.carData.currentHP -= 50;//�o�C�N��
	else if (motion == 5) game.carData.currentHP -= 1000;//���@

	if (game.carData.currentHP > 0) {
		for (int i = 0; i < 3; i++) {
			int randX = GetRand(450);
			int randY = GetRand(340);
			game.explosionData[i][0].x = game.carData.coordinate.x + randX;
			game.explosionData[i][0].y = game.carData.coordinate.y + randY;
			game.explosionData[i][1].x = game.explosionData[i][0].x;
			game.explosionData[i][1].y = game.explosionData[i][0].y;
		}
		game.flameCountExplosion = 0;
		HitLag(1);
		gameAddScore(0, game.carData.genus, motion);
	}
	else {
		if (game.carData.genus == 5)game.checkAppearLighttruck = 1;
		game.smorkData[0].x = 1280 / 2;
		game.smorkData[0].y = 540;
		game.smorkData[1].x = game.smorkData[0].x;
		game.smorkData[1].y = 540;
		game.flameCountSmork = 0;
		gameSystem.selectScene = 4;
		gameAddScore(1, game.carData.species, motion);
	}
}

/* ### �X�R�A�̉��Z ### */
void Task::gameAddScore(int destruction, int car, int motion) {
	//��b�X�R�A�̑��
	double basicScore;
	if (car == 1) basicScore = 10000;//��p�ԂP
	else if (car == 2) basicScore = 15000;//��p�ԂQ
	else if (car == 3) basicScore = 10000;//�o�C�N
	else if (car == 4) basicScore = 30000;//�p�g�J�[
	else if (car == 5) basicScore = 50000;//�L�����A�J�[
	else if (car == 6) basicScore = 100000;//��^�g���b�N
	else basicScore = 20000;//�y�g���i�L�����A�J�[2�i�K�ځj

	//���[�V�����̕␳�v�Z�i��j
	double motionCorrection = 1;
	if (motion == 1) motionCorrection *= 1.0;
	else if (motion == 2) motionCorrection *= 1.1;
	else if (motion == 3) motionCorrection *= 1.2;
	else if (motion == 4) motionCorrection *= 1.3;
	else motionCorrection *= 1.4;


	//OP���E�␳�v�Z�i���j
	double repetitionCorrection = 1;
	for (int i = 0; i < 3; i++) {
		if (destruction == game.repetitionCorrectionList[i]) {
			repetitionCorrection = repetitionCorrection * 0.9;
		}
	}

	//�j�󎞕␳�v�Z�i��j
	double destructionCorrection = 1;
	if (destruction == 1) destructionCorrection *= 8;

	//�����␳�v�Z�i���j
	double randomNumberCorrection = (static_cast<double>(GetRand(15)) + 85) * 0.01;

	//�X�R�A�v�Z
	int score = static_cast<int>(basicScore * motionCorrection * repetitionCorrection * destructionCorrection * randomNumberCorrection);

	//�g�[�^���X�R�A�֑��
	gameSystem.totalScore += score;
}

/* ### ����̎��ԃo�[�̕`�� ### */
int Task::gameDrawStatusBar() {
	if (game.carData.currentHP < 0) game.carData.currentHP = 0;
	int x1, x2, x3, y1, y2;
	x1 = 640 - game.carData.maxHP;
	x2 = x1 + game.carData.currentHP * 2;
	x3 = 640 + game.carData.maxHP;
	y1 = game.carData.coordinate.y - 40;
	y2 = game.carData.coordinate.y - 10;
	DrawBox(x1, y1, x2, y2, colorGreen, TRUE);
	DrawBox(x2, y1, x3, y2, colorRed, TRUE);
	return 0;
}

/* ### �t�@�C�����[�h�A�Z�[�u ### */
int Task::saveDataUpdate(int type, int score) {
	FILE* fp;
	char fname[] = "../data/saveData/saveData.txt";

	if (type == 0) {
		fp = fopen(fname, "r");
		if (fp == NULL) {
			return 1;
		}
		int cnt = 0;
		int getint;
		while (fscanf(fp, "%d", &getint) != EOF) {
			if (cnt == 0) {
				saveData.played = getint;
			}
			else {
				saveData.score[cnt - 1] = getint;
			}
			cnt++;
		}
		fclose(fp);
	}
	else {
		int proScore = score;
		saveData.played++;
		for (int i = 0; i < 5; i++) {
			if (proScore > saveData.score[i]) {
				int z = proScore;
				proScore = saveData.score[i];
				saveData.score[i] = z;
			}
		}
		saveData.score[5] = score;

		fp = fopen(fname, "w");
		for (int i = 0; i < 7; i++) {
			if (i == 0) {
				fprintf(fp, "%d\n", saveData.played);
			}
			else {
				fprintf(fp, "%d\n", saveData.score[i - 1]);
			}
		}
		fclose(fp);

	}
	return 1;
}

/* ### �A�����̓X�g�b�p�[ ### */
void Task::HitLag(int num) {
	if (num == 1) {
		LagCounter = 0;
		checkHit = 1;
	}
	else {
		if (checkHit == 1) {
			LagCounter++;
			if (LagCounter > 15) {
				checkHit = 0;
			}
		}
	}
}

/* ### �Q�[�����̐������Ԃ̊Ǘ� ### */
int Task::drawTimeLimitBar(int currentTime, int maxTime, int color) {
	int barLength = currentTime * 890 / (30 * maxTime) + 195;
	DrawLine(195, 550, barLength, 550, color, 3);
	DrawCircle(barLength, 550, 5, color, TRUE);
	if (gameSystem.timeLimit >= 30 * 42) {
		return 1;
	}
	return 0;
}

/* ### int->string�ɕϊ��A3�P�^���Ƃ�','������ ### */
string Task::formatScore(int num, int type) {
	int digit = 0;
	int n = num;
	vector<int> vec = {};
	while (n != 0) {
		n /= 10;
		digit++;
	}
	n = num;
	for (int i = 0; i < digit; i++) {
		vec.push_back(n / static_cast<int>(pow(10, digit - i - 1)));
		n %= static_cast<int>(pow(10, digit - i - 1));
	}
	string str;
	for (int i = 0; i < digit; i++) {
		str += to_string(vec[i]);
		if (1 == (digit - i) % 3 && digit != i + 1) {
			str += ",";
		}
	}
	if (type == 1) str += ",000,000";
	if (num == 0)str = '0';
	return str;
}