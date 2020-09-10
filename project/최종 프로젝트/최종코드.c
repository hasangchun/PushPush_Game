
#include<stdio.h>
#include <conio.h>
#include <string.h>
#include<Windows.h>
#include<time.h> // clock �Լ�
#include<stdlib.h> //feof, exit


#define STAGE_DATA_FILE "pushpush.txt"
#define RANK_DATA_FILE "rank.txt"
#define MAX_STAGE 200
#define EXT_KEY         0xffffffe0   //Ȯ��Ű �νİ� ����Ű �� �Է¹ޱ� ���� �Ű�ü�� ��� .
#define KEY_LEFT      75
#define KEY_RIGHT      77
#define KEY_UP         72
#define KEY_DOWN      80
#define JUMP     97 // ���ĺ� a
struct member {
	char name[30];
	float time_result;
};


enum {
	BLACK,      /*  0 : ��� */
	DARK_BLUE,    /*  1 : ��ο� �Ķ� */
	DARK_GREEN,    /*  2 : ��ο� �ʷ� */
	DARK_SKY_BLUE,  /*  3 : ��ο� �ϴ� */
	DARK_RED,    /*  4 : ��ο� ���� */
	DARK_VOILET,  /*  5 : ��ο� ���� */
	DARK_YELLOW,  /*  6 : ��ο� ��� */
	GRAY,      /*  7 : ȸ�� */
	DARK_GRAY,    /*  8 : ��ο� ȸ�� */
	BLUE,      /*  9 : �Ķ� */
	GREEN,      /* 10 : �ʷ� */
	SKY_BLUE,    /* 11 : �ϴ� */
	RED,      /* 12 : ���� */
	VOILET,      /* 13 : ���� */
	YELLOW,      /* 14 : ��� */
	WHITE,      /* 15 : �Ͼ� */
};

typedef struct _stage {
	char   map[20][20];
	int pos_x;   //ĳ������ x��ǥ
	int pos_y;
}STAGE;

//*********************************
//������������
//*********************************
int c_pos_x, c_pos_y;   //���� ĳ������ ��ǥ��
int stageNum = 0;   //���� �������� ��ȣ 1���� ����
int stageMax = 3;   //�ִ� �������� 3��
int step = 1;   //������ Ƚ��
int item1 = 0;
int item2 = 0;
int item3 = 0;
STAGE re_stage[2000];   //�ǵ����� ����� ���� �ӽ����� ������ ����������
STAGE stage_data[MAX_STAGE];   //�������� �������� ����

//*********************************
//�Լ� ����
//*********************************
void init();               //�������� �ʱ�ȭ
void logo();         //���۷ΰ�
int show_stage(STAGE *p_stage, int all_load);   //stage�� ȭ�鿡 ��� all_load�� 1�̸� ���� ���
int gotoxy(int x, int y);   //Ŀ���ű��
int check_success(STAGE *p_stage); //���������� ���´��� �˻�
int show_frame(int start_col, int all_load);   //ȭ�� �������� ����â��� all_load�� 1�̸� ������ 0�̸� ���������
int show_success();
void bublesort(struct member members[30], struct member temp);
void SetColor(int color);   //��ǥ��
void jump();
void item();

