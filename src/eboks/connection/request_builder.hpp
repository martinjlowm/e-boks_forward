/*
 * Copyright (c) 2015-2016, Martin Jesper Low Madsen
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     *  Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *     *  Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef EBOKS_CONNECTION_REQUEST_BUILDER_HPP_
#define EBOKS_CONNECTION_REQUEST_BUILDER_HPP_

#include <curl/curl.h>

#include <string>

namespace eBoks {
namespace Connection {

class Handler;

class RequestBuilder {
 public:
  explicit RequestBuilder(CURL *curl);

  RequestBuilder& At(const std::string &uri);
  RequestBuilder& WithLoginHeader(const std::string &device_id);
  RequestBuilder& WithLoginBody(const std::string &uri);
  RequestBuilder& As(const std::string &method);

  void Build();
 private:
  Handler *handler_;
  CURL *curl_;
  struct curl_slist *header_;
  struct curl_slist *body_;
};

}  // namespace Connection
}  // namespace eBoks

#endif  // EBOKS_CONNECTION_REQUEST_BUILDER_HPP_
