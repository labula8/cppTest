
#include "todo.h"

/**
* TODO:
* 计算机原理与C语言，公开课，北大
* 数学：
* 集合，
* 罗素悖论
* 哥德尔，哥德尔不完备性定理
* 可计算问题，计算模型
* 图灵，图灵机，ACM图灵奖，图灵测试，机器能思考吗
* 简单图灵机
*/

/*
*0.初始化
    存储带，初始值
    游标头
1.查表操作

a.条件（查指令表）
    1.指令当前状态
    2.读操作
b.动作（按指令表操作）
    3.写操作
    4.移动操作（维持操作）
    5.切换指令（查指令表）-指令陷入循环，表示停机（计算完毕），结果输出

加法演示3+4

指令集合
q1,1,1,R,q1
q1,0,1,R,q2
q2,1,1,R,q2
q2,0,0,L,q3
q3,1,0,H,q3
q3,0,0,H,q3

指令说明：
第1列：q1~q3,指令状态
第2列：0,1,当前状态
第3列：0,1,写入状态
第4列：RLH,移动操作（R-right，L-left,H-Hold）
第6列：q1~q3,下一指令状态
*/

void show_array(int array[], int array_size)
{
	for (int i = 0; i < array_size; i++)
	{
		printf("%d", array[i]);
	}
	printf("\n array_size=%d \n", array_size);
}

void array_high_left(int array[], int array_size)
{
	if (array_size > 100)
	{
		printf("array_size too big, array_size = %d \n", array_size);
		return;
	}
	int array_temp[100] = { 0 };
	for (int i = 0; i < array_size; i++)
	{
		array_temp[i] = array[i];
	}
	//memcpy(array_temp, array, array_size);

	bool high_start = false;
	int j = 0;
	for (int i = array_size - 1; i >= 0; i--)
	{
		if (array_temp[i] != 0)
		{
			high_start = true;
		}
		if (high_start)
		{
			//printf("%d", array_temp[i]);
			array[j] = array_temp[i];
			j++;
		}
	}
	//printf("\n array_size=%d \n", array_size);

	show_array(array, array_size);
}

void show_array_high_left(int array[], int array_size)
{
	bool high_start = false;
	for (int i = array_size-1; i >= 0; i--)
	{
		if (array[i] != 0)
		{
			high_start = true;
		}
		if (high_start)
		{
			printf("%d", array[i]);
		}
	}
	printf("\n array_size=%d \n", array_size);
}

/*
10进制转2进制，1024以内
5 转成 101
*/
bool ten2binary(int b_array[], int max_binary_array_size, const int num)
{
	int yu_shu = 0;
	int chu_shu = 0;
	int num_temp = num;
	for (int i = 0; i < max_binary_array_size; i++)
	{
		yu_shu = num_temp % 2;  //取2的余数
		chu_shu = num_temp / 2;  //取被2整除的数
		num_temp = chu_shu;    //将得到的商赋给变量variable,用来下次求%，获得下一个数

		b_array[i] = yu_shu;//将余数存放在数组中
	}
	show_array(b_array, max_binary_array_size);
	//show_array_high_left(b_array, max_binary_array_size);
	array_high_left(b_array, max_binary_array_size);
	show_array(b_array, max_binary_array_size);
	//show_array_high_left(b_array, max_binary_array_size);

	return true;
}

/*
0.初始化
存储带，初始值
游标头
*/
int init(int array[], const int size, const int pos_start, const int cur_value)
{
	int max_binary_array_size = 16;
	int b_array[16] = { 0 };

	ten2binary(b_array, max_binary_array_size, cur_value);

	for (int i = pos_start; i < pos_start+max_binary_array_size; i++)
	{
		array[i] = b_array[i- pos_start];
	}
	show_array(array, size);

	return 0;
}

void show_one_cmd(const stCMD cmd)
{
	printf("%d,%d,%d,%d,%d \n", 
		cmd.s_state, 
		cmd.r_alue, 
		cmd.w_value, 
		cmd.d_state, 
		cmd.n_state);
}

