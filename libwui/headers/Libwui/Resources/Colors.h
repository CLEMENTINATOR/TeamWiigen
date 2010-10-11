/*
 * Colors.h
 *
 *  Created on: 11 oct. 2010
 *      Author: Clément
 */

#ifndef COLORS_H_
#define COLORS_H_

#include "../FreeTypeGX.h"

namespace Libwui
{
namespace Resources
{
class Colors
{
public:
	static GXColor Black();
	static GXColor Red();
	static GXColor Blue();
	static GXColor Green();
	static GXColor Magenta();
	static GXColor Cyan();
	static GXColor Yellow();
	static GXColor White();
	static GXColor FromRGBA(int r, int g, int b, int a = 255);

};
}
}
#endif /* COLORS_H_ */
