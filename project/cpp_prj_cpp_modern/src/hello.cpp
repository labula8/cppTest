

#include "common.h"
#include "t_log.h"
#include "t_lambda.h"
#include "t_nullptr.h"
#include "t_constexpr.h"

using namespace std;

void t_test() 
{
    //t_log();
    //t_lambda_0();
    //t_nullptr_0();
    t_constexpr();
}

int main()
{	
	cout << "hello!" << endl;

	t_test();

	return 0;
}