void main()
{

	int i = 0;
	int flag = 0;
	int tempKey;
	int stage_max_width = 0;
	clock_t start = 0, end = 0;
	struct member members[30], temp = { "student",0 };  // �̸�, �ð� ����ü  i�� 0�ΰ� ���� ����
	int s = 0, p = 0;
	char ch;
	FILE  *fp = fopen("rank.txt", "a");
	STAGE cur_stage;
	init();
	logo();
	gotoxy(12, 12);
	printf("�̸��� �Է��ϼ��� :");
	while (1) {
		ch = getchar();
		if (ch == '\n') break;
		members[p].name[s++] = ch;
	}
	members[p].name[s] = '\0';
	start = clock();


	// ����ȭ�� 



	SetColor(GRAY);
	stageNum = 0;
	cur_stage = stage_data[stageNum];
	re_stage[0] = cur_stage; // �ǵ����� ���� �������� ���� ����
	c_pos_x = cur_stage.pos_x;
	c_pos_y = cur_stage.pos_y;

	stage_max_width = show_stage(&cur_stage, 1); // max_width ���ϰ� .. 1�� ��ȭ�� �ִ� �� ���� ��
	show_frame(stage_max_width, 1);  // ���� ����â ��� �� , maxwidth�� ���� ����Ʈ �����
	//gotoxy(c_pos_x, c_pos_y);
	int h = 0;

	while (h == 0)
	{
		if (kbhit()) //Ű���尡 hit �Ǹ�
		{
			tempKey = getch();
			if (tempKey == 224 || tempKey == 0)
			{
				tempKey = getch();// Ȯ��Ű(=����� �����̽��ٵ��) �ѹ� �� �޾��ָ� ���������� �ٲ� �� ����
				switch (tempKey)
				{
				case KEY_UP:

					//�����̵� /*���� �÷ȴµ� ���� Ŀ���� ���鼭 ��ǥ�� ����  '*'�ڸ����� ���� $�� �ø��� ����
					if (cur_stage.map[c_pos_y - 2][c_pos_x] == '@')
					{
						if (cur_stage.map[c_pos_y - 1][c_pos_x] == ' ')
						{
							cur_stage.map[c_pos_y - 2][c_pos_x] = ' ';
						}
						else if (cur_stage.map[c_pos_y - 1][c_pos_x] == '$')
						{
							cur_stage.map[c_pos_y - 2][c_pos_x] = '$';
							cur_stage.map[c_pos_y - 1][c_pos_x] = ' ';
						}
						else if (cur_stage.map[c_pos_y - 1][c_pos_x] == '*')
						{
							cur_stage.map[c_pos_y - 2][c_pos_x] = '$';
							cur_stage.map[c_pos_y - 1][c_pos_x] = ' ';
						}
						else if (cur_stage.map[c_pos_y - 1][c_pos_x] == '#')break;
						c_pos_y--;
						flag = 1;
						break;
					}

					if (cur_stage.map[c_pos_y - 1][c_pos_x] == '#')
						break; // ���̸� �̵� x
					if (cur_stage.map[c_pos_y - 1][c_pos_x] == '@')
					{
						cur_stage.map[c_pos_y - 1][c_pos_x] = ' ';
						c_pos_y--;
						flag = 1;
						break;
					}
					if (cur_stage.map[c_pos_y - 1][c_pos_x] == ' ' || cur_stage.map[c_pos_y - 1][c_pos_x] == '.')
					{
						c_pos_y--;
						flag = 1;
						break;
					} // �׳� �ƹ� ���ع� ���� �̵��� .�̶� ����� �϶�

					if (cur_stage.map[c_pos_y - 2][c_pos_x] == ' ' || cur_stage.map[c_pos_y - 2][c_pos_x] == '.') // ���ٿ��� ��ĭ ���� �����̰� ���� �̹Ƿ� ���� ������̶� �Ȱ�ħ ��, ���� ���� �ִٰ� ������ ��Ȳ�� ��.
					{
						if (cur_stage.map[c_pos_y - 2][c_pos_x] == ' ' && cur_stage.map[c_pos_y - 1][c_pos_x] == '$')
						{
							cur_stage.map[c_pos_y - 2][c_pos_x] = '$';
							cur_stage.map[c_pos_y - 1][c_pos_x] = ' ';
						}// �� �и� ���� ������ ��ĭ ���� ���� ���� ��ĭ ���� ����
						else if (cur_stage.map[c_pos_y - 2][c_pos_x] == '.' && cur_stage.map[c_pos_y - 1][c_pos_x] == '$')
						{
							cur_stage.map[c_pos_y - 2][c_pos_x] = '*'; // �� �о��µ� .�� ���� �������� *�� �ٲ��
							cur_stage.map[c_pos_y - 1][c_pos_x] = ' ';
						}
						if (cur_stage.map[c_pos_y - 1][c_pos_x] == '*')
						{

							cur_stage.map[c_pos_y - 2][c_pos_x] = '$';
							cur_stage.map[c_pos_y - 1][c_pos_x] = '.';

						}// ������ ��������� �����
						//������ �ڽ����� ������ �ٽ� �ڽ��� ����� 

						c_pos_y--; // ������ġ �� ĭ �ø���
						flag = 1;
						break;
					}
					break;
				case KEY_LEFT:      //�������� �̵�
					if (cur_stage.map[c_pos_y][c_pos_x - 2] == '@')
					{
						if (cur_stage.map[c_pos_y][c_pos_x - 1] == ' ')
						{
							cur_stage.map[c_pos_y][c_pos_x - 2] = ' ';
						}
						else if (cur_stage.map[c_pos_y][c_pos_x - 1] == '$')
						{
							cur_stage.map[c_pos_y][c_pos_x - 2] = '$';
							cur_stage.map[c_pos_y][c_pos_x - 1] = ' ';
						}
						else if (cur_stage.map[c_pos_y][c_pos_x - 1] == '#')break;
						c_pos_x--;
						flag = 1;
						break;
					}

					if (cur_stage.map[c_pos_y][c_pos_x - 1] == '@')
					{

						cur_stage.map[c_pos_y][c_pos_x - 1] = ' ';
						c_pos_x--;
						flag = 1;
						break;
					}
					if (cur_stage.map[c_pos_y][c_pos_x - 1] == '#')
						break;
					if (cur_stage.map[c_pos_y][c_pos_x - 1] == ' ' || cur_stage.map[c_pos_y][c_pos_x - 1] == '.' || cur_stage.map[c_pos_y][c_pos_x - 1] == '@')
					{
						c_pos_x--;
						flag = 1;
						break;
					}
					if (cur_stage.map[c_pos_y][c_pos_x - 2] == ' ' || cur_stage.map[c_pos_y][c_pos_x - 2] == '.')
					{
						if (cur_stage.map[c_pos_y][c_pos_x - 2] == ' ' && cur_stage.map[c_pos_y][c_pos_x - 1] == '$')
						{
							cur_stage.map[c_pos_y][c_pos_x - 2] = '$';
							cur_stage.map[c_pos_y][c_pos_x - 1] = ' ';
						}// �� �и� ���� ������ ��ĭ ���� ���� ���� ��ĭ ���� ����
						else if (cur_stage.map[c_pos_y][c_pos_x - 2] == '.' && cur_stage.map[c_pos_y][c_pos_x - 1] == '$')
						{
							cur_stage.map[c_pos_y][c_pos_x - 2] = '*'; // �� �о��µ� .�� ���� �������� *�� �ٲ��
							cur_stage.map[c_pos_y][c_pos_x - 1] = ' ';
						}
						if (cur_stage.map[c_pos_y][c_pos_x - 1] == '*')
						{

							cur_stage.map[c_pos_y][c_pos_x - 2] = '$';
							cur_stage.map[c_pos_y][c_pos_x - 1] = '.';
						}// ������ ��������� �����
						 //������ �ڽ����� ������ �ٽ� �ڽ��� �����

						c_pos_x--;
						flag = 1;
						break;
					}
					break;
				case KEY_RIGHT:
					//���������� �̵�
					if (cur_stage.map[c_pos_y][c_pos_x + 2] == '@')
					{
						if (cur_stage.map[c_pos_y][c_pos_x + 1] == ' ')
						{
							cur_stage.map[c_pos_y][c_pos_x + 2] = ' ';
						}
						else if (cur_stage.map[c_pos_y][c_pos_x + 1] == '$')
						{
							cur_stage.map[c_pos_y][c_pos_x + 2] = '$';
							cur_stage.map[c_pos_y][c_pos_x + 1] = ' ';
						}
						else if (cur_stage.map[c_pos_y][c_pos_x + 1] == '#')break;
						c_pos_x++;
						flag = 1;
						break;
					}

					if (cur_stage.map[c_pos_y][c_pos_x + 1] == '#')
						break;
					if (cur_stage.map[c_pos_y][c_pos_x + 1] == '@')
					{
						cur_stage.map[c_pos_y][c_pos_x + 1] = ' ';
						c_pos_x++;
						flag = 1;
						break;
					}
					if (cur_stage.map[c_pos_y][c_pos_x + 1] == ' ' || cur_stage.map[c_pos_y][c_pos_x + 1] == '.')
					{

						c_pos_x++;
						flag = 1;
						break;
					}
					if (cur_stage.map[c_pos_y][c_pos_x + 2] == ' ' || cur_stage.map[c_pos_y][c_pos_x + 2] == '.')
					{
						if (cur_stage.map[c_pos_y][c_pos_x + 2] == ' ' && cur_stage.map[c_pos_y][c_pos_x + 1] == '$')
						{
							cur_stage.map[c_pos_y][c_pos_x + 2] = '$';
							cur_stage.map[c_pos_y][c_pos_x + 1] = ' ';
						}// �� �и� ���� ������ ��ĭ ���� ���� ���� ��ĭ ���� ����
						else if (cur_stage.map[c_pos_y][c_pos_x + 2] == '.' && cur_stage.map[c_pos_y][c_pos_x + 1] == '$')
						{
							cur_stage.map[c_pos_y][c_pos_x + 2] = '*'; // �� �о��µ� .�� ���� �������� *�� �ٲ��
							cur_stage.map[c_pos_y][c_pos_x + 1] = ' ';
						}

						if (cur_stage.map[c_pos_y][c_pos_x + 1] == '*')
						{

							cur_stage.map[c_pos_y][c_pos_x + 1] = '.';
							cur_stage.map[c_pos_y][c_pos_x + 2] = '$';
						}// ������ ��������� �����
						 //������ �ڽ����� ������ �ٽ� �ڽ��� �����

						c_pos_x++;
						flag = 1;
						break;
					}
					break;
				case KEY_DOWN:      //�Ʒ��� �̵�
					if (cur_stage.map[c_pos_y + 2][c_pos_x] == '@')
					{
						if (cur_stage.map[c_pos_y + 1][c_pos_x] == ' ')
						{
							cur_stage.map[c_pos_y + 2][c_pos_x] = ' ';
						}
						else if (cur_stage.map[c_pos_y + 1][c_pos_x] == '$')
						{
							cur_stage.map[c_pos_y + 2][c_pos_x] = '$';
							cur_stage.map[c_pos_y + 1][c_pos_x] = ' ';
						}
						else if (cur_stage.map[c_pos_y + 1][c_pos_x] == '#')break;
						c_pos_y++;
						flag = 1;
						break;
					}

					if (cur_stage.map[c_pos_y + 1][c_pos_x] == '@')
					{
						cur_stage.map[c_pos_y + 1][c_pos_x] = ' ';
						c_pos_y++;
						flag = 1;
						break;
					}
					if (cur_stage.map[c_pos_y + 1][c_pos_x] == '#')
						break;
					if (cur_stage.map[c_pos_y + 1][c_pos_x] == ' ' || cur_stage.map[c_pos_y + 1][c_pos_x] == '.' || cur_stage.map[c_pos_y + 1][c_pos_x] == '@')
					{
						c_pos_y++;
						flag = 1;
						break;
					}
					if (cur_stage.map[c_pos_y + 2][c_pos_x] == ' ' || cur_stage.map[c_pos_y + 2][c_pos_x] == '.')
					{
						if (cur_stage.map[c_pos_y + 2][c_pos_x] == ' ' && cur_stage.map[c_pos_y + 1][c_pos_x] == '$')
						{
							cur_stage.map[c_pos_y + 2][c_pos_x] = '$';
							cur_stage.map[c_pos_y + 1][c_pos_x] = ' ';
						}// �� �и� ���� ������ ��ĭ ���� ���� ���� ��ĭ ���� ����
						else if (cur_stage.map[c_pos_y + 2][c_pos_x] == '.' && cur_stage.map[c_pos_y + 1][c_pos_x] == '$')
						{
							cur_stage.map[c_pos_y + 2][c_pos_x] = '*'; // �� �о��µ� .�� ���� �������� *�� �ٲ��
							cur_stage.map[c_pos_y + 1][c_pos_x] = ' ';
						}
						if (cur_stage.map[c_pos_y + 1][c_pos_x] == '*')
						{
							cur_stage.map[c_pos_y + 2][c_pos_x] = '$';
							cur_stage.map[c_pos_y + 1][c_pos_x] = '.'; // ������ ��������� �����
						} //������ �ڽ����� ������ �ٽ� �ڽ��� �����

						c_pos_y++;
						flag = 1;
						break;
					}
					break;
				}
			}

			else if (tempKey == 32)   //�����̽��ٸ� �������� �ٽ� ����
			{
				cur_stage = stage_data[stageNum];
				re_stage[0] = cur_stage;
				c_pos_x = cur_stage.pos_x;
				c_pos_y = cur_stage.pos_y;
				step = 1;
				flag = 1;
			}

			else if (tempKey == JUMP && item1 > 0) // ���ĺ� a �� ��
			{
				tempKey = getch();
				if (tempKey == 224 || tempKey == 0)
				{
					tempKey = getch();
					switch (tempKey)
					{
					case KEY_UP:
						if (cur_stage.map[c_pos_y - 1][c_pos_x] == '#' || cur_stage.map[c_pos_y - 1][c_pos_x] == '*' || cur_stage.map[c_pos_y - 1][c_pos_x] == '$')    //���̳� ���ڰ� ���� ����
						{
							if (cur_stage.map[c_pos_y - 2][c_pos_x] == '~' || cur_stage.map[c_pos_y - 2][c_pos_x] == '$')break;
							c_pos_y -= 2;
							flag = 1;
							break;
						}


					case KEY_LEFT:
						if (cur_stage.map[c_pos_y][c_pos_x - 1] == '#' || cur_stage.map[c_pos_y][c_pos_x - 1] == '*' || cur_stage.map[c_pos_y][c_pos_x - 1] == '$')
						{
							if (cur_stage.map[c_pos_y][c_pos_x - 2] == '~' || cur_stage.map[c_pos_y][c_pos_x - 2] == '$')break;
							c_pos_x -= 2;
							flag = 1;
							break;
						}


					case KEY_RIGHT:
						if (cur_stage.map[c_pos_y][c_pos_x + 1] == '#' || cur_stage.map[c_pos_y][c_pos_x + 1] == '*' || cur_stage.map[c_pos_y][c_pos_x + 1] == '$')
						{
							if (cur_stage.map[c_pos_y][c_pos_x + 2] == '~' || cur_stage.map[c_pos_y][c_pos_x + 2] == '$')break;
							c_pos_x += 2;
							flag = 1;
							break;
						}


					case KEY_DOWN:
						if (cur_stage.map[c_pos_y + 1][c_pos_x] == '#' || cur_stage.map[c_pos_y + 1][c_pos_x] == '*' || cur_stage.map[c_pos_y + 1][c_pos_x] == '$')
						{
							if (cur_stage.map[c_pos_y + 2][c_pos_x] == '~' || cur_stage.map[c_pos_y + 2][c_pos_x] == '$')break;
							c_pos_y += 2;
							flag = 1;
							break;
						}

					}

				}
				if (flag == 1)
				{

					re_stage[step] = cur_stage;
					re_stage[step].pos_x = c_pos_x;
					re_stage[step].pos_y = c_pos_y;
					show_stage(&cur_stage, 0);
					show_frame(stage_max_width, 0);
					flag = 0;
					step++;
				}
				fflush(stdin);
				SetColor(BLACK);
				Sleep(15);
				item1--;
			}
			// ���� �и� �ִ� �ڸ��� ���ڰ� ����� ���ڿ��� ������ ���� �����

			if (check_success(&cur_stage))
			{
				show_stage(&cur_stage, 0);
				show_success(); // �����߽��ϴ�!
				stageNum++;   //���� stage�� �Ѿ

				system("cls");
				if (stageNum != 3) {

					item();
				}

				else {
					system("cls");
				}

				if (stageNum < stageMax)
				{
					step = 0;
					cur_stage = stage_data[stageNum];
					c_pos_x = cur_stage.pos_x;
					c_pos_y = cur_stage.pos_y;
					re_stage[0] = cur_stage;
					stage_max_width = show_stage(&cur_stage, 1);
					show_frame(stage_max_width, 1);
				}
				else if (stageNum == stageMax)
				{
					h++;
				}
			}
		}
		if (flag == 1)
		{

			re_stage[step] = cur_stage;
			re_stage[step].pos_x = c_pos_x;
			re_stage[step].pos_y = c_pos_y;
			show_stage(&cur_stage, 0);
			show_frame(stage_max_width, 0);
			flag = 0;
			step++;
		}

		fflush(stdin);
		SetColor(BLACK);
		Sleep(15);
	}
	SetColor(WHITE);
	system("cls");
	gotoxy(12, 12);

	end = clock();
	members[i].time_result = (float)(end - start) / CLOCKS_PER_SEC;
	members[i].time_result = members[i].time_result - (item2 * 7);

	printf("�ҿ�ð� : %f\n\n\n\n", members[i].time_result);

	fprintf(fp, "%s %.2f\n", members[i].name, members[i].time_result);
	fclose(fp);
	system("cls");
	printf("************��ŷ************\n");
	bublesort(members, temp);
	Sleep(10000);
}

