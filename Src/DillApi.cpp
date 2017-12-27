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
    std::cout << "Console: ";
    std::cin >> command;
    
    if(command == "HALT"){
        stop();
    }else{
        std::cerr << "Err: Wrong Command!\nConsole: ";
        std::cin >> command;
    }
}

void Oculus::DillApi::setRoutes() {//routes
        Pistache::Rest::Routes::Post(router, "img/", Pistache::Rest::Routes::bind(&DillApi::postImg, this));
    }

void Oculus::DillApi::postImg(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response){
    nlohmann::json j;
    std::string requestBody;
    std::string base64img;
    std::string ocrResult;
    std::unique_ptr<std::string*> b64Decode;
    int posCtr;
    
    //write the file(assuming we get content as binary)
    std::ofstream fileOut("img", std::ofstream::binary);
    fileOut << request.body();
    requestBody = request.body();
    
    //find the comma right before the base64
    for(auto it = requestBody.begin(); it != requestBody.end() && *it != ','; ++it){
        ++posCtr;
    }
    
    //trouble causing code, this is too brittle for requests
    base64img = requestBody.substr(posCtr+1, (requestBody.size() - 34));
    std::cout << base64img << "\n";
        
    //write the file(assuming its base64)
    Base64::Decode(base64img, *b64Decode);
    std::cout << request.body() << "\n";
    std::cout << "***************\n";
    fileOut << *b64Decode;
    
    //tell ocr to get the content
    ocr.setFile("img");
    ocrResult = ocr.getText();
    std::cout << ocrResult;
    
    j = {{"Frame1:",{1,4}},{"Frame2:",{1,4}},{"Frame3:",{1,4}},{"Frame4:",{1,4}},{"Frame5:",{1,4}},{"Frame6:",{1,4}},
    {"Frame7:",{1,4}},{"Frame8:",{1,4}},{"Frame9:",{1,4}},{"Frame10:",{1,4}},{"Frame11:",{1,4}},{"Frame12:",{1,4}}};
    
    std::cout << j.dump();
    response.send(Pistache::Http::Code::Accepted, j.dump(), MIME(Application, Json));
}