void show_cmds(const stCMD cmd[], const int cmd_size)
{
	for (int i = 0; i < cmd_size; i++)
	{
		show_one_cmd(cmd[i]);
	}
}

int init_cmd(stCMD cmd[])
{

	show_cmds(cmd, 6);
	return 0;
}

/*
a.条件（查指令表）
	1.指令当前状态
	2.读操作
b.动作（按指令表操作）
	3.写操作
	4.移动操作（维持操作）
	5.切换指令（查指令表）-指令陷入循环，表示停机（计算完毕），结果输出
*/
void tu_ring_test(int array[], const int size, const int pos_start, const stCMD cmd[], const int cmd_size, int array_out[])
{
	int cur_cmd_index = 0;
	enum Q_STATE cur_state = cmd[0].s_state;
	enum Q_STATE next_state = cmd[0].n_state;
	enum D_STATE d_state = cmd[0].d_state;
	enum VALUE write_value = cmd[0].w_value;

	
	int cmd_stop_count = 0;//指令停止计数器
	int i = pos_start;
	do 
	{
		printf("STATE, i=%d \n", i);//游标

		//读操作, 指令当前状态, 查指令表
		int index = get_cmd(cmd, cmd_size, cur_state, array[i]);
		if (index <  0)
		{
			printf("error, array[%d]=%d \n", i, array[i]);
		}
		else
		{
			if ((HOLD == cmd[index].d_state) && (cur_cmd_index == index))
			{
				cmd_stop_count++;
			}
			
			if (index < cmd_size)
			{
				//3.写操作
				array_out[i] = cmd[index].w_value;
				//4.移动操作（维持操作）
				if (HOLD == cmd[index].d_state)
				{
					printf("HOLD, i=%d \n", i);//游标保持不动
				}
				else if (LEFT == cmd[index].d_state)
				{
					i--;
					printf("LEFT, i=%d \n", i);//游标left
				}
				else if (RIGHT == cmd[index].d_state)
				{
					i++;
					printf("RIGHT, i=%d \n", i);//游标right
				}

				//5.切换指令（查指令表） - 指令陷入循环，表示停机（计算完毕），结果输出
				cur_state = cmd[index].n_state;
				cur_cmd_index = index;

				if (HOLD != cmd[index].d_state)
				{
					show_array(array_out, size);
				}
			}
		}
	} while (i < size && cmd_stop_count < 2);

	return;
}

int get_cmd(const stCMD cmd[], const int cmd_size, const int cur_state, const int cur_value)
{
	bool find_cmd = false;
	for (int i = 0; i < cmd_size; i++)
	{
		if ((cmd[i].s_state == cur_state) && (cmd[i].r_alue == cur_value))
		{
			find_cmd = true;
			return i;
		}
	}

	printf("error, cur_state=%d, cur_value=%d \n", cur_state, cur_value);
	return -1;
}

int todo()
{
	printf("hello, todo\n");
	const int max_array_size = 200;
	int array[200] = { 0 };
	int array_out[200] = { 0 };
	int pos_start = 100;
	int cur_value = 235;// 247;

	stCMD cmd[6] = {
		{ Q1_STATE, ONE,	ONE, RIGHT, Q1_STATE },
		{ Q1_STATE, ZERO,	ONE, RIGHT, Q2_STATE },
		{ Q2_STATE, ONE,	ONE, RIGHT, Q2_STATE },
		{ Q2_STATE, ZERO,	ZERO, LEFT, Q3_STATE },
		{ Q3_STATE, ONE,	ZERO, HOLD, Q3_STATE },
		{ Q3_STATE, ZERO,	ZERO, HOLD, Q3_STATE },
	};

	init(array, max_array_size, pos_start, cur_value);
	init_cmd(cmd);

	tu_ring_test(array, max_array_size, pos_start, cmd, 6, array_out);

	show_array(array_out, max_array_size);
	
	return 0;
}