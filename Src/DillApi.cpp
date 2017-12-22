/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../OculusHeaders/DillApi.h"

//void DillApi::postImg(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response){
//    //take the content as string
//    auto id = request.param(":img").as<std::string>();
//    
//    //send it back to the user
//    auto res = response.send(Pistache::Http::Code::Accepted, id, MIME(Text, Json));
//    
//    //after the call returns the promise we should print out how many bytes were sent
//    res.then([](int bytes){std::cout << "Size of data sent:" << bytes << std::endl; },
//            Pistache::Async::NoExcept);
//}