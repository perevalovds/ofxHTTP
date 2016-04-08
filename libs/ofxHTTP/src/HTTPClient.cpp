// =============================================================================
//
// Copyright (c) 2013-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofx/HTTP/HTTPClient.h"
#include "ofx/HTTP/GetRequest.h"
#include "ofx/HTTP/JSONRequest.h"


namespace ofx {
namespace HTTP {


HTTPClient::HTTPClient()
{
    addRequestFilter(&_defaultClientSessionProvider);
    addRequestFilter(&_defaultProxyProcessor);
    addRequestFilter(&_defaultAuthenticationProcessor);
    addRequestFilter(&_defaultRedirectProcessor);
    addRequestFilter(&_defaultClientHeaders);

    // response processors
    addResponseFilter(&_defaultProxyProcessor);
    addResponseFilter(&_defaultAuthenticationProcessor);
    addResponseFilter(&_defaultRedirectProcessor);

    setResponseStreamFilter(&_responseStreamFilter);
}


HTTPClient::~HTTPClient()
{
}


std::unique_ptr<BufferedResponse> HTTPClient::get(const std::string& uri)
{
    HTTPClient client;
    GetRequest request(uri, Poco::Net::HTTPMessage::HTTP_1_1);
    return client.execute<BufferedResponse>(request);
}


std::unique_ptr<BufferedResponse> HTTPClient::post(const std::string& uri,
                                                   const ofJson& json)
{
    HTTPClient client;
    JSONRequest request(uri, json, Poco::Net::HTTPMessage::HTTP_1_1);
    return client.execute<BufferedResponse>(request);
}


std::unique_ptr<BufferedResponse> HTTPClient::form(const std::string& uri,
                                                   const std::multimap<std::string, std::string> formFields,
                                                   const std::vector<FormPart>& formParts)
{
    HTTPClient client;
    PostRequest request(uri, Poco::Net::HTTPMessage::HTTP_1_1);
    request.addFormFields(formFields);
    request.addFormParts(formParts);
    return client.execute<BufferedResponse>(request);
}


} } // namespace ofx::HTTP
