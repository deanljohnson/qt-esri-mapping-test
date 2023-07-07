#include <QApplication>
#include <QString>

#include "MainWindow.h"
#include <ArcGISRuntimeEnvironment.h>
#include <QDebug>
#include <stdexcept>

using namespace Esri::ArcGISRuntime;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  qDebug() << "hello?";

  const QString apiKey =
      QString("AAPK79ea44bb6a0842a8ad26d1504d738161Xum-wx35Pwp1HAb8wU-"
              "rPFLiKaxTxE5sopz5hSxqYOfOHz4MYMsX7dchcZCuA81D");

  if (apiKey.isEmpty()) {
    qWarning() << "Use of Esri location services, including basemaps, requires"
               << "you to authenticate with an ArcGIS identity or set the API "
                  "Key property.";
  } else {
    ArcGISRuntimeEnvironment::setApiKey(apiKey);
  }

  MainWindow window;
  window.show();

  return app.exec();
}
