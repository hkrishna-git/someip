/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.2.14.v202310241605.
* Used org.franca.core 0.13.1.201807231814.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_COMMONAPI_EXAMPLES_Attributes_STUB_DEFAULT_HPP_
#define V1_COMMONAPI_EXAMPLES_Attributes_STUB_DEFAULT_HPP_


#include <CommonAPI/Export.hpp>

#include <v1/commonapi/examples/AttributesStub.hpp>
#include <cassert>
#include <sstream>

# if defined(_MSC_VER)
#  if _MSC_VER >= 1300
/*
 * Diamond inheritance is used for the CommonAPI::Proxy base class.
 * The Microsoft compiler put warning (C4250) using a desired c++ feature: "Delegating to a sister class"
 * A powerful technique that arises from using virtual inheritance is to delegate a method from a class in another class
 * by using a common abstract base class. This is also called cross delegation.
 */
#    pragma warning( disable : 4250 )
#  endif
# endif

namespace v1 {
namespace commonapi {
namespace examples {

/**
 * Provides a default implementation for AttributesStubRemoteEvent and
 * AttributesStub. Method callbacks have an empty implementation,
 * remote set calls on attributes will always change the value of the attribute
 * to the one received.
 *
 * Override this stub if you only want to provide a subset of the functionality
 * that would be defined for this service, and/or if you do not need any non-default
 * behaviour.
 */
class COMMONAPI_EXPORT_CLASS_EXPLICIT AttributesStubDefault
    : public virtual AttributesStub {
public:
    COMMONAPI_EXPORT AttributesStubDefault()
        : remoteEventHandler_(this),
          interfaceVersion_(Attributes::getInterfaceVersion()) {
    }

    COMMONAPI_EXPORT const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client) {
        (void)_client;
        return interfaceVersion_;
    }

    COMMONAPI_EXPORT AttributesStubRemoteEvent* initStubAdapter(const std::shared_ptr< AttributesStubAdapter> &_adapter) {
        CommonAPI::Stub<AttributesStubAdapter, AttributesStubRemoteEvent>::stubAdapter_ = _adapter;
        return &remoteEventHandler_;
    }

    COMMONAPI_EXPORT virtual const int32_t &getTestAttribute() {
        return testAttributeValue_;
    }
    COMMONAPI_EXPORT virtual const int32_t &getTestAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) {
        (void)_client;
        return getTestAttribute();
    }
    COMMONAPI_EXPORT virtual void setTestAttribute(int32_t _value) {
        const bool valueChanged = trySetTestAttribute(std::move(_value));
        if (valueChanged) {
            fireTestAttributeChanged(testAttributeValue_);
        }
    }
    COMMONAPI_EXPORT virtual void setTestAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _value) {
        (void)_client;
        setTestAttribute(_value);
    }
    COMMONAPI_EXPORT virtual void dojob(const std::shared_ptr<CommonAPI::ClientId> _client, int16_t _input, dojobReply_t _reply) {
        (void)_client;
        (void)_input;
        std::string msg = "";
        _reply(msg);
    }


protected:
    COMMONAPI_EXPORT virtual bool trySetTestAttribute(int32_t _value) {
        if (!validateTestAttributeRequestedValue(_value))
            return false;

        bool valueChanged;
        std::shared_ptr<AttributesStubAdapter> stubAdapter = CommonAPI::Stub<AttributesStubAdapter, AttributesStubRemoteEvent>::stubAdapter_.lock();
        if(stubAdapter) {
            stubAdapter->lockTestAttribute(true);
            valueChanged = (testAttributeValue_ != _value);
            testAttributeValue_ = std::move(_value);
            stubAdapter->lockTestAttribute(false);
        } else {
            valueChanged = (testAttributeValue_ != _value);
            testAttributeValue_ = std::move(_value);
        }

       return valueChanged;
    }
    COMMONAPI_EXPORT virtual bool validateTestAttributeRequestedValue(const int32_t &_value) {
        (void)_value;
        return true;
    }
    COMMONAPI_EXPORT virtual void onRemoteTestAttributeChanged() {
        // No operation in default
    }
    class COMMONAPI_EXPORT_CLASS_EXPLICIT RemoteEventHandler: public virtual AttributesStubRemoteEvent {
    public:
        COMMONAPI_EXPORT RemoteEventHandler(AttributesStubDefault *_defaultStub)
            : 
              defaultStub_(_defaultStub) {
        }

        COMMONAPI_EXPORT virtual void onRemoteTestAttributeChanged() {
            assert(defaultStub_ !=NULL);
            defaultStub_->onRemoteTestAttributeChanged();
        }

        COMMONAPI_EXPORT virtual bool onRemoteSetTestAttribute(int32_t _value) {
            assert(defaultStub_ !=NULL);
            return defaultStub_->trySetTestAttribute(std::move(_value));
        }

        COMMONAPI_EXPORT virtual bool onRemoteSetTestAttribute(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _value) {
            (void)_client;
            return onRemoteSetTestAttribute(_value);
        }

    private:
        AttributesStubDefault *defaultStub_;
    };
protected:
    AttributesStubDefault::RemoteEventHandler remoteEventHandler_;

private:

    int32_t testAttributeValue_ {};

    CommonAPI::Version interfaceVersion_;
};

} // namespace examples
} // namespace commonapi
} // namespace v1


// Compatibility
namespace v1_0 = v1;

#endif // V1_COMMONAPI_EXAMPLES_Attributes_STUB_DEFAULT