void bublesort(struct member members[30], struct member temp)
{
	FILE *fp = fopen("rank.txt", "rt");
	int i = 0;
	while (!feof(fp)) {
		fscanf(fp, "%s %f", &members[i].name, &members[i].time_result);
		i++;
	}
	fclose(fp);

	for (int k = 0; k < i; k++)
	{
		for (int p = 0; p < k; p++)
		{
			if (members[k].time_result < members[p].time_result)
			{
				temp = members[k];
				members[k] = members[p];
				members[p] = temp;
			}
		}
	}
	fp = fopen("final_rank.txt", "wt");
	for (int k = 0; k < i; k++)
	{
		fprintf(fp, "%d�� : %s  �ð� : %.2f��\n", k + 1, members[k].name, members[k].time_result);
	}
	fclose(fp);
	for (int k = 0; k < i - 1; k++)
	{
		printf("%d�� : %s  �ð� : %.2f��\n", k + 1, members[k + 1].name, members[k + 1].time_result);
	}
}
int gotoxy(int x, int y)
{
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	return 0;
}

void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void init()
{
	FILE *fp;
	char buf[50];
	int stage_seq = -1;
	int row = 0;
	int i, j;
	fp = fopen(STAGE_DATA_FILE, "r");
	while (!feof(fp))
	{
		fgets(buf, 49, fp); //49 ��������ߵ� �� ������.. ~�߰��ϸ�
		if (buf[0] == ';')   //���������� ����
		{
			for (i = 0; i < 20; i++)   //������ġ ã��
			{
				for (j = 0; j < 20; j++)
				{
					if (stage_data[stage_seq].map[i][j] == '@')
					{
						stage_data[stage_seq].pos_y = i;
						stage_data[stage_seq].pos_x = j;
						i = 20;   //���� Ż��
						break; // ��ó������ -1�̴ϱ� �׳� ��ŵ
						// ���پ� ���� �ڿ� üũ 
					}

				}
			}
			row = 0;
			stage_seq++;
			continue;
		}
		if (stage_seq >= 0 && buf[0] != '\n')
		{
			strncpy(stage_data[stage_seq].map[row], buf, strlen(buf) - 1);
		}
		row++; //  stage�� 0�� ���¿��� buf�� ;�������� �� ���� ���پ� stage_data[i]�� �־��ִ� ���� buf�� ��� �ʱ�ȭ�Ǵ� �� ���� ������ 
	}


}
void item()
{
	srand(time(NULL)); //seed�����Ͽ� ����ð��� �̿��� �Ϻ��� ���� ���� 
	int num = rand() % 4 + 1; //�������� 1���� 3���� ���� 
	int choose; //�Է��� ���� Ƚ���� ���� ���� ���� ���� 
	int x = 5; //Ÿ��Ʋȭ���� ǥ�õǴ� x��ǥ 
	int y = 4; //Ÿ��Ʋȭ���� ǥ�õǴ� y��ǥ 
	gotoxy(x, y + 0); printf("������   ������   ������");
	gotoxy(x, y + 1); printf("��      ��   ��      ��   ��      ��");
	gotoxy(x, y + 2); printf("��   1  ��   ��   2  ��   ��   3  ��");
	gotoxy(x, y + 3); printf("��      ��   ��      ��   ��      ��");
	gotoxy(x, y + 4); printf("������   ������   ������");
	SetColor(WHITE);
	gotoxy(x + 40, y + 0); printf("���� : ���� �����ؼ� �Ѿ�� ������");
	gotoxy(x + 40, y + 2); printf("����������� : ���� �ð� ��Ͽ��� 7�ʸ� ��dream");
	gotoxy(x + 40, y + 4); printf("��: ���� ���ݾ�");

	gotoxy(x, y + 6); printf("�������� �̾��ּ���! : ");

	scanf("%d", &choose);
	if (num == 1) {
		item1++;
		gotoxy(x, y + 9); printf("%d�� ������ '����' ��÷! ", choose);
		gotoxy(x, y + 11); printf("���� ���� �Ѿ��! ��ĭ�� �ȵ�! �̰� �ɸ� ����� A+ ���� �ڰݵ� �ֱ���!");
	}
	else if (num == 2) {
		item2++;
		gotoxy(x, y + 9); printf("%d�� ������ '���� ��� ����' ��÷! ", choose);
		gotoxy(x, y + 11); printf("����� ���� ������ ��������! �������� �䱸�� ����! �̰� �ɸ� ����� A+ ���� �ڰݵ� �ֱ���! ");
	}
	else if (num == 3) {
		item3++;
		gotoxy(x, y + 9); printf("%d�� ������ ��! ", choose);
		gotoxy(x, y + 11); printf("����! 1/3�� Ȯ���� ���� ���! �̰� �ɸ� ����� A+ ���� �ڰݵ� �ֱ���!");
	}
	else
	{
		item3++;
		gotoxy(x, y + 9); printf("%d�� ������ ��! ", choose);
		gotoxy(x, y + 11); printf("����! 1/3�� Ȯ���� ���� ���! �̰� �ɸ� ����� A+ ���� �ڰݵ� �ֱ���!");

	}
	SetColor(YELLOW);
	gotoxy(x, y + 13); printf("���  ���  ����������");
	gotoxy(x, y + 14); printf("��      ��  ���� : %d ��", item1);
	gotoxy(x, y + 15); printf("�� wow! ��  ����������� : %d ��", item2);
	gotoxy(x, y + 16); printf("��      ��  �� : %d ��", item3);
	gotoxy(x, y + 17); printf("������");
	Sleep(5000);
}
void logo()
{
	gotoxy(0, 0);
	int i;
	SetColor(WHITE * 16);
	gotoxy(3, 2);
	printf("                                                                                  ");
	gotoxy(3, 10);
	printf("                                                                                  ");
	for (i = 3; i < 10; i++) {
		gotoxy(3, i);
		printf("  ");

		gotoxy(83, i);
		printf("  ");

	}
	Sleep(50);

	SetColor(RED * 16);
	//ù°��
	gotoxy(5, 3);
	printf("        ");
	gotoxy(15, 3);
	printf("  ");
	gotoxy(21, 3);
	printf("  ");
	gotoxy(25, 3);
	printf("        ");
	gotoxy(35, 3);
	printf("  ");
	gotoxy(41, 3);
	printf("  ");

	gotoxy(45, 3);
	printf("        ");
	gotoxy(55, 3);
	printf("  ");
	gotoxy(61, 3);
	printf("  ");
	gotoxy(65, 3);
	printf("        ");
	gotoxy(75, 3);
	printf("  ");
	gotoxy(81, 3);
	printf("  ");

	Sleep(50);
	//��°��
	SetColor(YELLOW * 16);
	gotoxy(5, 4);
	printf("  ");
	gotoxy(11, 4);
	printf("  ");
	gotoxy(15, 4);
	printf("  ");
	gotoxy(21, 4);
	printf("  ");
	gotoxy(25, 4);
	printf("  ");
	gotoxy(35, 4);
	printf("  ");
	gotoxy(41, 4);
	printf("  ");

	gotoxy(45, 4);
	printf("  ");
	gotoxy(55, 4);
	printf("  ");
	gotoxy(51, 4);
	printf("  ");
	gotoxy(61, 4);
	printf("  ");
	gotoxy(65, 4);
	printf("  ");
	gotoxy(75, 4);
	printf("  ");
	gotoxy(81, 4);
	printf("  ");
	Sleep(50);
	//��°��
	SetColor(GREEN * 16);
	gotoxy(5, 5);
	printf("  ");
	gotoxy(11, 5);
	printf("  ");
	gotoxy(15, 5);
	printf("  ");
	gotoxy(21, 5);
	printf("  ");
	gotoxy(25, 5);
	printf("  ");
	gotoxy(35, 5);
	printf("  ");
	gotoxy(41, 5);
	printf("  ");

	gotoxy(45, 5);
	printf("  ");
	gotoxy(55, 5);
	printf("  ");
	gotoxy(51, 5);
	printf("  ");
	gotoxy(61, 5);
	printf("  ");
	gotoxy(65, 5);
	printf("  ");
	gotoxy(75, 5);
	printf("  ");
	gotoxy(81, 5);
	printf("  ");

	Sleep(50);
	//��°��
	SetColor(DARK_SKY_BLUE * 16);
	gotoxy(5, 6);
	printf("        ");
	gotoxy(15, 6);
	printf("  ");
	gotoxy(21, 6);
	printf("  ");
	gotoxy(25, 6);
	printf("        ");
	gotoxy(35, 6);
	printf("        ");

	gotoxy(45, 6);
	printf("        ");
	gotoxy(55, 6);
	printf("  ");
	gotoxy(61, 6);
	printf("  ");
	gotoxy(65, 6);
	printf("        ");
	gotoxy(75, 6);
	printf("        ");
	Sleep(50);
	//�ټ�°��
	SetColor(BLUE * 16);
	gotoxy(5, 7);
	printf("  ");
	gotoxy(15, 7);
	printf("  ");
	gotoxy(21, 7);
	printf("  ");
	gotoxy(31, 7);
	printf("  ");
	gotoxy(35, 7);
	printf("  ");
	gotoxy(41, 7);
	printf("  ");

	gotoxy(45, 7);
	printf("  ");
	gotoxy(55, 7);
	printf("  ");
	gotoxy(61, 7);
	printf("  ");
	gotoxy(71, 7);
	printf("  ");
	gotoxy(75, 7);
	printf("  ");
	gotoxy(81, 7);
	printf("  ");
	Sleep(50);
	//����°��
	SetColor(VOILET * 16);
	gotoxy(5, 8);
	printf("  ");
	gotoxy(15, 8);
	printf("  ");
	gotoxy(21, 8);
	printf("  ");
	gotoxy(31, 8);
	printf("  ");
	gotoxy(35, 8);
	printf("  ");
	gotoxy(41, 8);
	printf("  ");

	gotoxy(45, 8);
	printf("  ");
	gotoxy(55, 8);
	printf("  ");
	gotoxy(61, 8);
	printf("  ");
	gotoxy(71, 8);
	printf("  ");
	gotoxy(75, 8);
	printf("  ");
	gotoxy(81, 8);
	printf("  ");
	Sleep(50);
	//�ϰ�°��
	SetColor(DARK_VOILET * 16);
	gotoxy(5, 9);
	printf("  ");
	gotoxy(15, 9);
	printf("        ");
	gotoxy(25, 9);
	printf("        ");
	gotoxy(35, 9);
	printf("  ");
	gotoxy(41, 9);
	printf("  ");

	gotoxy(45, 9);
	printf("  ");
	gotoxy(55, 9);
	printf("        ");
	gotoxy(65, 9);
	printf("        ");
	gotoxy(75, 9);
	printf("  ");
	gotoxy(81, 9);
	printf("  ");
	Sleep(50);

	SetColor(WHITE);
	gotoxy(18, 15);
	printf(" [����Ʈ����� ������Ʈ]");
	gotoxy(22, 17);
	SetColor(DARK_YELLOW);
	printf(" <FOEVERYOUNG��>");
	SetColor(GRAY);
	gotoxy(22, 19);
	printf(" 2018707034 ������");
	gotoxy(22, 21);
	printf(" 2017707029 �̽°�");
	gotoxy(22, 23);
	printf(" 2016707079 �ϻ�õ");

	SetColor(DARK_RED);
	gotoxy(17, 15);
	printf("��");
	gotoxy(17, 17);
	printf("��");
	gotoxy(17, 19);
	printf("��");
	gotoxy(17, 21);
	printf("��");
	gotoxy(17, 23);
	printf("��");
	gotoxy(44, 15);
	printf("��");
	gotoxy(44, 17);
	printf("��");
	gotoxy(44, 19);
	printf("��");
	gotoxy(44, 21);
	printf("��");
	gotoxy(44, 23);
	printf("��");
	SetColor(YELLOW * 16 + RED);
	gotoxy(16, 25);
	printf("                                 ");
	gotoxy(16, 26);
	printf("  �ƹ��ų� ������ �����Ѵ�(>_<)  ");
	gotoxy(16, 27);
	printf("                                 ");
	gotoxy(18, 30);

	fflush(stdin);
	Sleep(1000);
	getche();
	system("cls");
}


