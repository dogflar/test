#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include "strategy.h"

using namespace std;

void on_login(){}

void on_error(int ec, const char *lp){}

//处理分时行情事件
void on_bar(Bar *bar){}

//处理委托回报事件
void on_execrpt(ExecRpt *res){}

void on_order_status(Order *res){}

//委托回报函数类型(回调接口: 订单接受)
void on_order_new(Order *res){}

//委托回报函数类型(回调接口：订单完全成交)
void on_order_filled(Order *res){}

//委托回报函数类型(回调接口：订单部分成交)
void on_order_partiall_filled(Order *res){}

//委托回报函数类型(回调接口：订单停止)
void on_order_stop_executed(Order *res){}

//委托回报函数类型(回调接口：订单撤销成功)
void on_order_canceled(Order *res){}

//委托回报函数类型(回调接口：撤单失败)
void on_order_cancel_rejected(ExecRpt *res){}

int main(int argc, char *[])
{
	int ret;

	//初始化策略,根据配置文件
	ret = strategy_init_with_config("stock1.ini");

	if (ret)
	{
		printf("init got error: %d\n", ret);
		system("pause");
		return ret;
	}

	// 设置事件回调函数
	gm_td_set_login_callback(on_login);
	gm_td_set_error_callback(on_error);
	gm_md_set_bar_callback(on_bar);
	gm_td_set_execrpt_callback(on_execrpt);
	gm_td_set_order_status_callback(on_order_status);
	gm_td_set_order_new_callback(on_order_new);
	gm_td_set_order_filled_callback(on_order_filled);
	gm_td_set_order_partially_filled_callback(on_order_partiall_filled);
	gm_td_set_order_stop_executed_callback(on_order_stop_executed);
	gm_td_set_order_cancelled_callback(on_order_canceled);
	gm_td_set_order_cancel_rejected_callback(on_order_cancel_rejected);


	printf("策略起动成功! %s\n", gm_strerror(ret));

	// 执行并等待策略运行结束
	ret = gm_run();

	if (ret)
	{
		cout << "error:" << ret << " msg:" << gm_strerror(ret) << endl;
		getchar();
	}

	return 0;
}