#include <iostream>
#include <iomanip>
#include <stdbool.h>
#include <thread>
#include <chrono>
#include <memory>
#include <dlt/dlt.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/examples/AttributesProxy.hpp>

using namespace v1::commonapi::examples;

std::shared_ptr<AttributesProxy<>> proxy;

DLT_DECLARE_CONTEXT(client);

void ReceiveCallback(const int32_t& val)
{
      std::cout << "Received callback: " << val << std::endl;
      DLT_LOG(client, DLT_LOG_INFO, DLT_STRING("Client Side Rx Attribute val : "), DLT_INT32(val));
}

void receiveServiceAvailable(CommonAPI::AvailabilityStatus as) 
{
    if (as == CommonAPI::AvailabilityStatus::AVAILABLE) {

        // Subscribe for receiving values
        DLT_LOG(client, DLT_LOG_INFO, DLT_STRING("SomeIP Service Proxy is available NOW."));        
        proxy->getTestAttribute().getChangedEvent().subscribe(ReceiveCallback);

    } else if (as == CommonAPI::AvailabilityStatus::NOT_AVAILABLE) {

        std::cout << __FUNCTION__ << " : service not available" << std::endl;
    }
}

int main()
{
      CommonAPI::Runtime::setProperty("LogContext", "Example");
      CommonAPI::Runtime::setProperty("LogApplication", "Client");
      CommonAPI::Runtime::setProperty("LibraryBase", "Attributes");

      auto runtime = CommonAPI::Runtime::get();

      DLT_REGISTER_APP("CLNT", "Client Example");
      DLT_REGISTER_CONTEXT(client, "CCON", "Client context");
      DLT_LOG(client, DLT_LOG_INFO, DLT_STRING("SomeIP Client DLT Started!"));

      std::string domain = "local";
      std::string instance = "commonapi.examples.Attributes";
      std::string connection = "client-sample";
      static int16_t temp = 0;

      proxy = runtime->buildProxy<AttributesProxy>(domain, instance, connection);
      std::cout << "Waiting for service to become available." << std::endl;
      DLT_LOG(client, DLT_LOG_INFO, DLT_STRING("Waiting for service to become available."));

      proxy->getProxyStatusEvent().subscribe(receiveServiceAvailable);
      
      while (true)
      {
          std::this_thread::sleep_for(std::chrono::milliseconds(5000));
          CommonAPI::CallStatus _internalCallStatus; 
          const CommonAPI::CallInfo *_info = nullptr;
          std::string msg("");
          DLT_LOG(client, DLT_LOG_INFO, DLT_STRING("Client Side invoking service method : "), DLT_INT32(temp));
          proxy->dojob(temp++, _internalCallStatus, msg, _info);
          DLT_LOG(client, DLT_LOG_INFO, DLT_STRING("Client Side got reply for method : "), DLT_STRING(msg.c_str()));
      }

    DLT_UNREGISTER_CONTEXT(client);

    DLT_UNREGISTER_APP();
}

