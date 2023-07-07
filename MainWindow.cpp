#include "MainWindow.h"

#include <Basemap.h>
#include <Envelope.h>
#include <GeometryEngine.h>
#include <Graphic.h>
#include <GraphicsOverlay.h>
#include <Map.h>
#include <MapGraphicsView.h>
#include <MapTypes.h>
#include <PolylineBuilder.h>
#include <SimpleLineSymbol.h>
#include <SpatialReference.h>
#include <Viewpoint.h>

#include <QElapsedTimer>

using namespace Esri::ArcGISRuntime;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  // Create envelope for the area of interest. Don't understand the units being
  // used here. There are other methods for setting the viewpoint of the map
  // which probably make more sense to use
  Envelope envelope(-12211308.778729, 4645116.003309, -12208257.879667,
                    4650542.535773, SpatialReference(102100));

  // Create a new map with the imagery with labels basemap
  m_map = new Map(BasemapStyle::ArcGISImagery, this);

  // Set the initial viewpoint to the envelope
  m_map->setInitialViewpoint(Viewpoint(envelope));

  // Create a map view, and pass in the map
  m_mapView = new MapGraphicsView(m_map, this);

  GraphicsOverlay *overlay = new GraphicsOverlay(this);

  QElapsedTimer timer;
  timer.start();

  // Line builder can be re-used as long as geometry is reset when needed (see
  // replace geometry below)
  PolylineBuilder *polyline_builder =
      new PolylineBuilder(SpatialReference::wgs84(), this);

  // symbol can be re-used, even if the coordinates are different. The symbol
  // will set the color, width, and line type of the lines bu does not affect
  // coordinates
  SimpleLineSymbol *line_symbol = new SimpleLineSymbol(
      SimpleLineSymbolStyle::Solid, QColor(Qt::blue), 3, this);

  QList<Graphic *> graphics;

  for (int j = 0; j < 200; j++) {
    polyline_builder->replaceGeometry({});

    QList<Point> points;
    points.reserve(1000);
    points << Point(-118.8215 + (j * 0.50), 34.0140);
    for (int i = 0; i < 10000; i++) {
      points << Point(points.back().x() + 0.010, points.back().y() + 0.010);
    }

    polyline_builder->addPoints(points);

    // Create a graphic to display the line with its symbology
    Graphic *polyline_graphic =
        new Graphic(polyline_builder->toGeometry(), line_symbol, this);
    graphics << polyline_graphic;
  }

  // Adding all graphics at once should be faster
  overlay->graphics()->append(graphics);

  qDebug() << double(timer.nsecsElapsed()) / 1e6 << "ms";

  m_mapView->graphicsOverlays()->append(overlay);

  // Set up the UI
  setCentralWidget(m_mapView);

  startTimer(1000);
}

void MainWindow::timerEvent(QTimerEvent *event) {
  // This timer function shows that updating the symbol will update it for all
  // graphics (all graphics were created with the same symbol)
  static int i = 0;
  GraphicsOverlay *overlay = m_mapView->graphicsOverlays()->at(0);
  auto *symbol =
      qobject_cast<SimpleLineSymbol *>(overlay->graphics()->at(0)->symbol());

  i++;
  if (i % 3 == 0)
    symbol->setColor(Qt::cyan);
  else if (i % 3 == 1)
    symbol->setColor(Qt::red);
  else if (i % 3 == 2)
    symbol->setColor(Qt::white);
}
