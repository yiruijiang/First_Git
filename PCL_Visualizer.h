#ifndef PCLVIEWER_H
#define PCLVIEWER_H

#include <iostream>
#include <vector>

// Qt
#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QMutex>
#include <QTimer>
#include <QFileDialog>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPixmap>
#include <QIcon>
#include <QSize>

// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/pcl_macros.h>

// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkCamera.h>


namespace Ui
{
  class PCLViewer;
}

class PCLViewer : public QMainWindow
{
  Q_OBJECT

public:
  explicit PCLViewer (QWidget *parent = 0, Qt::WFlags flag = 0);
  ~PCLViewer ();
  
  unsigned int current_frame;
  unsigned int nr_frame;
public slots:
	void loadPCDPressed ();
	void playButtonPressed ();
//  void
 /* randomButtonPressed ();

  void
  RGBsliderReleased ();

  void
  pSliderValueChanged (int value);

  void
  redSliderValueChanged (int value);

  void
  greenSliderValueChanged (int value);

  void
  blueSliderValueChanged (int value);*/

protected:
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
  std::vector<std::string> pcd_files;
  std::vector<boost::filesystem::path> pcd_paths;
  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud;

		  

private:
  Ui::PCLViewer *ui;

};

#endif // PCLVIEWER_H
