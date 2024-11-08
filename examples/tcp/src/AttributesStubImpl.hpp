#ifndef ATTRIBUTESSTUBIMPL_HPP_
#define ATTRIBUTESSTUBIMPL_HPP_

#include <dlt/dlt.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/examples/AttributesStubDefault.hpp>

class AttributesStubImpl : public v1_0::commonapi::examples::AttributesStubDefault
{
    public:
    AttributesStubImpl();
    virtual ~AttributesStubImpl();
    virtual void incCounter();
    void dojob(const std::shared_ptr<CommonAPI::ClientId> _client, int16_t _input, dojobReply_t _reply) override;

    private:
    int m_counter;
};

#endif  // ATTRIBUTESSTUBIMPL_HPP_
