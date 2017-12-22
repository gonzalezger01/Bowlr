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
using namespace Pistache;

class DillApi {
public:

    void start() {//start the system
        try {
            std::cout << "initializing the system, Welcome to Oculus\n";
            Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
            endpoint = std::make_shared<Pistache::Http::Endpoint>(addr);
            auto opts = Pistache::Http::Endpoint::options().threads(1).flags(Pistache::Tcp::Options::InstallSignalHandler | Pistache::Tcp::Options::ReuseAddr);
            endpoint->init(opts);
            setRoutes();
            endpoint->setHandler(router.handler());
            endpoint->serve();
        }        catch (std::runtime_error &e) {
            std::cerr << "Error Found! : \n";
            std::cerr << e.what();
        }
    }

    void stop() {//shutdown
        endpoint->shutdown();
        std::cout << "Run Halted!";
    }
private:

    void setRoutes() {//routes
        Pistache::Rest::Routes::Post(router, "img/:img", Pistache::Rest::Routes::bind(&DillApi::postImg, this));
    }

    //request route for Post website/img/content
    void postImg(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    std::shared_ptr<Pistache::Http::Endpoint> endpoint;
    Pistache::Rest::Router router;
};
#endif /* DILLAPI_H */

