/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ocr.h
 * Author: pawn
 *
 * Created on December 20, 2017, 12:48 PM
 */

#ifndef OCR_H
#define OCR_H
#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>
#include <string>
namespace Oculus{
class Ocr{
//with tesseract we need to start the api  
public:
    //pass the filename to it
    Ocr(const std::string &fn);
    
    //return the content in the image file as text
    std::string getText();
    
    ~Ocr();//destructor
    Ocr& operator=(const Ocr &cpy);//copy-assign
    Ocr(const Ocr &cpy);//copy constructor

    
private:
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    PIX *img;
    char *content;
    std::string fileName;
};
}
#endif /* OCR_H */

