/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DillApi.h
 * Author: pawn
 *
 * Created on December 16, 2017, 11:30 PM
 */

#ifndef DILLAPI_H
#define DILLAPI_H
#include <pistache/http.h>
#include <pistache/router.h>
#include <pistache/endpoint.h>
#include <pistache/net.h>
#include <memory>
namespace Oculus{
class DillApi {
public:
    void start(); //start function, actually calls console
    void stop(); //stops the system gracefully
    void console(); //console is called automatically
private:
    void setRoutes(); //routes

    //request route for posting an image as binary
    void postImg(const Pistache::Rest::Request &request,
            Pistache::Http::ResponseWriter response);
    
    std::shared_ptr<Pistache::Http::Endpoint> endpoint;
    Pistache::Rest::Router router;
};
}
#endif /* DILLAPI_H */

