/*
    Copyright 2004 - 2007 Arnold Krille <arnold@arnoldarts.de>

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

// #include <QtCore/QDebug>
// #include <QtCore/QFile>
// #include <QtWidgets/QApplication>

// #include "jack_backend.h"
// #include "mainwindow.h"

// int main( int argc, char** argv ) {
// 	qDebug() << "JackMix starting";

// 	QApplication *qapp = new QApplication( argc, argv );
//         qRegisterMetaType<JackMix::BackendInterface::levels_t>("JackMix::BackendInterface::levels_t");
// 	QStringList args = qapp->arguments();
// 	QString file;
// 	for( int i=1; i<args.size(); ++i ) {
// 		qDebug() << QString( " arg %1: %2" ).arg( i ).arg( args[ i ] );
// 		if ( QFile::exists( args[ i ] ) )
// 			file = args[ i ];
// 	}

// 	JackMix::MainWindow *mw;
// 	if ( !file.isEmpty() )
// 		mw = new JackMix::MainWindow( file );
// 	else
// 		mw = new JackMix::MainWindow();
// 	mw->show();

// 	int ret = qapp->exec();

// 	delete mw;

// 	return ret;
// }

// #include "mainwindow.h"

// #include "jack_backend.h"

// #include "mixingmatrix.h"
// #include "channelselector.h"
// #include "editablechannelselector.h"
// #include "graphicalguiserver.h"

// #include "aux_elements.h"
// #include "stereo_elements.h"

// #include <QtCore/QDebug>
// #include <QtWidgets/QApplication>
// #include <QtWidgets/QDialog>
// #include <QtWidgets/QSpinBox>
// #include <QtWidgets/QLabel>
// #include <QtWidgets/QDialogButtonBox>
// #include <QtWidgets/QVBoxLayout>

// int main(int argc, char** argv) {
//     qDebug() << "JackMix starting";

//     QApplication *qapp = new QApplication(argc, argv);
//     qRegisterMetaType<JackMix::BackendInterface::levels_t>("JackMix::BackendInterface::levels_t");

//     QSpinBox *inputSpinBox = new QSpinBox;
//     QSpinBox *outputSpinBox = new QSpinBox;

//     inputSpinBox->setRange(1, 100);
//     outputSpinBox->setRange(1, 100);

//     QLabel *inputLabel = new QLabel("Input Count:");
//     QLabel *outputLabel = new QLabel("Output Count:");

//     QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    
//     QDialog dialog;
//     QVBoxLayout *layout = new QVBoxLayout(&dialog);
//     layout->addWidget(inputLabel);
//     layout->addWidget(inputSpinBox);
//     layout->addWidget(outputLabel);
//     layout->addWidget(outputSpinBox);
//     layout->addWidget(buttonBox);
    
//     QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
//     QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    
//     if (dialog.exec() != QDialog::Accepted) {
//         return 0;
//     }

//     int inputCount = inputSpinBox->value();
//     int outputCount = outputSpinBox->value();

//     JackMix::MainWindow *mw = new JackMix::MainWindow(inputCount, outputCount);
//     mw->show();

//     int ret = qapp->exec();

//     delete mw;

//     return ret;
// }

#include "mainwindow.h"

#include "jack_backend.h"

#include "mixingmatrix.h"
#include "channelselector.h"
#include "editablechannelselector.h"
#include "graphicalguiserver.h"

#include "aux_elements.h"
#include "stereo_elements.h"

#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>

int main(int argc, char** argv) {
    qDebug() << "JackMix starting";

    QApplication *qapp = new QApplication(argc, argv);
    qRegisterMetaType<JackMix::BackendInterface::levels_t>("JackMix::BackendInterface::levels_t");

    QSpinBox *inputSpinBox = new QSpinBox;
    QSpinBox *outputSpinBox = new QSpinBox;

    inputSpinBox->setRange(1, 100);
    outputSpinBox->setRange(1, 100);

    QLabel *inputLabel = new QLabel("Input Count:");
    QLabel *outputLabel = new QLabel("Output Count:");

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QPushButton *loadFileButton = new QPushButton("Load File"); 

    QDialog dialog;
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(inputLabel);
    layout->addWidget(inputSpinBox);
    layout->addWidget(outputLabel);
    layout->addWidget(outputSpinBox);
    layout->addWidget(loadFileButton); 
    layout->addWidget(buttonBox);

    QObject::connect(loadFileButton, &QPushButton::clicked, [&]() {
        QString fileName = QFileDialog::getOpenFileName(&dialog, "Open File", "", "All Files (*)");
        if (!fileName.isEmpty()) {
        }
    });

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() != QDialog::Accepted) {
        return 0;
    }

    int inputCount = inputSpinBox->value();
    int outputCount = outputSpinBox->value();

    JackMix::MainWindow *mw = new JackMix::MainWindow(inputCount, outputCount);
    mw->show();

    int ret = qapp->exec();

    delete mw;

    return ret;
}
