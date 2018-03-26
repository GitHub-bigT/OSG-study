#include "ViewerWidget.h"


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	ViewerWidget* viewWidget = new ViewerWidget();
	viewWidget->setGeometry(100, 100, 800, 600);
	viewWidget->show();

	return app.exec();
}