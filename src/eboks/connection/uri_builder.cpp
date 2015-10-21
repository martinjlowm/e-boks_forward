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

#include "eboks/connection/uri_builder.hpp"

#include <sstream>
#include <string>


eBoks::Connection::URIBuilder::URIBuilder() {
  std::stringstream uri_string_stream;

  // kProtocolScheme://kBaseURI/kServiceType/kUnknownIdentifier/kXMLService/kLocaleTag/
  uri_string_stream << kProtocolScheme;
  uri_string_stream << "://";
  uri_string_stream << kBaseURI;
  uri_string_stream << kURISplitter;

  uri_string_stream << kServiceType;
  uri_string_stream << kURISplitter;

  uri_string_stream << kUnknownIdentifier;
  uri_string_stream << kURISplitter;

  uri_string_stream << kXMLService;
  uri_string_stream << kURISplitter;

  uri_string_stream << kLocaleTag;

  uri_ = uri_string_stream.str();
}

void eBoks::Connection::URIBuilder::ServiceURIStream::Append(const std::string &string) {
  *this << kURISplitter << string;
}

eBoks::Connection::URIBuilder& eBoks::Connection::URIBuilder::Login() {
  service_uri_.Append(kSession);

  return *this;
}

std::string eBoks::Connection::URIBuilder::Build() {
  std::string final_uri(uri_ + service_uri_.str());

  // Reset the service URI
  service_uri_.str("");

  return final_uri;
}
