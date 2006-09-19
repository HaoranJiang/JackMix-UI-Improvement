/*
    Copyright ( C ) 2005 Arnold Krille <arnold@arnoldarts.de>

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

#ifndef OSCSERVER_H
#define OSCSERVER_H

#include <lo/lo.h>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QMap>

namespace OSC {

	int generic_handler( const char *path, const char *types, lo_arg **argv, int argc, void *data, void *user_data );
	void error( int num, const char *m, const char *path );

	class ServerPath;

	class Server : public QObject
	{
		friend class ServerPath;
	Q_OBJECT
	public:
		Server( QObject*, const char* =0 );
		Server( QString port="5282", QObject* =0, const char* =0 );
		~Server();
		int port() const { return lo_server_thread_get_port( _server ); }
		QString url() const { return lo_server_thread_get_url( _server ); }
		virtual void data( const char* data, QVariant=0 );
	public slots:
		void start( QString port="5282" );
		void stop();
	signals:
		void gotData( QString, QVariant );
	private:
		QMap <QString,ServerPath*> _paths;
		lo_server_thread _server;
	};

	class ServerPath : public QObject
	{
		Q_OBJECT
		public:
			ServerPath( Server*, QString path, QVariant::Type type );
			~ServerPath();
			void emitdata( QVariant d );
		signals:
			void data();
			void data( QVariant );
			void data( QString );
			void data( int );
		private:
			Server* _server;
			QString _path;
			QVariant::Type _type;
	};
};

#endif // OSCSERVER_H

