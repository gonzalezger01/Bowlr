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

void Oculus::DillApi::start(){//start the system
        try {//start the system on multiple threads
            std::cout << "initializing the system, Welcome to Oculus\n";
            Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
            endpoint = std::make_shared<Pistache::Http::Endpoint>(addr);
            
            auto opts = Pistache::Http::Endpoint::options().threads(4).
            flags(Pistache::Tcp::Options::InstallSignalHandler | Pistache::Tcp::Options::ReuseAddr);
            
            endpoint->init(opts);
            setRoutes();
            endpoint->setHandler(router.handler());
            endpoint->serveThreaded();
            
            console();//call console
        }        catch (std::runtime_error &e) {
            std::cerr << "Error Found! : \n";
            std::cerr << e.what();
        }
    }

void Oculus::DillApi::stop() {//shutdown
        endpoint->shutdown();
        std::cout << "Run Halted!";
    }

void Oculus::DillApi::console(){//console should shut down when it detects HALT
    std::string command;
    std::cout << "Console: \n";
    std::cin >> command;
    
    if(command == "HALT"){
        stop();
    }else{
        std::cerr << "Err: Wrong Command!\nConsole: ";
        std::cin >> command;
    }
}

void Oculus::DillApi::setRoutes() {//routes
        Pistache::Rest::Routes::Post(router, "img/g", Pistache::Rest::Routes::bind(&DillApi::postImg, this));
    }

void Oculus::DillApi::postImg(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
    //in here we should take the content respond to the user properly
    std::string contentJson;
    std::string content;
    
    //write the file
    std::ofstream fileOut("img", std::ofstream::binary);
    fileOut << request.body();
    
    content = ocr.getText();
    contentJson = "{\"content:\"" + contentJson + "\"}";
    
    response.send(Pistache::Http::Code::Accepted, contentJson, MIME(Application, Json));
}