/*
    Copyright ( C ) 2004 Arnold Krille <arnold@arnoldarts.de>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation;
    version 2 of the License.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.

*/

#ifndef CONNECTIONLISTER_H
#define CONNECTIONLISTER_H

#include <QtGui/QWidget>
#include <QtCore/QList>
#include <QtGui/QListWidget>

#include "mixingmatrix.h"

class QGridLayout;
class QPushButton;
class QListBox;

namespace JackMix {
	namespace MixingMatrix {

		class ConnectionLister : public QWidget
		{
		Q_OBJECT
		public:
			ConnectionLister( Widget*, QWidget* =0, const char* =0 );
			~ConnectionLister();

		public slots:
			void addElement( Element* );
			void removeElement( Element* );
		private slots:
			void connectControls();
			void disconnectMaster();
			void disconnectSlave();
			void selectionChanged();
		private:
			Widget *_widget;
			QGridLayout *_layout;
			QPushButton *_btn_connect, *_btn_close, *_btn_disconnectMaster, *_btn_disconnectSlave;
			QListWidget *_box_signals, *_box_slots;
		};

		class ElementConnectView : public QListWidgetItem
		{
		public:
			ElementConnectView( QListWidget*, Element* );
			~ElementConnectView();
			Element* element() const { return _element; }
			int rtti() const { return 5281; }
		private:
			Element* _element;
		};
		/*class ElementPropertyView : public QListWidgetItem
		{
		public:
			ElementPropertyView( ElementConnectView*, QString );
			~ElementPropertyView();
			ElementSlotSignalPair property() const;
			int rtti() const { return 5282; }
		private:
			QString _property;
			Element* _element;
		};*/


	}; // MixingMatrix
}; // JackMix

#endif // MIXINGMATRIX_PRIVAT_H

