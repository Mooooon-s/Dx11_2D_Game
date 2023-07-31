#pragma once
#include <list>
#include <map>
#include <iostream>

#include "MnEnums.h"

namespace Mn
{
		class Node
		{
		public:
			Node();
			virtual ~Node();
		public:
			virtual enums::eBTState Run() = 0;
		};
}