int show_stage(STAGE *p_stage, int all_load)
{
	int i, j;
	int max_width = 0;
	if (all_load == 1)
		system("cls");

	for (i = 0; i < 20; i++)
	{
		printf("  ");
		for (j = 0; j < 20; j++)
		{

			if (i == c_pos_y && j == c_pos_x)
			{
				gotoxy(j * 2 + 2, i + 2);
				SetColor(SKY_BLUE);
				printf("��");
			}
			else {
				switch (p_stage->map[i][j])
				{
				case '#':   //���϶�
					if (all_load == 1)
					{
						gotoxy(j * 2 + 2, i + 2);
						SetColor(WHITE);
						printf("��");

						if (j > max_width)
							max_width = j;
					}
					break;
				case '@':
					gotoxy(j * 2 + 2, i + 2);
					printf("  ");
					break;
				case '.':   //���ڸ� ���� ���(���� �����)
					SetColor(WHITE);
					gotoxy(j * 2 + 2, i + 2);
					printf("��");
					break;
				case '$':   //����
					SetColor(RED);
					gotoxy(j * 2 + 2, i + 2);
					printf("��");
					break;
					//case '+':
				case '*':   //���ڸ� ���� ���(���� ���ڰ� ���� ����)
					SetColor(GREEN);
					gotoxy(j * 2 + 2, i + 2);
					printf("��");
					break;
				case 0:
					if (all_load == 1)
					{
						gotoxy(j * 2 + 2, i + 2);
						printf("  ");
					}
					break;
				case ' ':   //����
					gotoxy(j * 2 + 2, i + 2);
					printf("  ");
					break;
				}
			}
		}
		printf("\n");
	}
	return max_width * 2 + 5;
}

