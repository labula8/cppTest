#pragma once

class DynamicMath
{
public:
	__declspec(dllexport) DynamicMath(void);
	__declspec(dllexport) ~DynamicMath(void);

	static __declspec(dllexport) double add(double a, double b);

	__declspec(dllexport) void show();
};
