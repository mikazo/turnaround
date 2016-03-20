#ifndef _XML_H_
#define _XML_H_

#include <string>
#include <vector>

#include "task.h"

bool ParseXML( const std::string& filename, std::vector<Task>& tasks );

#endif