int check_success(STAGE *p_stage)
{
	int i, j;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (p_stage->map[i][j] == '.' || p_stage->map[i][j] == '$')   //���̳� �󱸸��� ������
				return 0; //����
		}
	}
	return 1; //����
}

int show_frame(int start_col, int all_load)
{
	if (all_load == 1)
	{
		SetColor(WHITE);
		gotoxy(start_col, 1);
		printf("������������������������������������");
		gotoxy(start_col, 2);
		printf("��   ������б�   ��");
		gotoxy(start_col, 3);
		printf("�� ������Ű��а� ��");
		gotoxy(start_col, 4);
		printf("�� Foreveryoung�� ��");
		gotoxy(start_col, 5);
		printf("������������������������������������");
		gotoxy(start_col, 6);
		printf("�� Stage          ��");
		gotoxy(start_col, 7);
		printf("��                ��");
		gotoxy(start_col, 8);
		printf("�� Step  :        ��");
		gotoxy(start_col, 9);
		printf("������������������������������������");
		gotoxy(start_col, 10);
		printf("��     ���۹�     ��");
		gotoxy(start_col, 11);
		printf("��                ��");
		gotoxy(start_col, 12);
		printf("������� :����Ű��");
		gotoxy(start_col, 13);
		printf("��                ��");
		gotoxy(start_col, 14);
		printf("�� Space: �ٽý��ۦ�");
		gotoxy(start_col, 15);
		printf("��                ��");
		gotoxy(start_col, 16);
		printf("������������������������������������");
		SetColor(RED);
		gotoxy(start_col + 2, 2);
		printf("��");
		gotoxy(start_col + 14, 2);
		printf("��");
	}
	SetColor(GREEN);
	gotoxy(start_col + 9, 6);
	printf("%3d/%-3d", stageNum + 1, stageMax);
	SetColor(YELLOW);
	gotoxy(start_col + 12, 8);
	printf("%-4d", step);
	gotoxy(0, 0);
	return 0;
}


int show_success()
{
	SetColor(DARK_YELLOW);
	gotoxy(10, 6);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~");
	gotoxy(10, 7);
	printf(" ��   STAGE CLEAR !!  ��");
	gotoxy(10, 8);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~");


	Sleep(3000);
	return 0;
}