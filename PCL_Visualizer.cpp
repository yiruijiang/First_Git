#include "pclviewer.h"
#include "D:\Hiwi\QTFramework\VC10\ui_pclviewer.h"

PCLViewer::PCLViewer (QWidget *parent, Qt::WFlags flag) :
  QMainWindow (parent, flag),
  ui (new Ui::PCLViewer)
{
	// Define global variable
	// cloud_present
	ui->setupUi (this);
	this->setWindowTitle ("3D-Visualizer");
	
  // Set up the QVTK window
  viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false));
  ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
  viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());
  ui->qvtkWidget->update();

  // Setting the image icon of button
  QPixmap playButton_pix("D:\\Hiwi\\QTFramework\\Images\\Play.png");
  QPixmap pauseButton_pix("D:\\Hiwi\\QTFramework\\Images\\Pause.png");
  QPixmap stopButton_pix("D:\\Hiwi\\QTFramework\\Images\\Stop.png");
  QPixmap projectorButton_pix("D:\\Hiwi\\QTFramework\\Images\\Projector.png");
  QPixmap realtimeButton_pix("D:\\Hiwi\\QTFramework\\Images\\Time.png");
  QIcon playButton_icon(playButton_pix);
  QIcon pauseButton_icon(pauseButton_pix);
  QIcon stopButton_icon(stopButton_pix);
  QIcon projectorButton_icon(projectorButton_pix);
  QIcon realtimeButton_icon(realtimeButton_pix);
  ui->playButton->setIcon(playButton_icon);
  ui->pauseButton->setIcon(pauseButton_icon);
  ui->stopButton->setIcon(stopButton_icon);
  ui->projectorButton->setIcon(projectorButton_icon);
  ui->realtimeButton->setIcon(realtimeButton_icon);
  //ui->playButton->setIconSize(QSize(60,60));
  //ui->playButton->setFixedSize(playButton_pix.rect().size());

  // Connect the components on UI
  connect (ui ->LoadPCD, SIGNAL( triggered()), this, SLOT( loadPCDPressed()));
  connect (ui ->playButton, SIGNAL (clicked()), this, SLOT (playButtonPressed()));
	
  // Connect "random" button and the function
/*  connect (ui->pushButton_random,  SIGNAL (clicked ()), this, SLOT (randomButtonPressed ()));

  // Connect R,G,B sliders and their functions
  connect (ui->horizontalSlider_R, SIGNAL (valueChanged (int)), this, SLOT (redSliderValueChanged (int)));
  connect (ui->horizontalSlider_G, SIGNAL (valueChanged (int)), this, SLOT (greenSliderValueChanged (int)));
  connect (ui->horizontalSlider_B, SIGNAL (valueChanged (int)), this, SLOT (blueSliderValueChanged (int)));
  connect (ui->horizontalSlider_R, SIGNAL (sliderReleased ()), this, SLOT (RGBsliderReleased ()));
  connect (ui->horizontalSlider_G, SIGNAL (sliderReleased ()), this, SLOT (RGBsliderReleased ()));
  connect (ui->horizontalSlider_B, SIGNAL (sliderReleased ()), this, SLOT (RGBsliderReleased ()));

  // Connect point size slider
  connect (ui->horizontalSlider_p, SIGNAL (valueChanged (int)), this, SLOT (pSliderValueChanged (int)));
  */
  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
  std::vector<pcl::PointCloud<pcl::PointXYZRGBA>::Ptr> pcd_clouds;

  pcl::io::loadPCDFile("D:\\data\\PCL\\1.pcd", *cloud);
  	for(int i = 0; i < cloud->size(); i++){
		if(cloud->points[i].r!=cloud->points[i].g){
			long temp = cloud->points[i].rgb;
			temp>>=16;
			cloud->points[i].r = cloud->points[i].g = cloud->points[i].b = temp;
		}
	}
  viewer->addPointCloud (cloud, "cloud");
 // pSliderValueChanged (2);
  viewer->resetCamera ();
  ui->qvtkWidget->update ();
}
  void
	  PCLViewer::loadPCDPressed(){
		  pcd_files.clear();
		  pcd_paths.clear();

		  QStringList qt_pcd_files = QFileDialog::getOpenFileNames(this, "Select one or more PCD files to open",
																		".pcd",
																		"PointClouds(*.pcd)");
		  int nr_frame = qt_pcd_files.size();
		  PCL_INFO("Number of %ld files selected \n", nr_frame);

		  if (nr_frame == 0){
			  PCL_ERROR("Please selet valid pcd files!! \n");
			  getchar();
		  }
		  else{
			  for (int i = 0; i < qt_pcd_files.size(); i++){
				  pcd_files.push_back(qt_pcd_files.at(i).toStdString());
			  }
		  }
		  int current_frame = 0;
  }
  void PCLViewer::playButtonPressed(){
	  pcl::io::loadPCDFile("D:\\data\\PCL\\2.pcd", *cloud);
	  for(int i = 0; i < cloud->size(); i++){
		  if(cloud->points[i].r!=cloud->points[i].g){
			  long temp = cloud->points[i].rgb;
			  temp>>=16;
			  cloud->points[i].r = cloud->points[i].g = cloud->points[i].b = temp;
		  }
	  }
	  viewer->updatePointCloud(cloud,"cloud");
	  ui->qvtkWidget->update();
  }
  /*
void
PCLViewer::randomButtonPressed ()
{
  printf ("Random button was pressed\n");

  // Set the new color
  for (size_t i = 0; i < cloud->size(); i++)
  {
    cloud->points[i].r = 255 *(1024 * rand () / (RAND_MAX + 1.0f));
    cloud->points[i].g = 255 *(1024 * rand () / (RAND_MAX + 1.0f));
    cloud->points[i].b = 255 *(1024 * rand () / (RAND_MAX + 1.0f));
  }

  viewer->updatePointCloud (cloud, "cloud");
  ui->qvtkWidget->update ();
}

/*void
PCLViewer::RGBsliderReleased ()
{
  // Set the new color
  for (size_t i = 0; i < cloud->size (); i++)
  {
    cloud->points[i].r = red;
    cloud->points[i].g = green;
    cloud->points[i].b = blue;
  }
  viewer->updatePointCloud (cloud, "cloud");
  ui->qvtkWidget->update ();
}

void
PCLViewer::pSliderValueChanged (int value)
{
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, value, "cloud");
  ui->qvtkWidget->update ();
}

void
PCLViewer::redSliderValueChanged (int value)
{
  red = value;
  printf ("redSliderValueChanged: [%d|%d|%d]\n", red, green, blue);
}

void
PCLViewer::greenSliderValueChanged (int value)
{
  green = value;
  printf ("greenSliderValueChanged: [%d|%d|%d]\n", red, green, blue);
}

void
PCLViewer::blueSliderValueChanged (int value)
{
  blue = value;
  printf("blueSliderValueChanged: [%d|%d|%d]\n", red, green, blue);
}
*/
PCLViewer::~PCLViewer ()
{
  delete ui;
}
