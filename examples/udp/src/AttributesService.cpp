#include <thread>
#include <iostream>

#include <CommonAPI/CommonAPI.hpp>
#include "AttributesStubImpl.hpp"

int main()
{
      CommonAPI::Runtime::setProperty("LogContext", "Example");
      CommonAPI::Runtime::setProperty("LogApplication", "Service");
      CommonAPI::Runtime::setProperty("LibraryBase", "Attributes");

      auto runtime = CommonAPI::Runtime::get();

      std::string domain = "local";
      std::string instance = "commonapi.examples.Attributes";
      std::string connection = "service-sample";

      auto service = std::make_shared<AttributesStubImpl>();
      while (!runtime->registerService(domain, instance, service, connection))
      {
        std::cout << "Register Service failed, trying again in 100 milliseconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }

      std::cout << "Successfully Registered Service!" << std::endl;

      while (true)
      {
        service->incCounter();
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
      }
      return 0;
}
