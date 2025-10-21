#pragma once
#include <iostream>
#include "clsUser.h"

// This file contains a global user of all system after a valid login process

static clsUser CurrentUser = clsUser::Find("", "");