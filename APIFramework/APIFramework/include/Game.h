#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>

using namespace std;

#include "resource.h"
#include "Macro.h"
#include "Types.h"
#include "Flag.h"

template<typename T>
void Safe_Delete_VecList( T& p )
{
	typename T::iterator iter;
	typename T::iterator iterEnd = p.end();

	for( iter = p.begin(); iter != iterEnd; ++iter )
	{
		SAFE_DELETE( (*iter) );
	}

	p.clear();
}
