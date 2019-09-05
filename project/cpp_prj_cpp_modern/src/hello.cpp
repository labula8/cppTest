

#include "common.h"
#include "t_log.h"
#include "t_lambda.h"
#include "t_nullptr.h"
//#include "t_constexpr.h"
#include "t_if_switch.h"
#include "t_initializer_list.h"
#include "t_structured_binding.h"

using namespace std;

void t_test() 
{
    //t_log();
    //t_lambda_0();
    //t_nullptr_0();
    //t_constexpr();
    //t_if_switch();
    //t_initializer_list();
    t_structured_binding();
}

int main()
{	
	cout << "hello!" << endl;

	t_test();

	return 0;
}
