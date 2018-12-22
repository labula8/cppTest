
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum Q_STATE
{
	Q1_STATE = 1,
	Q2_STATE = 2,
	Q3_STATE = 3
};

enum D_STATE
{
	HOLD = 0,
	LEFT = 1,
	RIGHT = 2
};

enum VALUE
{
	ZERO = 0,
	ONE = 1
};

typedef struct _stCMD
{
	enum Q_STATE s_state;
	enum VALUE r_alue;	//read value
	enum VALUE w_value;	//write value
	enum D_STATE d_state;
	enum Q_STATE n_state;

}stCMD;

int todo();

void show_array(int array[], int array_size);

void array_high_left(int array[], int array_size);

void show_array_high_left(int array[], int array_size);

bool ten2binary(int b_array[], int max_binary_array_size, const int num);

int init(int array[], const int size, const int pos_start, const int cur_value);

int init_cmd();

void show_one_cmd(const stCMD cmd);
void show_cmds(const stCMD cmd[], const int cmd_size);

void tu_ring_test(int array[], const int size, const int pos_start, const stCMD cmd[], const int cmd_size, int array_out[]);
int get_cmd(const stCMD cmd[], const int cmd_size, const int cur_state, const int cur_value);