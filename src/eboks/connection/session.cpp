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

#include "eboks/connection/session.hpp"

#include <openssl/sha.h>

#include <sstream>
#include <string>

#include "eboks/application.hpp"
#include "eboks/connection/handler.hpp"

eBoks::Connection::Session::Session(eBoks::Connection::Handler *handler)
    : handler_(handler) {}


std::string
eBoks::Connection::Session::GenerateChallenge(const std::string &timestamp) {
  std::stringstream initial_challenge;

  initial_challenge << handler_->app()->user().activation_code() << ":";
  initial_challenge << handler_->app()->device_id() << ":";
  initial_challenge << handler_->app()->user().identity().type() << ":";
  initial_challenge << handler_->app()->user().identity().number() << ":";
  initial_challenge << handler_->app()->user().identity().nationality() << ":";
  initial_challenge << handler_->app()->user().passphrase() << ":";
  initial_challenge << timestamp;

  first = hashlib.sha256(challenge).hexdigest()
second = hashlib.sha256(first).hexdigest()
  return xml_body_stream.str();
}


void eBoks::Connection::Handler::Login() {
  request_builder_.At(uri_.Login().Build());
  request_builder_.WithLoginHeader(app_.device_id());
  request_builder_.As(kPUT);
  request_builder_.WithLoginBody(logon_, app_, &app_.user());
  request_builder_.Build();

  request_builder_.header()
}
