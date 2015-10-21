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

#include "eboks/connection/request_builder.hpp"

#include <curl/curl.h>

#include <sstream>
#include <string>

#include "eboks/application.hpp"
#include "eboks/constants.hpp"
#include "eboks/logon.hpp"
#include "eboks/user.hpp"

eBoks::Connection::RequestBuilder::RequestBuilder(CURL *curl)
    : curl_(curl), header_(0), body_(0) {
}


eBoks::Connection::RequestBuilder&
eBoks::Connection::RequestBuilder::WithLoginHeader(
    const eBoks::TimeManager &time_manager, const std::string &device_id) {
  std::stringstream login;

  // Header name
  login << kEBoksAuthenticate << ": ";

  std::string timestamp = time_manager.Timestamp("%F %XZ");
  std::string challenge = handler_->session().GenerateChallenge(timestamp);


  // Header value
  login << "login ";
  login << "deviceid=\"" << device_id << "\",";
  login << "datetime=\"" << timestamp << "\",";
  login << "challenge=\"" << challenge << "\"";

  header_ = curl_slist_append(header_, login.str().c_str());
  // Fill out the remaining fields
  // FillHeader()
  return *this;
}

std::string eBoks::Connection::RequestBuilder::WithLoginBody(
    eBoks::Logon &logon, Application &app, User &user) {
  std::stringstream xml_body_stream;

  pugi::xml_document doc;

  logon.AddXML(doc);

  app.AddXML(doc.child("Logon"));
  user.AddXML(doc.child("Logon"));

  doc.print(xml_body_stream);

  body_ = xml_body_stream.str().c_str();

  return *this;
}

eBoks::Connection::RequestBuilder&
eBoks::Connection::RequestBuilder::As(const std::string &method) {
  curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, method);
  return *this;
}

std::string eBoks::Connection::RequestBuilder::Build() {
  std::stringstream xml_body_stream;

  pugi::xml_document doc;

  logon_.AddXML(doc);

  app_.AddXML(doc.child("Logon"));
  user_.AddXML(doc.child("Logon"));

  doc.print(xml_body_stream);

  return xml_body_stream.str();
}
