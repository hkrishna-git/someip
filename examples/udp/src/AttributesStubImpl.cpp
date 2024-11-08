#include "AttributesStubImpl.hpp"

DLT_DECLARE_CONTEXT(service);

AttributesStubImpl::AttributesStubImpl() : m_counter(0)
{
    DLT_REGISTER_APP("SRVC", "Service Example");
    DLT_REGISTER_CONTEXT(service, "SCON", "Service context");
    DLT_LOG(service, DLT_LOG_INFO, DLT_STRING("SomeIP Service DLT Started!"));
}

AttributesStubImpl::~AttributesStubImpl()
{
    DLT_UNREGISTER_CONTEXT(service);
    DLT_UNREGISTER_APP();
}

void AttributesStubImpl::incCounter()
{
    m_counter++;
    DLT_LOG(service, DLT_LOG_INFO, DLT_STRING("Service Side Tx Attribute val : "), DLT_INT32(m_counter));
    setTestAttribute(static_cast<std::int32_t>(m_counter));
    std::cout << "New counter: " << m_counter << std::endl;
}

void AttributesStubImpl::dojob(const std::shared_ptr<CommonAPI::ClientId> _client, int16_t _input, dojobReply_t _reply) 
{
    DLT_LOG(service, DLT_LOG_INFO, DLT_STRING(__FUNCTION__), DLT_STRING(" : Rx'd : "), DLT_INT32(_input));
    std::cout << __FUNCTION__ << " : " << _input << std::endl;
    std::string msg("Done");
    msg += std::to_string(_input); 
    _reply(msg);
    DLT_LOG(service, DLT_LOG_INFO, DLT_STRING(__FUNCTION__), DLT_STRING(" : output : "), DLT_STRING(msg.c_str()));
}
