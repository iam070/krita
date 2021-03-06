/*
 *  Copyright (c) 2011 Cyrille Berger <cberger@cberger.net>
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
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#ifndef KIS_RECORDED_ACTION_CREATOR
#define KIS_RECORDED_ACTION_CREATOR
#include <QWidget>

class KisRecordedAction;

class KisRecordedActionCreator : public QWidget {
public:
    explicit KisRecordedActionCreator(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~KisRecordedActionCreator();
    /**
     * This function is called when the dialog is closed and the action has to be created
     * from the parameters in the widget.
     */
    virtual KisRecordedAction* createAction() const = 0;
private:
    struct Private;
    Private * const d;
};


#endif
