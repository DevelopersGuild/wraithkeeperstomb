#ifndef PATHS_H
#define PATHS_H

#include <string>

/*************************************************
 *	resourcePath
 *
 *	 Gets the path that the assets folder is in.
 *   Needed for Mac support.
 *
 *************************************************/
std::string resourcePath();

/*************************************************
 *	savePath
 *
 *	 Gets the path that that saves go in.
 *   Needed for Mac support.
 *
 *************************************************/
std::string savePath();

#endif
