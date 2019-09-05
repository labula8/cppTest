#pragma once

#include <iostream>

#define SAFE_DELETE(x) {if (x) { delete (x); (x) = NULL; }}
#define SAFE_DELETE_VEC(x) {if (x) { delete [](x); (x) = NULL; }}
