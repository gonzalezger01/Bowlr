/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "../OculusHeaders/Ocr.h"

//accepts the file name
//loads it into the program
Oculus::Ocr::Ocr(const std::string& fn):fileName(fn){}

std::string Oculus::Ocr::getText(){
    //file processing to get the content should happen here
    
    api->Init(nullptr, "eng");//have to start the OCR system tesseract
    img = pixRead(fileName.c_str());
    api->SetImage(img);
    
    content = api->GetUTF8Text();
    return content;
}

void Oculus::Ocr::setFile(const std::string s){
    fileName = s;
}

Oculus::Ocr::~Ocr(){
    //we destroy the pointers here or we risk a memory leak
    api->End();//end the tesseract engine
    pixDestroy(&img);//delete the picture pointer by ref
    delete [] content;//delete the char array
}

//copy assign
//we should take care of self assignment
Oculus::Ocr& Oculus::Ocr::operator =(const Ocr& cpy){
    img = new Pix (*cpy.img);
    content = new char (*cpy.content);
    fileName = cpy.fileName;
}

//copy constructor
Oculus::Ocr::Ocr(const Ocr& cpy): 
api(new tesseract::TessBaseAPI(*cpy.api)) ,img(new PIX(*cpy.img)){}