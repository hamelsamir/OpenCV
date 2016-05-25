//* projet samir hamel

#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
string text = "PROJET OPENCV SAMIR HAMEL LP OCI" ;
int fontFace = FONT_HERSHEY_PLAIN;
double fontScale = 1;
int thickness = 0.5;

int main(int argc, char* argv[])
{
//Ouvrir le fichier vidéo pour la lecture
    VideoCapture cap("/home/samir/Bureau/projet vision/rose.mp4"); 

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Impossible d'ouvrir le fichier" << endl;
         return -1;
    }

   
// Création des fenêtres  
    const char* pzOriginalWindowName = "MaVideo";
    namedWindow(pzOriginalWindowName, CV_WINDOW_AUTOSIZE); 

    const char* pzRotatingWindowName = "Rotatation Video";
    namedWindow( pzRotatingWindowName, CV_WINDOW_AUTOSIZE );
 
    int iAngle = 180;
   
    createTrackbar("Angle", pzRotatingWindowName, &iAngle, 360);
    
    while(1)
    {
        //Mat frame;
Mat matOriginalFrame;

        bool bSuccess = cap.read(matOriginalFrame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
                        cout << "Cannot read the frame from video file" << endl;
                       break;
        }  

        Mat imgL;
        matOriginalFrame.convertTo(imgL, -1, 0.4, 0); //dimunuer le contrast	
	
        Mat imgH;
       matOriginalFrame.convertTo(imgH, -1, 8, 0); //augmente le conntrast

        Mat imgH1 = matOriginalFrame + Scalar(50, 75, 50); //augmenter la luminosité
        Mat imgL1 = matOriginalFrame + Scalar(-50, -75, -50); //diminuer la luminosité
//Rendre la vidéo floue
	Mat framedest(matOriginalFrame.size(), matOriginalFrame.type());
	blur(matOriginalFrame,framedest,Size(1,99),Point(-1,-1));
//Addition de tous les traitements	
        Mat imgK ;
        imgK=imgH+imgH1+imgL+imgL1+framedest;
        
//Rotation de la  video originale
 Mat matRotation = getRotationMatrix2D( Point(matOriginalFrame.cols / 2, matOriginalFrame.rows / 2), (iAngle - 180), 1 );

 Mat matRotatedFrame;
 warpAffine( matOriginalFrame, matRotatedFrame, matRotation, matOriginalFrame.size() );
//Rotation de la  video contrast augmenté
Mat matRotation1 = getRotationMatrix2D( Point(imgH.cols / 2, imgH.rows / 2), (iAngle + 180), 1 );
Mat matRotatedFrame1;
 warpAffine( imgH, matRotatedFrame1, matRotation1, imgH.size() );
//Rotation de la  vidéo contrast dimunué
Mat matRotation2 = getRotationMatrix2D( Point(imgL.cols / 2, imgL.rows / 2), (iAngle + 180), 1 );
Mat matRotatedFrame2;
 warpAffine( imgL, matRotatedFrame2, matRotation2, imgL.size() );
//Rotation de la  video luminosité dimunuée
Mat matRotation3 = getRotationMatrix2D( Point(imgL1.cols / 2, imgL1.rows / 2), (iAngle + 180), 1 );
Mat matRotatedFrame3;
 warpAffine( imgL1, matRotatedFrame3, matRotation3, imgL1.size() );
//Rotation de la  video luminosité augmentée
Mat matRotation4 = getRotationMatrix2D( Point(imgH1.cols / 2, imgH1.rows / 2), (iAngle + 180), 1 );
Mat matRotatedFrame4;
 warpAffine( imgH1, matRotatedFrame4, matRotation4, imgH1.size() );
//Rotation de la  video floue
Mat matRotation5 = getRotationMatrix2D( Point(framedest.cols / 2, framedest.rows / 2), (iAngle + 180), 1 );
Mat matRotatedFrame5;
 warpAffine( framedest, matRotatedFrame5, matRotation5, framedest.size() );
//Rotation de la  video resultats de l'addition
Mat matRotation6 = getRotationMatrix2D( Point(imgK.cols / 2, imgK.rows / 2), (iAngle + 180), 1 );
Mat matRotatedFrame6;
 warpAffine( imgK, matRotatedFrame6, matRotation6, imgK.size() );
// ajout de texte sur la video originale
int baseline=0;
Size textSize = getTextSize(text, fontFace,
                            fontScale, thickness, &baseline);

Point textOrg(10,20);
putText(matOriginalFrame, text, textOrg, fontFace, fontScale,
        Scalar::all(255), thickness, 3);
putText(imgH, text, textOrg, fontFace, fontScale,
        Scalar::all(255), thickness, 3);
// afficher la  matOriginaleframe dans la fenetre "MaVideo"
imshow("MaVideo", matOriginalFrame); 
imshow( pzRotatingWindowName, matRotatedFrame );

cout << "*********************RESETER APPUYER SUR:***********************************" << endl;
cout << "******************** a pour voir la vidéo en mode luminosité augmentée *****" << endl;
cout << "******************** b pour voir la vidéo en mode luminosité dimunué *******" << endl;
cout << "******************** c pour voir la vidéo en mode contrast augmené**********" << endl;
cout << "******************** d  pour voir la vidéo en mode dimunué dimunué**********" << endl;
cout << "******************** e pour voir la vidéo en mode flou**********************" << endl;
cout << "******************** f pour voir l'addition de tous les traitements*********" << endl;
cout << "*********************APPUYER SUR  s POUR SAUVGARDER UNE IMAGE **************" << endl;
cout << "*********************glisser le trackbar pour tourner les vidéos ***********" << endl;
cout << "*********************APPUYER SUR Echap pour quiter*************** ***********" << endl;
cout << " " << endl;





char p =cvWaitKey(30);

switch(char(p)) 
{
    case 'a': 
         
        imshow("Luminosite augmentee",matRotatedFrame4);

    break;
 
case 'b': 
       imshow("Luminosité Dimunuee",  matRotatedFrame3);
        break;
case 'c': 
       imshow( "Contrast Augmente", matRotatedFrame1);
        break;
case 'd': 
       imshow("Contrast Diminue", matRotatedFrame2);
        break;
case 'e': 
imshow("FLOU", matRotatedFrame5);

        break;
case 'f': 
        imshow("Addition de tous les traitements",matRotatedFrame6);
        break;
case 's': 
     imwrite( "/home/samir/Bureau/projet vision/Image.jpg", matOriginalFrame );  
imshow(" imageName", matOriginalFrame );

        break;
}
        if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
       {
                cout << "esc key is pressed by user" << endl; 
                break; 
       }

    }


    return 0;

}
