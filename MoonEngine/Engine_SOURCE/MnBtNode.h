#pragma once
#include <list>
#include <map>
#include <iostream>

#include "MnEnums.h"

#include "MnAudioClip.h"
#include "MnResources.h"

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