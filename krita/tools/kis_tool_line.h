/*
 *  kis_tool_line.h - part of Krayon
 *
 *  Copyright (c) 2000 John Califf <jcaliff@comuzone.net>
 *  Copyright (c) 2002 Patrick Julien <freak@codepimps.org>
 *  Copyright (c) 2004 Boudewijn Rempt <boud@valdyas.org>
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

#ifndef KIS_TOOL_LINE_H_
#define KIS_TOOL_LINE_H_

#include "kis_tool_paint.h"

#include "kis_global.h"
#include "kis_types.h"
#include "kis_tool_factory.h"

class IntegerWidget;
class KisBrush;
class KisCmbComposite;
class KisPainter;

class QLabel;
class QPoint;
class QWidget;


class KisToolLine : public KisToolPaint {

	Q_OBJECT
	typedef KisToolPaint super;

 public:
	KisToolLine();
	virtual ~KisToolLine();

	virtual void setup(KActionCollection *collection);
	virtual void update(KisCanvasSubject *subject);

	virtual void buttonPress(KisButtonPressEvent *event);
	virtual void move(KisMoveEvent *event);
	virtual void buttonRelease(KisButtonReleaseEvent *event);

	virtual void paint(QPainter& gc);
	virtual void paint(QPainter& gc, const QRect& rc);


 private:
	void paintLine();
	void paintLine(QPainter& gc, const QRect& rc);

	KisPoint straightLine(KisPoint point);


	bool m_dragging;

	KisPoint m_startPos;
	KisPoint m_endPos;

	KisCanvasSubject *m_subject;
	KisImageSP m_currentImage;
	KisPainter *m_painter;

	QUANTUM m_opacity;
	CompositeOp m_compositeOp;
};


class KisToolLineFactory : public KisToolFactory {
	typedef KisToolFactory super;
public:
	KisToolLineFactory(KActionCollection * ac) : super(ac) {};
	virtual ~KisToolLineFactory(){};
	
	virtual KisTool * createTool() { KisTool * t =  new KisToolLine(); t -> setup(m_actionCollection); return t; }
	virtual QString name() { return i18n("Line tool"); }
};




#endif //KIS_TOOL_LINE_H_

