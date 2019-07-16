#include <cstdio>
#include <ros/ros.h>
#include <ros/package.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <dynamic_reconfigure/DoubleParameter.h>
#include <dynamic_reconfigure/Reconfigure.h>
#include <dynamic_reconfigure/Config.h>
#include <highgui.h>
#include <vector>
#include <math.h>
#include <signal.h>
#include <fstream>
#include <std_msgs/Int32.h>
#include <std_msgs/Int32MultiArray.h>
#include <sensor_msgs/LaserScan.h>
#include "vision/center.h"
#include "vision/white.h"
#include "vision/black.h"
#include "vision/bin.h"
#include "vision/color.h"
#include "vision/avoid.h"
#define PI 3.14159265
#define FRAME_COLS 659 //width  x659
#define FRAME_ROWS 493 //height y493
#define VISION_TOPIC "/camera/image_raw"
#define YAML_PATH ros::package::getPath("vision") + "/config/FIRA.yaml"
#define IMAGE "/src/vision/1.bmp"

typedef unsigned char BYTE;
using namespace cv;
using namespace std;

class NodeHandle
{
  protected:
    NodeHandle();
    void Readyaml();
    void Parameter_getting();
    //==========================================
    void AngleLUT();
    vector<double> Angle_sin;
    vector<double> Angle_cos;
    int Frame_Area(int coordinate, int range);
    int Angle_Adjustment(int angle);
    void Pub_avoidframe(Mat frame);
    void Pub_blackdis(std_msgs::Int32MultiArray distance);
    ros::Publisher avoidframe_pub;
    ros::Publisher blackdis_pub;
    vector <double> black_item_distance;
    vector <double> red_line_distance;
    //================center====================
    int CenterXMsg;
    int CenterYMsg;
    int InnerMsg;
    int OuterMsg;
    int FrontMsg;
    int HorizonMsg;
    double Camera_HighMsg;
    //==============distance==================
    double camera_f(double Omni_pixel);
    double Omni_distance(double pixel_dis);
    //========================================
    vector<int> HSV_green;
    //========================================
    double df_1;
    double df_2;
    double df_1_dis;
    double df_2_dis;
    double far_good_angle;
    double dd_1;
    double dd_2;
    double dd_1_dis;
    double dd_2_dis;
    double good_angle;
    double final_angle;
    double af_angle;
    double v_fast;
    double v_af;
    //============laser scan=================
    vector<double> ranges;

  private:
    ros::NodeHandle nh;
    ros::Subscriber save_sub;
    ros::Subscriber blackdis_sub;
    ros::Subscriber reddis_sub;
    ros::Subscriber avoid_sub;
    ros::Subscriber scan_sub;
    void blackdiscall(const std_msgs::Int32MultiArray msg);
    void reddiscall(const std_msgs::Int32MultiArray msg);
    void avoidcall(const vision::avoid msg);
    void SaveButton_setting(const vision::bin msg);
    void scancall(const sensor_msgs::LaserScan msg);
};