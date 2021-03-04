/*
    Virtual Painter using OpenCV
    It can detect colors Pink, Sky blue and Dark Green
    Created By: sdam1n
*/

// OpenCV headers
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <vector>


using namespace std;
using namespace cv;

// hmin, smin, vmin, hmax, smax, vmax
// vector for storing HSV min and max values

int noise = 800;
vector<vector<int>> colors_vector = {{162,125,0,179,214,255},   //pink
                                     {97,71,40,132,255,255},    //sky blue
                                     {60,49,0,78,255,117}      //Dark Green
                                    };

// vector for storing BGR values of detected colors
vector<Scalar> color_values = {{147,20,255},    //pink BGR
                               {236,206,135},   //sky blue BGR
                               {0,100,0}};      //Dark Green BGR (not exactly accurate BGR but i liked it)

// vector for storing the draw points
vector<vector<int>> draw_point_vector;          

// Function for getting contours
Point get_contours(Mat mask, Mat img)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundrect(contours.size());

    Point draw_point(0,0);
    for (int i=0;i<contours.size();i++)
    {
        int area = contourArea(contours[i]);

        string objType;

        if(area>noise)
        {
            float peri = arcLength(contours[i],true);
            approxPolyDP(contours[i],conPoly[i],0.02*peri,true);


            boundrect[i] = boundingRect(conPoly[i]);

            draw_point.x = boundrect[i].x + boundrect[i].width/2;
            draw_point.y = boundrect[i].y;

        }
        
        
    }

    return draw_point;
}


// function for finding colors
vector<vector<int>> find_color(Mat img)
{
    Mat imgHsv;
    cvtColor(img,imgHsv,COLOR_BGR2HSV);

    for(int i=0; i<colors_vector.size(); i++)
    {
        Scalar lower(colors_vector[i][0], colors_vector[i][1], colors_vector[i][2]);
        Scalar upper(colors_vector[i][3], colors_vector[i][4], colors_vector[i][5]);

        Mat mask;
        inRange(imgHsv, lower, upper,mask);

        Point draw_point = get_contours(mask,img);
        if(draw_point.x!=0 && draw_point.y!=0)
            draw_point_vector.push_back({draw_point.x,draw_point.y,i});

        
    }
    return draw_point_vector;
}

// Function for drawing the paint
void draw_paint(vector<vector<int>> draw_point_vector, vector<Scalar> color_values, Mat img)
{   
    for(int i=0; i<draw_point_vector.size(); i++)
    {
        
        // this draws circle
        circle(img,Point(draw_point_vector[i][0],draw_point_vector[i][1]),15, color_values[draw_point_vector[i][2]],FILLED);
        
        // this draws line
        line(img,Point(draw_point_vector[i][0],draw_point_vector[i][1]),Point(draw_point_vector[i][0],draw_point_vector[i][1]),color_values[draw_point_vector[i][2]],15);

    }


    
} 


int main()
{
    VideoCapture cap(0);    // to capture webcam feed
    Mat img;
    while(true)
    {
        cap.read(img);

        find_color(img);

        draw_paint(draw_point_vector,color_values,img);
        imshow("Virtual Painter", img);
        
        int key = waitKey(1);
        if(key==27) break;  // press ESC to exit
    }
    destroyAllWindows();
}