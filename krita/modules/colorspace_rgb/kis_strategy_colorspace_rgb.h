/*
 *  Copyright (c) 2002 Patrick Julien  <freak@codepimps.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#ifndef KIS_STRATEGY_COLORSPACE_RGB_H_
#define KIS_STRATEGY_COLORSPACE_RGB_H_

#include <qcolor.h>

#include <koColor.h>

#include "kis_global.h"
#include "kis_strategy_colorspace.h"
#include "kis_pixel.h"

const PIXELTYPE PIXEL_BLUE = 0;
const PIXELTYPE PIXEL_GREEN = 1;
const PIXELTYPE PIXEL_RED = 2;
const PIXELTYPE PIXEL_ALPHA = 3;

class KisStrategyColorSpaceRGB : public KisStrategyColorSpace {
public:
	KisStrategyColorSpaceRGB();
	virtual ~KisStrategyColorSpaceRGB();

public:
	virtual void nativeColor(const KoColor& c, QUANTUM *dst);
	virtual void nativeColor(const KoColor& c, QUANTUM opacity, QUANTUM *dst);

	virtual void toKoColor(const QUANTUM *src, KoColor *c);
	virtual void toKoColor(const QUANTUM *src, KoColor *c, QUANTUM *opacity);

	virtual KisPixelRO toKisPixelRO(QUANTUM *src) { return KisPixelRO (src, src + PIXEL_ALPHA); }
	virtual KisPixel toKisPixel(QUANTUM *src) { return KisPixel (src, src + PIXEL_ALPHA); }

	virtual KisChannelInfo* channels() const;
	virtual bool alpha() const;
	virtual Q_INT32 depth() const;
	virtual Q_INT32 nColorChannels() const;
	
	virtual QImage convertToQImage(const QUANTUM *data, Q_INT32 width, Q_INT32 height, Q_INT32 stride) const;

protected:

	virtual void bitBlt(Q_INT32 stride,
			    QUANTUM *dst, 
			    Q_INT32 dststride,
			    QUANTUM *src, 
			    Q_INT32 srcstride,
			    QUANTUM opacity,
			    Q_INT32 rows, 
			    Q_INT32 cols, 
			    CompositeOp op);

private:
	static KisChannelInfo channelInfo[4];
};

#endif // KIS_STRATEGY_COLORSPACE_RGB_H_
