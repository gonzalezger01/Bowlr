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
    img = std::make_unique<PIX *> (pixRead(fileName.c_str()));
    
    api->SetImage(*img);
    
    
    content = std::make_unique<char*>(api->GetUTF8Text());
    return *content;
}

void Oculus::Ocr::setFile(const std::string s){
    fileName = s;
}

Oculus::Ocr::~Ocr(){
    //we destroy the pointers here or we risk a memory leak
    api->End();//end the tesseract engine
}

//copy assign
//we should take care of self assignment
Oculus::Ocr& Oculus::Ocr::operator =(const Ocr& cpy){
    img = std::make_unique<PIX *>(*cpy.img);
    content = std::make_unique<char*>(*cpy.content);
    fileName = cpy.fileName;
}

//copy constructor
//we dont copy the content cause that would just copy the results
Oculus::Ocr::Ocr(const Ocr& cpy): 
api(new tesseract::TessBaseAPI(*cpy.api)) ,img(std::make_unique<PIX *>(*cpy.img)){}