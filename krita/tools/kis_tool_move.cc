/*
 *  Copyright (c) 1999 Matthias Elter  <me@kde.org>
 *                1999 Michael Koch    <koch@kde.org>
 *                2002 Patrick Julien <freak@codepimps.org>
 *                2004 Boudewijn Rempt <boud@valdyas.org>
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

#include <stdlib.h>
#include <qpoint.h>
#include <kaction.h>
#include <klocale.h>
#include <koColor.h>
#include "kis_canvas_subject.h"
#include "kis_cursor.h"
#include "kis_image.h"
#include "kis_paint_device.h"
#include "kis_tool_move.h"
#include "kis_tool_move.moc"
#include "kis_button_press_event.h"
#include "kis_button_release_event.h"
#include "kis_move_event.h"
#include "kis_selection.h"
#include "kis_selection_manager.h"

KisToolMove::KisToolMove()
{
	setName("tool_move");
	m_subject = 0;
	setCursor(KisCursor::moveCursor());
}

KisToolMove::~KisToolMove()
{
}

void KisToolMove::update(KisCanvasSubject *subject)
{
	m_subject = subject;
	m_strategy.reset(subject);
	super::update(subject);
}

void KisToolMove::buttonPress(KisButtonPressEvent *e)
{
	if (m_subject && e -> button() == QMouseEvent::LeftButton) {
		QPoint pos = e -> pos().floorQPoint();
		KisImageSP img = m_subject -> currentImg();
		KisLayerSP dev;

		if (!img || !(dev = img -> activeLayer()))
			return;

		if (dev -> hasSelection()) {
			QRect r = dev -> selection() -> selectedRect();

			if (r.contains(pos)) {
				// XXX: Put in undo macro
				m_subject -> selectionManager() -> copy();
				m_subject -> selectionManager() -> clear();
				dev = m_subject -> selectionManager() -> paste();
				if (dev) {
					dev -> move(r.x(), r.y());
					img -> activate(dev);
					m_strategy.startDrag(pos);
				}
			}
		}
		else if (dev -> contains(pos)) {
			m_strategy.startDrag(pos);
		}
	}
}

void KisToolMove::move(KisMoveEvent *e)
{
	if (m_subject)
		m_strategy.drag(e -> pos().floorQPoint());
}

void KisToolMove::buttonRelease(KisButtonReleaseEvent *e)
{
	if (m_subject && e -> button() == QMouseEvent::LeftButton)
		m_strategy.endDrag(e -> pos().floorQPoint());
}

void KisToolMove::setup(KActionCollection *collection)
{
	m_action = static_cast<KRadioAction *>(collection -> action(name()));

	if (m_action == 0) {
		m_action = new KRadioAction(i18n("Tool &Move"), 
					    "move", 
					    Qt::SHIFT+Qt::Key_V, 
					    this,
					    SLOT(activate()),
					    collection,
					    name());
		m_action -> setExclusiveGroup("tools");
		m_ownAction = true;
	}
}

