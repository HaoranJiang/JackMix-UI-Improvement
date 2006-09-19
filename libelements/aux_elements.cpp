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

#include "aux_elements.h"
#include "aux_elements.moc"

#include "qfloatpoti.h"
#include "qfloatslider.h"
#include "slider.h"
#include "jack_backend.h"

#include <QtGui/QLayout>
#include <QtGui/QPushButton>

using namespace JackMix;
using namespace JackMix::MixerElements;
using namespace JackMix::MixingMatrix;

/// The Factory for creating this things...
class AuxFactory : public JackMix::MixingMatrix::ElementFactory
{
public:
	AuxFactory() : ElementFactory() { globaldebug(); }
	~AuxFactory() {}

	QStringList canCreate() const {
		return QStringList()<<"AuxElement";
	}
	QStringList canCreate( int in, int out ) const {
		if ( in==1 && out==1 ) return QStringList()<<"AuxElement";
		return QStringList();
	}

	Element* create( QString type , QStringList ins, QStringList outs, Widget* p, const char* n=0 ) {
		if ( type=="AuxElement" ) {
			return new AuxElement( ins, outs, p, n );
		/*	AuxElement* tmp = new AuxElement( ins, outs, p, n );
			qDebug( "Created %s with address %p", type.latin1(), tmp );
			return tmp;*/
		} else
			return 0;
	}
};
AuxFactory* _auxfactory = new AuxFactory();

AuxElement::AuxElement( QStringList inchannel, QStringList outchannel, MixingMatrix::Widget* p, const char* n )
	: Element( inchannel, outchannel, p, n )
	, dB2VolCalc( -42, 6 )
	, _inchannel( inchannel[ 0 ] )
	, _outchannel( outchannel[ 0 ] )
{
	menu()->addAction( "Select", this, SLOT( slot_simple_select() ) );
	menu()->addAction( "Replace", this, SLOT( slot_simple_replace() ) );
	QGridLayout* _layout = new QGridLayout( this );

	QFloatPoti* poti = new QFloatPoti( amptodb( backend()->getVolume( _inchannel, _outchannel ) ), -36, 6, 10, QColor( 255,0,0 ), this, _inchannel.toStdString().c_str() );
	_layout->addWidget( poti, 0,0 );
	connect( poti, SIGNAL( valueChanged( float ) ), this, SLOT( emitvalue( float ) ) );
}
AuxElement::~AuxElement() {
}

void AuxElement::emitvalue( float n ) {
	//qDebug( "AuxElement::emitvalue( float %f dB ) that means ampfactor %f", n, dbtoamp( n ) );
	backend()->setVolume( _inchannel, _outchannel, dbtoamp( n ) );
}

