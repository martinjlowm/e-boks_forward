/*
 * Copyright (c) 2015, Martin Jesper Low Madsen
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

#include "eboks/connection/handler.hpp"

#include <curl/curl.h>

#include <sstream>
#include <string>

#include "eboks/application.hpp"

eBoks::Connection::Handler::Handler(Application *app)
    : app_(app), curl_(curl_easy_init()), uri_(),
      session_(this), request_builder_(curl_), response_parser_() {
  curl_easy_setopt(curl_, CURLOPT_READFUNCTION, response_parser_.Parse);
}

eBoks::Application* eBoks::Connection::Handler::app() const { return app_; }
eBoks::Connection::Session
eBoks::Connection::Handler::session() const { return session_; }

void eBoks::Connection::Handler::Login() {
  request_builder_.At(uri_.Login().Build());
  request_builder_.WithLoginHeader(app_->time_manager(), app_->device_id());
  request_builder_.As(kPUT);
  request_builder_.WithLoginBody(logon_, app_, &app_.user());
  request_builder_.Build();

  request_builder_.header();
  request_builder_.body();

  // connect
}
