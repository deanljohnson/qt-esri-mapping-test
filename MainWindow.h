#pragma once

#include <QMainWindow>

namespace Esri::ArcGISRuntime {
class Map;
class MapGraphicsView;
} // namespace Esri::ArcGISRuntime

class MainWindow : public QMainWindow {
public:
  explicit MainWindow(QWidget *parent = nullptr);

protected:
  void timerEvent(QTimerEvent *event) override;

private:
  Esri::ArcGISRuntime::Map *m_map{nullptr};
  Esri::ArcGISRuntime::MapGraphicsView *m_mapView{nullptr};
};
